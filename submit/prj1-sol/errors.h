#ifndef ERRORS_H_
#define ERRORS_H_

/** Print error message on stderr as per printf() style format string
 *  fmt and remaining arguments.
 */
void error(const char *fmt, ...);

/** Print error message on stderr as per printf() style format string
 *  fmt and remaining arguments.  Terminate program with error.
 */
_Noreturn void fatal(const char *fmt, ...);

#endif //ifndef ERRORS_H_
