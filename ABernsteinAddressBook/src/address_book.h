/*
 * address_book.h
 *
 *  Created on: Apr 17, 2018
 *      Author: ajbernstein
 *
 *      we define a young structure in this
 */

#ifndef ADDRESS_BOOK_H_
#define ADDRESS_BOOK_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct contact Contact;
typedef Contact* pContact;

struct contact {
	char firstName[256];
	char lastName[256];
	char email[256];
	char phoneNumber[256];
	Contact *pNext;
	Contact *pPrev;
};
typedef struct addressBook AddressBook;
struct addressBook {
	pContact pFirst;

};


Contact *CreateContact(char *word);
Contact *InsertContact(int insertLevel, char *name, AddressBook *myList);
void DelContact(int deleteLevel, AddressBook *myList);
Contact *GetContacts(int retreivalLevel, Contact *Contactz, AddressBook *myList);
void load(char* fileName, AddressBook *myList);
void save(char* filenameOut, AddressBook *myList);
#endif /* ADDRESS_BOOK_H_ */

