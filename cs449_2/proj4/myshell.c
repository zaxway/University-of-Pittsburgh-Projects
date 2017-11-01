#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>




int main() {
  char* command[100];
  int count = 0; // number of arguments that the user enters
  const char* delim = " \t\n()|&;";
  char* token;
  char* tokens[200]; // represents seperate tokens
  int isValid = 0;
  char* ptr;
  int exit_num = 0;
  char* dir;
  int stack = 0;
  //signal(SIGINT, sighandler);

  while(1) {
    // read command from user
    printf("myshell> ");
    fgets(&command, sizeof(command), stdin);
    // now command has something in it.


    // then parse the commmand


  	token = strtok(command, delim);
  	for(count = 0; token != NULL; count++)
  	{
  		//printf("token %d: '%s'\n", i, token);
      tokens[count] = token; // stores split up parts in array of tokens
  		token = strtok(NULL, delim);
  	}
    // we have parsed it and at this point we have the total number of arguments and
    // seperate tokens for the command tokens[0] and the arguments token[1 to count]

    // next check if the command is valid
    isValid = command_is_valid(tokens);

    if (isValid = 0) {
      // run the command along with its arguments
      if(strcmp(tokens[0], "exit") == 0) {
        if(tokens[1] != NULL) {
          exit_num = strtol(tokens[1], &ptr, 10);
        }
        printf("Exited with code %d\n", exit_num);
        exit(0);
      }
      else if(strcmp(tokens[0], "cd") == 0) {
        chdir(tokens[1]);
        if (chdir(tokens[1]) == -1) {
          printf("Error!\n");
        }
      }
      else if (strcmp(tokens[0], "pushd")) {
        if (stack > 4) {
          printf("Error!\n");
        }
        else if (stack < 4) {
          dir = getcwd(NULL, 0); // gets the name of the directory.
          chdir(dir); // goes to directory
          stack++;
        }
      }
      else if (strcmp(tokens[0], "popd")) {
        if (stack == 0) {
          printf("Error!\n");
          break;
        }
        else {
          dir = getcwd(NULL,0); // gets the name of directory.
          //chdir()
        }
      }

    }
  }
}



int command_is_valid(char tokens[]) {
  if (strcmp(tokens[0], "exit") == 0) {
    return 0;
  }
  else if (strcmp(tokens[0], "cd") == 0) {
    return 0;
  }
  else if (strcmp(tokens[0], "pushd") == 0) {
    return 0;
  }
  else if (strcmp(tokens[0], "popd") == 0) {
    return 0;
  }
  else if(strcmp(tokens[0], "ls")) {
    return 0;
  }
  else {
    return 1;
  }
}
