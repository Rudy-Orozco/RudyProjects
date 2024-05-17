#include <stdio.h>
#include <string.h>

void get_command_line_parameter(char *argv[], char Pname[], char Pvalue[])
{
    int i = 1;

    while (argv[i] != NULL)
    {
        if(!strncmp((argv[i]), Pname, strlen(Pname)))
        {
            strcpy(Pvalue, strchr(argv[i], '=') + 1);
        }
        i++;
    }
}

int main(int argc, char *argv[])
{
    char filename[100] = {"Hanger.txt"};

      char mode[2] = {"r+"};

      get_command_line_parameter(argv, "FILENAME=", filename);
      get_command_line_parameter(argv, "MODE=", mode);

      printf("%s%s", filename, mode);
    return 0;
}