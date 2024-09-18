#ifndef CALC_H
#define CALC_H

#include <stddef.h>

#include "variables.h"

/**
 * @brief Calc's options structure.
 *
 * @detail Contains options for calc. THe only available option
 *         type now is variable definition. Therefore structure
 *         fields are total number of variables defined and their
 *         descriptors.
 *
 * @var size_t vars_num Total number of variables defined.
 * @var var_t* vars     Variable's descriptor array.
 */
typedef struct
{
  size_t vars_num;
  var_descr_t* vars;
} calc_opts_t;

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
int calc_eval_expr(const char* expr, const calc_opts_t* calc_opts, float* eval_res);

#endif /* CALC_H */
