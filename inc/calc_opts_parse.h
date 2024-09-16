#ifndef CALC_OPTS_PARSE_H
#define CALC_OPTS_PARSE_H

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
int calc_opts_parse(const int argc, char* argv[], calc_opts_t* calc_opts);

/**
 * @brief Destructor for the calc's options structure.
 *        Frees allocated memory.
 */
void calc_opts_dtor(calc_opts_t* calc_opts);

#endif /* CALC_OPTS_PARSE_H */
