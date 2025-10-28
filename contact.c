/*Name: Jyotshna Rowlajanni
Date:17-09-2025
Description: Program to design AddressBook with list of contacts contains name,phone numberand email_id, initialisation of contacts, save and exit, creating
contacts with validations, Searching the contacts, editing the contacts, and deleting the contacts*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"

void listContacts(AddressBook *addressBook)
{
// Sort contacts based on the chosen criteria
    for (int i = 0; i < addressBook->contactCount - 1; i++) // outer for loop is to check the index from 0 to n-1
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) // inner for loop is to check 0 to n-i-1 (j is changed but i is changed after the whole inner loop complete )
        {
            if (strcasecmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0) // this to check the consecutive index elemets if arr[j] > arr[j+1] is true then do swap if false don't swap
            {
                Contact temp = addressBook->contacts[j];                 // 1st take a temp new element to store the 1st index
                addressBook->contacts[j] = addressBook->contacts[j + 1]; // 1st index is assign to equals consecutive index element
                addressBook->contacts[j + 1] = temp;                     // this consecutive element is assigned to temp element
            } // swapping done
        }
    }
        
    display(addressBook); // Display sorted contacts
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

// Validate if the name has only alphabets
int valid_name(AddressBook *addressBook, char *str)
{
    int i = 0;
    while (str[i] != '\0') // Loop through string until end
    {
        //if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) // only alphabets are valid
        if (!isalpha(str[i]) && str[i] != ' ') // Only letters and spaces allowed
        {
            return 1; // InValid character found
        }
        i++; // Move to next character
    }
    return 0; // valid if  alphabet found
}

// Validate phone number for 10 digits
int valid_phone(AddressBook *addressBook, char *phone_num)
{
    if (strlen(phone_num) != 10) // Check if length is exactly 10
    {
        return 0; // Invalid phone number
    }
    for (int i = 0; i < 10; i++)
    {
        if (phone_num[i] < '0' || phone_num[i] > '9')
        {
            return 0; // Invalid character (not a digit)
        }
    }
    return 1; // Valid phone number
}

// Validate Email
int valid_email(AddressBook *addressBook, char *email_id)
{
    int len = strlen(email_id);
    int at_count = 0, at_index = -1;
    int dot_index = -1;
    // 1. Check for only lowercase letters
    for (int i = 0; i < len; i++)
    {
        // email contains lowercase letters, digits, '@', and '.'
        if (!((email_id[i] >= 'a' && email_id[i] <= 'z') || (email_id[i] >= '0' && email_id[i] <= '9') || email_id[i] == '.' || email_id[i] == '@'))
        {
            printf("Invalid email: Contains forbidden characters.\n");
            return 0;
        }
    }

    // Find the position of @  and count of '@'
    for (int i = 0; i < len; i++)
    {
        if (email_id[i] == '@')
        {
            at_count++;
            at_index = i;
        }
    }

    // 2. Check '@'  present one time only
    if (at_count != 1)
    {
        printf("Invalid email: Must contain exactly one '@'.\n");
        return 0;
    }
    // 3.check for @ start 1st position
    if (at_index == 0)
    {
        printf("Invalid email: Cannot start with '@'.\n");
        return 0;
    }

    // 4. Check for ".com" at the end
    if (len < 5 || strcmp(email_id + len - 4, ".com") != 0)
    {
        printf("Invalid email: Does not end with '.com'.\n");
        return 0;
    }

    // Find the last dot's position to check  '@'
    dot_index = len - 4; //  index of '.' and ".com"

    // 5. Check for at least one character between '@' and '.com'
    if (at_index >= dot_index - 1)
    {
        printf("Invalid email: At least one character must be present between '@' and '.com'.\n");
        return 0;
    }

    return 1; // email is valid

}
// Create a new contact
void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */
    char str[100];      // To store name
    char phone_num[11]; // To store phone number
    char email_id[50];  // To store email
    int flag;
    // Get and validate name
    do
    {
        flag = 0; // Reset flag
        printf("Enter Name:");
        getchar();                             // Clear buffer
        scanf("%[^\n]", str);                  // Take full line input for name
        if (valid_name(addressBook, str) == 0) // Check if valid
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name, str); // Store name
            flag = 0;
        }
        else // Invalid name
        {
            printf("Invalid Name");
            flag = 0;
            return;
        }
    } while (flag == 1);

    // Get and validate phone number
    do
    {
        flag = 0;
        printf("Enter Number:");
        scanf("%s", phone_num);
        if (valid_phone(addressBook, phone_num) == 0) // Invalid if not 10 digits
        {
            printf("Invalid Phone number\n");
            flag = 1;
            return;
        }
        // Check for duplicate phone number
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, phone_num) == 0)
            {
                printf("Phone Number already exists\n");
                flag = 1;
                return;
            }
        }
    } while (flag == 1);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone_num); // Store phone number

    // Get and validate emailid
    do
    {
        flag = 0;
        printf("Enter email: ");
        getchar(); // Clear buffer
        scanf("%s", email_id);

        if (!valid_email(addressBook, email_id)) // If invalid email
        {
            flag = 1;
            continue;
            // return;
        }

        // Duplicate email check
        for (int j = 0; j < addressBook->contactCount; j++)
        {
            if (strcmp(addressBook->contacts[j].email, email_id) == 0)
            {
                printf("Email already exists\n");
                flag = 1;
                break;
            }
        }

    } while (flag == 1);

    strcpy(addressBook->contacts[addressBook->contactCount].email, email_id); // Store email
    addressBook->contactCount++;                                              // Increment total contacts
    display(addressBook);                                                     // Display updated list

}

// Search for a contact by name, phone, or email
void searchContact(AddressBook *addressBook)
{
    /* Define the logic for search */
    int choices;
    // Display search options
    printf("For Searching:\n");
    printf("  1. By Name\n");
    printf("  2. By phone\n");
    printf("  3. By email\n");
    // printf("4.Exit:\n");
    printf("Enter your choice:");
    scanf("%d", &choices);

    switch (choices)
    {
        case 1: // by name
            searchname(addressBook);
            break;

        case 2: // search by phone number
            searchbyNumber(addressBook);
            break;

        case 3: // search by email
            searchEmail(addressBook);
            break;

        default: // other than choices
            printf("Invalid choice. Please try again.\n");
            break;
    }
}
void searchname(AddressBook *addressBook)
{
    int flag = 0;
    char str[100];
    printf("Enter Name to search : ");
    scanf(" %[^\n]", str);
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, str) == 0) // Compare names
        {
            printf("\nContact Found:\n"); // print the contact details
            printf("---------------------------------------------------------------\n");
            printf("| %-3s | %-20s | %-12s | %-25s \n", "S.No", "Name", "Phone", "Email");
            printf("---------------------------------------------------------------\n");
            printf("| %-3d | %-20s | %-12s | %-25s \n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            printf("---------------------------------------------------------------\n");
            flag = 1;
            // break; // Exit after finding the contact
        }
    }
    if (flag == 0)
    {
        printf("Contact Not Found\n");
    }
}
void searchbyNumber(AddressBook *addressBook)
{
    int flag = 0;
    char phone_num[11];
    printf("Enter Phone number to search : ");
    getchar(); // Clear buffer
    scanf("%s", phone_num);
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone_num) == 0) // compare numbers
        {
            printf("\nContact Found:\n"); // print the contact details
            printf("---------------------------------------------------------------\n");
            printf("| %-3s | %-20s | %-12s | %-25s \n", "S.No", "Name", "Phone", "Email");
            printf("---------------------------------------------------------------\n");
            printf("| %-3d | %-20s | %-12s | %-25s \n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            printf("---------------------------------------------------------------\n");
            flag = 1;
        }
    }
    if (!flag)
    {
        printf("Contact Not Found\n");
    }
}
void searchEmail(AddressBook *addressBook)
{
    int flag = 0;
    char email_id[50];
    printf("Enter Email to search : ");
    getchar(); // Clear buffer
    scanf("%s", email_id);
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email_id) == 0) // compare emails
        {
            printf("\nContact Found:\n"); // print the contact details
            printf("---------------------------------------------------------------\n");
            printf("| %-3s | %-20s | %-12s | %-25s \n", "S.No", "Name", "Phone", "Email");
            printf("---------------------------------------------------------------\n");
            printf("| %-3d | %-20s | %-12s | %-25s \n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            printf("---------------------------------------------------------------\n");
            flag = 1;
        }
    }
    if (!flag)
    {
        printf("Contact Not Found\n");
    }
}
// edit a existing contact
void editContact(AddressBook *addressBook)
{
    int flag = 0;
    int s_no = -1;
    char new_name[100];
    char new_phone[11];
    char new_email[55];
    int index ;

    // First, search for the contact to edit
    searchContact(addressBook);

    // Ask which index user wants to edit
    printf("Enter the serial number of the contact you want to edit: ");
    scanf("%d", &s_no);
    index = s_no - 1;

    int choices;
    do
    {
        printf("\n------ Edit Contact Menu ------\n");
        printf("1. Edit Name\n");
        printf("2. Edit Phone\n");
        printf("3. Edit Email\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choices);

        switch (choices)
        {
            case 1: // Edit name
                printf("Enter New Name: ");
                getchar(); // Clear input buffer
                scanf("%[^\n]", new_name);

                if (valid_name(addressBook, new_name) == 0) // if it is a valid name
                {
                    strcpy(addressBook->contacts[index].name, new_name);
                    printf("Name updated successfully!\n");
                }
                else
                {
                    printf("Invalid Name! Please try again.\n");
                }
                break;

            case 2: // Edit phone number
                printf("Enter New Phone Number: ");
                getchar();
                scanf("%s", new_phone);

                if (valid_phone(addressBook, new_phone) == 1) // if valid number
                {
                    strcpy(addressBook->contacts[index].phone, new_phone);
                    printf("Phone Number updated successfully!\n");
                }
                else
                {
                    printf("Invalid Phone Number! Please try again.\n");
                }
                break;

            case 3: // Edit email
                printf("Enter New Email: ");
                getchar();
                scanf("%s", new_email);

                if (valid_email(addressBook, new_email) == 1) // if valid email
                {
                    strcpy(addressBook->contacts[index].email, new_email);
                    printf("Email updated successfully!\n");
                }
                else
                {
                    printf("Invalid Email! Please try again.\n");
                }
                break;

            case 4: // Exit menu
                printf("Exiting from editing menu.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choices != 4); // Repeat until exit
}


    // delete a contact
void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deletecontact */
    int s_no = -1;
    int index ;
    searchContact(addressBook); // Search to find contact index
    printf("Enter serial number:\n");
    scanf("%d", &s_no);
    index = s_no - 1;

    // Shift contacts left to overwrite deleted contact
    for (int i = index; i < addressBook->contactCount - 1; i++)
    {
        strcpy(addressBook->contacts[i].name, addressBook->contacts[i + 1].name);
        strcpy(addressBook->contacts[i].phone, addressBook->contacts[i + 1].phone);
        strcpy(addressBook->contacts[i].email, addressBook->contacts[i + 1].email);
    }
    // Step 5: Decrement contact count
    addressBook->contactCount--;
    printf("Contact deleted successfully!\n");
}
    // display contact
void display(AddressBook *addressBook)
{
    /*for (int i = 0; i < addressBook->contactCount; i++) //loop throuh contacts
    {
    printf("S.No: %d\n", i + 1); //to print serial number
    printf("Name : %s\n", addressBook->contacts[i].name);
    printf("Phone : %s\n", addressBook->contacts[i].phone);
    printf("Email : %s\n", addressBook->contacts[i].email);
    }*/
    printf("---------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-12s | %-25s \n", "S.No", "Name", "Phone", "Email");
    printf("---------------------------------------------------------------\n");
    // contact will displayed by alphabetical order
    for (int i = 0; i < addressBook->contactCount; i++) // loop throuh contacts
    {
        printf("| %-3d | %-20s | %-12s | %-25s \n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}   
