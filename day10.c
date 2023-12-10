#include "aoc.h"
#include "wchar.h"
#include "locale.h"


struct point {
	int x;
	int y;
};

struct neighbors {
	struct point neighbors[8];
};

struct pipeMatrix {
	int w;
	int h;
	char** data;
};

struct pathinfo {
	struct point* path;
	int length;
};

struct neighbors neighbaz(struct point n) {
	struct neighbors r = {{
		{ n.x - 1, n.y - 1 }, { n.x, n.y - 1 }, { n.x + 1, n.y - 1 },
		{ n.x - 1, n.y     },                   { n.x + 1, n.y     },
		{ n.x - 1, n.y + 1 }, { n.x, n.y + 1 }, { n.x + 1, n.y + 1 }
	}};
	return r;
}


struct pipeMatrix readMatrix(FILE* file) {
	struct pipeMatrix r;
	r.w = 0;
	r.h = 0;
	r.data = NULL;
	while (!feof(file)) {
		char* s;
		fscanf(file, "%ms\n", &s);
		r.w = strlen(s);
		r.h ++;
		r.data = realloc(r.data, sizeof(char*) * r.h);
		r.data[r.h - 1] = s;
	}
	return r;
}

void getPathInfo(struct pipeMatrix m, struct point cursor, struct point old, struct pathinfo* info) {
	//printf("I am %c\n", m.data[cursor.y][cursor.x]);
	info -> length ++;
	info -> path = realloc(info -> path, info -> length * sizeof(struct point));
	info -> path[info -> length - 1] = cursor;
	if (m.data[cursor.y][cursor.x] == 'S') {
		return;
	}
	else {
		struct point awld = cursor;
		struct point c1, c2;
		char me = m.data[cursor.y][cursor.x];
		if (me == '|') {
			c1.x = cursor.x;
			c1.y = cursor.y - 1;
			c2.x = cursor.x;
			c2.y = cursor.y + 1;
		}
		else if (me == '-') {
			c1.x = cursor.x - 1;
			c1.y = cursor.y;
			c2.x = cursor.x + 1;
			c2.y = cursor.y;
		}
		else if (me == 'L') {
			c1.x = cursor.x;
			c1.y = cursor.y - 1;
			c2.x = cursor.x + 1;
			c2.y = cursor.y; 
		}
		else if (me == 'J') {
			c1.x = cursor.x - 1;
			c1.y = cursor.y;
			c2.x = cursor.x;
			c2.y = cursor.y - 1;
		}
		else if (me == '7') {
			c1.x = cursor.x - 1;
			c1.y = cursor.y;
			c2.x = cursor.x;
			c2.y = cursor.y + 1;
		}
		else if (me == 'F') {
			c1.x = cursor.x + 1;
			c1.y = cursor.y;
			c2.x = cursor.x;
			c2.y = cursor.y + 1;
		}
		if (old.x == c1.x && old.y == c1.y) {
			cursor = c2;
		}
		else {
			cursor = c1;
		}
		getPathInfo(m, cursor, awld, info);
	}
}

struct point findStart(struct pipeMatrix* m) {
	int found = 0;
	struct point start;
	for (start.y = 0; start.y < m -> h; start.y ++) {
		for (start.x = 0; start.x < m -> w; start.x ++) {
			if (m -> data[start.y][start.x] == 'S') {
				found = 1;
				break;
			}
		}
		if (found) {
			break;
		}
	}
	return start;
}

long part1(FILE* f) {
	struct pipeMatrix m = readMatrix(f);
	struct point start = findStart(&m);
	struct point c = start;
	c.y ++; // interestingly, in all *my* inputs, there's a pipe directly down! saves time on the search.
	struct pathinfo info;
	info.path = NULL;
	info.length = 0;
	getPathInfo(m, c, start, &info);
	return info.length / 2;
}

int isOnPath(int x, int y, struct pathinfo info) {
	for (int i = 0; i < info.length; i ++) {
		if (info.path[i].x == x && info.path[i].y == y) {
			return 1;
		}
	}
	return 0;
}

wchar_t nicer(char in) {
	if (in == '-') {
		return L'─';
	}
	if (in == '|') {
		return L'│';
	}
	if (in == 'J') {
		return L'┘';
	}
	if (in == 'L') {
		return L'└';
	}
	if (in == '7') {
		return L'┐';
	}
	if (in == 'F') {
		return L'┌';
	}
	if (in == '.') {
		return L' ';
	}
	return in;
}

long part2(FILE* f) {
	struct pipeMatrix m = readMatrix(f);
	struct point start = findStart(&m);
	struct point c = start;
	c.y ++;
	struct pathinfo info;
	info.path = NULL;
	info.length = 0;
	getPathInfo(m, c, start, &info);
	int isInPath = 0;
	long ret = 0;
	char* oldlocale = strdup(setlocale(LC_ALL, NULL));
	setlocale(LC_ALL, "en_US.utf8");
	for (int y = 0; y < m.h; y ++) {
		for (int x = 0; x < m.w; x ++) {
			if (isOnPath(x, y, info)) {
				if (m.data[y][x] != '-' && m.data[y][x] != 'L' && m.data[y][x] != 'J') {
					isInPath = !isInPath;
				}
				if (m.data[y][x] == 'S') {
					wprintf(L"\033[44m%lc\033[0m", nicer(m.data[y][x]));
				}
				else {
					if (isInPath) {
						wprintf(L"\033[43m%lc\033[0m", nicer(m.data[y][x]));
					}
					else {
						wprintf(L"\033[43;30m%lc\033[0m", nicer(m.data[y][x]));
					}
				}
			}
			else if (isInPath) {
				ret ++;
				wprintf(L"\033[42m%lc\033[0m", nicer(m.data[y][x]));
			}
			else {
				wprintf(L"%lc", nicer(m.data[y][x]));
			}
		}
		wprintf(L"\n");
	}
	wprintf(L"Result: %d\n", ret); // locales are borked
	setlocale(LC_ALL, "C");
	free(oldlocale);
	printf("yeah\n");
	return ret;
}

ADVENT_OF_CODE(10, part1, part2)
