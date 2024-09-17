#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "calc.h"
#include "calc_opts_parse.h"

int main(const int argc, char* argv[])
{
  int res      = 0;
  int ret_code = EXIT_SUCCESS;

  const char* expr = strdup(argv[1]);

  /* Parse cmnd line arguments. */
  calc_opts_t calc_opts = { 0 };
  res                   = calc_opts_parse(argc, argv, &calc_opts);
  if (res != 0)
  {
    ret_code = EXIT_FAILURE;
    goto exit;
  }

  printf("Evaluating expression: %s \n", expr);

  float evaluation_result = 0.f;
  res                     = calc_eval_expr(expr, &calc_opts, &evaluation_result);
  if (res != 0)
  {
    ret_code = EXIT_FAILURE;
    goto exit;
  }

  printf("Evaluation result is %f \n", evaluation_result);

exit:

  /* Free allocated memory. */
  calc_opts_dtor(&calc_opts);
  free((void*) expr);

  /* Return with success. Yay! :) */
  return ret_code;
}
