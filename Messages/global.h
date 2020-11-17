/* Include-file defining global defines and constants  	 		*/
/* used by the operating system */
#ifndef __GLOBAL__
#define __GLOBAL__

#define	_CRT_SECURE_NO_WARNINGS		// suppress legacy warnings 

#include <stdlib.h>
// #include <time.h>3
#include "bs_types.h"
#include "core.h"

// Number of possible concurrent processes, i.e. size of the process table 
#define MAX_PROCESSES (unsigned)20		// for the demo scenario only a small number of processes
// Obwohl hier in der Demo nur wenige Prozesse vorgesehen sind, soll Ihre Implementierung 
// so ausgelegt sein, dass sie sinnvoll auch für eine große Anzahl (einige Huntert!) 
// von möglichen und auch aktuell laufenden Prozessen geeignet ist. 
// Legen Sie Datentypen und Implementierung entsprechend aus. 

/* ----------------------------------------------------------------	*/
/* Define global variables that will be visible in all sourcefiles	*/
extern PCB_t processTable[MAX_PROCESSES + 1]; 	// the process table

/* ----------------------------------------------------------------	*/
/* Define global constants that will be visible in all sourcefiles	*/


#endif  /* __GLOBAL__ */ 