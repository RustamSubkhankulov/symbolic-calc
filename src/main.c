#include <stdlib.h>

#include "calc_opts_parse.h"

int main(const int argc, char* argv[])
{
  int res = 0;

  /* Parse cmnd line arguments. */
  calc_opts_t calc_opts = { 0 };
  res                   = calc_opts_parse(argc, argv, &calc_opts);
  if (res != 0)
  {
    /*
     * Failed to parse cmnd line options.
     * Free allocated memory and return with the failure.
     */
    calc_opts_dtor(&calc_opts);
    return EXIT_FAILURE;
  }

  /* Free memory allocated for the variable descriptors. */
  calc_opts_dtor(&calc_opts);

  /* Return with success. Yay! :) */
  return EXIT_SUCCESS;
}
