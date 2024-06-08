#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main()
{
  clock_t start, end;
  double time;
  int MAX_ITR = 50000;

  printf("Running PerfTest to test performance\n\n");

  char * ptr_array[MAX_ITR];

  printf("Growing Heap 1. 50,000 iterations / Random & Initial Run\n");
  start = clock();
  for (int i = 0; i < MAX_ITR; i+=5 )
  {
    ptr_array[i] = ( char * ) malloc ( 30 ); 
    ptr_array[i+1] = ( char * ) malloc ( 100 ); 
    ptr_array[i+2] = ( char * ) malloc ( 4900 ); 
    ptr_array[i+3] = ( char * ) malloc ( 900 ); 
    ptr_array[i+4] = ( char * ) malloc ( 97 ); 

    ptr_array[i] = ptr_array[i];
    ptr_array[i+1] = ptr_array[i+1];
    ptr_array[i+2] = ptr_array[i+2];
    ptr_array[i+3] = ptr_array[i+3];
    ptr_array[i+4] = ptr_array[i+4];
    
    //contRun = i;
  }
  end = clock();
  time = (double)(end-start)/CLOCKS_PER_SEC;

  printf("Malloc time: %f\n", time);

  start = clock();
  for (int i = 0; i < MAX_ITR; i++ )
  {
    free( ptr_array[i] );
    ptr_array[i] = NULL; 
  }
  end = clock();
  time = (double)(end-start)/CLOCKS_PER_SEC;
  printf("Free time: %f\n", time);

  // =================================================

  printf("Growing Heap 2. 50,000 iterations / Random & 2nd Run\n");
  start = clock();
  for (int i = 0; i < MAX_ITR; i+=5 )
  {
    ptr_array[i+1] = ( char * ) malloc ( 40 ); 
    ptr_array[i] = ( char * ) malloc ( 300 ); 
    ptr_array[i+3] = ( char * ) malloc ( 9000 ); 
    ptr_array[i+2] = ( char * ) malloc ( 26 ); 
    ptr_array[i+4] = ( char * ) malloc ( 17 ); 

    ptr_array[i] = ptr_array[i];
    ptr_array[i+1] = ptr_array[i+1];
    ptr_array[i+2] = ptr_array[i+2];
    ptr_array[i+3] = ptr_array[i+3];
    ptr_array[i+4] = ptr_array[i+4];
    
    //contRun = i;
  }
  end = clock();
  time = (double)(end-start)/CLOCKS_PER_SEC;
  printf("Malloc time: %f\n", time);
  

  //FREE
  start = clock();
  for (int i = 0; i < MAX_ITR; i++ )
  {
    free( ptr_array[i] );
    ptr_array[i] = NULL; 
  }

  end = clock();
  time = (double)(end-start)/CLOCKS_PER_SEC;
  printf("Free time: %f\n", time);

  return 0;
}
