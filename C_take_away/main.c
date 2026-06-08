/*
Author: Nidhi Goswami
Date: 05/05/2026
Description : main function for all file system encryption 
*/

#include "header.h"
#include<stdio.h>
// Test result tracking
int total_tests = 0;
int passed_tests = 0;

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"

// Fixed XOR key (should match the one in functions.c)
#define FIXED_XOR_KEY 0xABCD  // 43981 in decimal

void print_test_result(const char* test_name, int expected, int actual, const char* description) {
    total_tests++;
    printf("\n" BLUE "Test: %s" RESET "\n", test_name);
    printf("Description: %s\n", description);
    printf("Expected: %d, Got: %d\n", expected, actual);

    if (expected == actual) {
        printf(GREEN "✓ PASSED" RESET "\n");
        passed_tests++;
    } else {
        printf(RED "✗ FAILED" RESET "\n");
    }
    printf("----------------------------------------\n");
}

void print_string_test_result(const char* test_name, const char* expected, const char* actual, const char* description) {
    total_tests++;
    printf("\n" BLUE "Test: %s" RESET "\n", test_name);
    printf("Description: %s\n", description);
    printf("Expected: %s\n", expected ? expected : "NULL");
    printf("Got:      %s\n", actual ? actual : "NULL");

    int passed = 0;
    if (expected == NULL && actual == NULL) {
        passed = 1;
    } else if (expected != NULL && actual != NULL && strcmp(expected, actual) == 0) {
        passed = 1;
    }

    if (passed) {
        printf(GREEN "✓ PASSED" RESET "\n");
        passed_tests++;
    } else {
        printf(RED "✗ FAILED" RESET "\n");
    }
    printf("----------------------------------------\n");
}

void test_task0_user_registration() {
    printf("\n" YELLOW "=== TASK 0: USER REGISTRATION AND AUTHENTICATION TESTS ===" RESET "\n");

    // Clean up existing users.db for fresh testing
    remove("users.db");
    remove("permissions.db");

    // Test Case 1: Register with username "user1" and password "pass123"
    int result1 = register_user("user1", "pass123");
    print_test_result("Register user1", 0, result1, "Register with username 'user1' and password 'pass123' should succeed");

    // Test Case 2: Register with existing username
    int result2 = register_user("user1", "newpass");
    print_test_result("Register existing user", 1, result2, "Register with existing username should return error code 1");

    // Test Case 3: Register with empty username
    int result3 = register_user("", "pass123");
    print_test_result("Register empty username", 2, result3, "Register with empty username should return error code 2");

    // Test Case 4: Register with empty password
    int result4 = register_user("user2", "");
    print_test_result("Register empty password", 2, result4, "Register with empty password should return error code 2");

    // Test Case 5: Register with NULL inputs
    int result5 = register_user(NULL, "pass123");
    print_test_result("Register NULL username", 2, result5, "Register with NULL username should return error code 2");

    // Test Case 6: Login with valid credentials
    int result6 = login_user("user1", "pass123");
    print_test_result("Login valid credentials", 0, result6, "Login with correct username/password should succeed");

    // Test Case 7: Login with wrong password
    int result7 = login_user("user1", "wrongpass");
    print_test_result("Login wrong password", 1, result7, "Login with wrong password should return error code 1");

    // Test Case 8: Login with non-existent user
    int result8 = login_user("nonexistent", "pass123");
    print_test_result("Login non-existent user", 3, result8, "Login with non-existent user should return error code 3");

    // Register additional users for later tests
    register_user("user2", "pass456");
    register_user("testuser", "testpass");
}

void test_task1_xor_encryption() {
    printf("\n" YELLOW "=== TASK 1: XOR ENCRYPTION TESTS ===" RESET "\n");

    // Test Case 1: Encrypt "Hello" with fixed key
    char* encrypted1 = xor_encrypt("Hello", FIXED_XOR_KEY);
    printf("\n" BLUE "Test: Encrypt Hello with fixed key" RESET "\n");
    printf("Description: Encrypt 'Hello' with fixed key %d (0x%X)\n", FIXED_XOR_KEY, FIXED_XOR_KEY);
    printf("Got: %s\n", encrypted1 ? encrypted1 : "NULL");

    // Test Case 2: Decrypt the encrypted result
    if (encrypted1) {
        char* decrypted1 = xor_decrypt(encrypted1, FIXED_XOR_KEY);
        print_string_test_result("Decrypt Hello", "Hello", decrypted1, "Decrypt should return original text 'Hello'");
        if (decrypted1) free(decrypted1);

        total_tests++;
        if (encrypted1 != NULL) {
            printf(GREEN "✓ PASSED (encryption produced result)" RESET "\n");
            passed_tests++;
        } else {
            printf(RED "✗ FAILED (encryption returned NULL)" RESET "\n");
        }
        free(encrypted1);
    }

    // Test Case 3: Encrypt "XOR Test" with fixed key
    char* encrypted2 = xor_encrypt("XOR Test", FIXED_XOR_KEY);
    if (encrypted2) {
        char* decrypted2 = xor_decrypt(encrypted2, FIXED_XOR_KEY);
        print_string_test_result("Encrypt/Decrypt XOR Test", "XOR Test", decrypted2, "Encrypt then decrypt 'XOR Test' should return original");
        if (decrypted2) free(decrypted2);
        free(encrypted2);
    }

    // Test Case 4: Encrypt empty string
    char* encrypted3 = xor_encrypt("", FIXED_XOR_KEY);
    print_string_test_result("Encrypt empty string", NULL, encrypted3, "Encrypt empty string should return NULL");
    if (encrypted3) free(encrypted3);

    // Test Case 5: Encrypt NULL input
    char* encrypted4 = xor_encrypt(NULL, FIXED_XOR_KEY);
    print_string_test_result("Encrypt NULL input", NULL, encrypted4, "Encrypt NULL input should return NULL");
    if (encrypted4) free(encrypted4);
}

void test_task2_file_creation() {
    printf("\n" YELLOW "=== TASK 2: FILE CREATION WITH XOR ENCRYPTION TESTS ===" RESET "\n");

    // Clean up existing test files
    remove("test1.txt");
    remove("empty.txt");
    remove("test2.txt");
    remove("append_test.txt");

    // Test Case 1: Create "test1.txt" with text "Hello" and fixed key
    int result1 = create_encrypted_file("test1.txt", "Hello", FIXED_XOR_KEY);
    print_test_result("Create test1.txt", 0, result1, "Create 'test1.txt' with 'Hello' and fixed key should succeed");

    // Test Case 2: Attempt to create "test1.txt" again (should fail - file exists)
    int result2 = create_encrypted_file("test1.txt", "World", FIXED_XOR_KEY);
    print_test_result("Create existing file", 1, result2, "Create existing file should return error code 1");

    // Test Case 3: Create file with empty text
    int result3 = create_encrypted_file("empty.txt", "", FIXED_XOR_KEY);
    print_test_result("Create empty file", 0, result3, "Create file with empty text should succeed");

    // Test Case 4: Invalid filename (NULL)
    int result4 = create_encrypted_file(NULL, "Hello", FIXED_XOR_KEY);
    print_test_result("Create NULL filename", 2, result4, "Create with NULL filename should return error code 2");

    // Test Case 5: Invalid text (NULL)
    int result5 = create_encrypted_file("test2.txt", NULL, FIXED_XOR_KEY);
    print_test_result("Create NULL text", 2, result5, "Create with NULL text should return error code 2");

    // Create additional test files
    create_encrypted_file("test2.txt", "World", FIXED_XOR_KEY);
    create_encrypted_file("append_test.txt", "Initial", FIXED_XOR_KEY);
}

void test_task3_reading_files() {
    printf("\n" YELLOW "=== TASK 3: READING ENCRYPTED FILES TESTS ===" RESET "\n");

    // Test Case 1: Read "test1.txt" with correct key
    char* content1 = read_encrypted_file("test1.txt", FIXED_XOR_KEY);
    print_string_test_result("Read test1.txt correct key", "Hello", content1, "Read 'test1.txt' with correct key should return 'Hello'");
    if (content1) free(content1);

    // Test Case 2: Read non-existent file
    char* content2 = read_encrypted_file("nonexistent.txt", FIXED_XOR_KEY);
    print_string_test_result("Read non-existent file", NULL, content2, "Read non-existent file should return NULL");
    if (content2) free(content2);

    // Test Case 3: Read file with wrong key (should not crash)
    char* content3 = read_encrypted_file("test1.txt", 99999);
    printf("\n" BLUE "Test: Read with wrong key" RESET "\n");
    printf("Description: Read 'test1.txt' with wrong key should not crash (content may be garbage)\n");
    printf("Got: %s\n", content3 ? content3 : "NULL");
    if (content3 == NULL || strcmp(content3, "Hello") != 0) {
        printf(GREEN "✓ PASSED (correctly handled wrong key)" RESET "\n");
        passed_tests++;
    } else {
        printf(RED "✗ FAILED (wrong key produced correct result - unlikely)" RESET "\n");
    }
    total_tests++;
    if (content3) free(content3);

    // Test Case 4: Read empty file
    char* content4 = read_encrypted_file("empty.txt", FIXED_XOR_KEY);
    print_string_test_result("Read empty file", "", content4, "Read empty file should return empty string");
    if (content4) free(content4);

    // Test Case 5: Invalid filename (NULL)
    char* content5 = read_encrypted_file(NULL, FIXED_XOR_KEY);
    print_string_test_result("Read NULL filename", NULL, content5, "Read with NULL filename should return NULL");
    if (content5) free(content5);
}

void test_task4_appending_files() {
    printf("\n" YELLOW "=== TASK 4: APPENDING TO ENCRYPTED FILES TESTS ===" RESET "\n");

    // Test Case 1: Append " World" to existing file
    int result1 = append_to_encrypted_file("append_test.txt", FIXED_XOR_KEY, " World");
    print_test_result("Append to existing file", 0, result1, "Append ' World' to existing file should succeed");

    // Verify the append worked
    if (result1 == 0) {
        char* content = read_encrypted_file("append_test.txt", FIXED_XOR_KEY);
        print_string_test_result("Verify append result", "Initial World", content, "After append, content should be 'Initial World'");
        if (content) free(content);
    }

    // Test Case 2: Append empty string
    int result2 = append_to_encrypted_file("append_test.txt", FIXED_XOR_KEY, "");
    print_test_result("Append empty string", 0, result2, "Append empty string should succeed (no change)");

    // Test Case 3: Append to non-existent file
    int result3 = append_to_encrypted_file("nonexistent.txt", FIXED_XOR_KEY, " test");
    print_test_result("Append to non-existent", 1, result3, "Append to non-existent file should return error code 1");

    // Test Case 4: Append with wrong key
    int result4 = append_to_encrypted_file("append_test.txt", 99999, " test");
    print_test_result("Append with wrong key", 4, result4, "Append with wrong key should return error code 4");

    // Test Case 5: Invalid inputs
    int result5 = append_to_encrypted_file(NULL, FIXED_XOR_KEY, " test");
    print_test_result("Append NULL filename", 2, result5, "Append with NULL filename should return error code 2");

    int result6 = append_to_encrypted_file("append_test.txt", FIXED_XOR_KEY, NULL);
    print_test_result("Append NULL data", 2, result6, "Append with NULL data should return error code 2");
}

void test_task5_logging() {
    printf("\n" YELLOW "=== TASK 5: LOGGING FILE OPERATIONS TESTS ===" RESET "\n");

    // Clean up existing log file
    remove("log.txt");

    // Test Case 1: Log a READ operation
    int result1 = log_operation("user1", "READ", "test1.txt");
    print_test_result("Log READ operation", 0, result1, "Log READ operation should succeed");

    // Test Case 2: Log a WRITE operation
    int result2 = log_operation("user2", "WRITE", "test2.txt");
    print_test_result("Log WRITE operation", 0, result2, "Log WRITE operation should succeed");

    // Test Case 3: Log an ENCRYPT operation
    int result3 = log_operation("testuser", "ENCRYPT", "secret.txt");
    print_test_result("Log ENCRYPT operation", 0, result3, "Log ENCRYPT operation should succeed");

    // Test Case 4: Log a DELETE operation
    int result4 = log_operation("user1", "DELETE", "oldfile.txt");
    print_test_result("Log DELETE operation", 0, result4, "Log DELETE operation should succeed");

    // Test Case 5: Invalid inputs
    int result5 = log_operation(NULL, "READ", "test.txt");
    print_test_result("Log NULL username", 1, result5, "Log with NULL username should return error code 1");

    int result6 = log_operation("user1", NULL, "test.txt");
    print_test_result("Log NULL operation", 1, result6, "Log with NULL operation should return error code 1");

    int result7 = log_operation("user1", "READ", NULL);
    print_test_result("Log NULL filename", 1, result7, "Log with NULL filename should return error code 1");

    // Print log contents for verification
    printf("\n" BLUE "Log file contents (for verification):" RESET "\n");
    FILE* log_file = fopen("log.txt", "r");
    if (log_file) {
        char line[256];
        while (fgets(line, sizeof(line), log_file)) {
            printf("%s", line);
        }
        fclose(log_file);
    } else {
        printf("Could not open log file for reading\n");
    }
}

void test_task6_secure_deletion() {
    printf("\n" YELLOW "=== TASK 6: SECURE FILE DELETION TESTS ===" RESET "\n");

    // Create a test file for deletion
    create_encrypted_file("delete_test.txt", "This will be deleted", FIXED_XOR_KEY);

    // Test Case 1: Delete file as owner
    int result1 = secure_delete("delete_test.txt", "user1");
    print_test_result("Delete as owner", 0, result1, "Delete file as owner should succeed");

    // Test Case 2: Delete non-existent file
    int result2 = secure_delete("nonexistent.txt", "user1");
    print_test_result("Delete non-existent", 1, result2, "Delete non-existent file should return error code 1");

    // Create another test file
    create_encrypted_file("delete_test2.txt", "Another test file", FIXED_XOR_KEY);

    // Test Case 3: Delete file as unauthorized user
    int result3 = secure_delete("delete_test2.txt", "unauthorized_user");
    print_test_result("Delete unauthorized", 2, result3, "Delete as unauthorized user should return error code 2");

    // Test Case 4: Invalid inputs
    int result4 = secure_delete(NULL, "user1");
    print_test_result("Delete NULL filename", 2, result4, "Delete with NULL filename should return error code 2");

    int result5 = secure_delete("delete_test2.txt", NULL);
    print_test_result("Delete NULL username", 2, result5, "Delete with NULL username should return error code 2");

    // Clean up - delete the remaining test file
    secure_delete("delete_test2.txt", "user1");
}

void print_final_summary() {
    printf("\n" YELLOW "==========================================" RESET "\n");
    printf(YELLOW "            FINAL TEST SUMMARY            " RESET "\n");
    printf(YELLOW "==========================================" RESET "\n");

    printf("Total Tests Run: %d\n", total_tests);
    printf("Tests Passed: " GREEN "%d" RESET "\n", passed_tests);
    printf("Tests Failed: " RED "%d" RESET "\n", total_tests - passed_tests);

    double success_rate = (double)passed_tests / total_tests * 100;
    printf("Success Rate: %.1f%%\n", success_rate);

    if (success_rate >= 90) {
        printf(GREEN "\n EXCELLENT! Your implementation is working very well!" RESET "\n");
    } else if (success_rate >= 70) {
        printf(YELLOW "\n GOOD! Most functions are working correctly." RESET "\n");
    } else if (success_rate >= 50) {
        printf(YELLOW "\n FAIR! Several functions need attention." RESET "\n");
    } else {
        printf(RED "\n NEEDS WORK! Many functions require implementation or fixes." RESET "\n");
    }

    printf("\n" BLUE "Fixed XOR Key Info:" RESET "\n");
    printf("- Using fixed key: %d (0x%X)\n", FIXED_XOR_KEY, FIXED_XOR_KEY);
    printf(RED"- Keep FIXED_XOR_KEY in both main.c and functions.c"RESET"\n");
}

int main()
{
    int choice;

    printf(BLUE "=============================================\n" RESET);
    printf(BLUE "      FILE ENCRYPTION SYSTEM TEST MENU\n" RESET);
    printf(BLUE "=============================================\n" RESET);

    printf("\nChoose Test Suite:\n");

    printf("0 -> Task 0 : User Registration\n");
    printf("1 -> Task 1 : XOR Encryption\n");
    printf("2 -> Task 2 : File Creation\n");
    printf("3 -> Task 3 : Read Encrypted Files\n");
    printf("4 -> Task 4 : Append Files\n");
    printf("5 -> Task 5 : Logging\n");
    printf("6 -> Task 6 : Secure Delete\n");
    printf("7 -> Run All Tests\n");

    printf("\nEnter choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 0:
            test_task0_user_registration();
            break;

        case 1:
            test_task1_xor_encryption();
            break;

        case 2:
            test_task2_file_creation();
            break;

        case 3:
            test_task3_reading_files();
            break;

        case 4:
            test_task4_appending_files();
            break;

        case 5:
            test_task5_logging();
            break;

        case 6:
            test_task6_secure_deletion();
            break;

        case 7:
            test_task0_user_registration();
            test_task1_xor_encryption();
            test_task2_file_creation();
            test_task3_reading_files();
            test_task4_appending_files();
            test_task5_logging();
            test_task6_secure_deletion();
            break;

        default:
            printf(RED "Invalid Choice\n" RESET);
            return 1;
    }

    print_final_summary();

    return 0;
}




