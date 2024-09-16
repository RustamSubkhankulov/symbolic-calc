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
  { NULL, 0, NULL, 0 }
};

/**
 * @brief Iterate through cmnd line args and enumerate all supported
 *        option's occurences. Sets 'calc_opts->vars_num' to this count.
 * @return 0 on success, -1 otherwise.
 */
static int calc_opts_count(const int argc, char* argv[], calc_opts_t* calc_opts)
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

    /* Only one long options is supported. */
    if (option_index != 0)
    {
      fprintf(stderr, "getopt() returned unexpected long option index (%d) \n", option_index);
      return -1;
    }

    calc_opts->vars_num += 1;
  }

  return 0;
}

/**
 * @brief Allocate memory for the variable descriptors. Pointer to the
 *        allocated memory is saved in 'calc_opts->vars'.
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
 * @brief Checks whether string is convertible into the interger value.
 * @return true if string is convertible, false otherwise.
 */
static bool is_number(const char* str)
{
  while (*str != '\0')
  {
    if (!isdigit(*str++))
    {
      return false;
    }
  }

  return true;
}

/**
 * @brief Parse option and fill in fields in the variable descriptor.
 * @return 0 on success, -1 otherwise.
 */
static int calc_opts_parse_var_descr(var_descr_t* var)
{
  if (optarg == NULL)
  {
    fprintf(stderr, "Invalid option: \'var\' does not have argument. \n");
    return -1;
  }

  printf("optarg: |%s| \n", optarg);

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

  if (is_number(var_value) == true)
  {
    /* Convert to integer value is possible. */
    var->value.integer_value = atoi(var_value);
  }
  else
  {
    /*
     * Variable value's string is not convertible to integer.
     * Assume that variable is defined with predefined named constant.
     */
    var->value.constant_name = var_value;
  }

  return 0;
}

/**
 * @brief Perform parsing process of the calc's options.
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

    /* Only one long options is supported. */
    if (option_index != 0)
    {
      fprintf(stderr, "getopt() returned unexpected long option index (%d) \n", option_index);
      return -1;
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

int calc_opts_parse(const int argc, char* argv[], calc_opts_t* calc_opts)
{
  assert(calc_opts != NULL);
  assert(argv != NULL);
  assert(argc >= 0);

  /* Count number of supported options. */
  int res = calc_opts_count(argc, argv, calc_opts);
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

void calc_opts_dtor(calc_opts_t* calc_opts)
{
  assert(calc_opts != NULL);
  free(calc_opts->vars);
}
