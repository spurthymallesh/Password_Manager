#include "../include/password_manager.h"

int register_user(void)
{
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char confirm[MAX_PASSWORD];

    printf("\n========== USER REGISTRATION ==========\n");

    get_username(username, MAX_USERNAME);
    //clear_input_buffer();

    if(user_exists(username))
    {
        printf("\nUsername already exists!\n");
        return FAILURE;
    }

    int attempts = 3;

while (1)
{
    printf("Enter Master Password : ");
    get_hidden_password(password, MAX_PASSWORD);

    if (is_strong_password(password) == SUCCESS)
        break;

    printf("\nWeak Password!\n");
    printf("Password must contain:\n");
    printf("  - Minimum 8 characters\n");
    printf("  - One uppercase letter\n");
    printf("  - One lowercase letter\n");
    printf("  - One digit\n");
    printf("  - One special character\n\n");
}

attempts = 3;

while (attempts > 0)
{
    printf("Confirm Password : ");
    get_hidden_password(confirm, MAX_PASSWORD);

    if(strcmp(password, confirm) == 0)
        break;

    attempts--;

    printf("\nPasswords do not match!\n");

    if(attempts > 0)
        printf("You have %d confirmation attempt(s) remaining.\n\n", attempts);
}

if (attempts == 0)
{
    printf("\nRegistration Failed! Maximum attempts exceeded.\n");
    return FAILURE;
}

    if(create_user_directory(username) == FAILURE)
    {
        printf("\nUnable to create user directory.\n");
        return FAILURE;
    }

    char hash[65];

sha256_string(password, hash);

create_master_file(username, hash);
create_vault_file(username);

    printf("\nRegistration Successful.\n");

    return SUCCESS;
}