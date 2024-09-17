#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "standard.h"

#define _USE_MATH_DEFINES

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

float std_const_value(std_const_t std_const)
{
  switch (std_const)
  {
    case PI:
      return (float) M_PI;
    case EXP:
      return (float) M_E;
    default: {
      fprintf(stderr, "Unexpected standard constant. \n");
      exit(EXIT_FAILURE);
    }
  }

  /* Unreachable. */
  return 0.f;
}

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

float std_const_value_from_str(const char* constant_name)
{
  assert(constant_name != NULL);
  return std_const_value(std_const_name_to_code(constant_name));
}
