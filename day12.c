#include "aoc.h"
#include <stdint.h>


struct row {
	int* pattern;
	int numGroups;
	char* data;
	int dataSize;
};


int rowConfigure(uint64_t configuration, struct row* v) {
	int cBit = 0;
	for (int i = v -> dataSize; i >= 0; i --) {
		char c = v -> data[i];
		if (c == '?' || c == '!') {
			v -> data[i] = (configuration & (1 << cBit)) ? '!' : '?';
			cBit ++;
		}
	}
	return 1 << cBit; // returns the possibility space
}


int doesSolve(struct row* v) {
	int clusterN = 0;
	int clusterL = 0;
	for (int i = 0; i < v -> dataSize + 1; i ++) { // note: there is a null terminator. this counts as like a ".". weird C trick. god I love this language.
		if (v -> data[i] == '#' || v -> data[i] == '?') { // '.' and '!' are functioning springs.
			clusterL ++;
		}
		else if (clusterL != 0) {
			if (clusterN >= v -> numGroups || v -> pattern[clusterN] != clusterL) {
				return 0;
			}
			clusterL = 0;
			clusterN ++;
		}
	}
	if (clusterN != v -> numGroups) {
		return 0;
	}
	else {
		return 1;
	}
}


void printRow(struct row* v) {
	printf("%s: ", v -> data);
	for (int i = 0; i < v -> numGroups; i ++) {
		printf("%d, ", v -> pattern[i]);
	}
	printf("\n");
}


int countSolutions(struct row* v) {
	int possibilitySet = rowConfigure(0, v);
	int ret = 0;
	printf("Possibility set: %d\n", possibilitySet);
	for (int i = 0; i < possibilitySet; i ++) {
		if (doesSolve(v)) {
			ret ++;
		}
		rowConfigure(i + 1, v);
	}
	return ret;
}


long part1(FILE* file) {
	struct row* rows = NULL;
	int numRows = 0;
	while (!feof(file)) {
		struct row cRow = { NULL, 0, NULL, 0 };
		fscanf(file, "%ms", &cRow.data);
		if (cRow.data == NULL) {
			break;
		}
		cRow.dataSize = strlen(cRow.data);
		while (fgetc(file) != 10) {
			int numbah;
			fscanf(file, "%d", &numbah);
			cRow.numGroups ++;
			cRow.pattern = realloc(cRow.pattern, cRow.numGroups * sizeof(int));
			cRow.pattern[cRow.numGroups - 1] = numbah;
		}
		numRows ++;
		rows = realloc(rows, numRows * sizeof(struct row));
		rows[numRows - 1] = cRow;
	}
	long ret = 0;
	for (int i = 0; i < numRows; i ++) {
		ret += countSolutions(&rows[i]);
	}
	return ret;
}

long part2(FILE* file) {
	struct row* rows = NULL;
	int numRows = 0;
	while (!feof(file)) {
		struct row cRow = { NULL, 0, NULL, 0 };
		fscanf(file, "%ms", &cRow.data);
		if (cRow.data == NULL) {
			break;
		}
		cRow.dataSize = strlen(cRow.data);
		char* newData = malloc(cRow.dataSize * 5 + 4);
		for (int i = 0; i < cRow.dataSize; i ++) {
			for (int x = 0; x < 5; x ++) {
				newData[x * (cRow.dataSize + 1) + i] = cRow.data[i];
				if (x < 4) {
					newData[x * (cRow.dataSize + 1) + cRow.dataSize] = '?';
				}
			}
		}
		free(cRow.data);
		cRow.data = newData;
		cRow.dataSize = cRow.dataSize * 5 + 4;
		while (fgetc(file) != 10) {
			int numbah;
			fscanf(file, "%d", &numbah);
			cRow.numGroups ++;
			cRow.pattern = realloc(cRow.pattern, cRow.numGroups * sizeof(int));
			cRow.pattern[cRow.numGroups - 1] = numbah;
		}
		numRows ++;
		rows = realloc(rows, numRows * sizeof(struct row));
		rows[numRows - 1] = cRow;
	}
	long ret = 0;
	for (int i = 0; i < numRows; i ++) {
		ret += countSolutions(&rows[i]);
	}
	return ret;

}

ADVENT_OF_CODE(12, part1, part2)
