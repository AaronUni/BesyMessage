/* Include-file defining elementary data types used by the 			*/
/* operating system (OS)											*/
/* data types needed by subsystems of the OS are additionally		*/ 
/* declared in the header files of the respective modules			*/
#ifndef __BS_TYPES__
#define __BS_TYPES__

typedef enum { FALSE = 0, TRUE } Boolean;


/* data type for storing of process IDs		*/
typedef unsigned pid_t;

/* data type for function pointer to the code implementing a process */
typedef int (*os_processCode_t) (void); 

/* data type for the Process Control Block */
/* +++ this might need to be extended to support future features	+++ */
/* +++ like additional schedulers or advanced memory management		+++ */
typedef struct PCB_struct
{
	Boolean valid;				// the data in this struct is valid
	pid_t pid;					// PID of this process, may be ommitted as it equals the index in the processtable
	pid_t ppid;					// PID of the parent
	unsigned size;				// size of logical process memory in pages
	os_processCode_t pCode;	//
} PCB_t;



#endif  /* __BS_TYPES__ */ 