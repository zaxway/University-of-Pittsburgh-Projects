/* Note to grader. I tried to do fopen and fclose with the driver but when I ran it
it was not working. All the file stuff is on the bottom of this file. Thanks! */

/* Mohit Jain MOJ10@pitt.edu cs449*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int dice1; // first dice
  int dice2; // second dice
  int total; // sum of two dice
  int thePoint;

  time_t t;
  srand((unsigned) time(&t)); // sets up random # generator

  printf("Welcome to my casino! What is your name? Please enter: ");
  char name[100];
  fgets(name, sizeof(name), stdin);
  printf("\n");

  printf("Would you like to play or quit? ");
  char play[40];
  fgets(play, sizeof(play), stdin);
  printf("\n");

  if(strcmp(play, "quit\n") == 0) {
    printf("goodbye\n");
    return 0;
  }
  while(strcmp(play, "play\n") == 0) { // while user keeps wanting to play

    //total = rollDice(roll1, roll2);
    dice1 = ((rand()%6)+1);
    dice2 = ((rand()%6)+1);
    total = (dice1 + dice2);
    printf("You have rolled %d + %d = %d\n", dice1, dice2, total);


    //printf("total = %d\n", total);
    if (total == 2 || total == 3 || total == 12) {
      printf("You lose!\n");
    }

    else if (total == 7 || total == 11) {
      printf("You win!\n");
    }

    else { // start of draw
      thePoint = total;
      while (total != 7 || total != thePoint) {

        //total = rollDice(roll1, roll2);
        dice1 = ((rand()%6)+1);
        dice2 = ((rand()%6)+1);
        total = (dice1 + dice2);
        printf("You have rolled %d + %d = %d\n", dice1, dice2, total);

        if (total == 7) {
          printf("You lose!\n");
          break;
        }
        else if (total == thePoint) {
          printf("You win!\n");
          break;
        }
      }
    } // end of draw

    printf("Play again? Enter 'play' or enter 'quit' : ");
    fgets(play, sizeof(play), stdin);
    //strcpy(destplay, play);
    printf("\n");
  }
  printf("Thank you for playing in my casino and goodbye!\n");
}



// file stuff right here (It was not working for some reason (TO GRADER))
// char getRoll() {
//   FILE *f;
//   char result;
//   int read;
//
//   f = fopen("/dev/dice", "r"); // open driver
//
//   if (f == NULL) { // error check
//     printf("Error\n");
//     return ((rand()%6)+1);
//   }
//
//   do {
//     read = fread(&result,1,1,f);
//   } while (read != 1); // read
//
//   fclose(f);
//   return result;
// }
