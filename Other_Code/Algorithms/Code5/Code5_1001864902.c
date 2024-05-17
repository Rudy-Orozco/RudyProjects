/* CA5 Rudy Orozco 1001864902*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAXVERTICES 6

typedef struct 
{
 char label[6];
 int distance;
 int previous;
 int visited;
}
Vertex;

void DijkstraAlgo(int StartVertex, Vertex VertexArray[MAXVERTICES], int VertexCount, int AdjMatrix[MAXVERTICES][MAXVERTICES])
{
    int CurrentVertex = StartVertex, SmallestVertexIndex;
    VertexArray[StartVertex].distance = 0;
    VertexArray[StartVertex].previous = -1;
    VertexArray[StartVertex].visited = 1;    
    
    for(int x = 0; x < VertexCount-1; x++)
    {
        for(int i = 0; i < VertexCount; i++) // relaxing edges
        {
            if (AdjMatrix[CurrentVertex][i] != -1 && !VertexArray[i].visited) 
            {
                if (VertexArray[CurrentVertex].distance + AdjMatrix[CurrentVertex][i] < VertexArray[i].distance)
                {
                    VertexArray[i].distance = VertexArray[CurrentVertex].distance + AdjMatrix[CurrentVertex][i];
                    VertexArray[i].previous = CurrentVertex;
                }
            }
        }

        SmallestVertexIndex = -1;
        int SmallestVertex = INT_MAX;

        for(int i = 0; i < VertexCount; i++) // looking for smallest vertex
        {
            if (!VertexArray[i].visited)
            {
                if (VertexArray[i].distance < SmallestVertex)
                {
                    SmallestVertex = VertexArray[i].distance;
                    SmallestVertexIndex = i;
                }
            }
        }
        CurrentVertex = SmallestVertexIndex; // Update Current Vertex
        VertexArray[CurrentVertex].visited = 1;
    }

}

int main(int argc, char *argv[])
{
    int AdjMatrix[MAXVERTICES][MAXVERTICES] = {}, index = 0, location, weight;
    char buffer[50], VertexLabel[MAXVERTICES], *token;

    Vertex VertexArray[MAXVERTICES];

    //Initialize Matrix
    for(int i = 0; i < MAXVERTICES; i++)
    {
        for(int j = 0; j < MAXVERTICES; j++)
        {
            AdjMatrix[i][j] = -1;
        }
    }

    //Read and Store filename
    FILE *filename = fopen(argv[1], "r");

    // Check if file is found, otherwise exit
    if(filename == NULL)
    {
        printf("File must be provided on command line...exiting\n");
        exit(0);
    }

    // POPULATE ADJ MATRIX
    while(fgets(buffer, 50, filename))
	{
        token = strtok(buffer, ","); // Letter
        strcpy(VertexArray[index].label, token);

        while(token != NULL)
        {
            token = strtok(NULL, ","); // Location
            if(token != NULL)
            {
                location = atoi(token);
            }

            token = strtok(NULL, ","); // Weight
            if(token != NULL)
            {
                weight = atoi(token);
            }

            AdjMatrix[index][location] = weight;
        }

        index++;
    }

    //PRINT ADJMATRIX
    #ifdef PRINTIT
    printf("\n");
    for(int i = 0; i < MAXVERTICES; i++)
    {
        for(int j = 0; j < MAXVERTICES; j++)
        {
            printf("%2d\t", AdjMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    #endif

    // SETUP STARTING VERTEX
    char StartVertexLet[6], EndVertexLet[6];
    int StartVertex, EndVertex, dofv, dofu, cofuv, SmallestVertexIndex, VertexCount = index;

    // ASK FOR START
    printf("What is the starting vertex? ");
    scanf("%s", StartVertexLet);

    // INIT DIST, PREV, VISIT, AND START VERT
    for(int i = 0; i < MAXVERTICES; i++)
    {
        if(!strcmp(StartVertexLet, VertexArray[i].label))
        {
            StartVertex = i;
        }

        VertexArray[i].visited = 0;
        VertexArray[i].previous = -1;
        VertexArray[i].distance = INT_MAX;
    }

    // DIJKSTRA'S ALGO
    DijkstraAlgo(StartVertex, VertexArray, VertexCount, AdjMatrix);

    // PRINT VERTARRY
    #ifdef PRINTIT
    printf("\n");
    printf("I\tL\tD\tP\tV\n");
    for(int i = 0; i < VertexCount; i++)
    {
        printf("%d\t%s\t%d\t%d\t%d\n", i, VertexArray[i].label, VertexArray[i].distance, VertexArray[i].previous, VertexArray[i].visited);
    }
    printf("\n");
    #endif

    int CurrentVertPath, FinDistance, PathNDX = 0;
    char Path[MAXVERTICES][6];

    // ASK FOR DESTINATION
    printf("What is the destination vertex? ");
    scanf("%s", EndVertexLet);

    for(int i = 0; i < MAXVERTICES; i++)
    {
        if(!strcmp(EndVertexLet, VertexArray[i].label))
        {
            EndVertex = i;
        }
    }
    
    // DISTANCE
    FinDistance = VertexArray[EndVertex].distance;
    CurrentVertPath = EndVertex;

    // FINDING PATH
    while(CurrentVertPath != -1)
    {   
        strcpy(Path[PathNDX],VertexArray[CurrentVertPath].label);
        CurrentVertPath = VertexArray[CurrentVertPath].previous;

        PathNDX++;
    }

    // PRINTING PATH
    printf("The path from %s to %s is ", StartVertexLet, EndVertexLet);

    for(int i = PathNDX-1; i >= 0; i--)
    {
        printf("%s", Path[i]);

        if(i != 0)
        {
            printf("->");
        }
    }

    printf(" and has a length of %d\n", FinDistance);
}