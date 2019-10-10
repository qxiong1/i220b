#include <stdio.h>
#include <stdlib.h>

int
main(int argc, const char *argv[])
{
  if (argc < 2) {
    fprintf(stderr, "usage: %s NAME...\n", argv[0]);
    exit(1);
  }
  for (int i = 1; i < argc; i++) {
    printf("hello %s\n", argv[i]);
  }
}
