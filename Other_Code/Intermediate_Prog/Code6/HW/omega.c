#include <stdio.h>
#include <string.h>
    

int main()
{
    FILE *MyFile;

    char buffer[20];

     

      MyFile = fopen("taxes2018", "r+");
      strcpy(buffer, "How are you?");
      fputs(buffer, MyFile);
      printf("The file pointer is %d ", ftell(MyFile));
      fseek(MyFile, 0, SEEK_SET);
      printf("The file pointer is %d\n", ftell(MyFile));

    return 0;
}

