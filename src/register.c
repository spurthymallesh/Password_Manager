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

    printf("Enter Master Password : ");
    scanf("%99s", password);

    printf("Confirm Password : ");
    scanf("%99s", confirm);

    if(strcmp(password, confirm) != 0)
    {
        printf("\nPasswords do not match!\n");
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