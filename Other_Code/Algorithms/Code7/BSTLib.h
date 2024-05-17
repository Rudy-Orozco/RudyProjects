/* BSTLib For Coding Assignment 7 */

#ifndef _BST_LIB_H
#define _BST_LIB_H

typedef struct BNODE
{
    char *MovieTheaterName;
    char ZipCode[6];
    char *FileName;
    char Dimensions[6];	
    struct BNODE *left;
    struct BNODE *right;
} 
BNODE;

// First parameter - Address of BSTnode
// Second parameter - MovieTheaterName
// Third parameter - ZipCode
// Fourth parameter - FileName containing seat map (XXXOOOO)
// Fifth parameter - Dimensions of theater
void AddBSTNode(BNODE **, char [], char [], char [], char []);

// First parameter - BST node
// Prints the theater name and zip code
void InOrder(BNODE *);

// First parameter - BST node
// Second parameter - zipcode of movie theater being searched for
BNODE *SearchForBNODE(BNODE *, char []);



#endif
