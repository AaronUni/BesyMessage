/* Module for message passing between processes, includes:			*/
/* registering for messages, unregistering at termination by the OS,*/
/* sending of messages, boadcast,									*/

#include "global.h"
#include "messages.h"
#include "stdlib.h"  //Durch uns ergänzt


/* ----------------------------------------------------------------	*/
/* Declarations of global variables visible only in this file 		*/

//Liste von Knoten
typedef struct node
{
	pid_t pid;
	msgHandler_t handler;
	struct node* next;
} node;

//Liste von Listen
typedef struct list
{
	msgType_t msgType_l;
	struct node* firstNode;
	struct list* listnext;
} list;

list* liste;
list* root;
node* curr;

/* ----------------------------------------------------------------	*/
/* Declarations of functions visible only in this file 				*/



/* ---------------------------------------------------------------- */
/*                Externally available functions                    */
/* ---------------------------------------------------------------- */

/* function to iniaitlise the message system, called by the os */
msgReturn_t msg_init(void)
{

	// Soweit nötig hier die Initialisierung Ihrer Datentypen implementieren 

	return 1;
}



/* registering a process for a certain message type					*/
msgReturn_t msg_register(pid_t pid, msgType_t msgType, msgHandler_t myHandler)
{

	node* newNode = malloc(sizeof(struct node));
	newNode->pid = pid;
	newNode->handler = myHandler;
	newNode->next = NULL;

	if (root == NULL)
	{
		list* newList = malloc(sizeof(struct list));
		newList->msgType_l = msgType;
		newList->firstNode = newNode;
		newList->listnext = NULL;
		root = newList;
	}
	liste = root;

	while (liste != NULL)
	{
		if (msgType == liste->msgType_l)
		{

			curr = liste->firstNode;
			while (curr->next != NULL)
			{
				curr = curr->next;
			}
			if (curr != newNode) 
			{
				curr->next = newNode;
			}
			break;
		}
		else
		{
			if (liste->listnext == NULL)
			{
				list* newList = malloc(sizeof(struct list));
				newList->msgType_l = msgType;
				newList->firstNode = newNode;
				newList->listnext = NULL;
				liste->listnext = newList;
			}
			liste = liste->listnext;
		}
	}


	return 1;

	// Als Ergebnis dieser Funktion ist ein Prozess mit einer von 
	// ihm angegebenen Funktion für einen Nachrichtentyp registriert.
	// Das Betriebssystem muss diese Information in Datenstrukturen 
	// ablegen so, dass das gezielte Senden einer Nachricht und ein 
	// Broadcast effizient möglich sind. 
	// Die Datenstruktur muss ohne mitwirken der Prozesse bei deren 
	// Terminierung aktualisiert werden können und ein terminierter 
	// Prozess entfernt werden können. 

}

/* sending a message to a process*/
msgReturn_t msg_send(pid_t receiverPid, msgType_t msgType, msgData_t msgData)
{
	msgReturn_t receiverResponse = -1;	// Buffer for the return-value provioded by the handler of the receiving process. 
	msgHandler_t receiverHandler = NULL;	// Function Pointer to the handler of the process receiving the message

	list* liste = root;

	while (liste != NULL)
	{
		node* curr = liste->firstNode;
		if (liste->msgType_l == msgType)
		{
			while (curr != NULL)
			{
				if (curr->pid == receiverPid)
				{
					receiverHandler = curr->handler;
					break;
				}
				curr = curr->next;
			}
			break;
		}
		liste = liste->listnext;
	}




	// Ihre Implementierung muss diesen Pointer ermitteln und dafür die 
	// in msg_register() aktualisierte Datenstruktur(en) verwenden.

	// call the handler of the receiving process 
	receiverResponse = (receiverHandler)(msgData);
	// return the return value provided by the handler in the receiving process
	return receiverResponse;
}

/* broadcasting a message to all processes */
void msg_broadcast(msgType_t msgType, msgData_t msgData)
{
	list* liste = root;
	list* pre = root;
	while (liste != NULL)
	{
		node* curr = liste->firstNode;
		if (liste->msgType_l == msgType)
		{
			while (curr != NULL)
			{
				msg_send(curr->pid, msgType, msgData);
				curr = curr->next;
			}
			pre->listnext = liste->listnext;
			free(liste);
			break;
		}
		pre = liste;
		liste = liste->listnext;
	}
}



/* ---------------------------------------------------------------- */
/*                Only locally available functions                  */
/* ---------------------------------------------------------------- */
