// Hauptteil 
// Diese Datei Beinhaltet die Funktion main() und damit den Startpunkt der Ausführung

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// nötige Defintionen einbinden
#include <stdio.h>
// Definitionen des Betriebssystems einbinden
#include "global.h"

#include "ProcessA.h"
#include "ProcessB.h"
#include "ProcessTest.h"

int main(int argc, char* argv[])
{
	printf("\n"); 
	// initialise the OS
	initOS(); 
	printf("ENV: OS initialised, starting demo\n");
	printf("ENV: Start process A, it shall register for kill message only\n");
	A_init(); 			// create and initialise Process A 
	A_run(); 			// create and run Process A, it will registeritself for 1 message type
	printf("ENV: Start process B, it shall register for kill and alert message\n");
	B_init();			// create and initialise Process B 
	B_run();			// create and run Process B, it will registeritself for 2 message types
	printf("ENV: Start test process that will call the broadcasts\n");
	TEST_init();		// create and initialise Test-Process 
	TEST_run();		// create and run Test-Process, it will trigger two broadcasts
	printf("ENV: End of testrun\n");
	return 0;
}



/* ----------------------------------------------------------------	*/
/* Declarations of global variables visible only in this file 		*/

/* ----------------------------------------------------------------	*/
/* Declarations of functions visible only in this file 				*/
void initProcessA(pid_t pid);


/* ---------------------------------------------------------------- */
/*                Externally available functions                    */
/* ---------------------------------------------------------------- */




/* ---------------------------------------------------------------- */
/*                Only locally available functions                  */
/* ---------------------------------------------------------------- */

void initProcessA(pid_t pid)
{

}