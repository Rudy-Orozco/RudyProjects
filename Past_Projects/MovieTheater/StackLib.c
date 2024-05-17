/* Stack Library */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "StackLib.h"
 
// First parameter - Address of StackTop
// Second parameter - Head of ticket linked list store in stack node 
// Third parameter - Receipt number stored in stack node
// Fourth parameter - Movie theater name 
void push(SNODE **StackTop, LNODE *TicketList, int ReceiptNumber, char MTN[])
{
    SNODE *NewNode = malloc(sizeof(SNODE));
    NewNode->ReceiptNumber = ReceiptNumber;
	NewNode->TicketList =  TicketList;
	NewNode->MovieTheaterName = malloc(strlen(MTN) * sizeof(char) + 1);
	strcpy(NewNode->MovieTheaterName, MTN);
	NewNode->next_ptr = NULL;
	
	if (*StackTop == NULL)
	{
		*StackTop = NewNode;
	}
	else
	{
		NewNode->next_ptr = *StackTop;
		*StackTop = NewNode;
    }
}

// First parameter - Address of StackTop
void pop(SNODE **StackTop)
{
	if (*StackTop != NULL)
	{
		SNODE *TempPtr = (*StackTop)->next_ptr;

		free(*StackTop);
		*StackTop = TempPtr;
	}
}
