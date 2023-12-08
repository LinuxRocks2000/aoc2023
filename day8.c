#include "aoc.h"


struct instr {
	char root[3];
	char right[3];
	char left[3];
};

int instrMatch(char one[3], char two[3]) {
	for (int i = 0; i < 3; i ++) {
		if (one[i] != two[i]) {
			return 0;
		}
	}
	return 1;
}


int findInstruction(struct instr* instructions, int instrCount, char instruction[3]) {
	for (int i = 0; i < instrCount; i ++) {
		if (instrMatch(instructions[i].root, instruction)) {
			return i;
		}
	}
	printf("FATAL: Instruction %3s Not Found!\n", instruction);
	exit(1);
}


long part1(FILE* file) {
	char* controls;
	fscanf(file, "%ms\n", &controls);
	int controlSize = strlen(controls);
	printf("Got controls %s\n", controls);
	struct instr* instructions = NULL;
	int instrCount = 0;
	while (!feof(file)) {
		struct instr temp;
		fscanf(file, "%3c = (%3c, %3c)\n", temp.root, temp.left, temp.right);
		instrCount ++;
		instructions = realloc(instructions, sizeof(struct instr) * instrCount);
		instructions[instrCount - 1] = temp;
	}
	char AAA[] = {'A', 'A', 'A'};
	char ZZZ[] = {'Z', 'Z', 'Z'};
	int cursor = findInstruction(instructions, instrCount, AAA);
	int i = 0;
	while (!instrMatch(instructions[cursor].root, ZZZ)) {
		char c = controls[i % controlSize];
		if (c == 'R') {
			cursor = findInstruction(instructions, instrCount, instructions[cursor].right);
			printf("Picked right element. Now at %.3s.\n", instructions[cursor].root);
		}
		else {
			cursor = findInstruction(instructions, instrCount, instructions[cursor].left);
		}
		i ++;
	}
	return i;
}

long part2(FILE* file) {
	char* controls;
	fscanf(file, "%ms\n", &controls);
	int controlSize = strlen(controls);
	printf("Got controls %s\n", controls);
	struct instr* instructions = NULL;
	int instrCount = 0;
	while (!feof(file)) {
		struct instr temp;
		fscanf(file, "%3c = (%3c, %3c)\n", temp.root, temp.left, temp.right);
		instrCount ++;
		instructions = realloc(instructions, sizeof(struct instr) * instrCount);
		instructions[instrCount - 1] = temp;
	}
	char ZZZ[] = {'Z', 'Z', 'Z'};
	int* cursors = NULL;
	int* cResults = NULL;
	int numCursors = 0;
	for (int i = 0; i < instrCount; i ++) {
		if (instructions[i].root[2] == 'A') {
			numCursors ++;
			cursors = realloc(cursors, numCursors * sizeof(int));
			cResults = realloc(cResults, numCursors * sizeof(int));
			cursors[numCursors - 1] = i;
		}
	}
	/*
	while (1) {
		int allSolved = 1;
		for (int j = 0; j < numCursors; j ++) {
			if (instructions[cursors[j]].root[2] != 'Z') {
				allSolved = 0;
				break; // no reason to keep looping
			}
		}
		if (allSolved) {
			break;
		}
		char c = controls[i % controlSize];
		for (int j = 0; j < numCursors; j ++) {
			if (c == 'R') {
				cursors[j] = findInstruction(instructions, instrCount, instructions[cursors[j]].right);
			}
			else {
				cursors[j] = findInstruction(instructions, instrCount, instructions[cursors[j]].left);
			}
		}
		i ++;
	}*/
	for (int i = 0; i < numCursors; i ++) {
		int j = 0;
		while (instructions[cursors[i]].root[2] != 'Z') {
			char c = controls[j % controlSize];
			if (c == 'R') {
				cursors[i] = findInstruction(instructions, instrCount, instructions[cursors[i]].right);
			}
			else {
				cursors[i] = findInstruction(instructions, instrCount, instructions[cursors[i]].left);
			}
			j ++;
		}
		cResults[i] = j;
	}
	unsigned long long lcm = 1;
	for (int i = 0; i < numCursors; i ++) {
		unsigned long long gcd = 1;
		for (long long j = 1; j <= lcm && j <= cResults[i]; j ++) {
			if (lcm % j == 0 && cResults[i] % j == 0) {
				gcd = j;
			}
		}
		//lcm /= gcd;
		lcm *= cResults[i] / gcd;
		printf("cresultsi = %ld; gcd = %ld; facturd = %ld; least common multiple now %ld\n", cResults[i], gcd, cResults[i]/gcd, lcm);
	}
	return lcm;
}

ADVENT_OF_CODE(8, part1, part2)
