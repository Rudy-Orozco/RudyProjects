// FileLib.h

#ifndef _FILELIB_H_
#define _FILELIB_H_

void ReadFileIntoLinkedList(FILE *DCFile, NODE **LinkedListHead);
FILE *OpenFile(int argc, char *argv[]);

#endif