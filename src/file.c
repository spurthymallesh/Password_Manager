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

int create_master_file(const char *username, const char *password)
{
    char filename[150];

    sprintf(filename, "users/%s/master.dat", username);

    FILE *fp = fopen(filename, "w");

    if (fp == NULL)
        return FAILURE;

    fprintf(fp,"%s\n",username);
    fprintf(fp,"%s\n",password);      // SHA-256 later

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