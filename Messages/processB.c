/* Modul that encapsulates all data and code of process A					*/
/* For the demo the processes are not really separate entities,				*/
/* however they are modelled disjunctly by using a module for each process	*/

#include "global.h"
#include "messages.h"
#include "processB.h"

/* ----------------------------------------------------------------	*/
/* Declarations of global variables visible only in this file 		*/

/* ----------------------------------------------------------------	*/
/* Declarations of functions visible only in this file 				*/

/* Handler für kill-message */			
msgReturn_t terminateMe(msgData_t pData);

/* Handler for alert-message    */
msgReturn_t myAlert(msgData_t pData);


pid_t B_init(void)
{
	/* call OS-routine to start a new process and remember the own name */
	return process_create(B_run);
}

int B_run(void)
{
	printf("B: Process started with PID %u\n", getpid(B_run));
	printf("B: Registering for kill-message\n");
	msg_register(getpid(B_run), msg_kill, terminateMe);
	printf("B: Registering done\n");
	printf("B: Registering for alert-message\n");
	msg_register(getpid(B_run), msg_alert, myAlert);
	printf("B: Registering done\n");
	// Status Ausgabe
	printf("B: Process is now computing the stuff it is supposed to do\n");
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

msgReturn_t terminateMe(msgData_t pData)
{
	// Status Ausgabe
	printf("B: Handler for kill-message started\n"); 
	printf("B: Received: \"%s\" \n", (char*)pData);
	printf("B: Cleaning my data, preparing to be shut down\n"); 
	// return successfull shut-down
	printf("B: Bye from process B \n");
	return 0;
}

msgReturn_t myAlert(msgData_t pData)
{
	// Status Ausgabe
	printf("B: Handler for alert-message started\n");
	printf("B: Received: \"%s\" \n", (char*)pData);
	printf("B: Switching to alert state\n");
	// return successfull shut-down
	printf("B: Alert-handler completed \n");
	return 0;
}