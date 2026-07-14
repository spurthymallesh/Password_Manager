#include "../include/password_manager.h"

int vault_menu(const char *username)
{
    int choice;

    while (1)
    {
        printf("\n=====================================\n");
        printf("        PASSWORD VAULT\n");
        printf("=====================================\n");

        printf("Logged in as : %s\n\n", username);

        printf("1. Add Credential\n");
        printf("2. View Credentials\n");
        printf("3. Search Credential\n");
        printf("4. Edit Credential\n");
        printf("5. Delete Credential\n");
        printf("6. Logout\n");

        printf("\nEnter Choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                add_credential(username);
                break;

            case 2:
                printf("\nView Credential Module\n");
                break;

            case 3:
                printf("\nSearch Credential Module\n");
                break;

            case 4:
                printf("\nEdit Credential Module\n");
                break;

            case 5:
                printf("\nDelete Credential Module\n");
                break;

            case 6:
                printf("\nLogged Out Successfully.\n");
                return SUCCESS;

            default:
                printf("\nInvalid Choice!\n");
        }
    }
}

int add_credential(const char *username)
{
    Credential cred;

    printf("\n========== ADD CREDENTIAL ==========\n");

    printf("Website : ");
    fgets(cred.website, MAX_WEBSITE, stdin);
    trim_newline(cred.website);

    printf("Username : ");
    fgets(cred.username, MAX_USERNAME, stdin);
    trim_newline(cred.username);

    printf("Password : ");
    get_hidden_password(cred.password, MAX_PASSWORD);

    printf("\nCredential Captured Successfully!\n");

    return SUCCESS;
}