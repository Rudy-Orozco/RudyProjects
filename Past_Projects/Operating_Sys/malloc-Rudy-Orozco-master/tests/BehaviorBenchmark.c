#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main()
{
  clock_t start, end;
  double time;

  printf("Testing for behaviour\n");

    char * ptr1 = ( char * ) malloc( 10 );
    char * ptr2 = ( char * ) malloc( 29 );
    char * ptr3 = ( char * ) malloc( 140 );
    char * ptr4 = ( char * ) malloc( 449 );
    char * ptr5 = ( char * ) malloc( 700 );
    char * ptr6 = ( char * ) malloc( 1024 );
    char * ptr7 = ( char * ) malloc( 824 );
    char * ptr8 = ( char * ) malloc( 152 );
    char * ptr9 = ( char * ) malloc( 498 );
    char * ptr0 = ( char * ) malloc( 500 );

    free( ptr0 );
    free( ptr1 );
    free( ptr2 );
    free( ptr6 );
    free( ptr8 );

    start = clock();

    printf("Malloc 4 Different Ptrs\n");
    char * ptrA = ( char * ) malloc( 30 );
    char * ptrB = ( char * ) malloc( 9 );
    char * ptrC = ( char * ) malloc( 500 );
    char * ptrD = ( char * ) malloc( 5000 );
    char * ptrE = ( char * ) malloc( 5000 );
    char * ptrF = ( char * ) malloc( 5000 );
    char * ptrG = ( char * ) malloc( 5000 );

    end = clock();
    time = (double)(end-start);
    printf("Grow time: %f\n", time);

    free( ptr3 );
    free( ptr4 );
    free( ptr5 );
    free( ptr7 );
    free( ptr9 );
    free( ptrA );
    free( ptrB );
    free( ptrC );
    free( ptrD );
    free( ptrE );
    free( ptrF );
    free( ptrG );


  return 0;
}
