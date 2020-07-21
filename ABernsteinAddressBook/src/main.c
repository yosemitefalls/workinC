/*
 ============================================================================
 Name        : ABernsteinAddressBook.c
 Author      : Aidan Bernstein
 Version     :
 Copyright   : Your copyright notice
 Description : bang bang - last assignment
 basically we use structures with a doubly linked list to store a set of contacts. we can alter
 these contacts within the strucuture defined and it does a whole lot of other jimmies see adressbbook.c
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>
#include "address_book.h"

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	AddressBook myList;
	myList.pFirst = NULL;
	Contact *MyContacts = NULL;
	Contact *pContactCur = NULL; /* current Person */
	Contact *pContactCurX = NULL;
	FILE *OutFile;
	char taskReader[BUFSIZ + 1];
	char buffer[BUFSIZ + 1];
	char bufferTwo[BUFSIZ + 1];
	char bufferThree[BUFSIZ + 1];
	char bufferFour[BUFSIZ + 1];
	char bufferFive[BUFSIZ + 1];
	char bufferSix[BUFSIZ + 1];
	char fileName[BUFSIZ + 1];
	char lastName[] = "lastName";
	char firstName[] = "firstName";
	char email[] = "email";
	char phoneNumber[] = "phoneNumber";
	char filenameOut[BUFSIZ + 1];

	printf("Ready\n");

	while (taskReader[0] != '\n') {
		fgets(taskReader, BUFSIZ, stdin);
		int nameLength = strlen(taskReader);
		taskReader[nameLength - 1] = '\0';
		char nextChar = taskReader[0];

		switch (nextChar) {
		case 'a':
			fgets(buffer, BUFSIZ, stdin);
			buffer[strlen(buffer) - 1] = '\0';
			fgets(bufferTwo, BUFSIZ, stdin);
			bufferTwo[strlen(bufferTwo) - 1] = '\0';
			int numbaX = atoi(buffer);
			InsertContact(numbaX, bufferTwo, &myList);
			//InsertContact(numbaX, bufferTwo, myList);
			break;
		case 'd':
			fgets(bufferThree, BUFSIZ, stdin);
			bufferThree[strlen(bufferThree) - 1] = '\0';
			int Numba = atoi(bufferThree);
			if (Numba < getCount(&myList)) {
				DelContact(Numba, &myList);
			}

			break;
		case 'g':
			fgets(bufferFour, BUFSIZ, stdin);
			bufferFour[strlen(bufferFour) - 1] = '\0';
			int numbaZ = atoi(bufferFour);
			pContactCur = GetContacts(numbaZ, MyContacts, &myList);
			printf("%s", pContactCur->lastName);
			printf(",");
			printf("%s", pContactCur->firstName);
			printf(",");
			printf("%s", pContactCur->email);
			printf(",");
			printf("%s\n", pContactCur->phoneNumber);

			break;
		case 'n':
			printf("%i\n", getCount(&myList));
			break;
		case 'f':
			fgets(bufferFive, BUFSIZ, stdin);
			bufferFour[strlen(bufferFive) - 1] = '\0';
			int numbaP = atoi(bufferFive);
			fgets(bufferSix, BUFSIZ, stdin);
			bufferSix[strlen(bufferSix) - 1] = '\0';
			pContactCurX = GetContacts(numbaP, MyContacts, &myList);
			if (strcmp(lastName, bufferSix) == 0) {
				printf("%s\n", pContactCurX->lastName);
			}
			if (strcmp(firstName, bufferSix) == 0) {
				printf("%s\n", pContactCurX->firstName);
			}
			if (strcmp(email, bufferSix) == 0) {
				printf("%s\n", pContactCurX->email);
			}
			if (strcmp(phoneNumber, bufferSix) == 0) {
				printf("%s\n", pContactCurX->phoneNumber);
			}

			break;

		case 'l':
			fgets(fileName, BUFSIZ, stdin);
			fileName[strlen(fileName) - 1] = '\0';
			load(fileName, &myList);
			break;
		case 's':

			fgets(filenameOut, BUFSIZ, stdin);
			int nameLengthTwo = strlen(filenameOut);
			filenameOut[nameLengthTwo - 1] = '\0';
			save(filenameOut, &myList);

			break;
		case 'q':
			printf("Complete\n");
			break;
		}
		if (taskReader[0] == 'q') {
			break;
		}
	}
	return EXIT_SUCCESS;
}
