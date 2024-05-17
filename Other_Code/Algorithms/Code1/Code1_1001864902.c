/* CA1 Rudy Orozco 1001864902*/
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>

typedef struct node
{
	int number;
	struct node *next_ptr;
}
NODE;

void AddNodeToLL(int Number, NODE **LinkedListHead)
{
    struct node *TempPtr, *NewNode;

    //Initialize Node
    NewNode = malloc(sizeof(struct node));
    NewNode->number = Number;
    NewNode->next_ptr = NULL;

    TempPtr = *LinkedListHead;

    //Check if LLH is Empty
	if(*LinkedListHead == NULL)
	{
		*LinkedListHead = NewNode;
	}
    else // Traverse to End
    {
        while (TempPtr->next_ptr != NULL)
        {
            TempPtr = TempPtr->next_ptr;
        }
        
        TempPtr->next_ptr = NewNode;
    }
}

void ReadFileIntoLL(int argc,  char *argv[], NODE **LLH)
{
    FILE *filename = fopen(argv[1], "r");
    char charNumber[15];
    int intNumber;
    int count = 0, sum = 0;

    // Check if file is found
    if(filename == NULL)
    {
        printf("File must be provided on command line...exiting\n");
        exit(0);
    }

    //Store Numbers in LL
    while(fgets(charNumber, 100, filename))
	{
        intNumber = atoi(charNumber);
        AddNodeToLL(intNumber, LLH);        
        
        sum = sum + intNumber;

        count++;
	}

    printf("%d records were read for a total sum of %d\n", count, sum);
}

void PrintLL(NODE *LLH) // NOTE: ONLY USED WHEN -D PRINT IS USED
{ 
    struct node *TempPtr;
    TempPtr = LLH;
    
    while (TempPtr != NULL)
    {
        printf("\n%p %d %p\n", TempPtr, TempPtr->number, TempPtr->next_ptr);

        TempPtr = TempPtr->next_ptr;
    }
}

void FreeLL(NODE **LLH) 
{ 
    struct node *TempPtr;
    int count = 0, sum = 0;
    
    //Traverse through LL
    while ((*LLH) != NULL)
    {
        TempPtr = *LLH;

        #ifdef PRINT
            printf("\nFreeing %p %d %p\n", TempPtr, TempPtr->number, TempPtr->next_ptr);
        #endif

        sum = sum + TempPtr->number;
    
        //Reset LLH and free the TempPtr
        *LLH = (*LLH)->next_ptr;
        free(TempPtr);

        count++;
    }

    printf("\n%d nodes were deleted for a total sum of %d\n", count, sum);
}

int main(int argc, char *argv[]) 
{ 
	NODE *LLH = NULL;
    
    clock_t start, end;
	
	/* capture the clock in a start time */
    start = clock();
	ReadFileIntoLL(argc, argv, &LLH);
    
	/* capture the clock in an end time */
    end = clock();
	printf("\n%ld tics to write the file into the linked list\n", end-start);

    #ifdef PRINT
	    /* capture the clock in a start time */
        start = clock();
	    PrintLL(LLH);

        /* capture the clock in an end time */
        end = clock();
	    printf("\n%ld tics to print the linked list\n", end-start);
    #endif

	/* capture the clock in a start time */
    start = clock();
	FreeLL(&LLH);

	/* capture the clock in an end time */
    end = clock();
	printf("\n%ld tics to free the linked list\n", end-start);
	
	return 0; 
} 
