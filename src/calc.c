#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "calc.h"
#include "lexer.h"

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

int calc_eval_expr(const char* expr, const calc_opts_t* calc_opts, float* result)
{
  assert(expr != NULL);
  assert(calc_opts != NULL);
  assert(result != NULL);

  if (is_empty_str(expr) == true)
  {
    fprintf(stderr, "calc_eval_expr(): expression string is empty. \n");
    return -1;
  }

  int res = lexer_tokenize(expr);
  if (res != 0)
  {
    return -1;
  }

  return 0;
}
