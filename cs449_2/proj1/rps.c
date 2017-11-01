#include <stdio.h>

int main() {
	printf("Welcome to Rock, Paper, Scissors\n");
	printf("\n");
	printf("Would you like to play? ");
	char buffer[100];
	fgets(buffer, sizeof(buffer), stdin);
	int i;
	i = 0;
	int f;
	for (f = 0; f < sizeof(buffer); f++) {
		if (buffer[f] == '\n') {
			buffer[f] = '\0';
		}
	}
	int computerWins = 0;
	int userWins = 0;
	printf("\n");
	// i is the counter till 5
	printf("buffer = %s.", buffer);
	if (strcmp(buffer, "yes") == 0) {
		while (i != 5) {
			char userChoice[100];
			printf("What is your choice? ");
			fgets(userChoice, sizeof(userChoice), stdin);
			printf("\n");
			for (f = 0; f < sizeof(userChoice); f++) {
				if (userChoice[f] == '\n') {
					userChoice[f] = '\0';
				}
			}
			int d;
			if (strcmp(userChoice, "rock") == 0) {
				d = 1;
			}
			else if (strcmp(userChoice, "scissors") == 0) {
				d = 2;
			}
			else if (strcmp(userChoice, "paper") == 0) {
				d = 3;
			}

			srand((unsigned int)time(NULL));
			int value = rand() % (3 + 1) + 1;
			if (value == d) {
				if (value == 1) {
					printf("The computer chooses rock. It's a tie. \n");

				}
				else if (value == 2) {
					printf("The computer chooses scissors. It's a tie. \n");

				}
				else if (value == 3) {
					printf("The computer chooses paper. It's a tie. \n");
					
				}
			}
			else if (value == 1 && d == 2) {
				printf("The computer chooses rock. You lose. \n");
				computerWins += 1;
			}
			else if (value == 1 && d == 3) {
				printf("The computer chooses rock. You win. \n");
				userWins += 1;
			}
			else if (value == 2 && d == 1) {
				printf("The computer chooses scissors. You win. \n");
				userWins += 1;
			}
			else if (value == 2 && d == 3) {
				printf("The computer chooses scissors. You lose. \n");
				computerWins += 1;
			}
			else if (value == 3 && d == 1) {
				printf("The computer chooses paper. You lose. \n");
				computerWins += 1;
			}
			else if (value == 3 && d == 2) {
				printf("The computer chooses paper. You lose. \n");
				userWins += 1;
			}

			printf("\n");

			printf("The score is now you: %d to computer: %d \n", userWins, computerWins);
			i++;
		}
	}
	else if (strcmp(buffer, "no") == 0) {
		exit(0);
	}
	return 0;
}
