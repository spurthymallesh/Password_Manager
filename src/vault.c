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
                search_credential(username);
                break;

            case 4:
                edit_credential(username);
                break;

            case 5:
                delete_credential(username);
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

int search_credential(const char *username)
{
    char path[200];
    FILE *fp;

    Credential cred;
    char password[MAX_PASSWORD];
    char website[MAX_WEBSITE];

    sprintf(path, "users/%s/vault.dat", username);

    fp = fopen(path, "r");

    if(fp == NULL)
    {
        printf("\nUnable to open vault.\n");
        return FAILURE;
    }

    printf("\nSearch Website : ");
    fgets(website, MAX_WEBSITE, stdin);
    trim_newline(website);

    int found = 0;

    while(fscanf(fp,
                 "%99[^|]|%99[^|]|%99[^\n]\n",
                 cred.website,
                 cred.username,
                 password) == 3)
    {
        if(strcmp(cred.website, website) == 0)
        {
            found = 1;

            printf("\n========== MATCH FOUND ==========\n");

            printf("Website : %s\n", cred.website);
            printf("Username : %s\n", cred.username);
            printf("Password : %s\n", password);

            printf("---------------------------------\n");
        }
    }

    if(!found)
    {
        printf("\nCredential not found.\n");
    }

    fclose(fp);

    return SUCCESS;
}

int edit_credential(const char *username)
{
    char path[200];
    char temp_path[200];

    FILE *fp;
    FILE *temp;

    Credential cred;
    char password[MAX_PASSWORD];
    char website[MAX_WEBSITE];

    sprintf(path, "users/%s/vault.dat", username);
    sprintf(temp_path, "users/%s/temp.dat", username);

    printf("\nEnter Website to Edit : ");
    fgets(website, MAX_WEBSITE, stdin);
    trim_newline(website);

    /* ---------- PASS 1 : Display Matching Credentials ---------- */

    fp = fopen(path, "r");

    if(fp == NULL)
    {
        printf("\nUnable to open vault.\n");
        return FAILURE;
    }

    int count = 0;

    printf("\n========== MATCHING CREDENTIALS ==========\n");

    while(fscanf(fp,
                 "%99[^|]|%99[^|]|%99[^\n]\n",
                 cred.website,
                 cred.username,
                 password) == 3)
    {
        if(strcmp(cred.website, website) == 0)
        {
            count++;

            printf("\n%d.\n", count);
            printf("Website : %s\n", cred.website);
            printf("Username : %s\n", cred.username);
        }
    }

    fclose(fp);

    if(count == 0)
    {
        printf("\nCredential Not Found.\n");
        return FAILURE;
    }

    int selected;

    printf("\nSelect Credential Number : ");
    selected = get_menu_choice();

    if(selected < 1 || selected > count)
    {
        printf("\nInvalid Selection.\n");
        return FAILURE;
    }

    /* ---------- PASS 2 : Edit Selected Credential ---------- */

    fp = fopen(path, "r");
    temp = fopen(temp_path, "w");

    if(fp == NULL || temp == NULL)
    {
        if(fp) fclose(fp);
        if(temp) fclose(temp);

        printf("\nUnable to open files.\n");
        return FAILURE;
    }

    int current = 0;
    int updated = 0;

    while(fscanf(fp,
                 "%99[^|]|%99[^|]|%99[^\n]\n",
                 cred.website,
                 cred.username,
                 password) == 3)
    {
        if(strcmp(cred.website, website) == 0)
        {
            current++;

            if(current == selected)
            {
                printf("\n========== CURRENT CREDENTIAL ==========\n\n");

                printf("Website : %s\n", cred.website);
                printf("Username : %s\n", cred.username);

                printf("Password : ");
                for(int i = 0; password[i] != '\0'; i++)
                    printf("*");

                printf("\n");

                printf("----------------------------------------\n");

                printf("\nWhat do you want to edit?\n");
                printf("1. Username\n");
                printf("2. Password\n");
                printf("3. Both Username & Password\n");
                printf("4. Cancel\n");

                printf("\nEnter Choice : ");

                int choice = get_menu_choice();

                switch(choice)
                {
                    case 1:

                        printf("\nEnter New Username : ");
                        fgets(cred.username, MAX_USERNAME, stdin);
                        trim_newline(cred.username);

                        updated = 1;
                        break;

                    case 2:

                        printf("\nEnter New Password : ");
                        get_hidden_password(password, MAX_PASSWORD);

                        updated = 1;
                        break;

                    case 3:

                        printf("\nEnter New Username : ");
                        fgets(cred.username, MAX_USERNAME, stdin);
                        trim_newline(cred.username);

                        printf("Enter New Password : ");
                        get_hidden_password(password, MAX_PASSWORD);

                        updated = 1;
                        break;

                    case 4:

                        printf("\nEdit Cancelled.\n");
                        break;

                    default:

                        printf("\nInvalid Choice.\n");
                }
            }
        }

        fprintf(temp,
                "%s|%s|%s\n",
                cred.website,
                cred.username,
                password);
    }

    fclose(fp);
    fclose(temp);

    remove(path);
    rename(temp_path, path);

    if(updated)
    {
        printf("\n========== UPDATED CREDENTIAL ==========\n\n");

        printf("Website : %s\n", cred.website);
        printf("Username : %s\n", cred.username);

        printf("Password : ");
        for(int i = 0; password[i] != '\0'; i++)
            printf("*");

        printf("\n");

        printf("----------------------------------------\n");

        printf("\nCredential Updated Successfully.\n");
    }

    return SUCCESS;
}
int delete_credential(const char *username)
{
    char path[200];
    char temp_path[200];

    FILE *fp;
    FILE *temp;

    Credential cred;
    char password[MAX_PASSWORD];
    char website[MAX_WEBSITE];

    sprintf(path, "users/%s/vault.dat", username);
    sprintf(temp_path, "users/%s/temp.dat", username);

    printf("\nEnter Website to Delete : ");
    fgets(website, MAX_WEBSITE, stdin);
    trim_newline(website);

    fp = fopen(path, "r");

    if(fp == NULL)
    {
        printf("\nUnable to open vault.\n");
        return FAILURE;
    }

    int count = 0;

    printf("\n========== MATCHING CREDENTIALS ==========\n");

    while(fscanf(fp,
                 "%99[^|]|%99[^|]|%99[^\n]\n",
                 cred.website,
                 cred.username,
                 password) == 3)
    {
        if(strcmp(cred.website, website) == 0)
        {
            count++;

            printf("\n%d.\n", count);
            printf("Website : %s\n", cred.website);
            printf("Username : %s\n", cred.username);
        }
    }

    fclose(fp);

    if(count == 0)
    {
        printf("\nCredential Not Found.\n");
        return FAILURE;
    }

    printf("\nSelect Credential Number : ");
    int selected = get_menu_choice();

    if(selected < 1 || selected > count)
    {
        printf("\nInvalid Selection.\n");
        return FAILURE;
    }

    fp = fopen(path, "r");
    temp = fopen(temp_path, "w");

    int current = 0;
    int deleted = 0;

    while(fscanf(fp,
                 "%99[^|]|%99[^|]|%99[^\n]\n",
                 cred.website,
                 cred.username,
                 password) == 3)
    {
        if(strcmp(cred.website, website) == 0)
        {
            current++;

            if(current == selected)
            {
                printf("\n========== DELETE CREDENTIAL ==========\n\n");

                printf("Website : %s\n", cred.website);
                printf("Username : %s\n", cred.username);

                printf("\nAre you sure?\n");
                printf("1. Yes\n");
                printf("2. No\n");

                printf("\nChoice : ");

                int confirm = get_menu_choice();

                if(confirm == 1)
                {
                    deleted = 1;
                    continue;
                }
            }
        }

        fprintf(temp,
                "%s|%s|%s\n",
                cred.website,
                cred.username,
                password);
    }

    fclose(fp);
    fclose(temp);

    remove(path);
    rename(temp_path, path);

    if(deleted)
        printf("\nCredential Deleted Successfully.\n");
    else
        printf("\nDeletion Cancelled.\n");

    return SUCCESS;
}