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

void clear_input_buffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

void trim_newline(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

int get_menu_choice(void)
{
    int choice;

    while (1)
    {
        printf("Enter your choice: ");

        if (scanf("%d", &choice) == 1)
        {
            clear_input_buffer();
            return choice;
        }

        printf("\nInvalid input! Please enter a number.\n\n");

        clear_input_buffer();
    }
}

void get_username(char *username, int size)
{
    while (1)
    {
        printf("Enter Username : ");

        if (fgets(username, size, stdin) == NULL)
            continue;

        trim_newline(username);

        if (strlen(username) == 0)
        {
            printf("\nUsername cannot be empty.\n\n");
            continue;
        }

        if (!is_valid_username(username))
        {
            printf("\nInvalid Username!\n");
            printf("Username may contain only:\n");
            printf("  • Letters (A-Z, a-z)\n");
            printf("  • Digits (0-9)\n");
            printf("  • Underscore (_)\n");
            printf("Spaces and special characters are not allowed.\n\n");
            continue;
        }

        return;
    }
}

void get_password(char *password, int size)
{
    while (1)
    {
        if (fgets(password, size, stdin) == NULL)
            continue;

        trim_newline(password);

        if (strlen(password) == 0)
        {
            printf("Password cannot be empty.\n");
            continue;
        }

        return;
    }
}

int is_valid_username(const char *username)
{
    if (strlen(username) == 0)
        return FAILURE;

    for (int i = 0; username[i] != '\0'; i++)
    {
        if (!(isalnum(username[i]) || username[i] == '_'))
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}

void get_hidden_password(char *password, int size)
{
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int i = 0;
    char ch;

    while (1)
    {
        ch = getchar();

        /* Enter key */
        if (ch == '\n' || ch == '\r')
            break;

        /* Backspace */
        if ((ch == 127 || ch == 8) && i > 0)
        {
            i--;
            printf("\b \b");
            fflush(stdout);
            continue;
        }

        if (i < size - 1)
        {
            password[i++] = ch;
            printf("*");
            fflush(stdout);
        }
    }

    password[i] = '\0';

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    printf("\n");
}
