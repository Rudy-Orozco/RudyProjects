/*CA6 1001864902 Rudy Orozco*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
 
#define HASHTABLESIZE 30
 
/* Node for storing information */
typedef struct PersonStats
{
    char *Name;
    float HeightInM;
    char FavColor;
    int Age;
    struct PersonStats *next_ptr;
}
PERSONSTATS;
 
/* This function creates an index corresponding to the input key */
int CalculateHashIndex(char *key) //DONE
{
	int Sum, Adding;

    // Alphanumeric Keys
    for(int i = 0; i < strlen(key); i++)
    {
        Adding = key[i]; // Adding the sum of all ASCII Values
        Sum = Sum + Adding;
    }

    return Sum % HASHTABLESIZE; 
}

void AddNode(PERSONSTATS *NewNode, PERSONSTATS *PersonList[]) //DONE
{
	int HashIndex = CalculateHashIndex(NewNode->Name);
	
	/* a linked list does not exist for this cell of the array */
	if (PersonList[HashIndex] == NULL) 
	{
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
		PersonList[HashIndex] = NewNode;
	}
	else   /* A Linked List is present at given index of Hash Table */ 
	{
		PERSONSTATS *TempPtr = PersonList[HashIndex];
	
		/* Traverse linked list */
		while (TempPtr->next_ptr != NULL) 
		{
			TempPtr = TempPtr->next_ptr;
		}
		TempPtr->next_ptr = NewNode;
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
	}
}

void FreeDynamicMemory(PERSONSTATS *PersonList[]) // DONE
{
	PERSONSTATS *TempPtr = NULL, *NextPtr = NULL;
	
	for (int i = 0; i < HASHTABLESIZE; i++)
	{
		TempPtr = PersonList[i];
 
		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL) 
			{
				free(TempPtr->Name);
				NextPtr = TempPtr->next_ptr;
				free(TempPtr);
				TempPtr = NextPtr;
			}	
		}
	}
}


/* Remove an element from Hash Table */ 
int DeleteNode(PERSONSTATS *PersonList[]) // DONE
{
	char LookupName[100] = {};
	int result = 0;
	
	printf("Enter the name of the Person from the list ");

	fgets(LookupName, sizeof(LookupName)-1, stdin); // Extra fgets
	fgets(LookupName, 100, stdin);

	if (LookupName[strlen(LookupName)-1] == '\n')
    {
        LookupName[strlen(LookupName)-1] = '\0';
    }

	int HashIndex = CalculateHashIndex(LookupName);

	/* Get linked list at key in array */
	PERSONSTATS *TempPtr = PersonList[HashIndex];
	PERSONSTATS *PrevPtr = NULL;
 
	/* This array index does not have a linked list; therefore, no keys */
	if (TempPtr == NULL) 
	{
		printf("\n\nThe person %s does not exist in the list\n\n", LookupName);
		result = 0;
	}
	else 
	{
		while (TempPtr != NULL) 
		{
			if (strcmp(TempPtr->Name, LookupName) == 0)
			{
				/* If the node being deleted is the head node */
				if (TempPtr == PersonList[HashIndex])
				{
					/* The node the head was pointing at is now the head */
					PersonList[HashIndex] = TempPtr->next_ptr;
					printf("\n%s has been deleted from the list\n\n", TempPtr->Name);
					free(TempPtr);
					TempPtr = NULL;
				}
				/* Found node to be deleted - node is not the head */
				else
				{
					PrevPtr->next_ptr = TempPtr->next_ptr;
					printf("\n%s has been deleted from the list\n\n", TempPtr->Name);
					free(TempPtr);
					TempPtr = NULL;
				}
				result = 1;
			}
			/* this is not the node that needs to be deleted but save */
			/* its info and move to the next node in the linked list  */
			else
			{
				PrevPtr = TempPtr;
				TempPtr = TempPtr->next_ptr;
			}
		}
		if (result == 0)
		{
			printf("\n\n%s does not exist in the list\n\n", LookupName);
		}
	}
	return result;
}

/* display the contents of the Hash Table */
void DisplayHashTable(PERSONSTATS *PersonList[]) //DONE
{
	int i;
	PERSONSTATS *TempPtr = NULL;
	
	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = PersonList[i];

		printf("\nPersonList[%d]-", i);
		
		if (TempPtr != NULL) 
        {
			while (TempPtr != NULL)
			{
				printf("%s|", TempPtr->Name);
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByLetter(PERSONSTATS *PersonList[]) // DONE
{
	int i;
	PERSONSTATS *TempPtr = NULL;
	char LookupLetter = 'A';

	printf("\n\nEnter a letter of the alphabet ");
	scanf(" %c", &LookupLetter);
	LookupLetter = toupper(LookupLetter);

	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = PersonList[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (toupper(TempPtr->Name[0]) == LookupLetter)
				{
					printf("%s\n", TempPtr->Name);
				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByName(PERSONSTATS *PersonList[]) //DONE
{
	PERSONSTATS *TempPtr = NULL;
	char height[10] = {};
	char age[10] = {};
	char color[10] = {};
	char LookupName[100] = {};
	int FoundIt = 0;
	
	printf("\n\nEnter Person's name ");

	fgets(LookupName, sizeof(LookupName)-1, stdin); // Extra fgets
	fgets(LookupName, 100, stdin);

	if (LookupName[strlen(LookupName)-1] == '\n')
    {
        LookupName[strlen(LookupName)-1] = '\0';
    }
	
	#if TIMING
	clock_t start, end;
	start = clock();
	#endif
	for (int i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = PersonList[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (strcmp(TempPtr->Name, LookupName) == 0)
				{
					#if TIMING
					end = clock();
					printf("\n\nSearch took %ld tics\n\n", end-start);
					#endif

					FoundIt = 1;
					printf("\n\n[%s]\n", TempPtr->Name); //NAME
					
					printf("Height\t\t\t");
					sprintf(height, "%.2f", TempPtr->HeightInM); //HEIGHT
					for (int i = 0; i < strlen(height); i++)
					{
						printf("%c", height[i]);
					}
					printf("m\n");

					printf("Age\t\t\t%1d\n", TempPtr->Age); //AGE

                    switch(TempPtr->FavColor) //FAVORITE COLOR
                    {
                        case 'R':
                            printf("Favorite Color\t\tRED\n");
                            break;
                        case 'O':
                            printf("Favorite Color\t\tORANGE\n");
                            break;
                        case 'Y':
                            printf("Favorite Color\t\tYELLOW\n");
                            break;
                        case 'G':
                            printf("Favorite Color\t\tGREEN\n");
                            break;
                        case 'B':
                            printf("Favorite Color\t\tBLUE\n");
                            break;
                        case 'P':
                            printf("Favorite Color\t\tPURPLE\n");
                            break;
                        default:
                            printf("Favorite Color\t\tUNKNOWN\n");
                    }

				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
	
	if (FoundIt == 0)
		printf("\n\n%s not found in list\n\n", LookupName);
}

void AddNewPerson(PERSONSTATS *PersonList[]) //DONE
{
	int HashIndex = 0;
	PERSONSTATS *NewNode;
	char TempBuffer[100] = {};
	char TempBuffer2[3] = {};

	NewNode = malloc(sizeof(PERSONSTATS));
	NewNode->next_ptr = NULL;

	printf("\n\nEnter new Person's name ");// NAME
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin); // Extra fgets
	fgets(TempBuffer, 100, stdin);
	if (TempBuffer[strlen(TempBuffer)-1] == '\n')
    {
        TempBuffer[strlen(TempBuffer)-1] = '\0';
    }

	NewNode->Name = malloc(strlen(TempBuffer)*sizeof(char)+1); 
	strcpy(NewNode->Name, TempBuffer);

    printf("\n\nEnter %s's age ", NewNode->Name); // AGE
	scanf("%d", &(NewNode->Age));

	printf("\n\nEnter %s's height in meters (1.8) ", NewNode->Name); // HEIGHT
	scanf("%f", &(NewNode->HeightInM)); 
	
	printf("\n\nEnter %s's favorite color (R, G, B, etc.) ", NewNode->Name); // FAVORITE COLOR
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin); // Clear Stdin
	scanf("%c", &(NewNode->FavColor)); 
	
	// Extra fgets to clear stdin
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);

	AddNode(NewNode, PersonList);
}

int ReadFileIntoHashTable(int argc, char *argv[], PERSONSTATS *PersonList[]) //DONE
{
	FILE *FH = NULL;
	char FileLine[100] = {};
	char *token = NULL;
	int counter = 0;
	int HashIndex = 0;
	PERSONSTATS *NewNode;

	if (argc > 1)
	{
		FH = fopen(argv[1], "r");

		if (FH == NULL)
		{
			perror("Exiting ");
			exit(0);
		}
		
		while (fgets(FileLine, sizeof(FileLine)-1, FH))
		{
			token = strtok(FileLine, "|");

			NewNode = malloc(sizeof(PERSONSTATS));
			NewNode->next_ptr = NULL;
			
			NewNode->Name = malloc(strlen(token)*sizeof(char)+1);//NAME
			strcpy(NewNode->Name, token);

			token = strtok(NULL, "|"); //HEIGHT
			NewNode->HeightInM = atof(token);
			
			token = strtok(NULL, "|"); //FAVORITE COLOR
			NewNode->FavColor = token[0];
			
			token = strtok(NULL, "|"); //AGE
			NewNode->Age = atoi(token); 

			AddNode(NewNode, PersonList);

			counter++;
		}

	}
	else
	{
		printf("File must be provided on command line...exiting\n");
		exit(0);
	}
	
	fclose(FH);
	
	return counter;
}

int main(int argc, char *argv[]) 
{
	int MenuChoice = 0;
	int counter = 0;
	PERSONSTATS *PersonList[HASHTABLESIZE] = {};

	enum Menu {SHOWBYLETTER=1, SHOWBYNAME, COUNT, DISPLAY, ADD, DELETE, EXIT};
 
	counter = ReadFileIntoHashTable(argc, argv, PersonList);
 
	do
	{
		printf("\n\nFriends List Menu\n\n"
			   "1. Show all Persons in list for a given letter\n"
			   "2. Look up person by name\n"
			   "3. How many people are in the list?\n"
			   "4. Display the list\n"
			   "5. Add a new Person\n"
			   "6. Delete a person from the list\n"
			   "7. Exit\n\n"
			   "Enter menu choice ");
	
		scanf("%d", &MenuChoice);
		printf("\n\n");

		switch (MenuChoice)
		{	
			case SHOWBYLETTER:
				ShowByLetter(PersonList);
				break;
			case SHOWBYNAME:
				ShowByName(PersonList);
				break;
			case COUNT:
				printf("Your list contains %d people\n", counter); 
				break;
 			case DISPLAY:
				DisplayHashTable(PersonList);
				break;
			case ADD:
				AddNewPerson(PersonList);
				counter++;
				break;
			case DELETE:
				if (DeleteNode(PersonList))
				{
					counter--;
				}
				break;
			case EXIT:
				break;
			default : 
				printf("Invalid menu choice\n\n"); 
		}
	}
	while (MenuChoice != EXIT);
	
	FreeDynamicMemory(PersonList);

	return 0;
}			  
