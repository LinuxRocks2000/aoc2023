#include <stdio.h>
#include <string.h>
#define RED_COUNT 12
#define GREEN_COUNT 13
#define BLUE_COUNT 14


struct game {
	int red;
	int blue;
	int green;	
};


void fdumpu(FILE* file, char end) { // dump all characters from a stream INCLUDING the final character it's set to delete
	while (fgetc(file) != end && !feof(file));
}


int fgetword(FILE* file, char* output, size_t mlen) { // read bytes into output until it reaches a space, a newline, any punctuation, or the max word length. Does not delete punctuation. Returns the length of the word.
	int i = 0;
	char buf;
	while (1) {
		buf = fgetc(file);
		if (buf == ' ' || buf == 10 || buf == '.' || buf == ',' || buf == ';' || buf == EOF || buf == ':') {
			ungetc(buf, file);
			break;
		}
		else {
			output[i] = buf;
			i ++;
			if (i == mlen) {
				break;
			}
		}
	}
	return i;
}


int fgeti(FILE* file) {
	char buf;
	int ret = 0;
	while (1) {
		buf = fgetc(file);
		if (buf >= '0' && buf <= '9') {
			ret *= 10;
			ret += buf - '0';	
		}
		else {
			if (buf != EOF) {
				ungetc(buf, file);
			}
			return ret;
		}
	}
}


int fnextgame(FILE* file, struct game* ret) {
	ret -> red = 0;
	ret -> green = 0;
	ret -> blue = 0;
	while (1) {
		int n = fgeti(file);
		fgetc(file); // purge the space
		char buffer[32];
		memset(buffer, 0, 32);
		fgetword(file, buffer, 32);
		printf("n: %d, le word: %s\n", n, buffer);
		if (buffer[0] == 'r') {
			ret -> red = n;
		}
		else if (buffer[0] == 'g') {
			ret -> green = n;
		}
		else if (buffer[0] == 'b') {
			ret -> blue = n;
		}
		char r = fgetc(file);
		fgetc(file); // purge space
		if (r == 10 || r == EOF) {
			return 1;
		}
		if (r == ';') {
			return 0;
		}
	}
}


int main(int argc, char** argv) {
	FILE* inFile = fopen("day2input", "r");
	int final = 0;
	while (!feof(inFile)) {
		fdumpu(inFile, ' '); // throw out the word "game"
		int num = fgeti(inFile);
		fdumpu(inFile, ' '); // throw out the ": "
		int isGood = 1;
		while (1) {
			struct game g;
			int end = fnextgame(inFile, &g);
			printf("Got game %d with r=%d, g=%d, b=%d\n", num, g.red, g.green, g.blue);
			if (g.red > RED_COUNT || g.blue > BLUE_COUNT || g.green > GREEN_COUNT) {
				isGood = 0;
			}
			if (end) {
				break;
			}
		}
		if (isGood) {
			final += num;
		}
	}
	printf("Final result: %d\n", final);
	return 0;
}
