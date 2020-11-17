/* Modul that encapsulates all data and code of process A					*/
/* For the demo the processes are not really separate entities,				*/
/* however they are modelled disjunctly by using a module for each process	*/

#include "global.h"
#include "messages.h"
#include "processA.h"

/* ----------------------------------------------------------------	*/
/* Declarations of global variables visible only in this file 		*/
pid_t myPID;		// PID dieses Prozesses (man merkt sich seinen Namen!)

/* ----------------------------------------------------------------	*/
/* Declarations of functions visible only in this file 				*/

/* Handler für kill-message */			
msgReturn_t myTermination(msgData_t pData);

/* Handler for alert-message    */
msgReturn_t myAlert(msgData_t pData);


pid_t A_init(void)
{
	/* call OS-routine to start a new process and remember the own name */
	return process_create(A_run);
}

int A_run(void)
{
	printf("A: Process started with PID %u\n", getpid(A_run));
	printf("A: Registering for kill-message\n");
	msg_register(getpid(A_run), msg_kill, myTermination);
	printf("A: Registering done\n");
	// Status Ausgabe
	printf("A: Process is now computing the stuff it is supposed to do\n");
	// Jetzt würde der Prozess normal ausgeführt werden. In der Demo muss nichts mehr im Prozess passieren
// 	Das Terminieren erfolgt als Reaktion auf die Kill-Nachricht.
	return 0; 
}

/* ---------------------------------------------------------------- */
/*                Externally available functions                    */
/* ---------------------------------------------------------------- */

/* ---------------------------------------------------------------- */
/*                Only locally available functions                  */
/* ---------------------------------------------------------------- */

msgReturn_t myTermination(msgData_t pData)
{
	// Status Ausgabe
	printf("A: Handler for kill-message started\n"); 
	printf("A: Received: \"%s\"\n", (char*)pData);
	printf("A: Cleaning my data, preparing to be shut down\n"); 
	myPID = 0;					// no longer a running process 
	// return successfull shut-down
	printf("A: Bye from process A \n");
	return 0;
}
