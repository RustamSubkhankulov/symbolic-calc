#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "calc.h"
#include "standard.h"
#include "variables.h"

/* Buffer handle. */
typedef struct yy_buffer_state* YY_BUFFER_STATE;

/* Sets string as input buffer for Flex. */
extern YY_BUFFER_STATE yy_scan_string(char* str);

/* Reclaim the storage associated with a buffer. */
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

/* Main parser method. */
extern int yyparse(float* eval_res);

/* Calc's options for the current expression evaluation. */
static const calc_opts_t* sCalc_opts;

static bool is_empty_str(const char* str)
{
  while (*str != '\0')
  {
    if (!isspace(*str++))
    {
      return false;
    }
  }

  return true;
}

float calc_get_var_value(const char* var_name)
{
  assert(var_name);

  for (size_t idx = 0U; idx < sCalc_opts->vars_num; ++idx)
  {
    /* Skip other variables. */
    if (strcmp(var_name, sCalc_opts->vars[idx].name))
    {
      continue;
    }

    if (sCalc_opts->vars[idx].value.is_named_constant)
    {
      /* Convert name of the standard constant to its value. */
      return std_const_value_from_str(sCalc_opts->vars[idx].value.constant_name);
    }

    /* Return variable's value. */
    return sCalc_opts->vars[idx].value.integer_value;
  }

  fprintf(stderr, "Undefined variable \'var_name\'. \n");
  exit(EXIT_FAILURE);

  /* Unreachable. */
  return 0.f;
}

int calc_eval_expr(const char* expr, const calc_opts_t* calc_opts, float* eval_res)
{
  assert(expr != NULL);
  assert(calc_opts != NULL);
  assert(eval_res != NULL);

  /* Check for the empty string. */
  if (is_empty_str(expr) == true)
  {
    fprintf(stderr, "calc_eval_expr(): expression string is empty. \n");
    return -1;
  }

  /*
   * Set 'expr' string as input stream for lexer.
   * FIXME: accroding to the specification, this function takes
   * 'const char*' parameter.
   */
  YY_BUFFER_STATE buffer_state = yy_scan_string((char*) expr);

  /* Set options for the current expression evaluation (for variable's values). */
  sCalc_opts = calc_opts;

  /* Call YACC main parser's method. */
  yyparse(eval_res);

  /* Reclaim allocated resources. */
  yy_delete_buffer(buffer_state);

  return 0;
}
