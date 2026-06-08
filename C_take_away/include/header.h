/*
Author: Nidhi Goswami
Date: 6-05-2026
Description : this is the header file
*/

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

/*Task 0: User Registration and Authentication*/
int register_user(const char *username, const char *password);
int login_user(const char *username, const char *password);

/*Task 1: XOR Encryption*/
char* xor_encrypt(const char *input_string, uint16_t key);
char* xor_decrypt(const char *encrypted_string, uint16_t key);

/*Task 2: File Creation with XOR Encryption*/
int create_encrypted_file(const char *filename, const char *text, uint16_t key);

/*Task 3: Reading Encrypted Files*/
char* read_encrypted_file(const char *filename, uint16_t key);

/*Task 4: Appending to Existing Encrypted Files*/
int append_to_encrypted_file(const char *filename, uint16_t key, const char *new_data);

/*Task 5: Logging File Operations*/
int log_operation(const char *username, const char *operation, const char *filename);

/*Task 6: Secure File Deletion*/
int secure_delete(const char *filename, const char *username);

/*Helper function prototypes (you may need these)*/
int check_file_permission(const char *filename, const char *username, const char *operation);
void set_file_permission(const char *filename, const char *username, const char *permissions);

#endif // HEADER_H


