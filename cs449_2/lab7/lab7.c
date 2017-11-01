#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

void sighandler();

int main(int argc, char** argv)
{
	if(argc < 2)
		return 0;

	if(fork() == 0)
	{
		// This will execute the program whose name is in the first
		// command-line argument, and whose arguments are after it.

		execvp(argv[1], &argv[1]);

		/************* HERE **************
		You should use perror() to print an error message.
		Then use exit() to exit with a non-zero error exit code.
		*********************************/
		perror("Error!");
		exit(1);
	}
	else
	{
		/************* HERE **************
		You should use the signal() function to *ignore* SIGINT.
		*********************************/
		signal(SIGINT, sighandler);
		


		// This waits for a child to exit in some way. *How* it exited
		// will be put in the stat variable.

		int stat;
		int childpid = waitpid(-1, &stat, 0);
		printf("----------\n");



		/************* HERE **************
		- if waitpid() returned an error value,
			use perror().
		- else, if the child exited successfully (with an exit status of 0),
			print "exited successfully".
		- else, if the child exited, but with a non-zero exit status,
			print "exited with code %d", and print the exit status.
		- else, if the child exited because of a signal,
			print "terminated due to signal %s", and use strsignal() to print the signal.
		- else
			print "terminated some other way!"
		*********************************/
		if (childpid == -1) {
			perror("Error!");
		}
		else if (childpid == 0) {
			printf("exited successfully\n");
		}
		else if (childpid != 0) {
			printf("exited with code %d\n", childpid);
		}
		else {
			printf("terminated some other way!\n");
		}

	}

	return 0;
}

void sighandler() {
	printf("Hello\n");
	exit(1);
}