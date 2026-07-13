#include "../include/password_manager.h"

int is_strong_password(const char *password)
{
    int upper = 0;
    int lower = 0;
    int digit = 0;
    int special = 0;

    if(strlen(password) < 8)
        return FAILURE;

    for(int i = 0; password[i] != '\0'; i++)
    {
        if(isupper(password[i]))
            upper = 1;
        else if(islower(password[i]))
            lower = 1;
        else if(isdigit(password[i]))
            digit = 1;
        else
            special = 1;
    }

    return (upper && lower && digit && special);
}