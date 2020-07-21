/*
 ============================================================================
 Name        : ABernsteinThreeNPlusOne.c
 Author      : Aidan Bernstein
 Version     :
 Copyright   : Your copyright notice
 Description : 3n + 1, calc range, calc longest iteration of formula within range
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int computeMaxSequenceLength(int left, int right);
int computeNextValue(int right);
int computeSequenceLength(int b);

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *outFile;
	char filenameOut[BUFSIZ + 1];
	int z = 0;
	int x = 0;
	int theMaxSequenceLength = 0;
	char buffer[BUFSIZ + 1];
	char bufferTwo[BUFSIZ + 1];
	//gets file name opens file cuts off next line char
	printf("Enter output filename:\n");
	fgets(filenameOut, BUFSIZ, stdin);
	int nameLengthTwo = strlen(filenameOut);
	filenameOut[nameLengthTwo - 1] = '\0';
	outFile = fopen(filenameOut, "w");

	//while an empty enter key isnt entered so to speak, will calc with values and print them to a file
	while (buffer[0] != '\n') {
		x = atoi(fgets(buffer, BUFSIZ, stdin));
		if (buffer[0] == '\n') {
			break;
		}
		z = atoi(fgets(bufferTwo, BUFSIZ, stdin));
		theMaxSequenceLength = computeMaxSequenceLength(x, z);
		theMaxSequenceLength = theMaxSequenceLength + 1;
		fprintf(outFile, "%i\t%i\t%i\n", x, z, theMaxSequenceLength);
	}

	fclose(outFile);
	printf("Complete\n");
	return EXIT_SUCCESS;
}
//compute max sequence will take in the left and right values (the range)  then pass in each vallue of the range into
//compute sequence length. each time it iterates it will add was is returned from compute max sequence length
int computeMaxSequenceLength(int left, int right) {
	int b = 0;
	int x = 0;
	int range = 0;
	range = left - right;
	if (range < 0) {
		range = range * -1;
	}
	if (left > right) {

		for (b = right; b < range + right;) {
			b++;
			if (computeSequenceLength(b) > x) {
				x = computeSequenceLength(b);

			}

		}
	}
	if (right > left) {
		for (b = left; b < left + range;) {
			b++;
			if (computeSequenceLength(b) > x) {
				x = computeSequenceLength(b);

			}

		}

	}

	return x;
}
//simple computes next value and returns it.
//the following value is passed in
int computeNextValue(int right) {
	if (right % 2 == 0) {
		right = right / 2;

	} else {
		right = (right * 3) + 1;

	}
	return right;
}

// takes in the each value of the range and then passes it into computenextvalue until 1 is returned. each time
// this iterates (the while loop) adds one to sequence length
int computeSequenceLength(int b) {
	int sequenceLength = 1;
	int temp = 0;
	while (computeNextValue(b) != 1) {
		b = computeNextValue(b);
		if (b == 1) {
			break;
		}
		sequenceLength++;
	}
	temp = sequenceLength;
	if (b == 1) {
		sequenceLength = 0;
	}
	return temp;

}

