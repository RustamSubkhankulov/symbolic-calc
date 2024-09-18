#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "standard.h"

#define _USE_MATH_DEFINES

/**
 * @brief Evaluate standar function 'std_func'
 *        with given argument 'arg'.
 *
 * @detail If 'std_func' does not correspond to
 *         one of the predefined standard functions,
 *         exits with failure.
 *
 * @param[in] std_func Standard function's code.
 * @param[in] arg      Argument to the standard function.
 *
 * @return Result of the expr: standard_function(arg).
 */
float std_func_evaluate(std_func_t std_func, float arg)
{
  switch (std_func)
  {
    case SIN:
      return (float) sin(arg);
    case COS:
      return (float) cos(arg);
    case TG:
      return (float) tan(arg);
    case CTG:
      return (float) (1. / tan(arg));
    case SQRT:
      return (float) sqrt(arg);
    default: {
      fprintf(stderr, "Unexpected standard function. \n");
      exit(EXIT_FAILURE);
    }
  }

  /* Unreachable. */
  return 0.f;
}

/**
 *  @brief Get standard constant value.
 *
 * @detail If 'std_const' does not correspond to
 *         one of the predefined standard constants,
 *         exits with failure.
 *
 * @param[in] std_const Standard constant's code.
 *
 * @return Value of the standard constant.
 */
float std_const_value(std_const_t std_const)
{
  switch (std_const)
  {
    case PI:
      return 3.141593f;
    case EXP:
      return 2.718282f;
    default: {
      fprintf(stderr, "Unexpected standard constant. \n");
      exit(EXIT_FAILURE);
    }
  }

  /* Unreachable. */
  return 0.f;
}

/**
 * @brief Convert standard constant's name to
 *        corresponding code.
 *
 * @detail If 'constant_name' does not correspond to
 *         one of the predefined standard constants,
 *         exits with failure.
 *
 * @param[in] constant_name Standard constant's name.
 *
 * @return Standard constant's code.
 */
static std_const_t std_const_name_to_code(const char* constant_name)
{
  if (!strcmp(constant_name, "PI"))
  {
    return PI;
  }

  if (!strcmp(constant_name, "EXP"))
  {
    return EXP;
  }

  fprintf(stderr, "Unexpected standard constant: %s. \n", constant_name);
  exit(EXIT_FAILURE);

  /* Unreachable. */
  return 0;
}

/**
 *  @brief Get standard constant value from
 *         its name's string representation.
 *
 * @detail If 'constant_name' does not correspond to
 *         one of the predefined standard constants,
 *         exits with failure.
 *
 * @param[in] constant_name Standard constant's name.
 *
 * @return Value of the standard constant.
 */
float std_const_value_from_str(const char* constant_name)
{
  assert(constant_name != NULL);
  return std_const_value(std_const_name_to_code(constant_name));
}
