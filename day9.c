#include "aoc.h"


int extDown(int* dataset, int length, int backw0rdz) { // return the next item
	for (int i = 0; i < length; i ++) {
		printf("%d, ", dataset[i]);
	}
	printf("\n");
	int* r = malloc((length - 1) * sizeof(int));
	int isTail = 1;
	for (int i = 0; i < length - 1; i ++) {
		r[i] = dataset[i + 1] - dataset[i];
		if (r[i] != 0) {
			isTail = 0;
		}
	}
	if (isTail) {
		printf("I'm a tail uwu\n");
		return dataset[0];
	}
	else {
		if (backw0rdz) {
			return dataset[0] - extDown(r, length - 1, 1);
		}
		return dataset[length - 1] + extDown(r, length - 1, 0);
	}
	free(r);
}

long part1(FILE* file) {
	int* f = NULL;
	int l = 0;
	long ret = 0;
	printf("Solving p1\n");
	while (!feof(file)) {
		long z;
		fscanf(file, "%d", &z);
		printf("Z, %d\n", z);
		l ++;
		f = realloc(f, l * sizeof(int));
		f[l - 1] = z;
		if (fgetc(file) == 10) {
			//printf("Got line value %d\n", extDown(f, l));
			ret += extDown(f, l, 0);
			free(f);
			f = NULL;
			l = 0;
		}
	}
	return ret;
}

long part2(FILE* file) {
	int* f = NULL;
	int l = 0;
	long ret = 0;
	printf("Solving p1\n");
	while (!feof(file)) {
		long z;
		fscanf(file, "%d", &z);
		printf("Z, %d\n", z);
		l ++;
		f = realloc(f, l * sizeof(int));
		f[l - 1] = z;
		if (fgetc(file) == 10) {
			//printf("Got line value %d\n", extDown(f, l));
			ret += extDown(f, l, 1);
			free(f);
			f = NULL;
			l = 0;
		}
	}
	return ret;
}


ADVENT_OF_CODE(9, part1, part2)
