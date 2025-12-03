# 📒 **Address Book Design (C Project)**

A modular Contact Management System built in C, implementing full CRUD operations with CSV file handling and structured programming practices.

---

## 🚀 **Project Overview**

This **Address Book Management System** is a command-line application developed in C for managing contact information efficiently. It allows users to add, search, edit, delete, and display contacts, with all records stored in a CSV file for persistence.

The goal of this project was to understand how data management systems work internally by implementing core operations manually using C concepts like structures, file handling, and modularization.

---

## 📂 **Project Structure**

```
📁 AddressBook-NewDesign
│
├── main.c          # Main menu and program flow
├── contact.c       # Core contact operations (add, edit, delete, search, display)
├── contact.h       # Header file for contact module
│
├── file.c          # CSV file reading and writing
├── file.h          # Header file for file I/O operations
│
├── contacts.csv    # Persistent storage for contacts
│
└── README.md
```

---

## 🧩 **Features**

### ✅ Add New Contact

Stores:

* Name
* Phone Number
* Email

### ✅ Display All Contacts

Prints all contacts in a clean, formatted output.

### ✅ Search Contacts

Search by:

* Name
* Phone
* Mail
### ✅ Edit Contact

Modify any stored field with input validation.

### ✅ Delete Contact

Removes a selected contact safely from the list and updates the CSV file.

### ✅ Persistent Storage (CSV)

All contacts are saved in `contacts.csv` and loaded automatically on startup.

### ✅ Modular Design

Separate `.c` and `.h` files help maintain clean code architecture.

---

## 🛠️ **Technologies & Concepts Used**

| Concept               | Purpose                      |
| --------------------- | ---------------------------- |
| C Programming         | Core application logic       |
| Structures (`struct`) | Contact data model           |
| File Handling (CSV)   | Persistent storage           |
| String Handling       | Search, compare, update data |
| Modular Programming   | Organized and reusable code  |
| Basic Validation      | Avoid invalid inputs         |

---

## ▶️ **How to Compile & Run**

### **Compile:**

```bash
gcc main.c contact.c file.c -o addressbook
or
gcc *c
```

### **Run:**

```bash
./addressbook
or
./a.out
```

---

## 📜 **CSV File Example**

```
Name,Phone,Email
Alice Roy,9123456789,alice@gmail.com
John Doe,9876543210,john@gmail.com
```

---

# 🚧 **Future Improvements**


### 🔹 **1. Enhanced User Interface**

* Better menu formatting
* Color-coded output (Linux ANSI colors)

### 🔹 **2. Switch to Database Storage**

* SQLite for scalability
* Faster search and indexing

### 🔹 **3. Add Undo/Delete Recovery**

* Temporary backup for restoring deleted entries



## 🧑‍💻 **Author**

**Jyotshna Rowlajanni**
*Embedded Systems & C Programming Enthusiast*
