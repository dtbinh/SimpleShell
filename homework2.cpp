#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector> // std::vector
#include <algorithm> // std::copy
#include "homework3.h"

#define PARSED_COMMAND_LEN 20

Options parseTheCommand(char command[], char *parsedCommand[]);
void getCommandFromUser (char command[]);
void freeArray(char* array[]);

// This function simply reads input from the user up until a newline is read.
// The max number of characters it will read is 256 corresponding to the size of 
// our destination array 'command[]'. 
void getCommandFromUser(char command[]) {
  fgets(command, 256, stdin);
}


// This function tokenizes the input string into arguments for the command to execute
// and puts the result in the parsedCommand array.
Options parseTheCommand(char command[], char *parsedCommand[]) {
  // Pointer to the tokenized argument from command string.
  char* arg = strtok(command, " \n");
  int counter = 0;
  char* prvArg = NULL;
  Options selected;

  // Run loop until strtok reads a NULL value or we read in too many arguments for the array.
  while (arg != NULL && counter < PARSED_COMMAND_LEN) {
    prvArg = arg;

    // Allocate memory in parsedCommand to hold current argument
    parsedCommand[counter] = (char *) malloc(sizeof(arg));
    strcpy(parsedCommand[counter], arg);
    counter++;

    // Check if the last agument read was &. If so set background to 1, otherwise to 0.
    // This ensures that the command only runs in the background if the last character 
    // in the array is &.
    if(*prvArg == '&')
      selected.background = 1;
    else {
      selected.background = 0;
    }

    if(!strcmp(arg, ">>")) {
        selected.redirect = 1;
        selected.splitChar = counter - 1;
    } else if(*arg == '|') {
        selected.pipe = 1;
        selected.splitChar = counter - 1;
    }

    // Read the next token from the buffer without adding anything more to it.
    arg = strtok(NULL, " \n");
  }

  // Set the element after the last element to NULL. Overwrite the & char if running in the background.
  if(selected.background) {
    free(parsedCommand[counter-1]);
    parsedCommand[counter-1] = NULL;
  }
  else
    parsedCommand[counter] = NULL;

  return selected;
}

// Function for freeing memory allocated to the parsedCommand array.
void freeArray(char* array[]) {
    int i = 0;
    while (array[i] != NULL && i < PARSED_COMMAND_LEN) {
        free(array[i]);
        array[i] = NULL;
        i++;
    }
}

int handleRedirectOrPipe(char* parsedCommand[], Options selected) {
    int split = selected.splitChar;
    
    std::vector<char*> firstHalf(split);
    std::copy(parsedCommand, parsedCommand+split+1, firstHalf.begin());
    firstHalf[split] = NULL;

    std::vector<char*> secondHalf(PARSED_COMMAND_LEN-split);
    std::copy(parsedCommand+split+1, parsedCommand+PARSED_COMMAND_LEN, secondHalf.begin());

    if(selected.redirect) {
        redirect(&firstHalf[0], secondHalf[0]);
        exit(0);
    }

    return 0;
}

int main()
{
  char commandline[256];
  char  *parsedCommand[PARSED_COMMAND_LEN];
  int   background = 0;
  Options selected;
  pid_t pid;
  printf ("\nMyshell> ");
  getCommandFromUser (commandline);
  selected = parseTheCommand(commandline, parsedCommand);
  background = selected.background;
  while((strcmp (commandline,"exit") != 0)
     && (strcmp (commandline,"quit") != 0))
  {
    if ( (pid = fork ())== 0)
    {
      if(selected.redirect == 1 || selected.pipe == 1) {
          handleRedirectOrPipe(parsedCommand, selected);
      } else {
          execvp(parsedCommand[0], parsedCommand);
          printf("\'%s\'", parsedCommand[0]);
          perror("execvp failed");
          exit(1);
      }
    }
    else
    {
      if(!background)
        waitpid(pid, NULL, 0);
      freeArray(parsedCommand);
      printf ("\nMyshell> ");
      strcpy (commandline, "\0");
      getCommandFromUser (commandline);
      selected = parseTheCommand(commandline, parsedCommand);
      background = selected.background;
    }
  }
}
