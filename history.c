#include <stdio.h>
#include <string.h>
#include "history.h"

static struct Cmd* hist;	//pointer to a Cmd struct called hist
static char counter = 0;	//counter for the number of history entries
static char fsn = -1;		//index of the firstSequenceNumber

void int_history(void) {			//Builds data structures for recording cmd history
	hist[malloc(sizeof(struct Cmd)) * MAXHISTORY];
}

void add_history(char *cmd, int exitStatus) {	//Adds an entry to the history
	
	if (counter >= 10) {
		/* Shift all entries down one */
		for (int i = 0; i < MAXHISTORY; i++) {
			strncpy(hist[i]->cmd, hist[i + 1]->cmd, sizeof(hist[i + 1]->cmd));
			hist[i]->exitStatus = hist[i + 1]->exitStatus;
		}
	
	}

	//sprintf(hist[fsn]->cmd, "[%d] ", exitStatus);
	//strncat(hist[fsn]->cmd, cmd, sizeof(cmd));
	strncpy(hist[fsn]->cmd, cmd, sizeof(cmd));
	hist[fsn]->exitStatus = exitStatus;

	counter++;
	if (fsn != MAXHISTORY - 1) {
		fsn++;
	}
	
}

void clear_history(void) {			//Frees all malloc’d memory in the history
	free(hist);
	hist = NULL;
}

void print_history(int firstSequenceNumber) {	//Prints the history to stdout
	for (int i = firstSequenceNumber; i >= 0; i--) {
		printf("[%d] %s\n", hist[i]->exitStatus, hist[i]->cmd);
	}
}
