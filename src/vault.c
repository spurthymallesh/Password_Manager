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
        clear_input_buffer(); 

        switch(choice)
        {
            case 1:
                add_credential(username);
                break;

            case 2:
                view_credentials(username);
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

   if (save_credential(username, &cred) == SUCCESS)
{
    printf("\nCredential Saved Successfully!\n");
}
else
{
    printf("\nFailed to Save Credential!\n");
}

return SUCCESS;
}

int view_credentials(const char *username)
{
    char path[200];
    FILE *fp;
    Credential cred;
    char password[MAX_PASSWORD];

    sprintf(path, "users/%s/vault.dat", username);

    fp = fopen(path, "r");

    if (fp == NULL)
    {
        printf("\nNo credentials found.\n");
        return FAILURE;
    }

    printf("\n========== SAVED CREDENTIALS ==========\n\n");

    int found = 0;

    while (fscanf(fp,
                  "%99[^|]|%99[^|]|%99[^\n]\n",
                  cred.website,
                  cred.username,
                  password) == 3)
    {
        found = 1;

        printf("Website : %s\n", cred.website);
        printf("Username : %s\n", cred.username);
        printf("Password : %s\n", password);

        printf("----------------------------------------\n");
    }

    if (!found)
    {
        printf("No credentials found.\n");
    }

    fclose(fp);

    return SUCCESS;
}