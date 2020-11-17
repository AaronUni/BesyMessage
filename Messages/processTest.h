/* Include-file defining the interface of the test-process*/

#ifndef __TEST__
#define __TEST__

/**
* @brief: function to iniaitlise process 
*
* This function initialises the demo "process"
* 
* @return			The function returns the PID that was assigned by the OS
*/
pid_t TEST_init(void);


/**
* @brief: function that implements the behaviour of the process
*
* This contains the actual functionality of the process
* The test-processs calls for two broadcasts 
*
* @return			The function returns an integer value 
*					negative values indicate an error
*					zero and positive values indicate success
*/
int TEST_run(void);

#endif