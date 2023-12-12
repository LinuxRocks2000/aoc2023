#include "aoc.h"
typedef unsigned long long big_t;


struct star {
	big_t x;
	big_t y;
	big_t dx;
	big_t dy;
};

struct starmap {
	struct star* stars;
	int numStars;
	big_t w;
	big_t h;
};

struct starmap getStars(FILE* file) {
	struct starmap ret = { NULL, 0, 0, 0 };
	struct star cStar = { 0, 0, 0, 0 };
	while (!feof(file)) {
		char g = fgetc(file);
		if (g == '#') {
			ret.numStars ++;
			ret.stars = realloc(ret.stars, ret.numStars * sizeof(struct star));
			ret.stars[ret.numStars - 1] = cStar;
			if (cStar.x >= ret.w) {
				ret.w = 1 + cStar.x;
			}
			if (cStar.y >= ret.h) {
				ret.h = 1 + cStar.y;
			}
		}
		cStar.x ++;
		if (g == 10) {
			cStar.x = 0;
			cStar.y ++;
		}
	}
	return ret;
}


void spacetime(struct starmap* m, int by) { // the name is ironic. I'm not nearly that idiotic.
	by --; // by is a multiplier. because we're doing it step-by-step, we subtract 1.
	int w, h;
	w = m -> w;
	h = m -> h;
	for (int x = 0; x < w; x ++) {
		int rowEmpty = 1;
		for (int i = 0; i < m -> numStars; i ++) {
			if (m -> stars[i].x == x) {
				rowEmpty = 0;
				break;
			}
		}
		if (rowEmpty) {
			for (int i = 0; i < m -> numStars; i ++) {
				if (m -> stars[i].x > x) {
					m -> stars[i].dx += by;
				}
			}
			m -> w += by;
		}
	}
	for (int y = 0; y < h; y ++) {
		int rowEmpty = 1;
		for (int i = 0; i < m -> numStars; i ++) {
			if (m -> stars[i].y == y) {
				rowEmpty = 0;
				break;
			}
		}
		if (rowEmpty) {
			for (int i = 0; i < m -> numStars; i ++) {
				if (m -> stars[i].y > y) {
					m -> stars[i].dy += by;
				}
			}
			m -> h += by;
		}
	}
	for (int i = 0; i < m -> numStars; i ++) {
		m -> stars[i].x += m -> stars[i].dx;
		m -> stars[i].y += m -> stars[i].dy;
		m -> stars[i].dx = 0;
		m -> stars[i].dy = 0;
	}
}


big_t dist(big_t one, big_t two) {
	if (one > two) {
		return one - two;
	}
	return two - one;
}


big_t countShawteez(struct starmap* m) {
	big_t ret = 0;
	for (int i = 0; i < m -> numStars - 1; i ++) {
		for (int j = i + 1; j < m -> numStars; j ++) {
			ret += dist(m -> stars[i].x, m -> stars[j].x) + dist(m -> stars[i].y, m -> stars[j].y);
		}
	}
	printf("ret: %lu\n", ret);
	return ret;
}


int isStarAt(int x, int y, struct starmap* m) {
	for (int i = 0; i < m -> numStars; i ++) {
		if (m -> stars[i].x == x && m -> stars[i].y == y) {
			return 1;
		}
	}
	return 0;
}


void printStars(struct starmap* m) {
	for (int y = 0; y < m -> h; y ++) {
		for (int x = 0; x < m -> w; x ++) {
			if (isStarAt(x, y, m)) {
				printf("\033[42m \033[0m");
			}
			else {
				printf(".");
			}
		}
		printf("\n");
	}
}


long part1(FILE* file) {
	struct starmap map = getStars(file);
	printStars(&map);
	spacetime(&map, 2);
	printf("space time\n");
	printStars(&map);
	return countShawteez(&map);
}

long part2(FILE* file) {
	struct starmap map = getStars(file);
	//printStars(&map);
	spacetime(&map, 1000000);
	//printf("\n");
	//printStars(&map);
	return countShawteez(&map);
}


ADVENT_OF_CODE(11, part1, part2)
