#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct race {
	float time;
	float distance;
};


int main(int argc, char** argv) {
	FILE* file;
	if (argc == 2) {
		file = fopen(argv[1], "r");
	}
	else {
		file = fopen("day6.txt", "r");
	}
	struct race* races = NULL;
	int raceCount = 0;
	char g = fgetc(file);
	while (g != 10) {
		if (g >= '0' && g <= '9') {
			struct race r;
			r.time = 0;
			while (g >= '0' && g <= '9') {
				r.time *= 10;
				r.time += g - '0';
				g = fgetc(file);
			}
			ungetc(g, file);
			raceCount ++;
			races = realloc(races, raceCount * sizeof(struct race));
			races[raceCount - 1] = r;
		}
		g = fgetc(file);
	}
	g = fgetc(file);
	int i = 0;
	while (g != 10 && g != EOF) {
		if (g >= '0' && g <= '9') {
			races[i].distance = 0;
			while (g >= '0' && g <= '9') {
				races[i].distance *= 10.f;
				races[i].distance += g - '0';
				g = fgetc(file);
			}
			ungetc(g, file);
			i ++;
		}
		g = fgetc(file);
	}
	int final1 = 1;
	/*
 		The function for achieved distance given any button time is held_time * (race_time - held_time); this is a quadratic b^2 - ab + d = 0 (where a is race time, b is hold time, and d is goal distance).
		Quadratic formula A = 1; B = -a; C = d. b = a / 2 +- sqrt(a^2 - 4d) / 2. 
  	*/
	for (int i = 0; i < raceCount; i ++) {	
		float ahalf = races[i].time / 2.f;
		float a2 = races[i].time * races[i].time;
		float d4 = 4.f * races[i].distance;
		float skrewt = sqrtf(a2 - d4) / 2.f;
		int solLower = (int)floorf(ahalf - skrewt);
		int solHigher = (int)ceilf(ahalf + skrewt);
		if (1 || (int)ahalf % 2 == 0) { // if it's even
			solLower += 1.f;
			solHigher -= 1.f;
		}
		//printf("Solution (%f, %f): must hold for %d millis, and no longer than %d millis (%d possible solutions)\n", races[i].time, races[i].distance, solLower, solHigher, solHigher - solLower);
		final1 *= solHigher - solLower + 1;
	}
	printf("Final result 1: %d\n", final1);
	return 0;
}
