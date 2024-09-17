#include "lexer.h"

/* Buffer handle. */
typedef struct yy_buffer_state* YY_BUFFER_STATE;

/* Main lexer method. */
extern int yylex(void);

/* Sets string as input buffer for Flex. */
extern YY_BUFFER_STATE yy_scan_string(char* str);

/* Reclaim the storage associated with a buffer. */
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

int lexer_tokenize(const char* str)
{
  /*
   * FIXME: accroding to the specification, this function takes
   * 'const char*' parameter.
   */
  YY_BUFFER_STATE buffer_state = yy_scan_string((char*) str);
  yylex();
  yy_delete_buffer(buffer_state);

  return 0;
}
