// FileLib

#include <stdio.h>
#include <string.h>
#include "ListLib.h"

FILE *OpenFile(int argc, char *argv[])
{	
	/* declare various variables needed */
	FILE *FH = NULL;
	char filename[100];

	/* if argc is 2, then use argv[1] as the input file name, else print the message 
	seen in sample output */
	if(argc == 2)
	{
		strcpy(filename, argv[1]);
	}

	do
	{
		/* open file with "r" mode */
		FH = fopen(filename, "r");
		/* if file did not open */
		if(FH == NULL)
		{
			///* print message seen in sample output */
			printf("Must be run with an input file name.");
			///* read in new filename */
			scanf("%s", filename);
			///* open the file "r" mode */
			FH = fopen(filename, "r");
		}
	}
	while (FH == NULL);

	/* return the file handle */
	return FH;
}

void ReadFileIntoLinkedList(FILE *DCFile, NODE **LinkedListHead)
{
	/* declare various variables needed */
	char line[100], *tok;
	char letter, *drawcmd;
	
	/* while fgets() reads the file */
	while(fgets(line, 100, DCFile))
	{
		/* if line from file ends with \n, then replace \n with \0 */
		if(line[sizeof(line) - 1] == '\n')
		{
			line[sizeof(line) - 1] = '\0';
		}
		
		/* tokenize to get the Letter and the DrawCommand */
		tok = strtok(line, "|");
		letter = tok[0];

		tok = strtok(NULL, "|");
		drawcmd = tok;

		/* Call AddDrawCommandToList with correct parameters */
		AddDrawCommandToList(letter, drawcmd, LinkedListHead);
	}
}
