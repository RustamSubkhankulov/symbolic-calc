#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "calc.h"

/* Buffer handle. */
typedef struct yy_buffer_state* YY_BUFFER_STATE;

/* Sets string as input buffer for Flex. */
extern YY_BUFFER_STATE yy_scan_string(char* str);

/* Reclaim the storage associated with a buffer. */
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

/* Main parser method. */
extern int yyparse(void);

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

  /* Call YACC main parser's method. */
  yyparse();

  /* Reclaim allocated resources. */
  yy_delete_buffer(buffer_state);

  return 0;
}
