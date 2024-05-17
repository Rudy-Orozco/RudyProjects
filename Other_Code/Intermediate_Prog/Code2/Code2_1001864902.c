/* Rudy Orozco 1001864902*/

#include <stdio.h>
#include <string.h>
#define BITS 8

void ConvertDecimalToBinary(int dec, char bw[BITS]);

int main()
{
   int FirstNumber, SecondNumber, Result;
   char BitwiseOperator[3];
   char BinaryNum[BITS];
   
   //PROMPT AND SCAN
   printf("\nEnter two base 10 values with a bitwise operator to see the\ndecimal result and the binary result.\n\n");
   printf("Format is: FirstNumber BitwiseOperator SecondNumber\n\n");
   printf("For example, enter the expression\n\n2 & 3\n\n");
   printf("This calculator can be used with &, |, ^, << and >>\n\n");
   printf("Please note that the spaces between numbers and operator is essential\nand the two entered values must be between 0 and 255\n\n");
   printf("Enter Expression: ");
   scanf("%d %s %d", &FirstNumber, BitwiseOperator, &SecondNumber);

   //CHECKING FOR VALID RANGE
   while(((FirstNumber < 0) || (FirstNumber > 255)) || ((SecondNumber < 0) || (SecondNumber > 255)))
   {
      printf("Invalid Number/Operator. Enter Expression: ");
      scanf("%d %s %d", &FirstNumber, BitwiseOperator, &SecondNumber);
   }

   //CHECKING FOR VALID OPERATOR & CALCULATION
   if((strcmp(BitwiseOperator, "&") == 0) || (strcmp(BitwiseOperator, "|") == 0) || (strcmp(BitwiseOperator, "^") == 0) || (strcmp(BitwiseOperator, "<<") == 0) || (strcmp(BitwiseOperator, ">>") == 0))
   {
      printf("In Base 10\n\n");
      if(strcmp(BitwiseOperator, "&") == 0)
      {
         Result = FirstNumber & SecondNumber;
      
         printf("%d %s %d = %d\n\n", FirstNumber, BitwiseOperator, SecondNumber, Result);
      }
      else if(strcmp(BitwiseOperator, "|") == 0)
      {
         Result = FirstNumber | SecondNumber;
      
         printf("%d %s %d = %d\n\n", FirstNumber, BitwiseOperator, SecondNumber, Result);
      }
      else if(strcmp(BitwiseOperator, "^") == 0)
      {
         Result = FirstNumber ^ SecondNumber;
      
         printf("%d %s %d = %d\n\n", FirstNumber, BitwiseOperator, SecondNumber, Result);
      }
      else if(strcmp(BitwiseOperator, "<<") == 0)
      {
         Result = FirstNumber << SecondNumber;
      
         printf("%d %s %d = %d\n\n", FirstNumber, BitwiseOperator, SecondNumber, Result);
      }
      else if(strcmp(BitwiseOperator, ">>") == 0)
      {
         Result = FirstNumber >> SecondNumber;
      
         printf("%d %s %d = %d\n\n", FirstNumber, BitwiseOperator, SecondNumber, Result);
      }

      //PRINTING THE RESULT IN BINARY
      printf("In %d-Bit base 2...\n\n   ", BITS);

      ConvertDecimalToBinary(FirstNumber, BinaryNum);
      printf("%s", BinaryNum);

      printf("\n  %s\n   ", BitwiseOperator);

      ConvertDecimalToBinary(SecondNumber, BinaryNum);
      printf("%s", BinaryNum);

      printf("\n   ");

      for(int i = 0; i < BITS; i++)
      {
         printf("=");
      }
      printf("\n   ");

      ConvertDecimalToBinary(Result, BinaryNum);
      printf("%s", BinaryNum);

      printf("\n");
   }
   else
   {
      printf("Invalid Operator Inputted, Terminating Program\n\n");
   }

   return 0;
}

void ConvertDecimalToBinary(int dec, char bw[BITS])
{
   int tmparry[BITS];

   for(int i = 0; i < BITS; i++)
   {
      int check;

      check = dec & 1;
      tmparry[i] = check;
      
      dec = dec >> 1;
   }

   // REVERSING ORDER & CONVERTING INT TO CHAR
   for(int i = (BITS-1); i >= 0; i--)
   {
      int revtmp;
      revtmp = tmparry[i] + 48;
      bw[BITS -1 - i] = revtmp;
   }
}