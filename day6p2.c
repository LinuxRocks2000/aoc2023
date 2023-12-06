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
	long raceTime = 0;
	long raceDist = 0;
	char g = fgetc(file);
	while (g != 10) {
		if (g >= '0' && g <= '9') {
			raceTime *= 10;
			raceTime += g - '0';
		}
		g = fgetc(file);
	}
	g = fgetc(file);
	while (g != 10 && g != EOF) {
		if (g >= '0' && g <= '9') {
			raceDist *= 10;
			raceDist += g - '0';
		}
		g = fgetc(file);
	}
	/*
 		The function for achieved distance given any button time is held_time * (race_time - held_time); this is a quadratic b^2 - ab + d = 0 (where a is race time, b is hold time, and d is goal distance).
		Quadratic formula A = 1; B = -a; C = d. b = a / 2 +- sqrt(a^2 - 4d) / 2. 
  	*/
	/*double ahalf = raceTime / 2.f;
	double a2 = raceTime * raceTime;
	double d4 = 4.f * raceDist;
	double skrewt = sqrt(a2 - d4) / 2.f;
	long solLower = (long)floor(ahalf - skrewt);
	long solHigher = (long)ceil(ahalf + skrewt);
	printf("Solution (%ld, %ld): must hold for %ld millis, and no longer than %ld millis (%ld possible solutions)\n", raceTime, raceDist, solLower, solHigher, solHigher - solLower + 1);
	long final2 = solHigher - solLower + 1;
	printf("Final result 2: %d\n", final2);*/
	long correctSols = 0;
	for (double test = 0; test < raceTime; test ++) {
		if (test * (raceTime - test) > raceDist) {
			correctSols ++;
		}
	}
	printf("Correct solutions: %d\n", correctSols);
	return 0;
}
