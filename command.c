#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif
#include "smash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "history.h"
#include <sys/types.h>
#include <sys/wait.h>


static int cmdcount = 0;

void executeCommand(char* str) {
	
	/* for history */
	int firstSequenceNumber = 1;

	if (cmdcount >= MAXHISTORY) {
		firstSequenceNumber = cmdcount - MAXHISTORY + 1;
	}  
	cmdcount++;

	char* copy = strndup(str, strlen(str));	// copy of the command string
	
	char* args[MAXLINE];			// array to store argument strings

	char* token = strtok(str, " ");		// token for the first arg
	
	/* putting the args into an args array */
	int i = 0;
	while (token != NULL) {
		args[i] = token;
		i++;
		token = strtok(NULL, " ");	// get the next token

	}
	args[i] = NULL;

	if (strcmp(args[0], "exit") == 0) {
		free(copy);
		clear_history();
		exit(0);
	} else if (strcmp(args[0], "cd") == 0) {
		if (i == 2){
			int cdir = chdir(args[1]);

			if (cdir != 0) {
				add_history(copy, 1);
				perror(args[i]);
			} else {
				add_history(copy, 0);
				fprintf(stdout, "%s\n", args[1]);
			}

		} else {
			
			fprintf(stderr, "Invalid command\n");
			add_history(copy, 1);
		}
	} else if (strcmp(args[0], "history") == 0) {
		
		print_history(firstSequenceNumber);
		add_history(copy, 0);

	} else {
		/* legacy code from before smash could handle external commands
		for (int j = 0; j < i; j++) {
			printf("[%2d] %s\n", j, args[j]);
		}
		*/
		
		int extCmd = executeExternalCommand(args);
		
		add_history(copy, 127);

		if (extCmd == -1) {
			fprintf(stderr, "Invalid external command\n");
		}

	}

	
}

int executeExternalCommand(char* args[1026]) {
	
	int pid = fork();

	if (pid == 0) {			// Child process
		int result = execvp(args[0], args); // first parameter is the file descriptor (command), second is args array
//		if (result == -1) {
//			return -1;
//		}
		perror(args[0]);
		exit(result);
	} else if (pid > 0) {		// Parent process
		int exitStatus;
		wait(&exitStatus);
		return exitStatus;
	} else {
		perror("Fork failed!");
	}

	return -1;
	
}
