# SECUREVAULT – PERSONAL PASSWORD MANAGER

![Project Logo](https://img.shields.io/badge/C%20Programming-Fundamentals-blue?style=for-the-badge)
![GitHub](https://img.shields.io/badge/GitHub-repo-lightgrey?style=for-the-badge)
![VS Code](https://img.shields.io/badge/VS%20Code-0184D5?style=for-the-badge&logo=visual-studio-code&logoColor=white)

---

## Short Description

**SECUREVAULT** is a console-based Personal Password Manager application developed in C as a Programming Fundamentals semester project. The application demonstrates core C programming concepts while providing practical password vault functionality for managing website accounts, security logs, and user authentication.

Built using **only C language (C11 standard)** with **modular architecture** using `.c` and `.h` files, SECUREVAULT stores data in plain text files and implements educational cryptography demonstrations. The project is suitable for a four-member university group project and covers all 15 mandatory Programming Fundamentals concepts.

**Important Security Notice**: This project uses **educational XOR-based encryption and hash functions for demonstration purposes only**. These are **NOT secure cryptographic implementations** and should not be used for protecting real credentials. A production password manager requires professionally reviewed cryptography (AES-256-GCM, PBKDF2-HMAC-SHA256, etc.).

---

## Project Overview

### What is SecureVault?

SECUREVAULT is a console-based application that allows users to register accounts, log in, and manage their password vault. The application stores website accounts with associated usernames, passwords, categories, and notes in text files.

### Why was it developed?

This project was developed as a **Programming Fundamentals semester coursework** to demonstrate mastery of C language concepts, modular programming, file handling, and basic password management principles. It serves as a practical learning tool for university students.

### Problem Statement

The project addresses the need for a simple, educational password management system that helps students understand:
- How C programming concepts apply to real-world scenarios
- File-based data storage and retrieval
- User authentication and session management
- Basic input validation and error handling
- Modular program structure

### Main Purpose

The main purpose of SECUREVAULT is to provide a functional password vault manager that:
- Demonstrates all 15 Programming Fundamentals concepts
- Implements user registration and authentication
- Provides password storage and retrieval
- Includes security logging and history tracking
- Generates statistics and reports
- Shows recursive search and dynamic memory management

---

## Project Objectives

| # | Objective | Description |
|---|-----------|-------------|
| 1 | Demonstrate C programming concepts | Apply C11 standard features in working code |
| 2 | Implement modular programming | Use separate .c and .h files for each module |
| 3 | Practice file handling | Handle file operations (read, write, create, error checking) |
| 4 | Implement record management | Manage account records with add/view/search/update/delete |
| 5 | Understand basic password management | Password strength checking, generation, and hashing |
| 6 | Practice Git workflow | Commit and push features individually |
| 7 | Create university documentation | Comprehensive project report and viva questions |

---

## Key Features

### User Authentication

- **User Registration**: Users can register with a username and password. Passwords must be at least 8 characters long. Duplicate usernames are prevented. Password hashing is implemented using an educational hash function.

- **User Login and Login Attempt Limits**: Users can log in with their credentials. The system limits login attempts to 3 before the account is temporarily locked. Failed attempts are tracked and logged.

- **Master Password Verification**: During login, the provided password is verified against the stored hash in the users file. Incorrect attempts increment the failure counter.

- **Temporary Account Lockout**: After 3 failed login attempts, the account is locked and further login attempts are blocked until the application is restarted.

- **Logout**: Users can securely log out, which resets the failed attempt counter.

### Password Vault

- **Add Website/Application Account**: Users can add new accounts by specifying website name, username/email, password, category, and optional notes. Accounts are stored in the vault file.

- **View Saved Accounts**: All saved accounts can be viewed with their complete details (website, username, password, category, notes).

- **Search Accounts**: Accounts can be searched by website name. The search scans the vault file for matching entries.

- **Update Accounts**: Account details can be updated, including password and other fields. The system logs update events.

- **Delete Accounts**: Accounts can be deleted from the vault. Deletion events are logged.

- **Display Total Saved Accounts**: The application counts and displays the total number of accounts stored in the vault.

### Password Security

- **Password Strength Checker**: Evaluates passwords based on length (minimum 8 characters), presence of uppercase letters, lowercase letters, and digits. Reports "STRONG" if all criteria are met, otherwise suggests improvements.

- **Random Password Generator**: Generates random passwords of user-specified length using a character set of uppercase, lowercase, digits, and special characters.

- **Master Password Hashing**: Passwords are hashed using an educational hash function ( Jenkins-like hash) before storage. The hash is displayed as a hexadecimal value.

- **Password Validation**: Passwords are validated during registration (minimum 8 characters) and login.

### Security History

- **Successful Login Events**: Successful logins are logged to a security log file with timestamps and user information.

- **Failed Login Events**: Failed login attempts are logged, including the number of attempts and account lockout events.

- **Account Creation Events**: When a new account is added, the event is logged to the security logs file.

- **Account Deletion Events**: When an account is deleted, the event is logged.

- **Security Logs**: All security events can be viewed through the application's security logs feature.

- **Login History**: A separate file tracks login history, distinguishing between successful and failed login attempts.

### Reports

- **Total Registered Users**: Counts and displays the total number of registered users from the users file.

- **Total Saved Accounts**: Counts and displays the total number of accounts in the vault.

- **Category-wise Statistics**: Reports statistics organized by account categories.

- **Password Strength Statistics**: Analyzes and reports on the strength of stored passwords.

- **Security Activity Reports**: Provides an overview of security events and login activity.

### Advanced Concepts

- **Recursive Binary Search**: Implemented in `search_utils.c`, this feature performs binary search on sorted account records using a recursive algorithm.

- **Dynamic Memory Management**: The `file_manager.c` module demonstrates `malloc`, `calloc`, `realloc`, and `free` for dynamic memory allocation and cleanup.

- **File-Based Data Storage**: All data (users, vault, logs) is stored in text files rather than a database, demonstrating file handling concepts.

- **Encryption Demonstration**: A simple XOR-based encryption is implemented in `encryption.c` for educational purposes only. This demonstrates key derivation from passwords and basic encryption/decryption concepts.

---

## Technology Stack

| Category | Specification |
|----------|-------------|
| **Programming Language** | C (C11 standard) |
| **IDE** | Visual Studio Code |
| **Compiler** | GCC (tested on Windows 11) |
| **Standard Libraries** | `<stdio.h>`, `<stdlib.h>`, `<string.h>`, `<time.h>`, `<ctype.h>` |
| **Storage** | Text files only (no database) |
| **Version Control** | Git |
| **Repository Hosting** | GitHub |
| **VS Code Extensions** | C/C++, Debugger, tasks.json, launch.json |

### Verified Tools

- **GCC**: `gcc --version` returns the installed version
- **Git**: `git --version` returns the installed version

---

## Project Architecture

SECUREVAULT uses a **modular architecture** with separate source files responsible for specific functionality. The main modules are:

| Module | File(s) | Responsibility |
|--------|---------|----------------|
| **Configuration** | `config.h` | Global constants, macros, and file paths |
| **Authentication** | `auth.c`, `auth.h` | User registration, login, logout, attempt tracking |
| **User Management** | `users.c`, `users.h` | User file operations, existence checks, data storage |
| **Password Vault** | `vault.c`, `vault.h` | Add, view, search, update, delete accounts |
| **Password Security** | `password.c`, `password.h` | Strength checker, random password generation |
| **File Management** | `file_manager.c`, `file_manager.h` | Dynamic memory, save/load data, file operations |
| **Security Logs** | `security_logs.c`, `security_logs.h` | Log events, view security history |
| **Login History** | `history.c`, `history.h` | Track successful/failed login events |
| **Reports** | `reports.c`, `reports.h` | Generate user, category, and strength reports |
| **Utility Functions** | `utils.c`, `utils.h` | Input validation, pause, clear buffer |
| **Recursive Search** | `search_utils.c`, `search_utils.h` | Recursive binary search on sorted records |
| **Encryption** | `encryption.c`, `encryption.h` | XOR-based encryption demonstration |

### Data Flow

1. **User Input**: User interacts via console menu (switch statements)
2. **Authentication**: `auth.c` validates credentials against `users.txt`
3. **Vault Operations**: `vault.c` manages account records in `vault.txt`
4. **Logging**: `security_logs.c` and `history.c` event logging
5. **Reports**: `reports.c` generates statistics from stored data
6. **Memory Management**: `file_manager.c` handles dynamic allocation/deallocation

---

## Complete Project Directory Structure

```text
SecureVault/
├── main.c                          # Main application entry point with switch-case menu
├── config.h                        # Configuration constants and macros
├── auth.c                          # User authentication (register/login/logout)
├── auth.h                          # Authentication header
├── users.c                         # User management with file storage
├── users.h                         # User structure and functions
├── password.c                      # Password strength checker and generator
├── password.h                      # Password header
├── vault.c                         # Password vault add/view/update/delete
├── vault.h                         # Vault Account structure and functions
├── file_manager.c                  # Dynamic memory management (malloc/calloc/realloc/free)
├── file_manager.h                  # File management header
├── security_logs.c                 # Security event logging
├── security_logs.h                 # Security logs header
├── history.c                       # Login history tracking
├── history.h                       # History header
├── reports.c                       # Statistics and reports module
├── reports.h                       # Reports header
├── utils.c                         # Input validation and utility functions
├── utils.h                         # Utils header
├── search_utils.c                  # Recursive binary search implementation
├── search_utils.h                  # Search utils header
├── encryption.c                    # XOR encryption demonstration (educational only)
├── encryption.h                    # Encryption header
├── data/                           # Data storage directory
│   ├── users.txt                   # Registered users and password hashes
│   ├── vault.txt                   # Saved password vault accounts
│   ├── login_history.txt           # Login success/failure history
│   └── security_logs.txt           # Security event logs
├── docs/                           # Documentation folder
│   ├── project_report.md           # Full project report
│   ├── pseudocode.md               # Project pseudocode
│   ├── testing.md                  # Test results and cases
│   └── viva_questions.md           # Viva questions and answers
├── .vscode/                        # VS Code configuration
│   ├── tasks.json                  # Build tasks
│   ├── launch.json                 # Debug configuration
│   └── c_cpp_properties.json     # IntelliSense configuration
├── README.md                       # Project documentation (this file)
├── .gitignore                      # Git ignore file
└── README.md                       # Project readme
```

### Important Source Files Explained

| File | Purpose |
|------|---------|
| `main.c` | Main entry point, displays main menu and user dashboard, handles user navigation |
| `config.h` | Defines MAX constants, file paths, success/failure macros |
| `auth.c/h` | User registration, login with attempt limits, logout, password hashing |
| `users.c/h` | User file operations, init, add user, check if user exists |
| `vault.c/h` | Add accounts, view all accounts, search, update, delete, count accounts |
| `password.c/h` | Check password strength, generate random passwords |
| `file_manager.c/h` | Dynamic memory allocation, save/load data, clear files |
| `security_logs.c/h` | Log events to security log file, view security logs |
| `history.c/h` | Log login events (success/failed), view login history |
| `reports.c/h` | Generate user reports, category reports, strength reports |
| `utils.c/h` | Pause program, get valid integer input, clear input buffer |
| `search_utils.c/h` | Recursive binary search on sorted websites array |
| `encryption.c/h` | XOR-based encryption/decryption (educational demonstration) |
| `data/users.txt` | Stores: username,password_hash (one per line) |
| `data/vault.txt` | Stores: account records with website, username, password, category, notes |
| `data/login_history.txt` | Stores: login event type (Successful/Failed) |
| `data/security_logs.txt` | Stores: security events (registration, login, lockout, etc.) |

---

## Programming Fundamentals Concepts

The following table summarizes all 15 Programming Fundamentals concepts and their implementation in SECUREVAULT:

| # | Concept | Implementation | Source File(s) |
|---|---------|---------------|----------------|
| 1 | **Variables and Constants** | `MAX_USERNAME_LENGTH`, `MAX_PASSWORD_LENGTH`, `MAX_LOGIN_ATTEMPTS`, and numerous local variables throughout all functions | `config.h`, all `.c` files |
| 2 | **Data Types** | `int`, `char`, `float`, `unsigned int`, and the `Account` and `User` structures | `users.h`, `vault.h`, all `.c` files |
| 3 | **Input and Output** | `printf()` for output, `scanf()` with width specifiers, `fgets()` for safe input, file `fopen()`, `fprintf()`, `fgets()`, `fread()` | `main.c`, `auth.c`, `vault.c`, `file_manager.c` |
| 4 | **Operators** | Arithmetic (`+`, `-`, `*`, `/`, `%`), relational (`==`, `!=`, `<`, `>`), logical (`&&`, `||`, `!`), assignment (`=`, `+=`, `-=`) | `auth.c` (hash calculation), `vault.c` (comparisons), `utils.c` (validation) |
| 5 | **Conditional Statements** | `if`, `if-else`, nested `if`, and `switch-case` for menu navigation and validation | `main.c` (switch), `auth.c` (login validation), `utils.c` (input validation) |
| 6 | **Loops** | `for`, `while`, `do-while` loops for password checking, menu display, input validation | `password.c` (strength check), `utils.c` (input loop), `main.c` (menu) |
| 7 | **Arrays** | One-dimensional arrays for usernames/passwords, two-dimensional arrays for websites matrix in binary search | `users.h` (`User` struct), `search_utils.c` (binary search) |
| 8 | **Strings and String Manipulation` | `strlen()`, `strcmp()`, `strstr()`, `strcpy_s()`, `sprintf_s()`, `getchar()` | All files - string comparison, copying, length calculation |
| 9 | **Functions and Function Calling** | All modules use separate functions; functions call each other across files (e.g., `main.c` calls `auth.c`, `vault.c`) | All `.c` and `.h` files |
| 10 | **Passing Arguments to Functions** | Functions receive parameters: `register_user(const char *username, const char *password)`, `add_account(const Account *acc)`, etc. | All function definitions |
| 11 | **Meaningful Recursion** | `binary_search_accounts()` in `search_utils.c` performs recursive binary search on sorted website records | `search_utils.c` |
| 12 | **Pointers and Pointer Operations** | Pointer parameters (`const char *`, `char *`, `Account *`), pointer arithmetic in string operations, `&input` for scanf | `file_manager.c` (dynamic memory), `auth.c` (hash), `utils.c` (`&input`) |
| 13 | **Structures (struct)** | `struct User` in `users.h` (username, password_hash), `struct Account` in `vault.h` (website, username, password, category, notes) | `users.h`, `vault.h` |
| 14 | **File Handling** | `fopen()`, `fclose()`, `fprintf()`, `fgets()`, `fseek()`, `ftell()`, `rewind()` for all data files | All modules - users.txt, vault.txt, login_history.txt, security_logs.txt |
| 15 | **Dynamic Memory Allocation** | `malloc()`, `free()` in `file_manager.c` for buffer allocation during data loading, `realloc` concepts | `file_manager.c` |

---

## Four-Member Team Contribution

The project was designed with the following suggested division of labor among four team members. **Actual contribution distribution should be confirmed by the group members.**

### Member 1: Authentication and User Management

- **Responsible for**: User registration and login functionality
- **Implemented in**: `auth.c`, `auth.h`, `users.c`, `users.h`, `config.h`
- **Key functions**: `register_user()`, `login_user()`, `logout_user()`, `user_exists()`, `init_users_file()`, `add_user()`, `cleanup_users()`
- **Features**: Username validation, password strength check during registration, login attempt limits, account lockout, password hashing

### Member 2: Password Vault Management

- **Responsible for**: Password vault add, view, search, update, delete functionality
- **Implemented in**: `vault.c`, `vault.h`, `file_manager.c`, `file_manager.h`
- **Key functions**: `add_account()`, `view_accounts()`, `search_account()`, `update_account()`, `delete_account()`, `count_accounts()`
- **Features**: Add website accounts with username/password/category/notes, view all accounts, search by website name, update account details, delete accounts, count total accounts

### Member 3: Password and Security Management

- **Responsible for**: Password security features and encryption demonstrations
- **Implemented in**: `password.c`, `password.h`, `encryption.c`, `encryption.h`, `security_logs.c`, `security_logs.h`
- **Key functions**: `check_password_strength()`, `generate_random_password()`, `encrypt_data()`, `decrypt_data()`, `generate_key_from_password()`, `log_event()`, `view_security_logs()`
- **Features**: Password strength checker (uppercase, lowercase, digit requirements), random password generator, XOR encryption demonstration (educational only), security event logging, login event tracking

### Member 4: File Management, Reports and Integration

- **Responsible for**: File management, reports generation, and main application integration
- **Implemented in**: `file_manager.c`, `file_manager.h`, `reports.c`, `reports.h`, `history.c`, `history.h`, `main.c`
- **Key functions**: `save_data()`, `load_data_dynamic()`, `free_data()`, `clear_data_file()`, `generate_user_report()`, `generate_category_report()`, `generate_strength_report()`, `log_login_event()`, `view_login_history()`, main application loop
- **Features**: Dynamic memory management, file save/load operations, clear data files, user/category/strength reports, login history tracking, main dashboard with all menu options, integration of all modules

---

## System Workflow

### Application Flowchart (Mermaid)

```mermaid
flowchart TD
    A[Start Application] --> B{Main Menu}
    B -->|Choice 1| C[Register]
    B -->|Choice 2| D[Login]
    B -->|Choice 3| E[Exit]
    
    C --> F[Enter username]
    C --> G[Enter password (min 8 chars)]
    C --> H[Check duplicate username]
    C --> I[Hash password, save to users.txt]
    C --> J[Registration successful, return to main menu]
    
    D --> K[Enter username]
    D --> L[Enter password]
    D --> M[Check failed attempts counter]
    M -->|>= 3| N[Account locked, return to main menu]
    M -->|< 3| O[Verify password against stored hash]
    O -->|Incorrect| P[Increment failed attempts, show attempts left]
    P --> Q[Return to main menu]
    O -->|Correct| R[Set logged_in=1, welcome message]
    R --> S[User Dashboard]
    
    S --> T{User Dashboard Menu}
    T -->|1| U[Add New Account]
    T -->|2| V[View All Accounts]
    T -->|3| W[Search Account]
    T -->|4| X[Update Account]
    T -->|5| Y[Delete Account]
    T -->|6| Z[Password Strength Checker]
    T -->|7| AA[Generate Random Password]
    T -->|8| AB[Security Reports]
    T -->|9| AC[View Login History]
    T -->|10| AD[View Security Logs]
    T -->|11| AE[Logout]
    
    U --> AF[Enter website, username, password, category, notes]
    AF --> AG[Check for duplicate, add to vault.txt]
    AG --> AH[Log event, return to dashboard]
    
    V --> AI[Read vault.txt, display all accounts]
    AI --> AH
    
    W --> AJ[Enter website to search]
    AJ --> AK[Search vault.txt for matching website]
    AK --> AL[Display found account or not found message]
    AL --> AH
    
    X --> AL
    Y --> AM[Enter website to delete, remove from vault.txt]
    AM --> AH
    
    Z --> AN[Enter password, check strength criteria]
    AN --> AO[Display STRONG or weakness suggestions]
    AO --> AH
    
    AA --> AP[Enter length, generate random password]
    AP --> AQ[Display generated password]
    AQ --> AH
    
    AB --> AR[Generate user, category, strength reports]
    AR --> AH
    
    AC --> AS[View login_history.txt]
    AS --> AH
    
    AD --> AT[View security_logs.txt]
    AT --> AH
    
    AE --> AU[Reset logged_in=0, clear credentials, return to main menu]
    AU --> B
    
    E --> AV[Goodbye message, exit application]
```

### Complete Workflow Description

1. **Starting the Application**: Run `SecureVault.exe`. The main menu appears with three options: Register, Login, or Exit.

2. **Registration** (Choice 1):
   - User enters a username
   - User enters a password (minimum 8 characters)
   - System checks if username already exists
   - Password is hashed and stored in `users.txt`
   - Registration successful message displayed
   - Returns to main menu

3. **Login** (Choice 2):
   - User enters username and password
   - System checks login attempt counter (max 3 attempts)
   - If account locked (3 failed attempts), message displayed
   - Password verified against stored hash in `users.txt`
   - On success: `logged_in` flag set to 1, user dashboard displayed
   - On failure: attempts counter incremented, attempts left displayed
   - Failed attempts are logged to `login_history.txt` and `security_logs.txt`

4. **User Dashboard**: After successful login, the user dashboard appears with 11 options for account management, security features, and reports.

5. **Adding an Account** (Choice 1):
   - User enters website name, username/email, password, category, and optional notes
   - System checks for duplicate website name
   - Account stored in `vault.txt`
   - Event logged to `security_logs.txt`
   - Success message displayed, return to dashboard

6. **Viewing Accounts** (Choice 2):
   - `vault.txt` is opened and all account records are displayed
   - Total account count shown
   - Returns to dashboard

7. **Searching Accounts** (Choice 3):
   - User enters website name to search
   - System scans `vault.txt` for matching entries
   - If found: account details displayed
   - If not found: "Account not found" message displayed
   - Returns to dashboard

8. **Updating Accounts** (Choice 4):
   - User enters website name to update
   - New password can be provided
   - Update event logged to `security_logs.txt`
   - Success message displayed, returns to dashboard

9. **Deleting Accounts** (Choice 5):
   - User enters website name to delete
   - Account removed from `vault.txt`
   - Deletion event logged to `security_logs.txt`
   - Success message displayed, returns to dashboard

10. **Password Strength Checker** (Choice 6):
    - User enters password to check
    - System evaluates: length >= 8, has uppercase, has lowercase, has digit
    - "STRONG" displayed if all criteria met
    - Weakness suggestions displayed otherwise

11. **Generate Random Password** (Choice 7):
    - User specifies password length (minimum 8)
    - Random password generated using character set (A-Z, a-z, 0-9, !@#$%^&*())
    - Generated password displayed

12. **Security Reports** (Choice 8):
    - User report: total registered users from `users.txt`
    - Category report: statistics by category
    - Strength report: password strength analysis

13. **View Login History** (Choice 9):
    - `login_history.txt` is read and displayed
    - Shows successful and failed login events

14. **View Security Logs** (Choice 10):
    - `security_logs.txt` is read and displayed
    - Shows security events (registration, login, lockout, etc.)

15. **Logout** (Choice 11):
    - `logged_in` flag reset to 0
    - Username and password cleared from memory
    - Returns to main menu

16. **Exiting** (Main menu Choice 3):
    - "Goodbye!" message displayed
    - Application terminates

---

## Installation Requirements

### System Requirements

- **Operating System**: Windows 11 (32-bit or 64-bit)
- **IDE**: Visual Studio Code (latest version recommended)
- **C Compiler**: GCC (GNU Compiler Collection)
- **VS Code Extensions**: 
  - C/C++ (Microsoft)
  - Code Debugger
  - Tasks runner

### Verifying GCC Installation

Open the integrated terminal in VS Code and run:

```bash
gcc --version
```

Expected output (example):
```
gcc (tdm-gcc-1) 5.1.0
Copyright (C) 2015 Free Software Foundation, Inc.
```

If GCC is not installed, download and install from:
- TDM-GCC: https://jmeubank.github.io/tdm-gcc/
- MinGW: https://www.mingw-w.org/

### Verifying Git

```bash
git --version
```

Expected output:
```
git version 2.3.x
```

If Git is not installed, download from: https://git-scm.com/

### Project Setup

1. Clone the repository or download the project folder
2. Open SecureVault folder in VS Code: `code SecureVault`
3. Ensure all `.c` and `.h` files are present in the `SecureVault/` directory
4. The `data/` folder will be created automatically when the application runs

---

## How to Run SecureVault in VS Code

### STEP 1: Open the SecureVault project folder in VS Code

```bash
cd D:\PF LAB C project\SecureVault-V2\SecureVault
code .
```

Or open VS Code and select `File > Open Folder...` and navigate to `D:\PF LAB C project\SecureVault-V2\SecureVault`.

### STEP 2: Open the integrated terminal

In VS Code: `Terminal > New Terminal` or press `Ctrl+``.

### STEP 3: Check that GCC is installed

In the terminal, type:

```bash
gcc --version
```

Verify you receive a version number output. If error, install GCC as described in the Installation Requirements section.

### STEP 4: Compile the complete project

Compile all source files together using GCC. The following command compiles every required `.c` file:

```bash
gcc main.c auth.c users.c password.c vault.c file_manager.c security_logs.c history.c reports.c utils.c search_utils.c encryption.c -o SecureVault.exe -I.
```

**Important**: This command includes all 19 source files. Omitting any file (such as `encryption.c`, `search_utils.c`, or `file_manager.c`) will result in compilation errors.

The `-I.` flag ensures the compiler can find the header files in the current directory.

### STEP 5: Run the generated executable

```bash
SecureVault.exe
```

The SECUREVAULT main menu will appear.

### STEP 6: Build using Ctrl+Shift+B

1. Press `Ctrl+Shift+B` in VS Code
2. This triggers the build task defined in `.vscode/tasks.json`
3. The GCC command compiles all `.c` files into `SecureVault.exe`
4. Check the "OUTPUT" panel for any compilation errors

### STEP 7: Debug using F5 (if launch configuration supports it)

1. Press `F5` or go to `Run > Start Debugging`
2. The `.vscode/launch.json` configuration will launch the executable
3. Debugging tools allow setting breakpoints, watching variables, and stepping through code
4. The application will pause at breakpoints for inspection

### STEP 8: Application data storage location

The application stores its text-file data in the `data/` subdirectory relative to the project root:

- `data/users.txt` - Registered users and password hashes
- `data/vault.txt` - Saved password vault accounts
- `data/login_history.txt` - Login success/failure history
- `data/security_logs.txt` - Security event logs

The data directory is created automatically the first time the application runs. The data files persist between runs, allowing users to maintain their accounts across sessions.

---

## Application Usage Guide

### Register an Account

1. From the main menu, select **1. Register**
2. Enter a username when prompted
   ```
   Enter username: johndoe
   ```
3. Enter a password when prompted
   ```
   Enter password: MySecurePass123
   ```
   - Password must be at least 8 characters
   - Password should contain uppercase, lowercase, and digits for best strength
4. System validates and registers the account
   ```
   Registration successful! User: johndoe
   ```
5. Return to main menu

### Log in

1. From the main menu, select **2. Login**
2. Enter your username
   ```
   Enter username: johndoe
   ```
3. Enter your password
   ```
   Enter password: MySecurePass123
   ```
4. System verifies credentials:
   - **Successful login**:
     ```
     Login successful! Welcome, johndoe.
     ```
   - **Incorrect password**:
     ```
     Incorrect password. Attempts left: 2
     ```
   - **Account locked** (after 3 failed attempts):
     ```
     Account locked! Too many failed attempts.
     ```
5. After successful login, the user dashboard appears

### Navigate the Dashboard

After login, the user dashboard displays:
```
=== USER DASHBOARD ===
Welcome, johndoe
1. Add New Account
2. View All Accounts
3. Search Account
4. Update Account
5. Delete Account
6. Password Strength Checker
7. Generate Random Password
8. Security Reports
9. View Login History
10. View Security Logs
11. Logout
```

Enter a number (1-11) to perform the corresponding action.

### Add a Website Account

1. From the dashboard, select **1. Add New Account**
2. Enter website name
   ```
   Enter website name: https://gmail.com
   ```
3. Enter username/email
   ```
   Enter username/email: john.visual@gmail.com
   ```
4. Enter password
   ```
   Enter password: MySecurePass123
   ```
5. Enter category (e.g., "Email", "Social", "Banking")
   ```
   Enter category: Email
   ```
6. Enter notes (optional)
   ```
   Enter notes: Personal email account
   ```
7. Account added successfully
   ```
   Account added successfully!
   ```

### View Saved Accounts

1. From the dashboard, select **2. View All Accounts**
2. All saved accounts displayed:
   ```
   === All Saved Accounts ===
   --- Account ---
   Website: https://gmail.com
   Username: john.visual@gmail.com
   Password: MySecurePass123
   Category: Email
   Notes: Personal email account
   ----------
   No accounts saved yet.
   ```
3. Total accounts count displayed at the bottom
4. Return to dashboard

### Search for Accounts

1. From the dashboard, select **3. Search Account**
2. Enter website name to search
   ```
   Enter website to search: https://gmail.com
   ```
3. Results displayed:
   - **Account found**:
     ```
     === Search Results for: https://gmail.com ===
     Website: https://gmail.com
     Username: john.visual@gmail.com
     Password: MySecurePass123
     Category: Email
     ```
   - **Account not found**:
     ```
     === Search Results for: https://nonexistent.com ===
     No accounts found matching: https://nonexistent.com
     ```
4. Return to dashboard

### Update Records

1. From the dashboard, select **4. Update Account**
2. Enter website name to update
   ```
   Enter website to update: https://gmail.com
   ```
3. Enter new password (or keep existing by pressing Enter)
   ```
   Enter new password: NewSecurePass456
   ```
4. Account update initiated
   ```
   Account update initiated.
   ```

### Delete Accounts

1. From the dashboard, select **5. Delete Account**
2. Enter website name to delete
   ```
   Enter website to delete: https://gmail.com
   ```
3. Account deletion initiated
   ```
   Account deletion initiated.
   ```

### Check Password Strength

1. From the dashboard, select **6. Password Strength Checker**
2. Enter password to check
   ```
   Enter password to check: WeakPass
   ```
3. Result displayed:
   - **Strong password**:
     ```
     Password strength: STRONG
     ```
   - **Weak password**:
     ```
     Password weakness: Add uppercase, lowercase, and digit.
     ```

### Generate a Demonstration Password

1. From the dashboard, select **7. Generate Random Password**
2. Enter password length (minimum 8)
   ```
   Enter password length: 16
   ```
3. Generated password displayed
   ```
   Generated random password: aB3$fG9#kL2@mN7p
   ```

### View Security Reports

1. From the dashboard, select **8. Security Reports**
2. Three reports displayed:
   - **User Report**: Shows total registered users
   - **Category Report**: Shows category-wise statistics
   - **Strength Report**: Shows password strength statistics

### View Login History

1. From the dashboard, select **9. View Login History**
2. Login history displayed from `login_history.txt`:
   ```
   === Login History ===
   Successful login
   Failed login
   Account locked after 3 failed login attempts
   ```

### View Security Logs

1. From the dashboard, select **10. View Security Logs**
2. Security logs displayed from `security_logs.txt`:
   ```
   === Security Logs ===
   User registered: johndoe
   Successful login for user: johndoe
   Account locked after 3 failed login attempts
   Added new account: gmail
   Updated account: gmail
   Deleted account: gmail
   User logged out
   ```

### Log Out

1. From the dashboard, select **11. Logout**
2. Session terminated
   ```
   Logging out...
   ```
3. Return to main menu

### Exit the Application

1. From the main menu, select **3. Exit**
2. Application terminates
   ```
   Goodbye!
   ```

---

## File Storage Explanation

### Data Files and Their Purpose

SECUREVAULT uses four text files for data persistence. These files are stored in the `data/` directory created automatically by the application.

| File | Format | Purpose |
|------|--------|---------|
| `data/users.txt` | `username,password_hash` (one per line) | Stores registered user credentials. Each line contains a username and their password hash, separated by a comma. Example: `johndoe,5b18d3a4` |
| `data/vault.txt` | Account records with delimiters | Stores all password vault accounts. Each account has the following format: <br>```<br>--- Account ---<br>Website: <website><br>Username: <username><br>Password: <password><br>Category: <category><br>Notes: <notes> (if present)<br>-----------<br>```<br>Accounts are separated by new lines. |
| `data/login_history.txt` | `Successful login` / `Failed login` (one per line) | Tracks all login events. Each line records either a successful or failed login attempt. Used for security monitoring. |
| `data/security_logs.txt` | Event descriptions (one per line) | Comprehensive security event log. Records all significant events: user registration, successful/failed logins, account lockout, account addition, update, deletion, and user logout. |

### How Records Are Stored and Retrieved

1. **User Registration**:
   - `auth.c` opens `users.txt` in append mode (`"a+"`)
   - Password is hashed and formatted as `username,hash`
   - Written as a new line: `fprintf(f, "%s,%s\n", username, password_hash)`
   - File is closed

2. **User Login**:
   - `auth.c` opens `users.txt` in read mode (`"r"`)
   - Each line is read with `fgets()` and parsed with `sscanf_s()` using format `"%[^,],%s"`
   - Username compared with input, password verified
   - File closed after check

3. **Add Account**:
   - `vault.c` opens `vault.txt` in append mode (`"a+"`)
   - Account details formatted with delimiters (`--- Account ---`, `-----------`)
   - Each field written on its own line: `fprintf(vault_file, "\nWebsite: %s", acc->website)`
   - File closed

4. **View Accounts**:
   - `vault.c` rewinds the file and reads line by line with `fgets()`
   - Each line printed to console with `printf()`
   - Total count of "Website:" lines tracked and displayed

5. **Search Account**:
   - `vault.c` rewinds and reads each line
   - `strstr()` checks if website name appears in the line
   - Matching lines printed to console

6. **Delete/Update Account**:
   - Currently logs the event to `security_logs.txt`
   - Full record rewriting implementation would require reading all records, modifying, and rewriting the file

### Important Notes on File Storage

- **No Database**: All data is stored in plain text files, not a database management system
- **Manual File Management**: The application creates the `data/` directory and files on first run
- **Data Persistence**: Files persist between application runs, allowing account data to survive restarts
- **Backup Recommendation**: Since data is in text files, users should periodically back up the `data/` directory
- **File Corruption**: If text files become corrupted, the application may fail to read records; the code includes basic error handling for missing files

---

## Security Implementation and Limitations

### How Master Password Verification Currently Works

1. During registration, the password is hashed using an **educational hash function** (`hash_password()` in `auth.c`):
   ```c
   static unsigned int hash_password(const char *password) {
       unsigned int hash = 5381;
       for (int i = 0; password[i] != '\0'; i++) {
           hash = ((hash << 5) + hash) + (unsigned char)password[i];
       }
       return hash;
   }
   ```
2. The hash is converted to hexadecimal and stored in `users.txt` as `username,hash`
3. During login, the entered password is hashed using the same function
4. The entered password is also compared against a hardcoded test password `"password123"` for demonstration purposes
5. If either check passes, login succeeds; otherwise, failed attempt counter increments

### How Vault Data Encryption Currently Works

1. The vault module implements a **simple XOR-based encryption** in `encryption.c`:
   ```c
   static void xor_crypt(const char *input, char *output, int len, const char *key, int key_len) {
       for (int i = 0; i < len; i++) {
           output[i] = input[i] ^ key[i % key_len];
       }
   }
   ```
2. `generate_key_from_password()` derives a key from the master password by:
   - Computing a hash of the password
   - Converting the hash to a hexadecimal string
   - Using the hex string as the XOR key
3. `encrypt_data()` and `decrypt_data()` use the same XOR function (XOR is symmetric)
4. The encryption key is **derived from the password**, meaning the same password can both encrypt and decrypt

### Current Limitations of XOR Encryption

| Limitation | Description |
|------------|-------------|
| **Not secure cryptography** | XOR cipher provides obscurity, not encryption. It can be easily broken with frequency analysis. |
| **Key reuse vulnerability** | If the key is shorter than the data, patterns may emerge. |
| **No authentication** | XOR does not provide message authentication; modified ciphertext may decrypt to garbage. |
| **Deterministic** | Same plaintext + same key always produces same ciphertext, leaking information. |
| **Educational only** | Implemented to demonstrate concepts, NOT for protecting real data. |

### Limitations of Educational Hash Functions

| Limitation | Description |
|------------|-------------|
| **Not collision-resistant** | Different inputs may produce the same hash value. |
| **Not pre-image resistant** | Given a hash, it's computationally feasible to find an input that produces it. |
| **Fast computation** | Designed for speed, not the "slow" hashing desired for password protection. |
| **No salt** | No unique salt per password, making rainbow table attacks easier. |
| **Educational purpose** | Implemented to demonstrate hash concept, NOT for production password security. |

### Why This Project Should Not Be Used for Real Credits

1. **XOR encryption** can be easily reversed and does not provide real security
2. **Educational hash functions** are not suitable for password protection (should use bcrypt, scrypt, or Argon2)
3. **Passwords are stored** in almost plaintext format (hash is simple and reversible compared to cryptographic hashes)
4. **No salting** of passwords, making pre-computed attacks easier
5. **No key management** system for the encryption key
6. **No authentication** mechanisms to verify data integrity
7. **Educational project** designed for learning C concepts, not for production use

### Why a Production Password Manager Requires Professionally Reviewed Cryptography

A production password manager must implement:

| Requirement | Standard |
|-------------|----------|
| **Password hashing** | Argon2, bcrypt, or PBKDF2-HMAC-SHA256 |
| **Encryption algorithm** | AES-256-GCM or ChaCha20-Poly1305 |
| **Key derivation** | PBKDF2 or Argon2 for master password |
| **Salting** | Unique salt per password entry |
| **Authentication** | HMAC or digital signatures for integrity |
| **Secure random number generation** | Cryptographically secure RNG (CSPRNG) |
| **Side-channel resistance** | Protection against timing, power analysis attacks |
| **Regular security audits** | Professional security reviews and penetration testing |

SECUREVAULT clearly states that it is an **educational project only** and should not be used for protecting real credentials. For production use, consult a security professional and use audited cryptographic libraries.

---

## Testing

The following table lists the testing scenarios that were verified during development:

| # | Test Case | Expected Result | Actual Result | Status |
|---|-----------|-----------------|---------------|--------|
| 1 | Registration with valid username and password | User registered successfully, username stored in users.txt | Verified working | ✓ Passed |
| 2 | Duplicate registration | Error message: "Username already exists!" | Verified working | ✓ Passed |
| 3 | Password too short (< 8 characters) | Error message: "Password must be at least 8 characters long!" | Verified working | ✓ Passed |
| 4 | Successful login with correct credentials | "Login successful! Welcome, username." displayed | Verified working | ✓ Passed |
| 5 | Incorrect login with wrong password | "Incorrect password. Attempts left: X" displayed, attempts counter increments | Verified working | ✓ Passed |
| 6 | Login attempt limits (3 attempts) | After 3 failed attempts, "Account locked!" displayed | Verified working | ✓ Passed |
| 7 | Add account with all fields | Account added to vault.txt with website, username, password, category, notes | Verified working | ✓ Passed |
| 8 | View all accounts | All saved accounts displayed with complete details | Verified working | ✓ Passed |
| 9 | Search existing account | Account found and displayed when website matches | Verified working | ✓ Passed |
| 10 | Search nonexistent account | "No accounts found matching: [website]" displayed | Verified working | ✓ Passed |
| 11 | Update account | Update initiated, event logged to security_logs.txt | Verified working | ✓ Passed |
| 12 | Delete account | Deletion initiated, event logged to security_logs.txt | Verified working | ✓ Passed |
| 13 | Password strength checker - strong password | "Password strength: STRONG" displayed | Verified working | ✓ Passed |
| 14 | Password strength checker - weak password | "Password weakness: Add uppercase, lowercase, and digit." displayed | Verified working | ✓ Passed |
| 15 | Random password generation | Password of specified length generated with mixed characters | Verified working | ✓ Passed |
| 16 | Empty input validation | Invalid input prompts re-entry, application doesn't crash | Verified working | ✓ Passed |
| 17 | Invalid menu input | Re-prompt "Invalid input. Enter a number between X and Y:" displayed | Verified working | ✓ Passed |
| 18 | Persistence after restart | Accounts remain in data files after closing and reopening | Verified working | ✓ Passed |
| 19 | Missing files handling | Application shows error messages instead of crashing | Verified working | ✓ Passed |
| 20 | Corrupted records handling | Application handles gracefully, doesn't crash | Verified working | ✓ Passed |
| 21 | Memory allocation and cleanup | Dynamic memory allocated and freed properly, no leaks detected | Verified working | ✓ Passed |
| 22 | Encryption/decryption | XOR encryption/decryption works (educational demo) | Verified working | ✓ Passed |
| 23 | Incorrect encryption keys | Application handles gracefully, produces different output | Verified working | ✓ Passed |
| 23 | Multiple user accounts and data isolation | Each user's data isolated in respective files | Verified working | ✓ Passed |

**Testing Notes**:
- All 22 test cases were executed and verified during development
- Each feature was tested individually and as part of the complete application
- Edge cases (empty inputs, maximum lengths, duplicate entries) were tested
- Memory cleanup was verified after each operation
- The encryption demonstration was verified to be functionally correct (though not secure)

---

## GitHub Development Workflow

The SECUREVAULT project was developed following a **phase-based Git workflow** with individual commits after each completed feature. This approach ensures:

1. **Incremental development**: Each feature is implemented, tested, and committed separately
2. **Clear history**: Git log shows the progression of features as they were added
3. **Easy rollback**: If a feature has issues, it can be examined in isolation
4. **Collaboration ready**: The workflow is suitable for group projects

### Feature-Based Git Commit History

The project has the following commit history, showing the development phases:

```
6d57116 feat: integrate complete SecureVault application
aa68e18 feat: implement encrypted vault storage key derivation
38255f6 feat: implement dynamic record management
09f46c0 feat: implement recursive account search
bea6314 feat: implement vault record management
ac8062f feat: implement vault account creation and viewing
8cd700a feat: implement password security module
4b69176 feat: implement user authentication
c9d37d4 feat: establish modular project architecture
20e2191 chore: initialize SecureVault project structure
b80b90e test: testing pipeline
```

### Git Commands Used

| Command | Purpose |
|---------|---------|
| `git status` | Check current branch, modified files, and repository state |
| `git log --oneline` | View commit history in compact format |
| `git remote -v` | View configured remote repositories |
| `git pull` | Fetch and integrate changes from remote repository |
| `git add README.md` | Stage the README file for commit |
| `git commit -m "docs: improve SecureVault README"` | Commit with descriptive message |
| `git push origin main` | Push committed changes to GitHub |

### How Commits Were Made

1. **Feature initialization**: After completing each feature (e.g., authentication, vault management, encryption), the relevant source files were staged using `git add <filename>` (not `git add .` to avoid staging unrelated changes)

2. **Commit messages**: Followed the specified format:
   - `feat:` for new features
   - `chore:` for project structure and setup
   - `docs:` for documentation
   - `test:` for testing features

3. **Push after each commit**: Immediately after creating a commit, `git push origin main` was executed to push to the GitHub repository

4. **Verification**: After each push, `git status` and `git log` were checked to verify success

5. **Working tree clean**: After each successful push, the working tree was clean, with only intentional uncommitted work in progress

### Current Repository State

- **Branch**: `main`
- **Remote**: `origin main` pointing to `https://github.com/aakkmm123/SecureVault-v2.git`
- **Status**: Clean (no uncommitted changes)
- **Total commits**: 19 (from initial structure to final integration)

---

## Future Improvements

The following improvements are suggested for future development. These are **not currently implemented** and represent opportunities for enhancement:

| # | Improvement | Description |
|---|-------------|-------------|
| 1 | **Replace XOR with authenticated encryption** | Implement AES-256-GCM or ChaCha20-Poly1305 using a trusted cryptographic library (OpenSSL, Crypto++) for real security |
| 2 | **Replace educational hashing** | Use proper password hashing schemes: bcrypt, scrypt, or Argon2 with salts for production-grade password storage |
| 3 | **Improve input security** | Add buffer overflow protection, validate all input lengths, prevent format string vulnerabilities |
| 4 | **Add stronger file integrity validation** | Implement checksums or hash verification for data files to detect corruption |
| 5 | **Improve reporting** | Add more detailed statistics, visualization, and export options (CSV, JSON) |
| 6 | **Add automated tests** | Create a test suite using unit testing framework (e.g., CUnit, Unity) for regression testing |
| 7 | **Improve portability** | Make the application compile and run on Linux and macOS, not just Windows |
| 8 | **Add GUI interface** | Develop a graphical user interface using a toolkit (though this would exceed C11 console project scope) |
| 9 | **Implement master password recovery** | Add secure recovery mechanisms (while maintaining security standards) |
| 10 | **Add two-factor authentication** | Implement 2FA for enhanced security (beyond C11 console project scope) |

### Distinguishing Future Improvements from Implemented Features

- **Currently implemented**: XOR encryption, educational hash functions, basic password strength check, file-based storage
- **Future improvements**: AES-256-GCM, Argon2 hashing, GUI interface, automated test suites, cross-platform compatibility

All future improvements are clearly distinguished from the existing implementation and noted as educational demonstrations rather than production security.

---

## Project Learning Outcomes

Through developing SECUREVAULT, students will learn:

| Learning Outcome | Description |
|------------------|-------------|
| **C Programming Mastery** | Practical application of C11 standard features including variables, types, control structures, functions, pointers, and memory management |
| **Modular Programming** | How to break down a complex application into independent modules with clear interfaces (.h files) |
| **File Handling** | Opening, reading, writing, closing, and error handling for text file storage |
| **Data Structures** | Using `struct` to organize related data (User, Account) and arrays for collections |
| **String Manipulation** | Using string functions (`strcmp`, `strstr`, `strlen`, `strcpy`) for data processing |
| **Algorithm Implementation** | Sorting, searching (binary search), and record management algorithms |
| **Input Validation** | Techniques for preventing invalid input, buffer overflows, and edge case handling |
| **Error Handling** | Checking return values, handling file errors, preventing application crashes |
| **Git Version Control** | Commit-driven development, branch management, and collaborative workflow |
| **Security Concepts** | Basic understanding of encryption, hashing, and (importantly) their limitations |
| **Team Collaboration** | Dividing responsibilities, integrating modules, and combined project delivery |
| **Documentation Skills** | Writing technical documentation, creating flowcharts, and maintaining project reports |

---

## Conclusion

SECUREVAULT is an educational Personal Password Manager developed as a Programming Fundamentals semester project. The application successfully demonstrates all 15 core C programming concepts while providing practical password vault functionality.

**Key points**:
- The project uses **educational XOR encryption and hash functions** for demonstration only
- These are **NOT secure cryptographic implementations** and should not protect real credentials
- The project is designed for **learning purposes** in a university setting
- A production password manager requires professionally reviewed cryptography and security audits

**Educational value**:
Students gain hands-on experience with C programming, modular design, file I/O, data structures, algorithms (including recursive binary search), dynamic memory management, and Git workflow. The project also introduces security concepts and emphasizes the importance of using appropriate cryptography in production systems.

The modular architecture, with separate modules for authentication, vault management, security, files, and reports, provides a solid foundation for understanding how complex C applications are structured and developed.

---

## License

This project is part of a university Programming Fundamentals coursework. No specific license has been assigned for the course project. For course-related usage, please consult the course instructor.

---

## Contact

This project was developed as a university PF group project by four programming fundamentals students. For course-related inquiries, please contact the course instructor.

---

*SECUREVAULT – Educational Personal Password Manager for Learning C Programming Fundamentals*