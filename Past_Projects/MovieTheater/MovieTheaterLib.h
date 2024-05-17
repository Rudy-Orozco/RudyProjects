// MovieTheaterLib.h

#ifndef _MOVIETHEATERLIB_H
#define _MOVIETHEATERLIB_H

#define MAXROWS 10
#define MAXCOLS 10

#include "BSTLib.h"

void PrintSeatMap(char [][MAXCOLS], int, int);
int ReadMovieTheaterFile(char [][MAXCOLS], char [], int, int);
void WriteSeatMap(BNODE *, char [][MAXCOLS], int, int);

#endif
