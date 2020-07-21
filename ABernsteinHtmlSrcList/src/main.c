/*
 ============================================================================
 Name        : ABernsteinHtmlSrcList.c
 Author      : Aidan Bernstein
 Version     :
 Copyright   : Your copyright notice
 Description : reads html copies to string analyzes string to find matches
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int parser(char string1[]);
void parserHeader(char string2[]);
void parserUrl(char String3[]);

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	char fileLines[BUFSIZ + 1];
	char fileName[BUFSIZ + 1];
	char taskReader[BUFSIZ + 1];
	int tagNumbers;

//GETS FILE NAME CUTS 'ENTER' KEY OFF
	printf("URL:\n");
	fgets(fileName, BUFSIZ, stdin);
	fileName[strlen(fileName) - 1] = '\0';
	printf("Ready\n");
//COMBINE CURL WITH FILENAME OPEN FILE
	char passer[BUFSIZ] = "curl -s ";
	strcat(passer, fileName);
	FILE *HtmlFile = popen(passer, "r");
	if (!HtmlFile) {
		printf("File could not be opened for reading!\n");
		return EXIT_FAILURE;
	}
	//ALLOCATES PROPER SIZE(MEMORY) TO STRING AT HAND THEN MAKES SURE WE REWIND TO BEGGINNING OF FILE
	fseek(HtmlFile, 0, SEEK_END);
	int sizeofFile = ftell(HtmlFile);
	char* bigString = (char*) malloc(sizeofFile + 1);
	rewind(HtmlFile);

	//FORMS JUMBO STRING OF INDIVIDUAL CHARACTERS FROM EACH LINE IN THE HTML FILE SOURCE
	while (fgets(fileLines, BUFSIZ, HtmlFile) != NULL) {
		strcat(bigString, fileLines);
	}
	//PASS BIGSTRING INTO FUNCTION THAT COUNTS THEN RETURNS PROPER TAGS

	while (taskReader[0] != '\n') {
		fgets(taskReader, BUFSIZ, stdin);
		int nameLength = strlen(taskReader);
		taskReader[nameLength - 1] = '\0';

		char nextChar = taskReader[0];

		switch (nextChar) {

		case 'C':
		case 'c':
			tagNumbers = parser(bigString);
			printf("%i\n", tagNumbers);
			printf("Ready\n");
			break;
		case 'T':
		case 't':
			parserHeader(bigString);
			printf("Ready\n");
			break;
		case 'U':
		case 'u':
			parserUrl(bigString);
			printf("Ready\n");
			break;
		case 'Q':
		case 'q':
			printf("Complete\n");
			break;
		}
		if (taskReader[0] == 'q') {
			break;
		}
	}

	pclose(HtmlFile);
	free(bigString);
	return EXIT_SUCCESS;
}

//SEARCHES THROUGH ARRAY FOR SRC THING MAKES SURE THE SPACE PREVIOUS TO THE SRC IS BLANK THEN INCREMENTS
//BOTH PROPERTAGS (AMOUNT OF TAGS) AND INCREMENTS TO THE NEXT CHARACTER IN THE STRING

int parser(char string1[]) {
	char *individualLetter = string1;
	int properTags = 0;
	char keyWord[] = "src=\"";
	while (individualLetter) {
		individualLetter = strstr(individualLetter, keyWord);
		if (individualLetter == NULL) {
			break;
		}
		if (individualLetter && isspace(*(individualLetter - 1))) {
			properTags++;

		}

		individualLetter++;
	}
	return properTags;
}
//DOES WHAT PARSER DOES HOWEVER WHILE WE FIND EACH TAG  WE ITERATE BACKWARDS FROM THE SRC TAG UNTIL < IS FOUND
// THEN WE ITERATE FORWARD THE AMOUNT OF TIMES WE ITERATED BACKWARDS PRINTING EACH CHARACTER IN THE PROCESS

void parserHeader(char string2[]) {
	char *individualLetter = string2;
	char keyWord[] = "src=\"";
	while (individualLetter) {
		individualLetter = strstr(individualLetter, keyWord);
		if (individualLetter == NULL) {
			break;
		}
		if (individualLetter && isspace(*(individualLetter - 1))) {

			int x = 0;
			while (*(individualLetter - x) != '<') {
				x++;
		}
			int i = 0;
			while(!isspace(*(individualLetter - x + i))){
				i++;
				printf("%c", *(individualLetter - x + i));
			}
				printf("\n");
			}

		individualLetter++;
	}

}
//REPLICATES PARSER FUNCTION HOWEVEVER-- FINDS THE FIRST QUOTES MARKS AND ADDS HOW MANY TIMES IT TAKES
// THEN FINDS THE AMOUNT TO THE NEXT AMOUNT OF QUOTES AND PRINTS ALONG THE WAY


void parserUrl(char string3[]) {
	char *individualLetter = string3;
	char keyWord[] = "src=\"";
	while (individualLetter) {
		individualLetter = strstr(individualLetter, keyWord);
		if (individualLetter == NULL) {
			break;
		}
		if (individualLetter && isspace(*(individualLetter - 1))) {
			int x = 0;
			while (*(individualLetter + x) != '"') {
				x++;
				;
			}

			int i = 0;
			while (*(individualLetter + i + x + 1) != '"') {
				i++;
				printf("%c", *(individualLetter + i + x));

			}
			printf("\n");
		}

		individualLetter++;
	}

}
