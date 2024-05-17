/*CA4 Rudy Orozco 1001864902*/
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>

void PrintArray(int *ArrayToPrint, int SizeAP)
{
    int i;
    for (i = 0; i < SizeAP; i++)
        printf("%d\n", ArrayToPrint[i]);

    printf("\n");
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

void merge(int *ArrayPtr, int left, int middle, int right) //COMEBACK TO THIS
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = ArrayPtr[left + i]; 
    for (j = 0; j < n2; j++)
        R[j] = ArrayPtr[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            ArrayPtr[k] = L[i];
            i++;
        }
        else
        {
            ArrayPtr[k] = R[j];
            j++;
        }
        k++;
    } 

    while (i < n1)
    {
        ArrayPtr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        ArrayPtr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int *ArrayPtr, int L, int R) 
{
    if (L < R)
    {
        int M = (L+R)/2;
        mergeSort(ArrayPtr, L, M);
        mergeSort(ArrayPtr, M+1, R);
        merge(ArrayPtr, L, M, R);
    } 
}

void QuickSort(int A*, int low, int high) 
{ 
    if (low < high) 
    { 
        int ndx = partition(A, low, high); 
        QuickSort(A, low, ndx - 1); 
        QuickSort(A, ndx + 1, high); 
    } 
}

int partition (int A*, int low, int high) 
{ 
    int i, j = 0;
    int pivot = A[high];
    i = (low - 1); 

    for (j = low; j < high; j++) 
    { 
        if (A[j] < pivot) 
        { 
            i++; 
            swap(&A[i], &A[j]); 
        } 
    } 
    swap(&A[i + 1], &A[high]); 
    return (i + 1); 
}

void swap(int *SwapA, int *SwapB) 
{ 
    int temp = *SwapA; 
    *SwapA = *SwapB; 
    *SwapB = temp; 
}

int main(int argc, char *argv[])
{
    char charNumber[500];
    int intNumber, sum = 0, count = 0, k = 0, MC, IC, ArraySize;
    clock_t start, end;

    //Dynamic Alloc. (Decl. ArryPtr)
    int *ArrayPtr = NULL;

    // READFILE FOR MS (Pass in Address of ArrayPtr) ===========================================================================
    ArraySize = ReadFileIntoArry(&ArrayPtr, argv[1]);
    
    #ifdef PRINTARRAY
        PrintArray(ArrayPtr, ArraySize-1);
    #endif

    start = clock();
    mergeSort(ArrayPtr, 0, ArraySize-1); 
    end = clock();

    MC = end-start;

    #ifdef PRINTARRAY
        PrintArray(ArrayPtr, ArraySize);
    #endif

    free(ArrayPtr);

    // READFILE FOR IS ===========================================================================================================
    ArraySize = ReadFileIntoArry(&ArrayPtr, argv[1]);

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

    // READFILE FOR QS ===========================================================================================================
    ArraySize = ReadFileIntoArry(&ArrayPtr, argv[1]);

    #ifdef PRINTARRAY
        PrintArray(ArrayPtr, ArraySize);
    #endif

    start = clock();
    QuickSort(&ArrayPtr, 0, ArraySize-1);
    end = clock();

    #ifdef PRINTARRAY
        PrintArray(ArrayPtr, ArraySize);
    #endif

    free(ArrayPtr);

    IC = end-start;
    
    //PRINT RESULT ================================================================================================================
    printf("Processed %d records\n", ArraySize);
    printf("Merge Sort = %d\n", MC);
    printf("Insertion Sort = %d\n", IC);

    return 0;
}

/* 

NOTES:

-Weird Behavior with merge sort (Not Fully Sorted)
-Deal with Array Access / Free() with second part of Insertion Sort

*/