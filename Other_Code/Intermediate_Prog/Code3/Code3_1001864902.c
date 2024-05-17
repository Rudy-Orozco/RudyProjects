/* Rudy Orozco 1001864902*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void BingoPrint(int BingArray[5][5]);
void BingoFill(int BingArray[5][5]);
int PickNum(int Number, int Count, int ChoiceArry[]);
int CheckNumber(int Number, int PntArray[5][5]);
int CompRow(int PntArray[5][5]);
int CompCol(int PntArray[5][5]);
int CompDiag(int PntArray[5][5]);

int main()
{
    int BingArray[5][5], ChoiceArry[75];
    int Number, CN, Count = 0, NumFlag = 0;
    char YN;

    // Initialize Rand
    srand(time(0));

    // Fill Bingo Card and Print Screen
    BingoFill(BingArray);
    BingoPrint(BingArray);

    // Start of game
    while((Count < 75) && ((CompRow(BingArray) + CompCol(BingArray) + CompDiag(BingArray)) == 0))
    {
        Number = ChoiceArry[Count] = PickNum(Number, Count, ChoiceArry);

        printf("Do you have it? (Y/N) :");
        scanf(" %c", &YN);

        if(YN == 'Y')
        {
            CN = CheckNumber(Number, BingArray);

            if(CN == 0)
            {
                printf("That value is not on your BINGO card - stop cheating.\n");
            }
        }

        BingoPrint(BingArray);

        Count++;
    }

    // Checking Result
    if(Count == 75)
    {
        printf("Ran out of Numbers. Game Over.");
    }
    else
    {
        switch (CompRow(BingArray) + CompCol(BingArray) + CompDiag(BingArray))
        {
        case 3:
            printf("You filled out a Row - BINGO!");
            break;
        case 4:
            printf("You filled out a Column - BINGO!");
            break;
        case 5:
            printf("You filled out a Diagonal - BINGO!");
            break;
        default: //FOR MULTIPLE FILLED LINES
            printf("You filled out multiple things! - BINGO!");
            break;
        }
    }
    
    return 0;
}

void BingoPrint(int BingArray[5][5])
{
    //Title
    printf("\n   B    I    N    G    O\n");
    printf("--------------------------\n");
    
    //Numbers and Replace 0 with X
    for(int j = 0; j < 5; j++ )
    {
        printf("|");
        for(int i = 0; i < 5; i++)
        {
            if(BingArray[i][j] == 0)
            {
                printf("  X |");
            }
            else
            {
                printf(" %2d |", BingArray[i][j]);
            }
        }
        printf("\n--------------------------\n");
    }
}

void BingoFill(int BingArray[5][5]) //USED ONLY ONCE
{
    // Initialize Random Numbers
    int tmpArry[5];
    int start = 1, end = 15;

    // Filling the Bingo Card
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            int tab = 0, count = 0;
            int randNum = rand() % (end-start+1) + start;
            
            //Checking for Duplicates
            for(int i = 0; i < 5; i++)
            {
                if(tmpArry[i] == randNum)
                {
                    randNum = rand() % (end-start+1) + start;
                }
                else
                {
                    i++;
                }
            }
            BingArray[i][j] = tmpArry[j] = randNum;
        }
        
        //Increment to the next Column Limits
        start = start + 15;
        end = end + 15;
    }
    BingArray[2][2] = 0;
}

int PickNum(int Number, int Count, int ChoiceArry[])
{
    Number = rand() % (75-1+1) + 1;

    for(int i = 0; i < Count; i++)
    {
        if(Number == ChoiceArry[i])
        {
            Number = rand() % (75-1+1) + 1;
            i = 0;
        }
    }

    if((Number >= 1) && (Number <= 15))
    {
        printf("Your next number is B%d\n\n", Number);
    }
    else if((Number >= 16) && (Number <= 30))
    {
        printf("Your next number is I%d\n\n", Number);
    }
    else if((Number >= 31) && (Number <= 45))
    {
        printf("Your next number is N%d\n\n", Number);
    }
    else if((Number >= 46) && (Number <= 60))
    {
        printf("Your next number is G%d\n\n", Number);
    }
    else if((Number >= 61) && (Number <= 75))
    {
        printf("Your next number is O%d\n\n", Number);
    }

    return Number;
}

int CheckNumber(int Number, int PntArray[5][5])
{
    int NumFlag = 0, x, y;
    char YN;

    for(int j = 0; j < 5; j++ )
    {
        for(int i = 0; i < 5; i++)
        {
            if(Number == PntArray[i][j])
            {
                PntArray[i][j] = 0;
                NumFlag = 1;
                x = i;
                y = j;
            }
        }
    }

    return NumFlag;
}

int CompRow(int PntArray[5][5])
{
    int sum = 0, NumFlag = 0;

    for(int j = 0; j < 5; j++)
    {
        for(int i = 0; i < 5; i++)
        {
            sum = sum + PntArray[i][j];
        }

        if(sum == 0)
        {
            NumFlag = 3;
        }
        sum = 0;
    }

    return NumFlag;
}

int CompCol(int PntArray[5][5])
{
    int sum = 0, NumFlag = 0;

    for(int j = 0; j < 5; j++)
    {
        for(int i = 0; i < 5; i++)
        {
            sum = sum + PntArray[j][i];
        }
        
        if(sum == 0)
        {
            NumFlag = 4;
        }
        sum = 0;
    }

    return NumFlag;
}

int CompDiag(int PntArray[5][5])
{
    int sum1 = 0, sum2 = 0, NumFlag = 0;
    
    for(int i = 0; i < 5; i++) 
    {
        sum1 = sum1 + PntArray[i][i]; // FOR BACKWARD DIAGONAL [\]
        sum2 = sum2 + PntArray[i][4-i]; // FOR FORWARD DIAGONAL [/]
    }
    if((sum1 == 0) || (sum2 == 0))
    {
        NumFlag = 5;
    }

    return NumFlag;
}