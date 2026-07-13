#include "../include/password_manager.h"

int login_user(char *logged_user)
{
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char entered_hash[65];
    User user;

    printf("\n========== LOGIN ==========\n");

    printf("Enter Username : ");
    scanf("%29s", username);

    if (!user_exists(username))
    {
        printf("\nUser does not exist!\n");
        return FAILURE;
    }

    if (read_master_file(username, &user) == FAILURE)
    {
        printf("\nUnable to read user information.\n");
        return FAILURE;
    }

    printf("\nUser Information Loaded Successfully.\n");

    int attempts = 3;

while (attempts > 0)
{
    printf("Enter Master Password : ");
    scanf("%99s", password);

    sha256_string(password, entered_hash);

    if (strcmp(user.password_hash, entered_hash) == 0)
    {
        break;
    }

    attempts--;

    printf("\nIncorrect Password!\n");

    if (attempts > 0)
    {
        printf("You have %d attempt(s) remaining.\n\n", attempts);
    }
}

if (attempts == 0)
{
    printf("\nMaximum login attempts exceeded.\n");
    return FAILURE;
}

    strcpy(logged_user, user.username);

    printf("\nLogin Successful.\n");
    printf("Welcome %s!\n", logged_user);

    return SUCCESS;
}