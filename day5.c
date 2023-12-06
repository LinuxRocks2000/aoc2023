#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct range {
	unsigned long in; // the starting point for INPUTS of this range
	unsigned long out; // the starting point for OUTPUTS of this range
	unsigned long coverage; // the length of this range
};


struct map {
	struct range* ranges;
	int rangeCount;
	char* from;
	char* to;
};


struct map freadmap(FILE* file) {
	struct map ret;
	ret.ranges = NULL;
	ret.rangeCount = 0;
	fscanf(file, "%m[^-]-to-%m[^ ] map:\n", &ret.from, &ret.to);
	//printf("Processing map from %s to %s\n", ret.from, ret.to);
	while (1) {
		char g = fgetc(file);
		if (g == 10 || g == EOF) { // if this is an empty line or the end of file
			return ret;
		}
		else {
			ungetc(g, file);
			struct range r;
			fscanf(file, "%lu %lu %lu", &r.out, &r.in, &r.coverage);
			fgetc(file); // purge newline
			ret.rangeCount ++;
			ret.ranges = realloc(ret.ranges, ret.rangeCount * sizeof(struct range));
			ret.ranges[ret.rangeCount - 1] = r;
		}
	}
	//printf("Processing complete\n");
}


int moink(const char* from, struct map* maps, int mapsCount) { // grab the index of the map that will convert from this type
	for (int i = 0; i < mapsCount; i ++) {
		if (strcmp(maps[i].from, from) == 0) {
			return i;
		}
	}
	return -1;
}


/*int yoinkLocation(int seed, struct map* maps, int mapsCount) {
	char* cType = "seed";
	int cVal = seed;
	//printf("Seed %lu ", seed);
	while (strcmp(cType, "location") != 0) {
		int converter = moink(cType, maps, mapsCount);
		if (converter == -1) {
			printf("FATAL: Map not found for type %s!\n", cType);
			exit(1);
		}
		cType = maps[converter].to;
		struct range r;
		for (int i = 0; i < maps[converter].rangeCount; i ++) {
			r = maps[converter].ranges[i];
			if (cVal >= r.in && cVal < (r.in + r.coverage)) {
				//printf("It is!\n");
				cVal -= maps[converter].ranges[i].in;
	
	                 mapsCount ++;
			cVal += maps[converter].ranges[i].out;
				break;
			} // if it can't find a range that matches, it's fine - it just maps directly.
		}
		//printf("-> %s %lu ", cType, cVal);
	}
	//printf("\n");
	return cVal;
}*/


unsigned long yoinkBackwards(struct map* maps, int mapsLength, unsigned long check) {
	for (int map = mapsLength - 1; map >= 0; map --) {
		for (int range = 0; range < maps[map].rangeCount; range ++) {
			struct range r = maps[map].ranges[range];
			if (check >= r.out && check < r.out + r.coverage) {
				check -= r.out;
				check += r.in;
				break;
			}
		}
	}
	return check;
}


struct seedrange {
	unsigned long start;
	unsigned long range;
};


int main(int argc, char** argv) {
	FILE* file;
	if (argc == 2) {
		file = fopen(argv[1], "r");
	}
	else {
		file = fopen("day5.txt", "r");
	}
	int seedsCount = 0;
	struct seedrange* seeds = NULL;
	char g = fgetc(file);
	while (fgetc(file) != ' '); // purge
	while (g != 10) {
		struct seedrange range;
		fscanf(file, "%lu %lu", &range.start, &range.range);
		seedsCount ++;
		seeds = realloc(seeds, seedsCount * sizeof(struct seedrange));
		seeds[seedsCount - 1] = range;
		g = fgetc(file);
	}
	fgetc(file);
	int mapsCount = 0;
	struct map* maps = NULL;
	while (!feof(file)) {
		struct map m = freadmap(file);
		mapsCount ++;
		maps = realloc(maps, mapsCount * sizeof(struct map));
		maps[mapsCount - 1] = m;
	}
	/*for (int i = 0; i < mapsCount; i ++) {
		for (int j = 0; j < maps[i].rangeCount; j ++) {
			printf("%d (%d) -> %d\n", maps[i].ranges[j].in, maps[i].ranges[j].out, maps[i].ranges[j].coverage);
		}
	}*/
	unsigned long final1 = -1;
	/*for (int i = 0; i < seedsCount; i ++) {
		for (int j = seeds[i].start; j < seeds[i].start + seeds[i].range; j ++) {
			int loc = yoinkLocation(j, maps, mapsCount);
			if ((final1 == -1) || (loc < final1)) {
				final1 = loc;
			}
		}
	}*/
	int l = mapsCount - 1;
	//for (int i = 0; i < maps[l].rangeCount; i ++) {
	//	for (unsigned long j = 0; j < maps[l].ranges[i].coverage; j ++) {
		unsigned long check = 0;
		while (1) {
			//unsigned long check = maps[l].ranges[i].out + j;
			unsigned long yoinked = yoinkBackwards(maps, mapsCount, check);
			//printf("Checking %lu (yoinked %lu)\n", check, yoinked);
			if (check < final1) {
				for (int seed = 0; seed < seedsCount; seed ++) {
					//printf("Is %lu between [%lu, %lu)?\n", yoinked, seeds[seed].start, seeds[seed].start + seeds[seed].range);
					if (yoinked >= seeds[seed].start && yoinked < seeds[seed].start + seeds[seed].range) {
						final1 = check;
						//printf("Yeah, the final result is now %lu\n", final1);
					}
					else {
						//printf("Nope, the final result is still %lu\n", final1);
					}
				}
			}
			else {
				break;
			}
			check ++;
		}
	//}
	printf("Final result p1 = %lu\n", final1);
	return 0;
}
