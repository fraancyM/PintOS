/* Tests the exit system call. */

#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  msg("Executing 'exit_test' with exit code 20...");
  exit (20);
  fail ("should have called exit(20)");
}
