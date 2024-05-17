/* Rudy Orozco 1001864902*/

#include <stdio.h>

int main()
{
   //initiallizing Max and Mins
   int i_max, i_min, j_max, j_min, k_max, k_min;

   //Inputting Values
   printf("Enter i's starting value ");
   scanf("%d", &i_min);
   printf("Enter i's ending value ");
   scanf("%d", &i_max);

   printf("Enter j's starting value ");
   scanf("%d", &j_min);
   printf("Enter j's ending value ");
   scanf("%d", &j_max);

   printf("Enter k's starting value ");
   scanf("%d", &k_min);
   printf("Enter k's ending value ");
   scanf("%d", &k_max);   

   printf("\n");
   
   //For Loops
   for(int i = i_min; i < i_max; i++)
   {
      for(int j = j_min; j < j_max; j++)
      {
         for(int k = k_min; k < k_max; k++)
         {
            printf("*");
         }
         printf("\n");
      }
      printf("\n");
   }

   return 0;
}