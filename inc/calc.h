#ifndef CALC_H
#define CALC_H

#include <stddef.h>

#include "variables.h"

/**
 * @brief Calc's options sturcture.
 *
 * @var size_t vars_num Number of variables defined.
 * @var var_t* vars     Variable descriptors array.
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
 *         expression may contain variales. Each variable used must
 *         be defined and its descriptor is found in 'calc_opts'
 *
 * @param[in]  expr      String representation of the expression
 *                       to be evaluated.
 * @param[in]  calc_opts Calc's options (variables descriptors).
 * @param[out] eval_res  Result of the expression evaluation.
 *
 * @return 0 on success, -1 otherwise.
 */
int calc_eval_expr(const char* expr, const calc_opts_t* calc_opts, float* eval_res);

#endif /* CALC_H */
