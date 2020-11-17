/* Include-file defining the interface of the demo-process A */

#ifndef __A__
#define __A__


/**
* @brief: function to iniaitlise process
*
* This function initialises the demo "process"
*
* @return			The function returns the PID that was assigned by the OS
*/
pid_t A_init(void);

/**
* @brief: function that implements the behaviour of the process
*
* This contains the actual functionality of the process
* The demo-processs A registers for the kill-message
*
* @return			The function returns an integer value
*					negative values indicate an error
*					zero and positive values indicate success
*/
int A_run(void);


#endif
