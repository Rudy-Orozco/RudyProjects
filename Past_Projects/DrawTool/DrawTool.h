// DrawTool.h

#ifndef _DRAWTOOL_H
#define _DRAWTOOL_H

#include <stdio.h>

#define MAXMAPSIZE 20

void InitializeMap(char [][MAXMAPSIZE], int*);
void DrawLine(char [][MAXMAPSIZE], int, int, char, int, char);
void PrintMap(char [][MAXMAPSIZE], int);
void PrintInstructions();

#endif
