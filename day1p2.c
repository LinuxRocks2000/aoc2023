#include <stdio.h>
#include <string.h>
#define BUF_SIZE 128


const char* numbers[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};


int matchesAt(char* text, const char* match, int start) {
	int matchLen = strlen(match);
	for (int i = 0; i < matchLen; i ++) {
		if (text[start + i] != match[i]) {
			return 0;
		}
	}
	return 1;
}


int tokenize(char* string, int* result, int length) { // return the number of integers pushed to the array
	int cToken = 0;
	for (int i = 0; i < length; i ++) {
		if (string[i] >= '0' && string[i] <= '9') {
			result[cToken++] = string[i] - '0';
			continue;
		}
		for (int numTry = 1; numTry <= 9; numTry ++) {
			if (matchesAt(string, numbers[numTry - 1], i)) {
				result[cToken++] = numTry;
				continue;
			}
		}
	}
	return cToken;
}


int main(){
	FILE* file = fopen("day1p2-input", "r");
	char buffer[BUF_SIZE];
	int final = 0;
	while (!feof(file)) {
		fgets(buffer, BUF_SIZE, file);
		//printf("First char of line: %d\n", buffer[0]);
		if (buffer[0] == 10) { break; } // if it's an empty EOF newline.
		int resultBuffer[BUF_SIZE]; // BUF_SIZE is the maximum possible number of ints on any line (because lines longer than BUF_SIZE will fail).
		for (int i = 0; i < BUF_SIZE; i ++) {
			resultBuffer[i] = -1;
		}
		int len = tokenize(buffer, resultBuffer, strlen(buffer));
		printf("%s: ", buffer);
		for (int i = 0; i < len; i ++) {
			printf("%d, ", resultBuffer[i]);
		}
		printf("\n");
		printf("Result: %d%d\n", resultBuffer[0], resultBuffer[len - 1]);
		final += resultBuffer[0] * 10 + resultBuffer[len - 1];
	}
	printf("Result: %d\n", final);
}

