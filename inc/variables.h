#ifndef VARIABLES_H
#define VARIABLES_H

#include <stdbool.h>

/**
 * @brief To make the development process easier, we limit
 *        the allowed length of a variable name from above.
 */
#define VAR_NAME_MAX_LEN 16U

/**
 * @brief To make the development process easier, we limit
 *        the allowed length of a constant name from above.
 *        TODO: Move this macrodefinition to appropiate header.
 */
#define CONSTANT_NAME_MAX_LEN 16U

/**
 * @brief Variable's value structure.
 *
 * @var bool   is_named_constant Flag, indicating how the variable is defined.
 *                               Clear flag indicates that its value is defined
 *                               with integer value. Otherwise variable's value
 *                               is defined as named constant, predefined
 *                               in the grammar.
 * @var int    integer_value     Integer value of the variable.
 * @var char[] constant_name     Name of the predefined constant.
 */
typedef union
{
  bool is_named_constant;

  union
  {
    int integer_value;
    const char* constant_name;
  };
} var_value_t;

/**
 * @brief Variable descriptor. Contains its name and value.
 *        Used for substitution of variable's name with its
 *        value on the tree processing stage.
 *
 * @var char[]      name  Variable's name.
 * @var var_value_t value Variable's value.
 */
typedef struct
{
  const char* name;
  var_value_t value;
} var_descr_t;

#endif /* VARIABLES_H */
