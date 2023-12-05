#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct scratchcard {
	int numbah; // the number of this scratch card we won
	int value;  // the worth of this scratch card
	int push;   // the number of scratch cards forward this scratch card adds to
};


int main(int argc, char** argv) {
	FILE* file;
	if (argc == 2) {
		file = fopen(argv[1], "r");
	}
	else {
		file = fopen("day4input", "r");
	}
	int scratchersLen = 0;
	struct scratchcard* scratchers = NULL;
	while (!feof(file)) {
		while (fgetc(file) != ':' && !feof(file)); // purge "Card <x>:"
		if (feof(file)) {
			break;
		}
		//fgetc(file); // purge space
		char g = fgetc(file);
		int stage = 0;
		int* winning = NULL;
		int winningCount = 0;
		int* values = NULL;
		int valuesCount = 0;
		while (g != 10) {
			if (g == '|') {
				stage = 1;
			}
			else if (g >= '0' && g <= '9') {
				int i = g - '0';
				g = fgetc(file);
				while (g >= '0' && g <= '9') {
					i *= 10;
					i += g - '0';
					g = fgetc(file);
				}
				ungetc(g, file);
				if (stage == 0) {
					winningCount ++;
					winning = realloc(winning, winningCount * sizeof(int));
					winning[winningCount - 1] = i;
				}
				else if (stage == 1) {
					valuesCount ++;
					values = realloc(values, valuesCount * sizeof(int));
					values[valuesCount - 1] = i;
				}
			}
			g = fgetc(file);
		}
		int thisV = 0;
		for (int i = 0; i < winningCount; i ++) {
			for (int ii = 0; ii < valuesCount; ii ++) {
				if (winning[i] == values[ii]) {
					thisV ++;
				}
			}
		}
		struct scratchcard scratcher;
		scratcher.numbah = 1;
		scratcher.push = thisV;
		scratcher.value = (1 << thisV) >> 1; // bitshifts!
		scratchersLen ++;
		scratchers = realloc(scratchers, scratchersLen * sizeof(struct scratchcard));
		scratchers[scratchersLen - 1] = scratcher;
		printf("Value %d\n", thisV);
		if (values != NULL) {
			free(values);
		}
		if (winning != NULL) {
			free(winning);
		}
	}
	for (int i = 0; i < scratchersLen; i ++) {
		for (int ii = i + 1; ii < i + 1 + scratchers[i].push; ii ++) {
			scratchers[ii].numbah += scratchers[i].numbah;
		}
	}
	long final1 = 0;
	for (int i = 0; i < scratchersLen; i ++) {
		final1 += scratchers[i].numbah;
	}
	printf("Final result p1: %d\n", final1);
	return 0;
}
