#ifndef _X86_64_LDE_H
#define _X86_64_LDE_H

/** Length decoder for x86-64 instructions. Requires linking with
 *  libbeaengine.  See implementation file for details.
 */

//.1
/** Return length of x86-64 instruction pointed to by p.  Returns < 0
 *  on error.
 */
int get_op_length(void *p);
//.2

#endif //ifndef _X86_64_LDE_H
