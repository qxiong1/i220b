#include "bits-to-ints.h"
#include "errors.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


static void
do_file_bits(FILE *in, const char *inName, int nBits, FILE *out)
{
  bool isDone = false;
  do {
    BitsValue result = bits_to_ints(in, inName, nBits, &isDone);
    if (!isDone) {
      fprintf(out, "%0*" BITS_VALUE_FORMAT "x\n", nBits/4, result);
    }
  } while (!isDone);
}

static int count_ones(unsigned n) {
  int count = 0;
  while (n > 0) { n &= n - 1; count++; }
  return count;
}

int
main(int argc, const char *argv[])
{
  if (argc < 2) {
    fatal("usage: %s N_BITS [FILE...]", argv[0]);
  }
  char *p;
  int nBits = strtol(argv[1], &p, 10);
  if (*p != '\0') {
    fatal("invalid N_BITS '%s'", argv[1]);
  }
  else if (nBits < 8 || nBits > sizeof(BitsValue)*CHAR_BIT ||
           count_ones(nBits) != 1) {
    fatal("N_BITS must be a power of 2 between 8 and %d",
           sizeof(BitsValue)*CHAR_BIT);
  }
  if (argc == 2) {
    do_file_bits(stdin, "<stdin>", nBits, stdout);
  }
  else {
    for (int i = 2; i < argc; i++) {
      const char *inName = argv[i];
      FILE *inFile = fopen(inName, "r");
      if (inFile == NULL) {
        error("cannot read file %s", inName);
      }
      do_file_bits(inFile, inName, nBits, stdout);
    }
  }
  return 0;
}
