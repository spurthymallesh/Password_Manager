#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

/* Standard Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

/* Constants */
#define MAX_USERNAME    30
#define MAX_PASSWORD    100
#define MAX_WEBSITE     50
#define MAX_RECORDS     100
#define HASH_SIZE       65

/* Return Status */
#define SUCCESS         1
#define FAILURE         0

/* Credential Structure */
typedef struct
{
    char website[MAX_WEBSITE];
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} Credential;

/* User Structure */
typedef struct
{
    char username[MAX_USERNAME];
    char password_hash[HASH_SIZE];
} User;

/* Registration */
int register_user(void);

/* Login */
int login_user(char *logged_user);

/* Validation */
int username_exists(const char *username);
int is_strong_password(const char *password);
void clear_input_buffer(void);

/* File Operations */
int user_exists(const char *username);
int create_user_directory(const char *username);
int create_master_file(const char *username, const char *password);
int create_vault_file(const char *username);
int read_master_file(const char *username, User *user);

/* SHA-256 Wrapper */
void sha256_string(const char *input, char output[HASH_SIZE]);
void sha256_string(const char *input, char output[65]);

/* Vault */
int vault_menu(const char *username);

int add_credential(const char *username);

int view_credentials(const char *username);

int search_credential(const char *username);

int edit_credential(const char *username);

int delete_credential(const char *username);

/* Input Utilities */
void clear_input_buffer(void);

int get_menu_choice(void);

void get_username(char *username, int size);

void get_password(char *password, int size);

void trim_newline(char *str);

int is_valid_username(const char *username);

void get_hidden_password(char *password, int size);

/* Encryption */
void encrypt_password(const char *plain, char *encrypted);
void decrypt_password(const char *encrypted, char *plain);

int add_credential(const char *username);

int save_credential(const char *logged_user, Credential *cred);
int load_credentials(const char *logged_user);

#endif