// DrawTool.c

#include "DrawTool.h"

void InitializeMap(char Map[][MAXMAPSIZE])
{
	int j, k;
	char Background = ' ';
	
	printf("What is the background character? ");
	scanf(" %c", &Background);
	
	/* Initialize Map to the entered background character */
	for (j = 0; j < MAXMAPSIZE; j++)
	{
		for (k = 0; k < MAXMAPSIZE; k++)
		{
			*(*(Map + j) + k) = Background;
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
			*(*(Map + from) + (to+j)) = mark;
//			Map[from][to+j] = mark;
		}	
	}
	else
	{	
		for (j = 0; j < count; j++)
		{
			*(*(Map + (from+j)) + to) = mark;			
//			Map[from+j][to] = mark;
		}		
	}
}

void PrintMap(char Map[][MAXMAPSIZE])
{
	int i, j;
	
	printf("\n\n");
	
	for (i = 0; i < MAXMAPSIZE; i++)
	{
		for (j = 0; j < MAXMAPSIZE; j++)
		{
//			printf("%c  ", Map[i][j]);
			printf("%c  ", *(*(Map + i) + j));
		}
		printf("\n");
	}
}	
