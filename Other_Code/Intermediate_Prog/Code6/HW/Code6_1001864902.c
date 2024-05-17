/* Rudy Orozco 1001864902*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "DrawTool.h"
#include "ListLib.h"
#include "FileLib.h"

int main(int argc, char *argv[])
{
    //ARRAY
    char Arry[MAXMAPSIZE][MAXMAPSIZE];

    //INITIALIZING VARIABLES
    char *tok;
    char drawtype, marker, cmmdline[15], chdrawtype[3], chmarker[3];
    int introw, intcol, dist, markerval, offset = 0, mapsize = MAXMAPSIZE;

	//CA6 STUFF
	NODE *LinkedListHead, *TempPtr = NULL, Temp[20] = {};
	LinkedListHead = NULL;
	char strlet[4], tempch, DrawCmd[10], tempint[3];

	//CA6 STUFF
	FILE *FH = OpenFile(argc, argv);
	ReadFileIntoLinkedList(FH, &LinkedListHead);

	//OTHER THINGS
    InitializeMap(Arry);

	//PROMPT FOR LETTERS
	printf("Please enter 1-3 letters: ");
	scanf("%s", strlet);
	while((strlen(strlet) > 3) || (strlen(strlet) < 1))
	{
		printf("Please enter 1-3 letters: ");
		scanf("%s", strlet);
	}

	for(int i = 0; i < strlen(strlet); i++)
	{
		tempch = toupper(strlet[i]);
		TempPtr = FindLetter(LinkedListHead, tempch, DrawCmd); 

		while(DrawCmd[0] != '\0')
		{	
			tok = strtok(DrawCmd,"(,)");
			drawtype = tok[0];

			tok = strtok(NULL,"(,)");
			strcpy(tempint, tok);
			introw = atoi(tempint);
			
			tok = strtok(NULL,"(,)");
			strcpy(tempint, tok);
			intcol = atoi(tok);
			
			tok = strtok(NULL,"(,)");
			strcpy(tempint, tok);
			dist = atoi(tok);
			
			tok = strtok(NULL,"|");
			marker = tok[0];

			TempPtr = FindLetter(TempPtr, tempch, DrawCmd);
			
			//if mark value not found, use X as default
			if(marker == '\n')
			{
				marker = 'X';
			}

			//Check for coordinate validity
			if((introw <= mapsize-1) && (introw >= 0) && (intcol <= mapsize-1) && (intcol >= 0)) 
			{
				if(drawtype == 'P') //if P, update array point with mark
				{
					DrawLine(Arry, introw, intcol + offset, drawtype, 1, marker);
				}
				else if(drawtype == 'V') //if V, call function DrawLine()
				{
					if((introw + dist-1) > mapsize-1)
					{
						printf("That draw command is out of range");
					}
					else
					{
						DrawLine(Arry, introw, intcol + offset, drawtype, dist, marker);
					}
				}
				else if(drawtype == 'H') //if H, call function DrawLine()
				{
					if((intcol + dist-1) > mapsize-1)
					{
						printf("That draw command is out of range");
					}
					else
					{
						DrawLine(Arry, introw, intcol + offset, drawtype, dist, marker);
					}
				}
				else //if anything else, prompt unknown command
				{
					printf("Unknown command inputed");
				}
			}
			else
			{
				printf("That draw command is out of range");
			}
			
		}

		offset = offset + 7;
	}
	PrintMap(Arry);
	return 0;
}