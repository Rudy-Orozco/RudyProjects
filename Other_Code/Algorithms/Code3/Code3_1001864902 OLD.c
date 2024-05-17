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

    printf("\n");
}

void ReadFileIntoArry(FILE *filename, int *ArrayPtr)
{
    char charNumber[30];
    int intNumber, k = 0, sum = 0;

    // Check if file is found, otherwise exit ===============================
    if(filename == NULL)
    {
        printf("File must be provided on command line...exiting\n");
        exit(0);
    }

    //Store Numbers in Array
    while(fgets(charNumber, 100, filename))
	{
        intNumber = atoi(charNumber);
        *(ArrayPtr + k) = intNumber;
        
        sum = sum + intNumber;

        k++;
	}
}

void InsSort(int *ArrayPtr, int ArraySize)
{
    //Insertion Sort Code ===================================================
        int i, key, j;
        for (i = 1; i < ArraySize; i++) 
        {
            key = *(ArrayPtr+i);
            j = i - 1;

            while (j >= 0 && *(ArrayPtr+j) > key) 
            {
                *(ArrayPtr+j+1) = *(ArrayPtr+j);
                j = j - 1;
            }
            *(ArrayPtr + j + 1) = key;
    }
}

void merge(int *ArrayPtr, int left, int middle, int right) //COMEBACK TO THIS
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = *(ArrayPtr + left + i); 
    for (j = 0; j < n2; j++)
        R[j] = *(ArrayPtr + middle + 1 + j);

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            *(ArrayPtr + k) = L[i];
            i++;
        }
        else
        {
            *(ArrayPtr + k) = R[j];
            j++;
        }
        k++;
    } 
}

void mergeSort(int *ArrayPtr, int L, int R) //COMEBACK TO THIS
{
    if (L < R)
    {
        int M = (L+R)/2;
        mergeSort(ArrayPtr, L, M);
        mergeSort(ArrayPtr, M+1, R);
        merge(ArrayPtr, L, M, R);
    } 
}

int main(int argc, char *argv[])
{
    char charNumber[500];
    int intNumber, sum = 0, count = 0, k = 0, MC, IC;
    clock_t start, end;

    //Read and Store filename
    FILE *filename = fopen(argv[1], "r");

    // Check if file is found, otherwise exit
    if(filename == NULL)
    {
        printf("File must be provided on command line...exiting\n");
        exit(0);
    }

    // Check number of lines
    while(fgets(charNumber, 100, filename))
	{
        count++;
	}
    fseek(filename, 0, SEEK_SET); // Set to the beginning of the file

    int ArraySize = count;

    //Dynamic Alloc. (Decl. ArryPtr)
    int *ArrayPtr = NULL;                               
    ArrayPtr = (int*) malloc(ArraySize*sizeof(int));

    ReadFileIntoArry(filename, ArrayPtr);
    
    #ifdef PRINTARRAY
        PrintArray(ArrayPtr, ArraySize);
    #endif

    start = clock();
    mergeSort(ArrayPtr, 0, ArraySize-1); //COMEBACK TO THIS
    end = clock();

    MC = end-start;

    #ifdef PRINTARRAY
        PrintArray(ArrayPtr, ArraySize);
    #endif

    free(ArrayPtr);
    ArrayPtr = (int*) malloc(ArraySize*sizeof(int));

    ReadFileIntoArry(filename, ArrayPtr);

    #ifdef PRINTARRAY
        PrintArray(ArrayPtr, ArraySize);
    #endif

    start = clock();
    InsSort(ArrayPtr, ArraySize);
    end = clock();

    #ifdef PRINTARRAY
        PrintArray(ArrayPtr, ArraySize);
    #endif

    free(ArrayPtr);

    IC = end-start;

    printf("Processed %d records\n", count);
    printf("Merge Sort = %d\n", MC);
    printf("Insertion Sort = %d\n", IC);

    return 0;
}

/* 

NOTES:

-Weird Behavior with merge sort (Not Fully Sorted)
-Deal with Array Error with second part of Insertion Sort

*/