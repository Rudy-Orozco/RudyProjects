// DrawTool.c

#include <stdio.h>
#include "DrawTool.h"

void InitializeMap(char Map[][MAXMAPSIZE], int *MyMapSize)
{
	int j, k;
	char Background = ' ';
	
	printf("How big is the array? (Enter a value between 1 and %d) ", MAXMAPSIZE);
	scanf("%d", MyMapSize);

	while (*MyMapSize < 1 || *MyMapSize > MAXMAPSIZE)
	{
		printf("That value is outside of the max bounds of the array.  Please reenter\n\n");
		printf("How big is the array? (Enter a value between 1 and %d) ", MAXMAPSIZE);
		scanf("%d", MyMapSize);
	}
	
	printf("What is the background character? ");
	scanf(" %c", &Background);
	
	/* Initialize Map to the entered background character */
	for (j = 0; j < *MyMapSize; j++)
	{
		for (k = 0; k < *MyMapSize; k++)
		{
			Map[j][k] = Background;
		}
	}
}

void DrawLine(char Map[][MAXMAPSIZE], int from, int to, char LineType, int count, char mark)
{
	int j;
	
	if (LineType == 'H')     
	{
		for (j = 0; j < count; j++)
		{
			Map[from][to+j] = mark;
		}	
	}
	else
	{	
		for (j = 0; j < count; j++)
		{
			Map[from+j][to] = mark;
		}		
	}
}

void PrintMap(char Map[][MAXMAPSIZE], int MyMapSize)
{
	int i, j;
	
	printf("\n\n");
	
	for (i = 0; i < MyMapSize; i++)
	{
		for (j = 0; j < MyMapSize; j++)
		{
			printf("%c  ", Map[i][j]);
		}
		printf("\n");
	}
}	

void PrintInstructions()
{
	printf("\nDraw commands start with\n\n\tP for a single point\n\tH for a horizontal line\n\t"
	       "V for a vertical line\n\n");
	printf("After the P/V/H, enter a row,col coordinate and the "
	       "number of spots to mark\nenclosed in () and separated by commas and then the "
		   "character for the mark.\n\'X\' will be used if a mark is not entered.  "
		   "For example,\n\n\tP(2,3,1)* \tstart at "
		   "point 2,3 in the array and mark one spot\n\t\t\t"
		   "with an *.  For P, the 3rd parameter is ignored.\n\n");
	printf("\tV(1,2,3)$ \tstart at point 1,2 in the array and mark the next\n"
    	   "\t\t\t3 spots to the right with $\n\n");
	printf("\tH(4,6,7)# \tstart at point 4,6 in the array and mark the next\n"
    	   "\t\t\t7 spots down from the current position with #\n");		   
	printf("\nCoordinates out of range and lines drawn past the borders are not allowed.\n");
	printf("\nEnter Q at the draw command prompt to quit\n");
	printf("\nPress <ENTER> to continue");
	getchar();
}
