#include <stdio.h>
#include <string.h>
#include "smash.h"
#include "history.h"

#define MAXLINE 4096
int main(void) {
	char bfr[MAXLINE];
	fputs("$ ", stderr);
	while (fgets(bfr, MAXLINE, stdin) != NULL) {
		bfr[strlen(bfr) - 1] = '\0'; 		// replace the newline char with NUL
		executeCommand(bfr);
		fputs("$ ", stderr);
	}

	return 0;
}
