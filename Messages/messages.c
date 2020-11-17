/* Module for message passing between processes, includes:			*/
/* registering for messages, unregistering at termination by the OS,*/
/* sending of messages, boadcast,									*/

#include "global.h"
#include "messages.h"
#include "stdlib.h"  //Durch uns erg�nzt


/* ----------------------------------------------------------------	*/
/* Declarations of global variables visible only in this file 		*/

//Liste von Knoten
typedef struct node				//Knoten sind Listen welche die Prozess ID�s und die Handler speichern.
{
	pid_t pid;					//ProzessID des aktuell betrachteten Knoten
	msgHandler_t handler;		//Handler des aktuell betrachteten Knoten
	struct node* next;			//Zeiger auf den n�chsten Knoten in der Liste
} node;							

//Liste von Listen
typedef struct list				//In list werden die Listen mit den Prozess ID�s gespeichert mit
{
	msgType_t msgType_l;		//Nachrichtentyp der aktuell betrachteten Liste von Knoten
	struct node* firstNode;		//Zeiger auf den ersten Knoten in der Liste
	struct list* listnext;		//Zeiger auf die N�chste Liste von Knoten
} list;

list* root;						//Zeiger auf die erste Liste von Knoten

/* ----------------------------------------------------------------	*/
/* Declarations of functions visible only in this file 				*/



/* ---------------------------------------------------------------- */
/*                Externally available functions                    */
/* ---------------------------------------------------------------- */

/* function to iniaitlise the message system, called by the os */
msgReturn_t msg_init(void)
{

	// Soweit n�tig hier die Initialisierung Ihrer Datentypen implementieren 

	return 1;
}



/* registering a process for a certain message type					*/
msgReturn_t msg_register(pid_t pid, msgType_t msgType, msgHandler_t myHandler)
{

	node* newNode = malloc(sizeof(struct node));	//Speicher reservieren f�r den neuen Knoten
	newNode->pid = pid;								//PID wir in Den Knoten eingetragen
	newNode->handler = myHandler;					//Handler wird in den Knoten eingetragen
	newNode->next = NULL;							//Referenz auf den NULL als Marker f�r das ende der Liste

	if (root == NULL)								//Falls noch keine Liste von Listen existiert
	{
		list* newList = malloc(sizeof(struct list));//Speicher reservieren f�r eine neue Liste von Knoten
		newList->msgType_l = msgType;				//msgType wird als Type der Liste von Knoten definiert
		newList->firstNode = newNode;				//Neuer Knoten wird als erster Knoten in die Liste eingef�gt
		newList->listnext = NULL;					//Referenz auf den NULL als Marker f�r das Ende der Liste
		root = newList;								//Die neue Liste wird als Startwert gesetzt
		return 1;
	}
	list* liste = root;								//Erstellen eines tempor�ren Laufzeigers f�r die Listen von Knoten

	while (liste != NULL)							//Schleife die bis zum Ende der Liste von Listen l�uft 
	{
		if (msgType == liste->msgType_l)			//Check ob gesuchter msgType gleich dem der Liste ist
		{
		

			node* curr = liste->firstNode;			//Erstellen eines Laufzeigers f�r die Knoten in einer Liste
			while (curr->next != NULL)				//Schleife um ans Ende der Liste zu kommen
			{
				if (curr != newNode)				//Check ob Prozess bereits in der Liste eingetragen ist
				{
					curr = curr->next;				//Laufzeiger wird einen weiter verschoben
				}
				else								//Falls der Knoten bereits in der Liste vorhanden ist
				{
					break;							//Abbruch wenn der Prozess bereits in der Liste vorhanden ist
				}
			}
			curr->next = newNode;					//Neuer Knoten wird in die Liste von Knoten eingef�gt
			break;									//Abbruch der Schleife wenn der Knoten eingef�gt wurde
		}
		else										//Falls msgType nicht �bereinstimmt
		{
			if (liste->listnext == NULL)			//Falls der Laufzeiger am Ende der Liste angekommen ist
			{
				list* newList = malloc(sizeof(struct list));	//Speicher f�r eine neue Liste von Knoten wird reserviert
				newList->msgType_l = msgType;		//msgType wird als Type der Liste von Knoten definiert
				newList->firstNode = newNode;		//Neuer Knoten wird als erster Knoten in die Liste eingef�gt
				newList->listnext = NULL;			//Referenz auf den NULL als Marker f�r das Ende der Liste
				liste->listnext = newList;			//Neue Liste von Knoten wird in die Liste von Listen eingef�gt
				break;								//Abbruch der Schleife da neues Element hinzugef�gt wurde
			}
			liste = liste->listnext;				//Laufzeiger wird auf die n�chste Liste Verschoben
		}
	}

	return 1;

	// Als Ergebnis dieser Funktion ist ein Prozess mit einer von 
	// ihm angegebenen Funktion f�r einen Nachrichtentyp registriert.
	// Das Betriebssystem muss diese Information in Datenstrukturen 
	// ablegen so, dass das gezielte Senden einer Nachricht und ein 
	// Broadcast effizient m�glich sind. 
	// Die Datenstruktur muss ohne mitwirken der Prozesse bei deren 
	// Terminierung aktualisiert werden k�nnen und ein terminierter 
	// Prozess entfernt werden k�nnen. 

}

/* sending a message to a process*/
msgReturn_t msg_send(pid_t receiverPid, msgType_t msgType, msgData_t msgData)
{
	msgReturn_t receiverResponse = -1;	// Buffer for the return-value provioded by the handler of the receiving process. 
	msgHandler_t receiverHandler = NULL;	// Function Pointer to the handler of the process receiving the message

	list* liste = root;									//Erstellen eines Laufzeigers f�r die Liste von Listen

	while (liste != NULL)								//Solange wir nicht am Ende der Liste angekommen sind 
	{
		
		if (liste->msgType_l == msgType)				//Wenn der msgType mit dem der Liste �bereinstimmt
		{
			node* curr = liste->firstNode;				//Erstellen eines Laufzeigers f�r die Knoten in einer Liste
			while (curr != NULL)						//Durchlauf bis ans Ende der Liste
			{
				if (curr->pid == receiverPid)			//Wenn die �bergebene PID mit der aktuellen 
				{
					receiverHandler = curr->handler;	//der aktuelle Handler wird an den receiverHandler �bergeben
					break;								//Abbruch der Schleife
				}
				curr = curr->next;						//Laufzeiger wird auf den n�chsten Wert gesetzt
			}

			break;										//Abbruch wenn die Liste abgearbeitert ist
		}
		liste = liste->listnext;						//Laufzeiger wird auf die n�chste Liste Verschoben
	}


	// Ihre Implementierung muss diesen Pointer ermitteln und daf�r die 
	// in msg_register() aktualisierte Datenstruktur(en) verwenden.

	// call the handler of the receiving process 
	receiverResponse = (receiverHandler)(msgData);
	// return the return value provided by the handler in the receiving process
	return receiverResponse;
}

/* broadcasting a message to all processes */
void msg_broadcast(msgType_t msgType, msgData_t msgData)
{
	list* liste = root;									//Erstellen eines Laufzeigers f�r die Liste von Listen
	while (liste != NULL)								//Solange wir nicht am Ende der Liste angekommen sind
	{
		node* curr = liste->firstNode;					//Erstellen eines Laufzeigers f�r die Knoten in einer Liste
		if (liste->msgType_l == msgType)				//Es wird gepr�ft ob der �bergebe msgType mit dem aktuellen �bereinstimmt
		{
			while (curr != NULL)						//Durchlauf bis ans Ende der Liste
			{
				msg_send(curr->pid, msgType, msgData);	//msg_send wird aufgerufen und die Werte f�r die Aktuelle pid, msgType und msgData werden �bergeben
				curr = curr->next;						//Laufzeiger wird auf den n�chsten Wert gesetzt
			}
			break;										//Abbruch wenn die Liste abgearbeitet ist
		}
		liste = liste->listnext;						//Laufzeiger wird auf die n�chste Liste gesetzt
	}

}



/* ---------------------------------------------------------------- */
/*                Only locally available functions                  */
/* ---------------------------------------------------------------- */
