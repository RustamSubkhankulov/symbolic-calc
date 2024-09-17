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
 */
float std_func_evaluate(std_func_t std_func, float arg);

/**
 *  @brief Get standard constant value.
 */
float std_const_value(std_const_t std_const);

/**
 *  @brief Get standard constant value from
 *         its name's string representation.
 */
float std_const_value_from_str(const char* constant_name);

#endif /* STANDARD_H */
