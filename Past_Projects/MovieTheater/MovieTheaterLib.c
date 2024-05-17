// MovieTheaterLib

#include <stdio.h>
#include <string.h>
#include "MovieTheaterLib.h"

void PrintSeatMap(char MovieTheaterMap[][MAXCOLS], int row, int col)
{
	int i, j;

	printf("\n\n\t");
	for (i = 1; i <= col; i++)
	{
		printf("Seat%-3d", i);		
	}
	printf("\n");
	
	for (i = 0; i < row; i++)
	{
		printf("Row %c\t", i+65);
		for (j = 0; j < col; j++)
		{
			printf("%-7c", MovieTheaterMap[i][j]);
		}
		printf("\n");
	}
//	printf("\n\n");	
}

int ReadMovieTheaterFile(char MovieTheaterMap[][MAXCOLS], char FileName[], int row, int col)
{
	FILE *MapFile;
	char MapLine[MAXROWS*MAXCOLS+10]={};
	int i, j, k = 0;
	
	MapFile = fopen(FileName, "r+");
	if (MapFile == NULL)
	{
		printf("\nFile \"%s\" did not open\n\n", FileName);
		return 0;
	}
	
	fgets(MapLine, sizeof(MapLine)-1, MapFile);
	
	if (strlen(MapLine) != row*col)
		return 0;
	
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			MovieTheaterMap[i][j] = MapLine[k++];
		}
	}
	
	fclose(MapFile);
	
	return 1;
}

void WriteSeatMap(BNODE *MyTheater, char MovieTheaterMap[][MAXCOLS], int MapRow, int MapCol)
{
	FILE *MapFile;
	int i, j, k = 0;
	char MovieTheaterLine[MapRow*MapCol];
	
	MapFile = fopen(MyTheater->FileName, "w+");
	if (MapFile == NULL)
	{
		printf("\nFile \"%s\" did not open\n\n", MyTheater->FileName);
	}
	
	for (i = 0; i < MapRow; i++)
	{
		for (j = 0; j < MapCol; j++)
		{
			MovieTheaterLine[k++] = MovieTheaterMap[i][j];
		}
	}		
	MovieTheaterLine[k] = '\0';
	
	fputs(MovieTheaterLine, MapFile);
	fclose(MapFile);
}
