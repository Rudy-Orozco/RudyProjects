/* Rudy Orozco 1001864902 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "DrawTool.h"

int main()
{
    //ARRAY
    char Arry[MAXMAPSIZE][MAXMAPSIZE];

    //INITIALIZING VARIABLES
    char *tok;
    char drawtype, marker, cmmdline[15], chdrawtype[3], chmarker[3];
    int introw, intcol, dist, markerval, mapsize;

    //OTHER THINGS
    InitializeMap(Arry, &mapsize);
    PrintInstructions();
    PrintMap(Arry, mapsize);

    printf("\nEnter draw command (enter Q to quit) "); //Prompt User
    fgets(cmmdline, 15, stdin); // Get string

    //Use strtok() to parse out DrawComand only to check for Q
    tok = strtok(cmmdline, "(),");
    strcpy(chdrawtype, tok);
    drawtype = toupper(chdrawtype[0]);

    while(drawtype != 'Q')
    {
        //Continue Parsing out Values
        tok = strtok(NULL, "(),");
        introw = atoi(tok);
            
        tok = strtok(NULL, "(),");
        intcol = atoi(tok);

        tok = strtok(NULL, "(),");
        dist = atoi(tok);
            
        tok = strtok(NULL, "");
        strcpy(chmarker, tok);
        marker = chmarker[0];

        //if mark value not found, use X as default
        if(marker == '\n')
        {
            marker = 'X';
        }

        //Check for coordinate validity
        if((introw <= mapsize-1) && (introw >= 0) && (intcol <= mapsize-1) && (intcol >= 0)) 
        {
            if(drawtype == 'P') //if P, update array point with mark
            {
                DrawLine(Arry, introw, intcol, drawtype, 1, marker);
            }
            else if(drawtype == 'V') //if V, call function DrawLine()
            {
                if((introw + dist-1) > mapsize-1)
                {
                    printf("That draw command is out of range");
                }
                else
                {
                    DrawLine(Arry, introw, intcol, drawtype, dist, marker);
                }
            }
            else if(drawtype == 'H') //if H, call function DrawLine()
            {
                if((intcol + dist-1) > mapsize-1)
                {
                    printf("That draw command is out of range");
                }
                else
                {
                    DrawLine(Arry, introw, intcol, drawtype, dist, marker);
                }
            }
            else //if anything else, prompt unknown command
            {
                printf("Unknown command inputed");
            }
        }
        else
        {
            printf("That draw command is out of range");
        }

        PrintMap(Arry, mapsize);

        //Ask for another command
        printf("\nEnter draw command (enter Q to quit) "); //Prompt User
        fgets(cmmdline, 15, stdin); // Get string

        //Use strtok() to parse out DrawComand only to check for Q
        tok = strtok(cmmdline, "(),");
        strcpy(chdrawtype, tok);
        drawtype = toupper(chdrawtype[0]);
    }

    return 0;
}