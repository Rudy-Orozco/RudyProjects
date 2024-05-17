/* QueueLib */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "QueueLib.h"

// First parameter - Customer's name
// Second parameter - Address of QueueHead
// Third parameter - Address of QueueTail
void enQueue(char CustomerName[], QNODE **QueueHead, QNODE **QueueTail)
{
    QNODE *NewNode = malloc(sizeof(QNODE));
	NewNode->name = malloc(strlen(CustomerName) * sizeof(char) + 1);
    strcpy(NewNode->name, CustomerName);
    NewNode->next_ptr = NULL;

	/* Queue is empty */
	if (*QueueHead == NULL)
	{
		*QueueHead = *QueueTail = NewNode;
	}
	else
	{
		(*QueueTail)->next_ptr = NewNode;
		*QueueTail = NewNode;
	}
}
 
// First parameter - Address of QueueHead
void deQueue(QNODE **QueueHead)
{
	QNODE *TempPtr = (*QueueHead)->next_ptr;
	
    if (*QueueHead != NULL)
	{
		free(*QueueHead);
		*QueueHead = TempPtr;
	}
}
 
// First parameter - QueueHead 
void DisplayQueue(QNODE *QueueHead)
{
	QNODE *TempPtr = QueueHead;
	
	while (TempPtr != NULL)
	{
		printf("%s\n", TempPtr->name);
		TempPtr =  TempPtr->next_ptr;
	}
} 


