#include "../include/password_manager.h"

int user_exists(const char *username)
{
    char path[100];

    sprintf(path, "users/%s", username);

    struct stat st;

    return (stat(path, &st) == 0);
}

int create_user_directory(const char *username)
{
    char path[100];

    sprintf(path, "users/%s", username);

    if (mkdir(path, 0755) == 0)
        return SUCCESS;

    return FAILURE;
}

int create_master_file(const char *username, const char *password_hash)
{
    char filename[150];

    sprintf(filename, "users/%s/master.dat", username);

    FILE *fp = fopen(filename, "w");

    if (fp == NULL)
        return FAILURE;

    fprintf(fp,"Username: %s\n",username);
    fprintf(fp,"PasswordHash: %s\n",password_hash);      // SHA-256 later

    fclose(fp);

    return SUCCESS;
}

int create_vault_file(const char *username)
{
    char filename[150];

    sprintf(filename, "users/%s/vault.dat", username);

    FILE *fp = fopen(filename,"w");

    if(fp == NULL)
        return FAILURE;

    fclose(fp);

    return SUCCESS;
}

int read_master_file(const char *username, User *user)
{
    char filename[150];

    sprintf(filename, "users/%s/master.dat", username);

    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
        return FAILURE;

    fscanf(fp, "Username: %29s\n", user->username);
    fscanf(fp, "PasswordHash: %64s", user->password_hash);

    fclose(fp);

    return SUCCESS;
}

#include "../include/password_manager.h"

int save_credential(const char *logged_user, Credential *cred)
{
    char path[200];
    FILE *fp;

    sprintf(path, "users/%s/vault.dat", logged_user);

    fp = fopen(path, "a");

    if(fp == NULL)
    {
        printf("Unable to open vault file.\n");
        return FAILURE;
    }

    fprintf(fp,
            "%s|%s|%s\n",
            cred->website,
            cred->username,
            cred->password);

    fclose(fp);

    return SUCCESS;
}