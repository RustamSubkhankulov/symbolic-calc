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
    calc_opts_dtor(&calc_opts);
    return EXIT_FAILURE;
  }

  calc_opts_dtor(&calc_opts);
  return EXIT_SUCCESS;
}