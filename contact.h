#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct
{
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct
{
    int contactCount;
    Contact contacts[100];
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *addressBook);
void display(AddressBook *addressBook);
int valid_name(AddressBook *addressBook, char *str);
int valid_phone(AddressBook *addressBook, char *phone_num);
int valid_email(AddressBook *addressBook, char *email_id);
void searchname(AddressBook *addressBook);
void searchbyNumber(AddressBook *addressBook);
void searchEmail(AddressBook *addressBook);
void editname(AddressBook *addressBook, int i);
void editMobilenum(AddressBook *addressBook, int i);
void editEmail(AddressBook *addressBook, int i);
//void saveAndExit(AddressBook *addressBook);

#endif
