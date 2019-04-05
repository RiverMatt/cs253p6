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

static int cmdcount = 0;

void executeCommand(char* str) {

	int firstSequenceNumber = 1;

	if (cmdcount >= MAXHISTORY) {
		firstSequenceNumber = cmdcount - MAXHISTORY + 1;
	}  
	cmdcount++;

	char* copy = strndup(str, strlen(str));
	
	char* args[MAXLINE];

	char* token = strtok(str, " ");

	int i = 0;
	while (token != NULL) {
		args[i] = token;
		i++;
		token = strtok(NULL, " ");

	}
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
			
			fprintf(stderr, "Invalid Command\n");
			add_history(copy, 1);
		}
	} else if (strcmp(args[0], "history") == 0) {
		
		print_history(firstSequenceNumber);
		add_history(copy, 0);

	} else {
		for (int j = 0; j < i; j++) {
			printf("[%d] %s\n", j, args[j]);
		}
		add_history(copy, 127);

	}

	
}
