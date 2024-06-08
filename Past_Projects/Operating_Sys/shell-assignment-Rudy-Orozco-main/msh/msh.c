// The MIT License (MIT)
// 
// Copyright (c) 2024 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 32     

int main(int argc, char *argv[])
{

  char * command_string = (char*) malloc( MAX_COMMAND_SIZE );
  FILE *filename;

  
  //BATCH MODE SETUP
  if(argc == 2)
  {
    filename = fopen(argv[1],"r");
    if(filename == NULL)
    {
      char error_message[30] = "An error has occurred\n";
      write(STDERR_FILENO, error_message, strlen(error_message));
      exit(1);
    }
  }
  else if(argc > 2)
  {
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1); 
  }

  while( 1 )
  {
    // BATCH MODE
    if(argc == 2)
    {
      if(fgets(command_string, MAX_COMMAND_SIZE, filename) == NULL) // Read line, if EOF, exit.
      {
        exit(0);
      }
    }

    // INTERACTIVE MODE
    if(argc == 1)
    {
      // Print out the msh prompt
      printf ("msh> ");

      // Read the command from the commandi line.  The
      // maximum command that will be read is MAX_COMMAND_SIZE
      // This while command will wait here until the user
      // inputs something.
      while( !fgets (command_string, MAX_COMMAND_SIZE, stdin) );
    }
    /* Parse input */
    char *token[MAX_NUM_ARGUMENTS];

    int token_count = 0;                                 
                                                           
    // Pointer to point to the token
    // parsed by strsep
    char *argument_pointer;                                         
                                                           
    char *working_string  = strdup( command_string );                

    // we are going to move the working_string pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    
    char *head_ptr = working_string;
    
    // Tokenize the input with whitespace used as the delimiter
    while ( ( (argument_pointer = strsep(&working_string, WHITESPACE ) ) != NULL) &&
              (token_count<MAX_NUM_ARGUMENTS))
    {
      token[token_count] = strndup( argument_pointer, MAX_COMMAND_SIZE );
      if( strlen( token[token_count] ) == 0 )
      {
        token[token_count] = NULL;
      }
        token_count++;
    }

    // Now print the tokenized input as a debug check
    // \TODO Remove this code and replace with your shell functionality
/*
    int token_index  = 0;
    for( token_index = 0; token_index < token_count; token_index ++ ) 
    {
      printf("token[%d] = %s\n", token_index, token[token_index] );  
    }
*/
    //char dir[200];
    
    //DEAL WITH WHITE SPACE =======================================================================
    //Find First Token
    int startTok = 0;
    int secTok = 0;
    char *splitToken[MAX_NUM_ARGUMENTS];
    while((token[startTok] == NULL) && (startTok <= MAX_NUM_ARGUMENTS))
    {
      startTok++;
    }
    
    // DEAL WITH WHITESPACE
    for(int i = startTok; i < token_count; i++)
    {
      if(token[i] != NULL)
      {
        splitToken[secTok] = malloc(strlen(token[i]) + 1);
        strcpy(splitToken[secTok], token[i]);
        secTok++;
      }

    }
    splitToken[secTok] = NULL;


    //CHECK FOR BUILT IN COMMANDS ================================================================
    
    if((startTok <= MAX_NUM_ARGUMENTS) && (splitToken[0] != NULL)) //DEAL WITH EMPTY INPUTS
    {
      if(strcmp(splitToken[0],"exit") == 0)     // EXIT COMMAND
      {
        if(splitToken[1] != NULL)
        {
          char error_message[30] = "An error has occurred\n";
          write(STDERR_FILENO, error_message, strlen(error_message)); 
        }
        else
        {
          exit(0);
        }
      }
      else if(strcmp(splitToken[0],"cd") == 0)      // CD COMMAND
      { 
        if(splitToken[1] == NULL || splitToken[2] != NULL)
        {
          char error_message[30] = "An error has occurred\n";
          write(STDERR_FILENO, error_message, strlen(error_message)); 
        }
        else
        {
          chdir(splitToken[1]);
          //printf("%s\n", getcwd(dir, 200));
        }
      }
      else 
      { 
        /*
          1. Check for redirect
          2. Exec commands
          3. executable files
        */

      // CHECK FOR REDIRECT ============================================================
      int redir = 0;
      int err = 0;
      int stat;

      for(int i = 0; i < secTok; i++)
      {
        if( strcmp( splitToken[i], ">" ) == 0 )
        {
          redir = 1;
          if((splitToken[i+1] == NULL) || (splitToken[i+2] != NULL) ||  strcmp( splitToken[0], ">" ) == 0 ) // if no file was given || if there is more than one file || if there is not input
          {
            err = 1;
          }     
        }
      }
      if((redir == 1) && (err == 0)) // IF THERE ARE NO ERRORS
      {
        pid_t pid = fork();

        if( pid == 0 )
        {
            // Iterate over the provided command and see if there is a redirect
            // operator in it.  If there is then open a pipe between 
            
            for(int i=1; i<secTok; i++ )
            {
              if( strcmp( splitToken[i], ">" ) == 0 )
              {
                  int fd = open( splitToken[i+1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );
                  if( fd < 0 )
                  {
                    perror( "Can't open output file." );
                    exit( 0 );                    
                  }
                  printf("check/n");
                  
                  dup2(fd, STDOUT_FILENO);
                  close( fd );
                  
                  // TRIM >
                  splitToken[i] = NULL;
              }
            }
            execvp(splitToken[0], splitToken); 
            waitpid(pid, &stat, 0 );
        }
        else if( pid > 0 )
        {
          wait( NULL );
        }
        else
        {
          perror( "Fork failed." );
        }
      }

      // IF THERE IS ANY REDIR ERROR
      if((redir == 1) && (err == 1))
      {
        char error_message[30] = "An error has occurred\n";
        write(STDERR_FILENO, error_message, strlen(error_message)); 
      }

      // CHECK FOR ANY EXEC COMMANDS =======================================================================
      if(redir != 1)
      {
        pid_t pid = fork();

        if(pid == 0)
        {
          execvp(splitToken[0], splitToken); 
          exit(EXIT_SUCCESS);
        }
        waitpid(pid, &stat, 0 );

        // CHECK FOR ANY OTHER COMMANDS ==================================================================
        int acc = 0;
        char path1[MAX_COMMAND_SIZE] = "/bin/";
        char path2[MAX_COMMAND_SIZE] = "/usr/bin/";
        char path3[MAX_COMMAND_SIZE] = "/usr/local/bin/";
        char path4[MAX_COMMAND_SIZE] = "./";
        for(int i = 0; i < strlen(splitToken[0]); i++)
        {
          if(splitToken[0][i] == '.')
          {
            acc = 1;
          }
        }
        if(acc == 1)
        {
          strcat(path1, splitToken[0]);
          strcat(path2, splitToken[0]);
          strcat(path3, splitToken[0]);
          strcat(path4, splitToken[0]);
          if((access(path4, X_OK) != 0) && (access(path3, X_OK) != 0) && (access(path2, X_OK) != 0) && (access(path1, X_OK) != 0))
          {
            char error_message[30] = "An error has occurred\n";
            write(STDERR_FILENO, error_message, strlen(error_message)); 
          }
        }
      }
      }
    }

      for(int i = 0; i < token_count; i++) // FREE MALLOCS
      {
        splitToken[i] = NULL;
        free(splitToken[i]);
      }

      /* 
      
      check if ls first token is true
      check if there is another agument, otherwise exec ls
      if there is another argument, check type, if no other argumetns are needed, exec
      if there is an addiontal, exec.

      */
    free(head_ptr);
    
  }
  fclose(filename);

  return 0;
  // e2520ca2-76f3-90d6-0242ac1210022
}

