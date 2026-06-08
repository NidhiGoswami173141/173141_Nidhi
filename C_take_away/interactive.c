#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define FIXED_XOR_KEY 0xABCD

int main()
{
    int choice;
    int logged_in = 0;

    char current_user[100];

    char username[100];
    char password[100];

    char string[1000];
    char filename[100];
    char new_data[1000];

    int key;

    while(1)
    {
        while(logged_in == 0)
        {
            printf("\n====================================\n");
            printf(" TAKE AWAY FILE ENCRYPTION SYSTEM\n");
            printf("====================================\n");

            printf("1. Register\n");
            printf("2. Login\n");
            printf("3. Exit\n");

            printf("Enter choice: ");
            scanf("%d", &choice);

            switch(choice)
            {

                case 1:

                    printf("Enter username: ");
                    scanf("%s", username);

                    printf("Enter password: ");
                    scanf("%s", password);

                    int reg_result;

                    reg_result = register_user(username, password);

                    if(reg_result == 0)
                        printf("Registration successful\n");

                    else if(reg_result == 1)
                        printf("Username already exists\n");

                    else if(reg_result == 2)
                        printf("Invalid input\n");

                    else
                        printf("Storage error\n");

                    break;


                case 2:

                    printf("Enter username: ");
                    scanf("%s", username);

                    printf("Enter password: ");
                    scanf("%s", password);

                    int login_result;

                    login_result = login_user(username, password);

                    if(login_result == 0)
                    {
                        printf("Login successful\n");

                        logged_in = 1;

                        strcpy(current_user, username);
                    }

                    else if(login_result == 1)
                        printf("Incorrect password\n");

                    else if(login_result == 2)
                        printf("Invalid input\n");

                    else
                        printf("User not found\n");

                    break;


                case 3:

                    printf("Exit bye bye...\n");
                    return 0;

                default:

                    printf("Invalid choice\n");
            }
        }
        while(logged_in == 1)
        {

            printf("\n====================================\n");
            printf(" Welcome %s\n", current_user);
            printf("====================================\n");

            printf("1. XOR Encryption\n");
            printf("2. XOR Decryption\n");
            printf("3. Create Encrypted File\n");
            printf("4. Read Encrypted File\n");
            printf("5. Append To Encrypted File\n");
            printf("6. Log File Operation\n");
            printf("7. Secure Delete File\n");
            printf("8. Logout\n");

            printf("Enter choice: ");
            scanf("%d", &choice);

            switch(choice)
            {

                case 1:
                {

                    printf("Enter string for encryption:\n");
                    scanf(" %[^\n]", string);

                    printf("Enter key: ");
                    scanf("%x", &key);

                    char *result = xor_encrypt(string, key);

                    if(result == NULL)
                    {
                        printf("Encryption failed\n");
                    }
                    else
                    {
                        printf("Encrypted text: %s\n", result);
                        free(result);
                    }

                    break;
                }


                case 2:
                {

                    printf("Enter encrypted hex string:\n");
                    scanf("%s", string);

                    printf("Enter key: ");
                    scanf("%x", &key);

                    char *result = xor_decrypt(string, key);

                    if(result == NULL)
                    {
                        printf("Decryption failed\n");
                    }
                    else
                    {
                        printf("Decrypted text: %s\n", result);
                        free(result);
                    }

                    break;
                }


                case 3:
                {

                    printf("Enter filename: ");
                    scanf("%s", filename);

                    printf("Enter text:\n");
                    scanf(" %[^\n]", string);

                    printf("Enter key: ");
                    scanf("%x", &key);

                    int result;

                    result = create_encrypted_file(filename, string, key);

                    if(result == 0)
                        printf("Encrypted file created successfully\n");

                    else if(result == 1)
                        printf("File already exists\n");

                    else if(result == 2)
                        printf("Invalid input\n");

                    else
                        printf("File creation error\n");

                    break;
                }


                case 4:
                {

                    printf("Enter filename: ");
                    scanf("%s", filename);

                    printf("Enter key: ");
                    scanf("%x", &key);

                    char *content;

                    content = read_encrypted_file(filename, key);

                    if(content == NULL)
                    {
                        printf("Unable to read/decrypt file\n");
                    }
                    else
                    {
                        printf("Decrypted file content:\n%s\n", content);
                        free(content);
                    }

                    break;
                }


                case 5:
                {

                    printf("Enter filename: ");
                    scanf("%s", filename);

                    printf("Enter new text:\n");
                    scanf(" %[^\n]", new_data);

                    printf("Enter key: ");
                    scanf("%d", &key);

                    int result;

                    result = append_to_encrypted_file(filename, key, new_data);

                    if(result == 0)
                        printf("Data appended successfully\n");

                    else if(result == 1)
                        printf("File does not exist\n");

                    else if(result == 2)
                        printf("Invalid input\n");

                    else if(result == 4)
                        printf("Wrong key\n");

                    else
                        printf("Append error\n");

                    break;
                }


                case 6:
                {

                    char operation[100];

                    printf("Enter operation (READ/WRITE/DELETE): ");
                    scanf("%s", operation);

                    printf("Enter filename: ");
                    scanf("%s", filename);

                    int result;

                    result = log_operation(current_user, operation, filename);

                    if(result == 0)
                        printf("Operation logged successfully\n");

                    else if(result == 1)
                        printf("Invalid input\n");

                    else
                        printf("Log file error\n");

                    break;
                }


                case 7:
                {

                    printf("Enter filename: ");
                    scanf("%s", filename);

                    int result;

                    result = secure_delete(filename, current_user);

                    if(result == 0)
                        printf("File securely deleted\n");

                    else if(result == 1)
                        printf("File not found\n");

                    else if(result == 2)
                        printf("Unauthorized user\n");

                    else
                        printf("Delete error\n");

                    break;
                }


                case 8:

                    logged_in = 0;

                    printf("Logout successful\n");

                    break;


                default:

                    printf("Invalid choice\n");
            }
        }
    }

    return 0;
}
