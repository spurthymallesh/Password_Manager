#include "../include/password_manager.h"

void encrypt_password(const char *plain, char *encrypted)
{
    int i = 0;

    while (plain[i] != '\0')
    {
        encrypted[i] = plain[i] ^ 0x5A;
        i++;
    }

    encrypted[i] = '\0';
}

void decrypt_password(const char *encrypted, char *plain)
{
    int i = 0;

    while (encrypted[i] != '\0')
    {
        plain[i] = encrypted[i] ^ 0x5A;
        i++;
    }

    plain[i] = '\0';
}