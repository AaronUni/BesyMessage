/* Include-file defining functions of the OS-core 	 		*/
#ifndef __CORE__
#define __CORE__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_PID 1		// PID of the init process

void initOS(void);
/* all initialisation steps are started in this function					*/

pid_t process_create(os_processCode_t code);

pid_t getpid(os_processCode_t);
/* return the PID of the referred process*/
/* with this prototype and implementation this is function is only suitable for this demo-environment */
#endif /* __CORE__ */