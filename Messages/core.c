/* Implementation of core functionality of the OS					*/
/* this includes the handling of internal data structures			*/
/* for comments on the global functions see the associated .h-file	*/

/* ---------------------------------------------------------------- */
/* Include required external definitions */
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bs_types.h"
#include "global.h"
#include "core.h"
#include "messages.h"

/* ----------------------------------------------------------------	*/
/* Declarations of global variables that will be globally visible	*/
unsigned int	maxPID;					// largest valid PID
PCB_t processTable[MAX_PROCESSES + 1]; 	// the process table
unsigned systemTime; 					// the current system time (up time)

/* ----------------------------------------------------------------	*/
/* Declarations of global variables visible only in this file 		*/

/* ----------------------------------------------------------------	*/
/* Declarations of functions visible only in this file 				*/
void initProcessTable(void); 
pid_t getNextPID(); 
/* ---------------------------------------------------------------- */
/*                Externally available functions                    */
/* ---------------------------------------------------------------- */

void initOS(void)
{
	systemTime = 0;						// reset the system time to zero
	initProcessTable();					// create the process table with empty PCBs
	printf("CORE: Processtable initialised\n");
	msg_init();							// init the message system
	printf("CORE: Message system initialised\n");
	srand( (unsigned)time( NULL ) );	// init the random number generator
	printf("CORE: OS fully initialised\n\n");
}


pid_t process_create(os_processCode_t pCode)
{
	pid_t newPID = 0; 
	
	newPID = getNextPID();	// find a PID for the new process

	processTable[newPID].pid = newPID; 
	processTable[newPID].ppid = INIT_PID;
	processTable[newPID].pCode = pCode; 
	processTable[newPID].valid = TRUE;	// finally, mark the PID valid
	printf("CORE: Process with PID %u created\n", newPID);
	return newPID;
}


pid_t getpid(os_processCode_t pCode)
{ /* with this prototype and implementation this is function is only suitable for this demo-environment */
	unsigned i=1; 
	while ((i <= MAX_PROCESSES) && (processTable[i].pCode!=pCode))
	{	
		i++; 
	}
	return i;

}


/* ---------------------------------------------------------------- */
/*                Only locally available functions                  */
/* ---------------------------------------------------------------- */

/* initialise the PCBs in the Processtable							*/
/* Minimum: at least mark unitialised PCBs as invalid				*/
void initProcessTable(void)
{
	for (int i = 0; i <= MAX_PROCESSES; i++)
	{
		processTable[i].valid = FALSE; 
	}
	// create an "init-process" that is registered as parent of other processes
	processTable[INIT_PID].pid = INIT_PID;
	processTable[INIT_PID].ppid = 0;
	processTable[INIT_PID].pCode = NULL;
	processTable[INIT_PID].valid = TRUE;	// finally, mark the PID valid
}


/* a simple implementation to retrieve a new PID only suidable for		*/
/* this demo, must be replaced with a decent function in a real OS		*/
pid_t getNextPID()
{
	pid_t i = 1; 
	while ((processTable[i].valid) && (i < MAX_PROCESSES))
		i++; 
	if (i < MAX_PROCESSES)	return i;	// successfull 
	else					return 0;	// unsuccessfull 
		
}