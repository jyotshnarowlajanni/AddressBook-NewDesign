/*
Name: Jyotshna Rowlajanni
Date: 17-09-2025
Description: Program to create AddressBook with savecontacts to file, and laodcontacts to file
*/
#include <stdio.h>
#include "file.h"
// Function Definition for saving the contacts
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr; // Declare file pointer
    fptr = fopen("contacts.csv", "w"); // Open the file in write mode ("w")
    fprintf(fptr,"%d\n" , addressBook->contactCount); // Write the number of contacts into AddressBook
    for(int i = 0; i < addressBook->contactCount; i++)// By using loop write the details of each contact
    {
        fprintf(fptr,"%s,%s,%s\n",addressBook -> contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);// Write the contacts details
    }
    fclose(fptr);// Close the file
}
// Function Definition for load the contacts
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr;// Declare file pointer
    fptr = fopen("contacts.csv", "r");// Open the file in read mode ("r")
    fscanf(fptr, "%d\n" ,&addressBook->contactCount);// Read the number of contacts
    
    for(int i = 0; i < addressBook->contactCount; i++)// By using loop, read the details of each contacts
    {
        // Read the contact details
        fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook -> contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
    }
    // Close the file
    fclose(fptr);
}
