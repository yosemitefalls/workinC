/*
 * address_book.c
 *
 *  Created on: Apr 17, 2018
 *      Author: ajbernstein
 */
#include "address_book.h"
char loadedLines[BUFSIZ + 1];

Contact * CreateContact(char *pInfo) {
	Contact * pContactNewContact = (Contact *) malloc(sizeof(Contact));

	int x = 0;
	if (pContactNewContact) {
		char *token = strtok(pInfo, ",");
		while (token != NULL) {
			x++;
			if (x == 1) {
				strcpy(pContactNewContact->lastName, token);
			}

			if (x == 2) {
				strcpy(pContactNewContact->firstName, token);

			}
			if (x == 3) {
				strcpy(pContactNewContact->email, token);

			}
			if (x == 4) {
				strcpy(pContactNewContact->phoneNumber, token);
				pContactNewContact->pNext = NULL;
				pContactNewContact->pPrev = NULL;
			}
			token = strtok(NULL, ",\n");
		}
	}
	return pContactNewContact;
}
Contact * InsertContact(int insertLevel, char *pInfo, AddressBook *myList) {
	Contact * pContactNew;
	pContactNew = CreateContact(pInfo);
	int x = 0;
	pContact pCurNode;  //current node pointer

	if (insertLevel == 0) {
		pContactNew->pPrev = NULL;
		pContactNew->pNext = (myList->pFirst);
		if ((myList->pFirst))
			(myList->pFirst)->pPrev = pContactNew;

		(myList->pFirst) = pContactNew;
	} else {
		pCurNode = myList->pFirst;
	}

	while (x != insertLevel) {
		x++;

		if (x == insertLevel) /* not inserting at beginning of list */
		{

			pContactNew->pPrev = pCurNode;
			pContactNew->pNext = pCurNode->pNext;
			pCurNode->pNext = pContactNew;
			if (pContactNew->pNext) { /* Verify there is a next Person */
				pContactNew->pNext->pPrev = pContactNew;
				//pContactNew->pNext = pCurNode->pPrev->pNext;
			}

		} else {
			pCurNode = pCurNode->pNext;
		}

	}
	return (pContactNew);
}

void DelContact(int deleteLevel, AddressBook *myList) {
	int x = 0;
	pContact deleteThisNode;
	pContact pCurNode = myList->pFirst; //current node pointer

	if (deleteLevel == 0) {

		if (pCurNode->pNext) /* not the only Person in list */
		{
			deleteThisNode = pCurNode;

			pCurNode = pCurNode->pNext;
			pCurNode->pPrev = NULL;
			myList->pFirst = pCurNode;
			free(deleteThisNode);
			return;
		} else /* only Person in list */
		{
			free(pCurNode);
			myList->pFirst = NULL;
			return;
		}
	}
	while (x != deleteLevel + 1) {
		x++;

		if (x == deleteLevel + 1) {
			if (pCurNode->pNext) /* not the last Person in the list */
			{
				//pCurNode = pCurNode->pNext;
				deleteThisNode = pCurNode;
				pCurNode->pPrev->pNext = pCurNode->pNext;
				pCurNode->pNext->pPrev = pCurNode->pPrev;
				free(deleteThisNode);

			} else /* deleting last Person in list */
			{
				//pCurNode = pCurNode->pNext;
				deleteThisNode = pCurNode;
				pCurNode = pCurNode->pPrev;
				pCurNode->pNext->pPrev = NULL;
				pCurNode->pNext = NULL;
				free(deleteThisNode);
			}
		} else {
			pCurNode = pCurNode->pNext;

		}
	}

}

int getCount(AddressBook* myList) {
	int count = 0;
	Contact* cursor = myList->pFirst;
	while (cursor != NULL) {
		count++;
		cursor = cursor->pNext;
	}
	return count;
}

void load(char *fileName, AddressBook *myList) {
//	FILE *extractedfile = popen(fileName, "r");
//
//	//ALLOCATES PROPER SIZE(MEMORY) TO STRING AT HAND THEN MAKES SURE WE REWIND TO BEGGINNING OF FILE
//	fseek(extractedfile, 0, SEEK_END);
//	int sizeofFile = ftell(extractedfile);
//	char* bigString = (char*) malloc(sizeofFile + 1);
//	rewind(extractedfile);
//	pContact pCurNode;
//	pCurNode = myList->pFirst;
//	int lineCounter = 0;
//	//counters lines in the file
//	while (pCurNode->pNext) {
//		pCurNode = pCurNode->pNext;
//		lineCounter++;
//	}
//	//stores lines in string
//	while (fgets(loadedLines, BUFSIZ, extractedfile) != NULL) {
//		strcat(bigString, loadedLines);
//	}
//	char *token;
//	token = strtok(bigString, "\n");
//	int skipFirst = 0;
//
//	pCurNode = myList->pFirst;
//	//while there are new lines
//	while (token != NULL) {
//		//skips first because of unwanted header on file
//		if (skipFirst == 0) {
//			token = strtok(NULL, "\n");
//			skipFirst++;
//		}
//		//if there is a node in existence increment line counter by one and insert there
//		if (myList->pFirst) {
//			lineCounter++;
//			InsertContact(lineCounter, token, myList);
//			token = strtok(NULL, "\n");
//		}
//		//if it starts at the beggining set counter (base ==null) - insert level to 0 and insert there- will only
//		//trigger once
//		else {
//			lineCounter = 0;
//			InsertContact(lineCounter, token, myList);
//			token = strtok(NULL, "\n");
//		}
//	}
	int count = getCount(myList);
	FILE * extractedFile = fopen(fileName, "r");
	char info[BUFSIZ];
	fgets(info, BUFSIZ, extractedFile);
	while(fgets(info, BUFSIZ, extractedFile) != NULL){
		InsertContact(count++, info, myList);
	}

}
void save(char *filenameOut, AddressBook *myList) {

	FILE* OutFile = fopen(filenameOut, "w");
	pContact pCurNode = myList->pFirst;
	fprintf(OutFile, "lastName,firstName,email,phoneNumber\n");

	while (pCurNode->pNext) {
		fprintf(OutFile, "%s", pCurNode->lastName);
		fprintf(OutFile, ",");
		fprintf(OutFile, "%s", pCurNode->firstName);
		fprintf(OutFile, ",");
		fprintf(OutFile, "%s", pCurNode->email);
		fprintf(OutFile, ",");
		fprintf(OutFile, "%s\n", pCurNode->phoneNumber);
		pCurNode = pCurNode->pNext;
		if(pCurNode->pNext == NULL){
			fprintf(OutFile, "%s", pCurNode->lastName);
			fprintf(OutFile, ",");
			fprintf(OutFile, "%s", pCurNode->firstName);
			fprintf(OutFile, ",");
			fprintf(OutFile, "%s", pCurNode->email);
			fprintf(OutFile, ",");
			fprintf(OutFile, "%s\n", pCurNode->phoneNumber);
		}
	}
}
Contact *GetContacts(int retreivalLevel, Contact *Contactz, AddressBook *myList) {
	pContact pCurNode = myList->pFirst;
	int x = 0;
	while (x != retreivalLevel) {
		pCurNode = pCurNode->pNext;
		x++;
	}
	return pCurNode;
}



