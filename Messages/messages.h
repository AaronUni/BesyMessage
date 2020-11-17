/* Include-file defining data types used by message subsystem		*/

#ifndef __MESSAGES__
#define __MESSAGES__

#include "global.h"

/* ----------------------------------------------------------------	*/
/* Declarations of global variables declared for messages			*/

/* ----------------------------------------------------------------	*/
/* Declarations of data types for messages							*/


/* data type for the possible types of messages */
typedef enum
{
	msg_kill, msg_sleep, msg_wakeup, msg_pause, msg_alert
} msgType_t;
#define MSG_NUMTYPES 5					// Number of message types
// In dieser Demo gibt es nur fünf Nachritentypen, das ist unrealistisch klein. 
// Ihre Implementierung soll auch mit einigen zig bis 
// zu ca. 200 Nachrichtentypen effizient zumgehen können. 
// Legen Sie Datentypen und Implementierung entsprechend aus. 


/* data type for the message payload */
/* currently this is the most generic data type and it might be adapted*/
typedef void*
msgData_t;

/* data type for the message return value */
/* negative values indicate unsuccessful execution (error)		*/
/* positive values and zero indicate successful execution		*/
typedef int
msgReturn_t;

/* data type for function pointer to the handler for a message type */
 //int (*msgHandler_t) (void);
typedef msgReturn_t (*msgHandler_t) (msgData_t);
/* ----------------------------------------------------------------	*/
/* Declarations of functions for messages							*/

/**
* @brief: function to iniaitlise the message system, called by the os
*
* This function initialises the message system, i.e. creates and initialises 
* all data structured used by this part of the OS.
* It must be called during boot-up of the OS
*
* @return			The function returns an integer value typed msgReturn_t
*					negative values indicate an error
*					zero and positive values indicate success
*/
msgReturn_t msg_init(void);


/** 
* @brief: function to register for a certain message type
* 
* By calling this function, the named process is registered for the given
* message type. The OS will call the handler-function that is passed. 
* The handler must be part of the process with the given PID. 
* This function is intended to be called by a process to register itself.
* 
* @param pid		the PID of the process that is registered for a message
* @param msgType	the type of the message that the process shall react to
*					must be one of the types given by the enum msgType_t
* @param myHandler	a function pointer to the function inside the process 
*					with the given PID. The handler must be of the prototype 
*					given by msgHandler_t
* @return			The function returns an integer value typed msgReturn_t
*					negative values indicate an error
*					zero and positive values indicate success
*/
msgReturn_t msg_register(pid_t pid, msgType_t msgType, msgHandler_t myHandler);



/**
* @brief: function to send a message to a process
*
* By calling this function, a message of the given type with the given 
* content is sent to the target process
* This function can be used by authorised user processes and the OS core
* REMEMBER: In this demo the authorisation is not checked.
*
* @param pid		the PID of the process that is registered for a message
* @param msgType	the type of the message to be sent
*					must be one of the types given by the enum msgType_t
* @param msgData	pointer to the payload of the message. 
*					The payload must be of the prototype given by msgHandler_t
* @return			The function returns an integer value typed msgReturn_t
*					negative values indicate an error
*					zero and positive values indicate success
*/
msgReturn_t msg_send(pid_t receiverPid, msgType_t msgType, msgData_t msgData);

/**
* @brief: function to send a message to all registered processes 
*
* By calling this function, a message of the given type with the given
* content is sent via broadcast to all processes that are registered to 
* messages of this type. There is no acknowledge to the entity initiating 
* the broadcast. 
*
* @param msgType	the type of the message to be sent
*					must be one of the types given by the enum msgType_t
* @param msgData	pointer to the payload of the message.
*					The payload must be of the prototype given by msgHandler_t
* @return			none 
*/
void msg_broadcast(msgType_t msgType, msgData_t msgData);


#endif