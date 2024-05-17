/* BSTLib */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BSTLib.h"

// First parameter - Address of BSTnode
// Second parameter - MovieTheaterName
// Third parameter - ZipCode
// Fourth parameter - FileName containing seat map (XXXOOOO)
// Fifth parameter - Dimensions of theater
void AddBSTNode(BNODE **BSTnode, char MTN[], char ZC[], char FN[], char DIM[])
{
	// If passed in BNODE is empty, then current BNODE becomes root
    if (*BSTnode == NULL)
    {
        *BSTnode = malloc(sizeof(BNODE));
        
		(*BSTnode)->left = (*BSTnode)->right = NULL;
		
		(*BSTnode)->MovieTheaterName = malloc(strlen(MTN) * sizeof(char) + 1);
        strcpy((*BSTnode)->MovieTheaterName, MTN);
        strcpy((*BSTnode)->ZipCode, ZC);
		(*BSTnode)->FileName = malloc(strlen(FN) * sizeof(char) + 1);
        strcpy((*BSTnode)->FileName, FN);
        strcpy((*BSTnode)->Dimensions, DIM);
    }
    else
    {
        if (strcmp(ZC, (*BSTnode)->ZipCode) < 0)
			AddBSTNode(&(*BSTnode)->left, MTN, ZC, FN, DIM);
		
        else if(strcmp(ZC, (*BSTnode)->ZipCode) > 0)
            AddBSTNode(&(*BSTnode)->right, MTN, ZC, FN, DIM);
        
		else
            printf(" Duplicate Element !! Not Allowed !!!");

    }
}

// First parameter - BST node
void InOrder(BNODE *bnode)
{
    if(bnode != NULL)
    {
		InOrder(bnode->left);
        printf("%-40s %5s\n", bnode->MovieTheaterName, bnode->ZipCode);
		InOrder(bnode->right);
    }
}

// First parameter - BST node
// Second parameter - zipcode of movie theater being searched for
BNODE *SearchForBNODE(BNODE *BSTnode, char zip[])
{
	if (BSTnode == NULL || strcmp(BSTnode->ZipCode, zip) == 0)
	{
		return BSTnode;
	}

	if (strcmp(zip, BSTnode->ZipCode) < 0)
		return SearchForBNODE(BSTnode->left, zip);
		
    else if (strcmp(zip, BSTnode->ZipCode) > 0)
    	return SearchForBNODE(BSTnode->right, zip);
}
