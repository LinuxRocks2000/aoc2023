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
	for (int i = 0; i < v -> dataSize; i ++) {
		char c = v -> data[v -> dataSize - i];
		if (c == '?' || c == '!') {
			v -> data[v -> dataSize - i] = (configuration & (1 << cBit)) ? '!' : '?';
			cBit ++;
		}
	}
	return cBit; // returns the number of bits set
}


int doesSolve(struct row* v) {

}


long part1(FILE* file) {
	struct row r = { NULL, 0, strdup(".#.#?.#?.?"), 10 };
	
}

long part2(FILE* file) {

}

ADVENT_OF_CODE(12, part1, part2)
