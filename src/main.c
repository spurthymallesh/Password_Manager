#include "../include/password_manager.h"

int main(void)
{
    int choice;
    char logged_user[MAX_USERNAME];


    // test_aes();
    
    while (1)
    {
        printf("\n=====================================\n");
        printf("      SECURE PASSWORD MANAGER\n");
        printf("=====================================\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");

        //printf("\nEnter your choice: ");

        choice = get_menu_choice();

        switch (choice)
        {
            case 1:
                register_user();
                break;

            case 2:
                if (login_user(logged_user) == SUCCESS)
                {
                    vault_menu(logged_user);
                }
                break;

            case 3:
                printf("\nThank you for using Password Manager.\n");
                return 0;

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}