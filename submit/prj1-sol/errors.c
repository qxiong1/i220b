#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/** Print error message on stderr as per printf() style format string
 *  fmt and remaining arguments.
 */
void
error(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  fprintf(stderr, "\n");
}

/** Print error message on stderr as per printf() style format string
 *  fmt and remaining arguments.  Terminate program with error.
 */
_Noreturn void
fatal(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  fprintf(stderr, "\n");
  exit(1);
}
