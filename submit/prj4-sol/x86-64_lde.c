#include "x86-64_lde.h"

#include "beaengine/BeaEngine.h"

#include <string.h>

/** Length decoder for x86_64 instructions. Uses BeaEngine disassembler
 *  library.
 *
 *  Dependencies:
 *
 *  Preprocessing: When compiling, requires include files installed
 *  in course include directory.  Hence course include directory must
 *  be specified via -I option usually specified using make's CPPFLAGS.
 *
 *  Linking: Requires access to the BeaEngine library libbeaengine
 *  installed in the course lib directory.  Hence that directory must
 *  be added to the set of directories searched for libraries using the
 *  -L compiler option; the library must be specified using -l beaengine.
 *  Usually, these options can be specified using make's LDFLAGS
 *  LDLIBS options respectively.
 *
 *  Runtime: The BeaEngine library must be accessed at load-time.  Hence
 *  the LD_LIBRARY_PATH environmental variable must contain the course
 *  library directory when any program linked with this code is run.
 */

/** Return length of x86-64 instruction pointed to by p.  Returns < 0
 *  on error.
 */
int
get_op_length(void *p)
{
  DISASM bea;
  (void) memset (&bea, 0, sizeof(DISASM));
  bea.Archi = 64;
  bea.EIP = (UIntPtr)p;
  int n = Disasm(&bea);
  return (n <= 0) ? -1 : n;
}
