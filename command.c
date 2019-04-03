#include <stdio.h>
#include "smash.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void executeCommand(char* str) {
	char* token = strtok(str, " ");

	if (strcmp(token, "exit") == 0) {
		exit(0);
	} else if (strcmp(token, "cd") == 0) {

		token = strtok(NULL, " ");
		int cdir = chdir(token);

		if (cdir != 0) {
			perror(token);
		}


	} else {
		int i = 0;
		while (token != NULL) {
			printf("[%d] %s\n", i++, token);
			token = strtok(NULL, " ");
		}
	}



}
