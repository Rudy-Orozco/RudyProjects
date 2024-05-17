/*CA2 Rudy Orozco 1001864902*/
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>

void PrintArray(int *ArrayToPrint, int SizeAP)
{
    int i;
    for (i = 0; i < SizeAP; i++)
        printf("%d\n", *(ArrayToPrint + i));

    printf("\nProcessed %d Records", SizeAP);
}

void InsSort(int *ArrayPtr, int ArraySize)
{
    //Insertion Sort Code ===================================================
        int i, key, j;
        for (i = 1; i < ArraySize; i++) 
        {
            key = ArrayPtr[i];
            j = i - 1;

            while (j >= 0 && ArrayPtr[j] > key) 
            {
                ArrayPtr[j+1] = ArrayPtr[j];
                j = j - 1;
            }
            ArrayPtr[j + 1] = key;
    }
}

int ReadFileIntoArry(int **ArrayPtr, char argv[])
{
    char charNumber[30];
    int intNumber, k = 0, sum = 0, count = 0;

    //Read and Store filename
    FILE *filename = fopen(argv, "r");

    // Check if file is found, otherwise exit
    if(filename == NULL)
    {
        printf("File must be provided on command line...exiting\n");
        exit(0);
    }

    // Check number of lines
    while(fgets(charNumber, 30, filename)) // MOVE TO FUNCTION
	{
        count++;
	}
    fseek(filename, 0, SEEK_SET); 

    // MALLOC ARRAY
    *ArrayPtr = malloc(count*sizeof(int));

    //Store Numbers in Array
    while(fgets(charNumber, 30, filename))
	{
        intNumber = atoi(charNumber);
        (*ArrayPtr)[k] = intNumber;
        
        sum = sum + intNumber;

        k++;
	}

    return count;
}

int main(int argc, char *argv[])
{
    char charNumber[30];
    int intNumber, sum = 0, count = 0, k = 0;
    clock_t start, end;

    // Read File Into Array 
    int *ArrayPtr = NULL;                               
    int ArraySize = ReadFileIntoArry(&ArrayPtr, argv[1]);

    #ifdef PRINTARRAY
        PrintArray(ArrayPtr, ArraySize);
        printf("\n");
    #endif

    //Insertion Sort Code
    int i, key, j;
    start = clock();
    InsSort(ArrayPtr, ArraySize);
    end = clock();

    #ifdef PRINTARRAY
        PrintArray(ArrayPtr, ArraySize);
    #endif

    printf("Insertion Sort = %ld Tics\n", end-start);

    free(ArrayPtr);

    return 0;
}
