#include "../include/password_manager.h"

int register_user(void)
{
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char confirm[MAX_PASSWORD];

    printf("\n========== USER REGISTRATION ==========\n");

    printf("Enter Username : ");
    scanf("%29s", username);

    if(user_exists(username))
    {
        printf("\nUsername already exists!\n");
        return FAILURE;
    }

    int attempts = 3;

while (attempts > 0)
{
    printf("Enter Master Password : ");
    scanf("%99s", password);

    printf("Confirm Password : ");
    scanf("%99s", confirm);

    if (strcmp(password, confirm) != 0)
    {
        attempts--;

        printf("\nPasswords do not match!\n");

        if (attempts > 0)
            printf("You have %d attempt(s) remaining.\n\n", attempts);

        continue;
    }

    if (is_strong_password(password) == FAILURE)
    {
        attempts--;

        printf("\nWeak Password!\n");
        printf("Password must contain:\n");
        printf("  - Minimum 8 characters\n");
        printf("  - One uppercase letter\n");
        printf("  - One lowercase letter\n");
        printf("  - One digit\n");
        printf("  - One special character\n");

        if (attempts > 0)
            printf("\nYou have %d attempt(s) remaining.\n\n", attempts);

        continue;
    }

    /* Password is valid */
    break;
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

    create_master_file(username,password);
    create_vault_file(username);

    printf("\nRegistration Successful.\n");

    return SUCCESS;
}