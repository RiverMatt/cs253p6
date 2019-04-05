#include <stdio.h>
#include "smash.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "history.h"

void executeCommand(char* str) {
	
	char* args[MAXLINE];

	char* token = strtok(str, " ");

	int i = 0;
	while (token != NULL) {
		args[i] = token;
		i++;
		token = strtok(NULL, " ");

	}
	if (strcmp(args[0], "exit") == 0) {
		exit(0);
	} else if (strcmp(args[0], "cd") == 0) {
		if (i == 2){
			int cdir = chdir(args[1]);

			if (cdir != 0) {
				perror(args[i]);
			}

		} else {
			fprintf(stderr, "Invalid Command\n");
		}
	} else if (strcmp(args[0], "history") == 0) {

		print_history(i);
	
	} else {
		for (int j = 0; j < i; j++) {
			printf("[%d] %s\n", j, args[j]);
		}

	}

}
