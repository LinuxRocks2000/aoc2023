#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct symbol {
	int x;
	int y;
	char v;
	int adjacents;
	long adjacentPower;
};

struct num {
	int value;
	int x;
	int y;
	int l;
};


int doesAdjace(struct symbol s, struct num n) {
	if ((s.y >= n.y - 1) && (s.y <= n.y + 1) && (s.x >= n.x - 1) && (s.x <= n.x + n.l)) {
		return 1;
	}
	return 0;
}


struct symbol* symbols = NULL;
int symbolCount = 0;
struct num* numbers = NULL;
int numberCount = 0;

int addNumber(struct num n) {
	numberCount ++;
	numbers = realloc(numbers, sizeof(struct num) * numberCount);
	numbers[numberCount - 1] = n;
}

int addSymbol(struct symbol s) {
	symbolCount ++;
	symbols = realloc(symbols, sizeof(struct symbol) * symbolCount);
	symbols[symbolCount - 1] = s;
}


int main(int argc, char** argv) {
	FILE* f = fopen("day3input", "r");
	int x, y;
	x = 0;
	y = 0;
	int p1final = 0;
	while (!feof(f)) {
		char g = fgetc(f);
		if (g >= '0' && g <= '9') {
			struct num n;
			n.value = 0;
			n.x = x;
			n.y = y;
			n.l = 0;
			while (g >= '0' && g <= '9') {
				n.value *= 10;
				n.value += g - '0';
				n.l ++;
				x ++;
				g = fgetc(f);
			}
			addNumber(n);
			ungetc(g, f);
			x --;
		}
		else if (g == 10) {
			x = -1; // because it's gonna be incremented by one soon
			y ++;
		}
		else if (g != '.' && g != ' ' && g != EOF) {
			struct symbol s = {x, y, g, 0, 1};
			addSymbol(s);
		}
		x ++;
	}
	for (int i = 0; i < numberCount; i ++) {
		printf("Number %d at %d, %d with length %d\n", numbers[i].value, numbers[i].x, numbers[i].y, numbers[i].l);
	}
	for (int i = 0; i < symbolCount; i ++) {
		printf("Symbol %c at %d, %d\n", symbols[i].v, symbols[i].x, symbols[i].y);
	}
	for (int i = 0; i < numberCount; i ++) {
		for (int ii = 0; ii < symbolCount; ii ++) {
			if (doesAdjace(symbols[ii], numbers[i])) {
				printf("%d adjaces with %c!\n", numbers[i].value, symbols[ii].v);
				p1final += numbers[i].value;
				symbols[ii].adjacents ++;
				symbols[ii].adjacentPower *= numbers[i].value;
			}
		}
	}
	long p2final = 0;
	for (int i = 0; i < symbolCount; i ++) {
		if (symbols[i].v == '*' && symbols[i].adjacents == 2) {
			p2final += symbols[i].adjacentPower;
		}
	}
	printf("Final result part 1: %d, part 2: %d\n", p1final, p2final);
	return 0;
}
