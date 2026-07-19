# 🔐 Secure Password Manager in C

A secure command-line based Password Manager developed in **C**, designed to safely store and manage user credentials. The application uses **SHA-256 hashing** for master password authentication and **AES-128 encryption** to securely store website passwords.

---

## 📌 Features

- 👤 Multi-user Registration & Login
- 🔒 Secure Master Password Authentication (SHA-256)
- 🔑 Hidden Password Input
- 🔐 AES-128 Encrypted Password Storage
- ➕ Add New Credentials
- 📋 View Saved Credentials
- 🔍 Search Credentials
- ✏️ Edit Existing Credentials
- 🗑️ Delete Credentials
- 📁 File-based Secure Storage
- 🖥️ Interactive Command Line Interface

---

## 🛠️ Technologies Used

- C Programming
- OpenSSL Cryptography Library
- SHA-256 Hashing
- AES-128 Encryption
- GCC Compiler
- Makefile
- Git & GitHub
- Linux / WSL

---

## 📂 Project Structure

```
Password_Manager/
│
├── include/
│   └── password_manager.h
│
├── src/
│   ├── main.c
│   ├── register.c
│   ├── login.c
│   ├── vault.c
│   ├── encryption.c
│   ├── sha256.c
│   ├── utils.c
│   └── file.c
│
├── users/
│
├── Makefile
├── README.md
└── .gitignore
```

---

## 🔐 Security Features

### SHA-256 Password Hashing

- Master passwords are never stored in plain text.
- Passwords are hashed using the SHA-256 algorithm before storage.
- Login authentication is performed by comparing password hashes.

### AES-128 Encryption

- Website passwords are encrypted before being stored.
- Credentials are decrypted only when viewed or searched.
- The vault stores only encrypted hexadecimal ciphertext.

Example:

```
insta|Spurthy|30C1326BE725F287DD51337FBCF1920C
```

---

## ⚙️ How It Works

```
                User Registration
                        │
                        ▼
          SHA-256 Hash Master Password
                        │
                        ▼
             Store User Information
                        │
                        ▼
                    User Login
                        │
                        ▼
          Verify SHA-256 Password Hash
                        │
                        ▼
           Generate AES Session Key
                        │
                        ▼
     ┌───────────────────────────────────┐
     │                                   │
     ▼                                   ▼
 Add Credential                    View/Search
     │                                   │
 Encrypt Password              Decrypt Password
     │                                   │
     ▼                                   ▼
 Store Ciphertext             Display Plain Password
```

---

## 🚀 Building the Project

Clone the repository

```bash
git clone https://github.com/spurthymallesh/Password_Manager.git
```

Move into the project directory

```bash
cd Password_Manager
```

Compile the project

```bash
make
```

Run

```bash
./password_manager
```

---

## 📸 Sample Output

```
=====================================
      SECURE PASSWORD MANAGER
=====================================

1. Register
2. Login
3. Exit
```

---

### Viewing Credentials

```
========== SAVED CREDENTIALS ==========

Website : Instagram
Username : Spurthy
Password : ********

----------------------------------------
```

---

## 📖 Functionalities

### User Management

- Register New User
- Login Existing User
- Secure Authentication

### Password Vault

- Add Credential
- View Credentials
- Search Credential
- Edit Credential
- Delete Credential

---

## 💻 Git Workflow

This project was developed using Git feature branches.

```
main
│
├── feature/register
├── feature/login
├── feature/sha256
├── feature/vault
└── feature/aes-encryption
```

Each feature was implemented independently and later merged into the `main` branch.

---

## 📚 Concepts Used

- Structures
- File Handling
- Dynamic Memory Concepts
- Modular Programming
- Cryptography
- SHA-256
- AES-128
- String Manipulation
- Command Line Interface
- Git Version Control

---

## 🔮 Future Enhancements

- Password Generator
- Password Strength Checker
- Export & Import Vault
- Auto Logout on Inactivity
- Password Categories
- Secure Backup & Restore
- Two-Factor Authentication
- Password Expiry Notifications

---

## 👩‍💻 Author

**Spurthy Mallesh**

Electronics & Telecommunication Engineer

Aspiring Embedded Systems Engineer

GitHub:
https://github.com/spurthymallesh

---
