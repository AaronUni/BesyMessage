/* Include-file defining the interface of the demo-process B */

#ifndef __B__
#define __B__

/**
* @brief: function to iniaitlise process
*
* This function initialises the demo "process"
*
* @return			The function returns the PID that was assigned by the OS
*/
pid_t B_init(void);


/**
* @brief: function that implements the behaviour of the process
*
* This contains the actual functionality of the process
* The demo-processs B registers for the kill message and the alert message
*
* @return			The function returns an integer value
*					negative values indicate an error
*					zero and positive values indicate success
*/
int B_run(void);

#endif