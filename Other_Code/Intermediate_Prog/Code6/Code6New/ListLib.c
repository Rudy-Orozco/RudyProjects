/* ListLib */

#include "ListLib.h"
void AddDrawCommandToList(char Let, char Draw[], NODE **LinkedListHead)
{
    
	/* declare pointers of type NODE named TempPtr and NewNode */
	NODE *TempPtr, *NewNode;

	/* malloc a new node and assign the Letter and the DrawCommand 
	(after mallocing memory for it) */

	NewNode = malloc(sizeof(NODE));

	NewNode->Letter = Let;

	NewNode->DrawCommand = malloc((strlen(Draw)*sizeof(char)+1));
	strncpy(NewNode->DrawCommand, Draw, (strlen(Draw) + 1));

	/* If the LinkedListHead is NULL, then give it the address of the new node */
	if(*LinkedListHead == NULL)
	{
		*LinkedListHead = NewNode;
	}
	else /* Else traverse to the end of the linked list and add the new node */
	{
		TempPtr = *LinkedListHead;
		while (TempPtr->next_ptr != NULL)
		{
			TempPtr = TempPtr->next_ptr;
		}

		TempPtr->next_ptr = NewNode;
	}
	
}

NODE *FindLetter(NODE *LinkedListHead, char Letter, char DC[])
{
	NODE *TempPtr;

	//TempPtr = malloc(sizeof(*LinkedListHead));
	TempPtr = LinkedListHead;

	/* while traversing the linked list AND the Letter in the node is not the Letter passed in */
	while((TempPtr != NULL) && ((TempPtr->Letter) != Letter))
	{
		TempPtr = TempPtr->next_ptr;
	}

	if (TempPtr != NULL)
	{
		/* copy the DrawCommand from the node into the passed in parameter */
		strcpy(DC, TempPtr->DrawCommand);
		/* return the next pointer stored in TempPtr */
		return TempPtr->next_ptr;
	}
	else
	{
		memset(DC, '\0', sizeof(*DC));  
		//Set DC to NULLs to signal that we found all of the nodes for this letter
		return TempPtr;
	}
}
