#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "calc.h"
#include "standard.h"
#include "variables.h"

/* Buffer handle for providing YACC & Lex input data. */
typedef struct yy_buffer_state* YY_BUFFER_STATE;

/* Sets string as input buffer for YACC & Lex. */
extern YY_BUFFER_STATE yy_scan_string(char* str);

/* Reclaim the storage associated with a buffer. */
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

/* Main YACC parser method. */
extern int yyparse(float* eval_res);

/**
 * @brief Current experession string.
 */
static const char* sCur_expr_str;

/**
 * @brief Current symbol position in lexer.
 *        Maintained to diagnose errors in
 *        readable format.
 * */
int gCur_pos;

/*
 * Calc's options for the current expression evaluation.
 * This
 */

/**
 * @brief Calc's options for the current expression
 *        evaluation.
 *
 * @detail Set as static variable inside this translation unit
 *         to provide access to variable's definitions from the
 *         inside of yyparse() (from yacc/yacc.y) to substitute
 *         variable with its value in the evaluation process.
 */
static const calc_opts_t* sCalc_opts;

/**
 * @brief Checks if the string contains non-space characters.
 */
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

/**
 * @brief Calc's helper method for the parser.
 *
 * @detail Provides means to get variable's value during
 *         expression evaluation from the inside of yyparse()
 *         (from rules in yacc/yacc.y). Meant to be used by the
 *         parser only and only during parsing process
 *         (in yyparse() called from the main evaluation
 *         method - calc_eval_expr()). Otherwise behaviour
 *         of this function may be invalid.
 *
 *         If variable is undefined, exits with failure.
 *
 * @param[in] var_name Variable's name.
 *
 * @return Variable's value.
 */
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
    return sCalc_opts->vars[idx].value.float_value;
  }

  fprintf(stderr, "Undefined variable \'var_name\'. \n");
  exit(EXIT_FAILURE);

  /* Unreachable. */
  return 0.f;
}

/**
 * @brief Checks variables for for uniqueness.
 *
 * @param[in] calc_opts Calc's options containing
 *                      variable's descriptors.
 *
 * @return true if all of the variables defined have unique names,
 *         false otherwise.
 */
static bool check_vars_unique(const calc_opts_t* calc_opts)
{
  for (size_t idx = 0U; idx < calc_opts->vars_num; ++idx)
  {
    for (size_t j = 0U; j < calc_opts->vars_num; ++j)
    {
      if (j != idx && !strcmp(calc_opts->vars[idx].name, calc_opts->vars[j].name))
      {
        fprintf(stderr, "calc_eval_expr(): variable %s redefined. \n", calc_opts->vars[idx].name);
        return false;
      }
    }
  }

  return true;
}

void underline_print_error(int cur_pos)
{
  fprintf(stderr, "%s\n", sCur_expr_str);
  for (int sym_ct = 0; sym_ct < cur_pos; ++sym_ct)
  {
    fprintf(stderr, " ");
  }
  fprintf(stderr, "^\n");
}

/**
 * @brief Evaluate expression given in 'expr'.
 *
 * @detail Parses expression, represented as string parameter 'expr'.
 *         Besides integer and float numbers, operators and brackets
 *         expression may contain variales. Each variable used in
 *         expression must be defined and in 'calc_opts'. Variables
 *         passed as options are checked for uniqueness.
 *         calc_eval_expr() will return with failure if any two
 *         variables have the same name.
 *
 * @param[in]  expr      String representation of the expression
 *                       to be evaluated.
 * @param[in]  calc_opts Calc's options (variable's descriptors).
 * @param[out] eval_res  Result of the expression evaluation.
 *
 * @return 0 on success, -1 otherwise.
 */
int calc_eval_expr(const char* expr, const calc_opts_t* calc_opts, float* eval_res)
{
  assert(expr != NULL);
  assert(calc_opts != NULL);
  assert(eval_res != NULL);

  /* Validate variables definitions. */
  if (check_vars_unique(calc_opts) != true)
  {
    return -1;
  }

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

  /* Set current expr string and processed symbol position to 0. */
  sCur_expr_str = expr;
  gCur_pos      = 0;

  /* Call YACC main parser's method. */
  yyparse(eval_res);

  if (gCur_pos != (int) strlen(expr))
  {
    fprintf(stderr, "calc_eval_expr(): invalid expression. \n");
    underline_print_error(gCur_pos - 1U);
  }

  /* Reclaim allocated resources. */
  yy_delete_buffer(buffer_state);

  return 0;
}
