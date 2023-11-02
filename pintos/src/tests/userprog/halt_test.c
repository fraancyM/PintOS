/* Tests the halt system call. */

#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
	msg("Sto eseguendo la chiamata a sys_halt...");

	//Chiamata a sys halt
	halt();

	//Questo codice non dovrebbe essere mai eseguito se funziona correttamente la sys_halt
	msg("Dopo la chiamata a sys_halt\n");
	fail ("Errore halt");

	return 0;
}

