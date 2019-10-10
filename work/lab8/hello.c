#include <stdio.h>
#include <stdlib.h>

int
main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "usage: %s NAME\n", argv[0]);
    exit(1);
  }
  printf("hello %s\n", argv[1]);
}
