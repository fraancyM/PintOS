/* Tests the exit system call. */

#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  msg("Sto eseguendo la chiamata a kill()...");
  kill ();
  fail ("should have called kill()");
}
