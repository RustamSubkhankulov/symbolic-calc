#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "calc_opts_parse.h"

/**
 * @brief Long options used by the calc.
 */
static const struct option sLong_options[] = {
  /* Example: '--var x=PI --var y=2' */
  { "var", required_argument, NULL, 0 },
  { "help", no_argument, NULL, 0 },
  { NULL, 0, NULL, 0 }
};

/**
 * @brief Iterate through cmnd line args and enumerate all variable definitions.
 *        Sets 'calc_opts->vars_num' to this count.
 *
 * @return 0 on success, -1 otherwise.
 */
static int calc_opts_count_vars(const int argc, char* argv[], calc_opts_t* calc_opts)
{
  optind           = 0;
  int option_index = 0;

  calc_opts->vars_num = 0U;

  while (true)
  {
    /* Iterate over cmnd line args. */
    int c = getopt_long(argc, argv, "", sLong_options, &option_index);

    /* No more options to parse. */
    if (c == -1)
    {
      break;
    }

    /* We support long options only. */
    if (c != 0)
    {
      fprintf(stderr, "getopt() returned unexpected code (%d) \n", c);
      return -1;
    }

    /* Count only '--var' options. */
    if (option_index == 0)
    {
      calc_opts->vars_num += 1;
    }
  }

  return 0;
}

/**
 * @brief Allocate memory for the variable descriptors. Pointer to the
 *        allocated memory is saved in 'calc_opts->vars'.
 *
 * @return 0 on success, -1 otherwise.
 */
static int calc_opts_alloc(calc_opts_t* calc_opts)
{
  calc_opts->vars = (var_descr_t*) calloc(calc_opts->vars_num, sizeof(var_descr_t));
  if (calc_opts->vars == NULL)
  {
    return -1;
  }

  return 0;
}

/**
 * @brief Checks whether string is convertible into the float value.
 *
 * @return true if string is convertible, false otherwise.
 */
static bool is_numflt_str(const char* str)
{
  while (*str != '\0')
  {
    if (!isdigit(*str) && *str != '.')
    {
      return false;
    }

    ++str;
  }

  return true;
}

/**
 * @brief Parse option and fill in fields in the variable descriptor.
 *
 * @return 0 on success, -1 otherwise.
 */
static int calc_opts_parse_var_descr(var_descr_t* var)
{
  if (optarg == NULL)
  {
    fprintf(stderr, "Invalid option: \'var\' does not have argument. \n");
    return -1;
  }

  /* Find separator. */
  char* delim = strchr(optarg, '=');
  if (delim == NULL)
  {
    fprintf(stderr, "Invalid \'var\' option argument. Missing separator '='.\n");
    return -1;
  }

  /* Replace separator with '\0' and initialize var's name. */
  *delim    = '\0';
  var->name = optarg;

  /* Variables value is the rest of the string after delim symbol '='. */
  const char* var_value = delim + 1;

  if (is_numflt_str(var_value) == true)
  {
    /* Convertion to float value is possible. */
    var->value.is_named_constant = false;
    var->value.float_value       = atof(var_value);
  }
  else
  {
    /*
     * Variable value's string is not convertible to float value.
     * Assume that variable is defined with predefined named constant.
     */
    var->value.is_named_constant = true;
    var->value.constant_name     = var_value;
  }

  return 0;
}

/**
 * @brief Displays help message. Invoked by using '--help' option.
 */
void display_help_msg(void)
{
  printf("Symbolic expression evaluator. \n");
  printf("Usage: calc \"expression\" [--var variable_name=variable_value]* [--help]\n");

  printf("Flags: \n");
  printf("\t--var:  define variable. Examples: '--var x=PI', '--var y=2'.\n");
  printf("\t--help: display this message. \n");
}

/**
 * @brief Perform parsing process of the calc's options.
 *
 * @return 0 on success, -1 otherwise.
 */
static int calc_opts_do_parse(const int argc, char* argv[], calc_opts_t* calc_opts)
{
  optind           = 0;
  int option_index = 0;

  size_t option_ct = 0U;

  while (true)
  {
    /* Iterate over cmnd line args. */
    int c = getopt_long(argc, argv, "", sLong_options, &option_index);

    /* No more options to parse. */
    if (c == -1)
    {
      break;
    }

    /* We support long options only. */
    if (c != 0)
    {
      fprintf(stderr, "getopt() returned unexpected code (%d) \n", c);
      return -1;
    }

    /* Display help message if '--help' options is present. */
    if (option_index == 1)
    {
      display_help_msg();
      continue;
    }

    /* Initialize variable descriptor for the found option. */
    int res = calc_opts_parse_var_descr(&calc_opts->vars[option_ct++]);
    if (res != 0)
    {
      return -1;
    }
  }

  return 0;
}

/**
 * @brief  Parses cmnd line arguments via 'argc' and 'argv' to get
 *         options for calc.
 *
 * @detail Variable decsriptos returned in 'calc_opts->vars'.
 *         Remember to call calc_opts_dtor() after finishing
 *         work with calc's options structure.
 *
 * @param[in]  argc      Number of cmnd line arguments.
 * @param[in]  argv      Array of cmnd line arguments.
 * @param[out] calc_opts Resulting calc's options.
 *
 * @return 0 on success, -1 otherwise.
 *
 * @see calc_opts_dtor
 */
int calc_opts_parse(const int argc, char* argv[], calc_opts_t* calc_opts)
{
  assert(calc_opts != NULL);
  assert(argv != NULL);
  assert(argc >= 0);

  /* Count number of supported options. */
  int res = calc_opts_count_vars(argc, argv, calc_opts);
  if (res != 0)
  {
    return -1;
  }

  /* No options recognized in cmnd line arguments. */
  if (calc_opts->vars_num == 0U)
  {
    return 0;
  }

  /* Allocate memory for variable's descriptors. */
  res = calc_opts_alloc(calc_opts);
  if (res != 0)
  {
    return -1;
  }

  /* Perform option's parsing, filling variable's descriptors. */
  res = calc_opts_do_parse(argc, argv, calc_opts);
  if (res != 0)
  {
    return -1;
  }

  return 0;
}

/**
 * @brief Destructor for the calc's options structure.
 *        Frees allocated memory.
 */
void calc_opts_dtor(calc_opts_t* calc_opts)
{
  assert(calc_opts != NULL);
  free(calc_opts->vars);
}
