/* Modul that encapsulates all data and code of process A					*/
/* For the demo the processes are not really separate entities,				*/
/* however they are modelled disjunctly by using a module for each process	*/

#include "global.h"
#include "messages.h"
#include "processTest.h"

/* ----------------------------------------------------------------	*/
/* Declarations of global variables visible only in this file 		*/
char alertPayload[] = "Just a drill"; 
char killPayload[] = "You are done!";

/* ----------------------------------------------------------------	*/
/* Declarations of functions visible only in this file 				*/

/* Handler für kill-message */			
msgReturn_t terminateMe(msgData_t pData);

/* Handler for alert-message    */
msgReturn_t myAlert(msgData_t pData);


pid_t TEST_init(void)
{
	/* call OS-routine to start a new process and remember the own name */
	return process_create(TEST_run);
}

int TEST_run(void)
{
	printf("TEST: Process started with PID %u\n", getpid(TEST_run));
	printf("TEST: Broadcasting an alert-message\n");
	msg_broadcast(msg_alert, alertPayload);
	printf("TEST: Please check the log if the correct processes have reacted\n");
	printf("TEST: Broadcasting a kill-message\n");
	msg_broadcast(msg_kill, killPayload);
	printf("TEST: Please check the log if the correct processes have reacted\n");
	// Status Ausgabe
	printf("TEST: Test stimulus complete\n");
	// process now needs to be terminated
	return 0; 
}

/* ---------------------------------------------------------------- */
/*                Externally available functions                    */
/* ---------------------------------------------------------------- */

/* ---------------------------------------------------------------- */
/*                Only locally available functions                  */
/* ---------------------------------------------------------------- */
