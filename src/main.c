#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "calc.h"
#include "calc_opts_parse.h"

int main(const int argc, char* argv[])
{
  int res      = 0;
  int ret_code = EXIT_SUCCESS;

  if (argc < 2)
  {
    /* 
     * Not enough args. 
     * Display help message and exit with failure. 
     */
    display_help_msg();
    exit(EXIT_FAILURE);
  }

  /* Save up expression string. */
  char* expr = (char*) calloc(strlen(argv[1]) + 1U, sizeof(char));
  assert(expr);
  strcpy(expr, argv[1]);

  /* Parse cmnd line arguments. */
  calc_opts_t calc_opts = { 0 };
  res                   = calc_opts_parse(argc, argv, &calc_opts);
  if (res != 0)
  {
    ret_code = EXIT_FAILURE;
    goto exit;
  }

  printf("Evaluating expression: %s \n", expr);

  float eval_res = 0;
  res            = calc_eval_expr(expr, &calc_opts, &eval_res);
  if (res != 0)
  {
    ret_code = EXIT_FAILURE;
    goto exit;
  }

  printf("Evaluation result is %f \n", eval_res);

exit:

  /* Free allocated memory. */
  calc_opts_dtor(&calc_opts);
  free((void*) expr);

  /* Return with success. Yay! :) */
  return ret_code;
}
