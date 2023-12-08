#include "aoc.h"


long countOccurrences(char hand[5], char thing) {
	long ret = 0;
	for (int i = 0; i < 5; i ++) {
		if (hand[i] == thing) {
			ret ++;
		}
	}
	return ret;
}

long highestSimilarity(char hand[5]) {
	long ret = 0;
	for (int i = 0; i < 5; i ++) {
		long c = countOccurrences(hand, hand[i]);
		if (c > ret) {
			ret = c;
		}
	}
	return ret;
}

int is5ok(char hand[5]) {
	return countOccurrences(hand, hand[0]) == 5;
}

int is4ok(char hand[5]) {
	return highestSimilarity(hand) == 4;
}

int isfullhouse(char hand[5]) {
	for (int i = 0; i < 5; i ++) {
		long c = countOccurrences(hand, hand[i]);
		if (c != 2 || c != 3) { // magic.
			return 0;
		}
	}
	return 1;
}

int is3ok(char hand[5]) {
	return highestSimilarity(hand) == 3; // must do full house checks before this.
}

int countPairs(char hand[5]) {
	int r = 0;
	for (int i = 0; i < 5; i ++) {
		if (countOccurrences(hand, hand[i]) == 2) {
			 r ++;
		}
	}
	return r / 2;
}

int is2p(char hand[5]) {
	return countPairs(hand) == 2;
}

int is1p(char hand[5]) {
	return highestSimilarity(hand) == 2;
}

int parseHandT(char hand[5]) {
	if (is5ok(hand)) {
//		printf("%s is 5ok\n", hand);
		return 6;
	}
	if (is4ok(hand)) {
//		printf("%s is 4ok\n", hand);
		return 5;
	}
	if (isfullhouse(hand)) {
//		printf("%s is fullhouse\n", hand);
		return 4;
	}
	if (is3ok(hand)) {
//		printf("%s is 3ok\n", hand);
		return 3;
	}
	if (is2p(hand)) {
//		printf("%s is 2p\n", hand);
		return 2;
	}
	if (is1p(hand)) {
//		printf("%s is 1p\n", hand);
		return 1;
	}
//	printf("%s is Highc\n", hand);
	return 0; // it's a High Card
}

int cardValue(char c) {
	if (c >= '2' && c <= '9') {
		return c - '2';
	}
	if (c == 'T') {
		return 8;
	}
	if (c == 'J') {
		return 9;
	}
	if (c == 'Q') {
		return 10;
	}
	if (c == 'K') {
		return 11;
	}
	if (c == 'A') {
		return 12;
	}
	printf("FATAL: Invalid card type!\n");
	exit(1);
}

int handBeats(char hand1[5], char hand2[5]) {
	int h1v = parseHandT(hand1);
	int h2v = parseHandT(hand2);
	if (h1v > h2v) {
		return 1;
	}
	if (h1v < h2v) {
		return 0;
	}
	for (int i = 0; i < 5; i ++) {
		int c = cardValue(hand1[i]) - cardValue(hand2[i]);
		if (c < 0) {
			return 0;
		}
		if (c > 0) {
			return 1;
		}
	}
	printf("FATAL: Tie detected\n");
	exit(1);
}

struct hand {
	char cards[5];
	long bid;
};

long aocSolutionP1(FILE* file) {
	long long ret = 0;
	struct ARRAY* hands = ARRAY_create();
	while (!feof(file)) {
		struct hand* h = malloc(sizeof(struct hand));
		if (fscanf(file, "%s %d\n", h -> cards, &h -> bid) == 2) {
			ARRAY_push(hands, h);
		}
		else {
			printf("FATAL: Read Error\n");
		}
	} // slow-but-reliable bubblesort variant: trudge through the list until you find something that needs swapping. swap it. continue. if you swapped anything, go back to the start of the list. so stupid!
	int sorted = 0;
	while (!sorted) {
		sorted = 1;
		for (int i = 0; i < hands -> length - 1; i ++) {
			struct hand* h0 = (struct hand*)ARRAY_get(hands, i);
			struct hand* h1 = (struct hand*)ARRAY_get(hands, i + 1);
			if (handBeats(h0 -> cards, h1 -> cards)) {
				ARRAY_swapat(hands, i);
				sorted = 0;
			}
		}
	}
	printf("Sorted!\n");
	for (int i = 0; i < hands -> length; i ++) {
		struct hand* h = (struct hand*)ARRAY_get(hands, i);
		ret += (i + 1) * h -> bid;
		printf("%s : %d (rank %d; ret now %d)\n", h -> cards, h -> bid, i + 1, ret);
	}
	printf("Ret is %d\n", ret);
	return ret;
}

long aocSolutionP2(FILE* file) {
	return -1;
}

ADVENT_OF_CODE(7, aocSolutionP1, aocSolutionP2)
