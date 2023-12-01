#include <stdio.h>
#include <string.h>
#define BUF_SIZE 128


int trackAlong(char* thing, int forwards) {
	int length = strlen(thing);
	for (int i = 0; i < length; i ++) {
		char thisChar;
		if (forwards) {
			thisChar = thing[i];
		}
		else {
			thisChar = thing[length - i - 1];
		}
		if (thisChar >= '0' && thisChar <= '9') {
			return thisChar - '0';
		}
	}
	return 0;
}


int main() {
	FILE* file = fopen("day1-input", "r");
	char buffer[BUF_SIZE];
	int final = 0;
	while (!feof(file)) {
		memset(buffer, 0, BUF_SIZE);
		fgets(buffer, BUF_SIZE, file);
		final += trackAlong(buffer, 1) * 10 + trackAlong(buffer, 0);
		//printf("Line %s number 1 %d number 2 %d\n", buffer, num1, num2);
	}
	printf("Result: %d", final);
}
