// utilities to make aoc solutions more betterer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct ARRAY {
	void** bytes; // each element is guaranteed to be 64 bits on an x64 system like mine. This means it can store every number type! so stupid.
	unsigned long length; // length of elements in the array
	unsigned long capacity; // capacity of the array (size of the allocated space)
};


struct ARRAY* ARRAY_create() {
	struct ARRAY* ret = malloc(sizeof(struct ARRAY));
	ret -> bytes = NULL;
	ret -> length = 0;
	ret -> capacity = 0;
	return ret;
}

void ARRAY_push(struct ARRAY* array, void* item) {
	if (array -> length == array -> capacity) { // the array is at capacity
		array -> capacity ++;
		array -> bytes = realloc(array -> bytes, array -> capacity * sizeof(void*)); // memory inefficient for smaller types, sadly
	}
	array -> bytes[array -> length] = item;
	array -> length ++;
}

void* ARRAY_get(struct ARRAY* array, unsigned long index) {
	return array -> bytes[index];
}

void* ARRAY_pop(struct ARRAY* array) {
	array -> length --;
	return array -> bytes[array -> length];
}

void ARRAY_pushLong(struct ARRAY* array, long val) {
	ARRAY_push(array, (void*)val);
}

long ARRAY_getLong(struct ARRAY* array, unsigned long index) {
	return (long)ARRAY_get(array, index);
}

long ARRAY_popLong(struct ARRAY* array) {
	return (long)ARRAY_pop(array);
}

void ARRAY_pushDouble(struct ARRAY* array, double val) {
	ARRAY_push(array, (void*)*(long long*)&val);
}

double ARRAY_getDouble(struct ARRAY* array, unsigned long index) {
	return (double)(long long)ARRAY_get(array, index);
}

double ARRAY_popDouble(struct ARRAY* array) {
	return (double)(long long)ARRAY_pop(array);
}

void ARRAY_delete(struct ARRAY* array, unsigned long index) { // SLOW array delete
	array -> length --;
	for (unsigned long i = index; i < array -> length; i ++) {
		array -> bytes[i] = array -> bytes[i + 1];
	}
}

void ARRAY_swapat(struct ARRAY* array, unsigned long index) {
	void* cache = array -> bytes[index];
	array -> bytes[index] = array -> bytes[index + 1];
	array -> bytes[index + 1] = cache;
}

long fgetlong(FILE* file) {
	char g = fgetc(file);
	long ret = 0;
	while (g >= '0' && g <= '9') {
		ret *= 10;
		ret += g - '0';
	}
	ungetc(g, file);
	return ret;
}

double fgetdouble(FILE* file) {
	double ret;
	fscanf(file, "%lf", &ret);
	return ret;
}

void fstrip(FILE* file) {
	char g = fgetc(file);
	while (g == ' ' || g == 10 || g == '\r') {
		g = fgetc(file);
	}
	ungetc(g, file);
}

void aocMain(int AOC_DAY, long aocSolutionP1(FILE*), long aocSolutionP2(FILE*), int argc, char** argv) {
	if (argc == 2) {
		FILE* file = fopen(argv[1], "r");
		if (file == NULL) {
			printf("FATAL: Could not open input file.\n");
			exit(1);
		}
		long solp1 = aocSolutionP1(file);
		rewind(file);
		long solp2 = aocSolutionP2(file);
		printf("Solved day %d, part 1 is %d and part 2 is %d.\n", AOC_DAY, solp1, solp2);
	}
	else {
		printf("FATAL: No input filename specified.\n");
		exit(1);
	}
}

#define ADVENT_OF_CODE(DAY, solp1, solp2) int main(int argc, char** argv) {aocMain(DAY, solp1, solp2, argc, argv); return 0;}
