#ifndef STANDARD_H
#define STANDARD_H

/**
 * @brief Enumerated type, describing supported standard functions.
 */
typedef enum
{
  SIN, /* Sine. */
  COS, /* Cosine. */
  TG, /* Cotangent. */
  CTG, /* Tangent. */
  SQRT, /* Square root. */
} std_func_t;

/**
 * @brief Enumerated type, describing supported standard constants.
 */
typedef enum
{
  PI, /* Pi. */
  EXP, /* Euler's number. */
} std_const_t;

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
float std_func_evaluate(std_func_t std_func, float arg);

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
float std_const_value(std_const_t std_const);

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
float std_const_value_from_str(const char* constant_name);

#endif /* STANDARD_H */
