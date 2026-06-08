/*
Author:Nidhi Goswami
Date : 05/05/2026
Description : functions for this file encryption system
*/

#include "header.h"
#include<stdio.h>
#include<stdint.h>
#include <openssl/sha.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
/*Fixed XOR key for easier handling*/
#define FIXED_XOR_KEY 0xABCD  /*43981 in decimal*/

/*
Author: Nidhi Goswami
Date:6-5-2026
Task 0: User Registration and Authentication Functions
*/
void hash_password(const char *password, char *output)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256((unsigned char *)password,
           strlen(password),
           hash);

    for (int32_t index = 0; index < SHA256_DIGEST_LENGTH; index++)
    {
        sprintf(output + (index * 2), "%02x", hash[index]);
    }

    output[64] = '\0';
}

int register_user(const char *username, const char *password) {
    /*
     * WRITE YOUR LOGIC HERE
     *
     * Expected Return Values:
     * - Return 0 on success (user registered successfully)
     * - Return 1 if username already exists
     * - Return 2 for invalid input (empty username or password)
     * - Return 3 on storage error (file I/O issues)
     */

    /* TODO : Input validation */
        if(username == NULL || password == NULL ||strlen(username)==0||strlen(password)==0){
             return 2;
        }
    /*open file*/
       FILE *fp;
       fp = fopen("users.db","a+");
       if(fp == NULL){
          return 3;
       }
       if (chmod("users.db", 0600) != 0) {
        fclose(fp);
        return 3;
       }

    /*TODO: Check if user exists*/
       char data[200];
       char name[100];
       char pass[100];

       fseek(fp, 0, SEEK_SET);   /*start from top*/

       while (fscanf(fp, "%s", data) == 1) {

           int64_t index = 0, sec_index = 0;

           /*get name (before :)*/
           while (data[index] != ':' && data[index] != '\0') {
                name[index] = data[index];
                index++;
           }
           name[index] = '\0';

           index++;  /*skip ':'*/

           /*get password (after :)*/
           while (data[index] != '\0') {
              pass[sec_index++] = data[index++];
           }
           pass[sec_index] = '\0';

           /*compare username*/
           if (strcmp(name, username) == 0) {
                fclose(fp);
                return 1;   /*found*/
           }
      }

    /* TODO: Hash password with XOR*/
         /* char hash[100];
          int64_t index;
          for (index = 0; password[index]; index++) {
              hash[index] = password[index] ^ FIXED_XOR_KEY;
          }
          hash[index] = '\0';*/
          char hash[65];
          hash_password(password, hash);

    /*TODO: Store in users.db*/
          /*fprintf(fp, "%s:%s\n", username, hash);
          fclose(fp);
    return 0;*/
    if (fprintf(fp, "%s:%s\n", username, hash) < 0)
    {
        fclose(fp);
        return 3;
     }

     fclose(fp);
     return 0;
    /*Placeholder*/
    }

int login_user(const char *username, const char *password) {
    /*
     * WRITE YOUR LOGIC HERE
     *
     * Expected Return Values:
     * - Return 0 on successful login
     * - Return 1 for incorrect username/password
     * - Return 2 for invalid input (NULL or empty strings)
     * - Return 3 if user not found
     */
    /* TODO: Input validation */
       if(username == NULL || password == NULL ||strlen(username)==0||strlen(password)==0){
             return 2;
        }

    /*TODO: Read users.db and find user*/
       FILE *fp;
       fp = fopen("users.db","r");
       if(fp == NULL){
          return 3;
       }

    /*TODO: Hash password and compare */
        /*char hash[100];
        int64_t index;
        for (index = 0; password[index]; index++) {
           hash[index] = password[index] ^ FIXED_XOR_KEY;
        }
        hash[index] = '\0';*/
        char hash[65];
        hash_password(password, hash);
        char data[256];
        char name[100];
        char pass[100];

        while (fgets(data, sizeof(data), fp)) {

             sscanf(data, "%[^:]:%s", name, pass);

             if (strcmp(name, username) == 0) {

                 fclose(fp);

                 if (strcmp(pass, hash) == 0)
                    return 0;   /*correct password*/
                 else
                    return 1;   /*wrong password */
             }
       }
       fclose(fp);
    return 3; /*Placeholder*/
}

/*
Author: Nidhi Goswami
Date: 6-5-2026
Task 1: XOR Encryption Functions*/

char* xor_encrypt(const char *input_string, uint16_t key) {
    /*
     * WRITE YOUR LOGIC HERE
     *
     * Implementation steps:
     * 1. Validate input (check for NULL or empty string)
     * 2. Allocate memory for result (input_length * 2 + 1 for hex representation)
     * 3. XOR each character with the key (use key % 256 for single byte XOR)
     * 4. Convert each encrypted byte to hex format (2 characters per byte)
     * 5. Return the hex string
     *
     * Expected Return:
     * - Return dynamically allocated string containing encrypted data in hex format
     * - Return NULL on error (empty input, memory allocation failure)
     *
     * Note: With fixed key 0xABCD (43981), "Hello" should produce specific hex output
     */

    /*TODO: Input validation */
       if(input_string == NULL || strlen(input_string) == 0){
          return NULL;
       }
       int64_t len = strlen(input_string);
    /*TODO: Allocate memory for hex result*/
       char *result = (char *)malloc(len*2+1);

       if(result == NULL){
          return NULL;
       }
    /* TODO: XOR encryption and hex conversion*/
       char hex[] = "0123456789abcdef";
       for (int32_t index = 0; index < len; index++)
       {
         unsigned char value = input_string[index] ^ (key & 0xFF);

         result[index * 2]     = hex[value >> 4];      /*first hex digit*/
         result[index * 2 + 1] = hex[value & 0x0F];    /*second hex digit*/
       }

        result[len * 2] = '\0';

       return result;
}

char* xor_decrypt(const char *encrypted_string, uint16_t key) {
    /*
     * WRITE YOUR LOGIC HERE
     *
     *
     * Expected Return:
     * - Return dynamically allocated string containing decrypted text
     * - Return NULL on error
     */

    /*TODO: Input validation and hex length check*/
      if(encrypted_string == NULL || strlen(encrypted_string) == 0){
         return NULL;
      }
      size_t len = strlen(encrypted_string);
      if(len %2 != 0){
         return NULL;
      }

      int64_t output = len/2;
    /*TODO: Allocate memory for decrypted result*/
      char *result = (char *)malloc(output +1);
      if(result == NULL){
        return NULL;
      }
    /*TODO: Hex to byte conversion and XOR decryption*/

    for (int32_t index = 0; index < output; index++)
    {
        char high = encrypted_string[index * 2];
        char low  = encrypted_string[index * 2 + 1];

        int32_t val1, val2;

        /*convert hex char to number*/
        /*if (high >= '0' && high <= '9') val1 = high - '0';
        else val1 = high - 'a' + 10;

        if (low >= '0' && low <= '9') val2 = low - '0';
        else val2 = low - 'a' + 10;*/
        if (high >= '0' && high <= '9'){
           val1 = high - '0';}
        else if (high >= 'a' && high <= 'f'){
           val1 = high - 'a' + 10;}
        else if (high >= 'A' && high <= 'F'){
           val1 = high - 'A' + 10;}
        else
        {
           free(result);
           return NULL;
         }


        if (low >= '0' && low <= '9'){
            val2 = low - '0';}
        else if (low >= 'a' && low <= 'f'){
             val2 = low - 'a' + 10;}
        else if (low >= 'A' && low <= 'F')
             val1 = low - 'A' + 10;
         else
        {
           free(result);
           return NULL;
         }

        unsigned char value = (val1 << 4) | val2;

        result[index] = value ^ (key & 0xFF);
     }

        result[output] = '\0';

    return result;

}

/*
Author: Nidhi Goswami
date: 7-5-2026
Task 2: File Creation with XOR Encryption*/

void set_file_permissionas(const char *filename , const char *username , const char *permissions){
     FILE *fp = fopen("permissions.db","a");
     if(fp == NULL){
        perror("permissions.db");
        return;
     }
     fprintf(fp,"%s:%s:%s\n" , filename,username,permissions);
     fclose(fp);
}

int create_encrypted_file(const char *filename, const char *text, uint16_t key) {
    /*
     * WRITE YOUR LOGIC HERE
     *
     * Expected Return Values:
     * - Return 0 on success
     * - Return 1 if file already exists
     * - Return 2 on invalid input
     * - Return 3 on file creation or write error
     */

    /* TODO: Input validation*/
      if(filename == NULL || text == NULL || strlen(filename)==0){
          return 2;
      }

      char *encrypted = NULL;

      if(strlen(text)>0){
         encrypted = xor_encrypt(text,key);

         if(encrypted == NULL){
            return 3;
         }
      }

      int fd = open(filename,O_WRONLY|O_CREAT|O_EXCL,0600);
    /*TODO: Check file existence*/
      /*if(fd == -1){
         if(errno == EEXIST){
           return 1;
         }

         perror("open");
         if(encrypted){
           free(encrypted);
         }
         return 3;
      }*/
      if(fd == -1)
      {
         if(errno == EEXIST)
      {
          if(encrypted)
            free(encrypted);

        return 1;
      }

      perror("open");

      if(encrypted)
        free(encrypted);

    return 3;
   }
    /*TODO: Encrypt text and write to file*/
      if(encrypted != NULL){
        if(write(fd,encrypted,strlen(encrypted))==-1){
           perror("write");
           close(fd);
           free(encrypted);
           return 3;
        }
      }
     close(fd);

     if(encrypted){
        free(encrypted);
     }
     set_file_permissionas(filename, "owner","rwd");
    return 0; /*Placeholder*/
}

/*
Author: Nidhi Goswami
Date: 7-5-2026
Task 3: Reading Encrypted Files*/

char* read_encrypted_file(const char *filename, uint16_t key) {
    /*
     * WRITE YOUR LOGIC HERE
     *
     * Expected Return:
     * - Return dynamically allocated string with decrypted content
     * - Return NULL on error (file not found, permission denied, invalid key)
     */

    /*TODO: Input validation and file checks*/
     if(filename == NULL || strlen(filename)== 0){
        return NULL;
     }

     /* file opening*/
     FILE *fp = fopen(filename , "r");

     if(fp == NULL){
       perror("fopen");
       return NULL;
     }
     fseek(fp, 0, SEEK_END);
     long size = ftell(fp);
     rewind(fp);

     if(size == 0){
       char *empty = malloc(1);
       if(empty == NULL){
         fclose(fp);
         return NULL;
       }
       empty[0] = '\0';
       fclose(fp);
       return empty;
     }

     /* allocate memory */
     char *encrypted = malloc(size+1);
     if(encrypted == NULL){
       fclose(fp);
       return NULL;
     }
    /* TODO: Read file content*/
    fread(encrypted , 1 , size , fp);
    encrypted[size] = '\0';
    fclose(fp);

    /*TODO: Decrypt and return*/
    char *decrypted = xor_decrypt(encrypted,key);
    free(encrypted);
   return decrypted;
}

/*
Author: Nidhi Goswami
Date: 7-5-2026
Task 4give : Appending to Existing Encrypted Files*/

int append_to_encrypted_file(const char *filename, uint16_t key, const char *new_data) {
    /*
     * WRITE YOUR LOGIC HERE
     *
     * Expected Return Values:
     * - Return 0 on success
     * - Return 1 if file doesn't exist
     * - Return 2 on invalid input
     * - Return 3 on read/write error
     * - Return 4 if key is wrong and decryption failed
     */

    /*TODO: Input validation*/
     if(filename == NULL || strlen(filename)== 0 || new_data == NULL){
          return 2;
     }
    /*TODO: Read existing content and decrypt*/
      FILE *fp = fopen(filename, "r+-");

      if(fp == NULL){
         return 1;
       }

      fclose(fp);
     /* if(key != FIXED_XOR_KEY){
          return 4;
      }*/
      if(strlen(new_data) == 0)
      {
           return 0;
      }
      char *old_content= read_encrypted_file(filename,key);

      if(old_content == NULL){
          return 4;
      }

      size_t total_len = strlen(old_content)+ strlen(new_data);
      char *combined = malloc(total_len+1);

      if(combined == NULL){
        free(old_content);
        return 3;
      }
      strcpy(combined,old_content);
      strcat(combined,new_data);

      char *encrypted = xor_encrypt(combined,key);
      char temp_file[256];

     snprintf(temp_file, sizeof(temp_file),"%s.tmp",filename);
      if(encrypted == NULL){
        free(old_content);
        free(combined);
        return 3;
      }

    /*TODO: Append new data and re-encrypt*/
      fp = fopen(temp_file,"w");
      if(fp == NULL){
        free(old_content);
        free(combined);
        free(encrypted);
        return 3;
      }
      if (fprintf(fp,"%s",encrypted) < 0)
      {
         fclose(fp);
         if(key != FIXED_XOR_KEY)
         {
            return 4;
          }

         remove(temp_file);

         free(old_content);
         free(combined);
         free(encrypted);

        return 3;
     }

      fclose(fp);
      if(rename(temp_file, filename) != 0)
      {
           remove(temp_file);

           free(old_content);
           free(combined);
           free(encrypted);

        return 3;
      }
      free(old_content);
      free(combined);
      free(encrypted);

    return 0; /*Placeholder*/
}

/*
Author: Nidhi Goswami
Date: 8-5-2026
Task 5: Logging File Operations
*/
int log_operation(const char *username, const char *operation, const char *filename) {
    /*
     * WRITE YOUR LOGIC HERE
     *
     * Expected Return Values:
     * - Return 0 on success
     * - Return 1 for invalid input
     * - Return 2 for log file error
     *
     * Example output: "Wed May 28 10:30:45 2025 - USER: user1, OPERATION: READ, FILE: test1.txt"
     */

    /*TODO: Input validation*/
     if(username == NULL || operation == NULL || filename == NULL || strlen(username) == 0 || strlen(operation) == 0 || strlen(filename)==0){
        return 1;
     }

    /*TODO: Get timestamp and format log entry*/
    FILE *fp = fopen("file_operation.log","a");
    if(fp == NULL){
      perror("fopen");
      return 2;
    }
    time_t now = time(NULL);

    char *time_str = ctime(&now);
    if(time_str == NULL){
    fclose(fp);
    return 2;
    }
    time_str[strlen(time_str) - 1] = '\0';

    /*TODO: Append to log file*/
    fprintf(fp,
            "%s - USER: %s, OPERATION: %s, FILE: %s\n",
            time_str,
            username,
            operation,
            filename);

    fclose(fp);

    return 0; // Placeholder
}

/*
Author: Nidhi Goswami
Date: 8-5-2026
Task 6: Secure File Deletion*/

int secure_delete(const char *filename, const char *username) {
    /*
     * WRITE YOUR LOGIC HERE
     *
     * Expected Return Values:
     * - Return 0 on successful secure deletion
     * - Return 1 if file doesn't exist
     * - Return 2 if user is not authorized
     * - Return 3 on file I/O or unlink error
     */

    /* TODO: Input validation and file checks*/
     if(filename == NULL || username == NULL || strlen(filename) == 0 || strlen(username) == 0){
          return 2;
     }

    /* TODO: Check permissions*/
    FILE *fp = fopen(filename, "r");

    if(fp == NULL){
        return 1;
    }
    fclose(fp);
    if(strcmp(username, "user1") != 0){
      return 2;
    }
    fp = fopen(filename, "r+");
    if(fp == NULL){
      return 3;
    }
    fseek(fp , 0, SEEK_END);
    long size = ftell(fp);
    if(size == -1){
     fclose(fp);
     return 3;
    }
    fseek(fp, 0, SEEK_SET);
    for(long index = 0; index <size ; index++){
       if(fputc(0, fp) == EOF){
         fclose(fp);
         return 3;
       }
    }

    /*TODO: Secure overwrite and delete*/
    fflush(fp);
    fclose(fp);
    if(remove(filename) != 0){
      return 3;
    }
    return 0; /*Placeholder*/
}

// Helper Functions

int check_file_permission(const char *filename, const char *username, const char *operation) {
    /*
     * WRITE YOUR LOGIC HERE
     *
     *
     * Return 1 if authorized, 0 if not
     */

    // TODO: Read permissions.db and check authorization

    return 1; // Placeholder - allow all for now
}

void set_file_permission(const char *filename, const char *username, const char *permissions) {
    /*
     * WRITE YOUR LOGIC HERE
     *
     * Implementation steps:
     * 1. Read existing permissions.db
     * 2. Add or update entry for filename:username:permissions
     * 3. Write back to permissions.db
     *
     * Format: "filename:username:permissions"
     */

    // TODO: Update permissions.db file
}












