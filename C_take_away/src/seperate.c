#include "../include/header.h"
#include <stdio.h>
#include <stdlib.h>

extern void test_task0_user_registration();
extern void test_task1_xor_encryption();
extern void test_task2_file_creation();
extern void test_task3_reading_files();
extern void test_task4_appending_files();
extern void test_task5_logging();
extern void test_task6_secure_deletion();
extern void print_final_summary();

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./test.out <task_number>\n");
        return 1;
    }

    int choice = atoi(argv[1]);

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
            printf("Invalid Task Number\n");
            return 1;
    }

    print_final_summary();

    return 0;
}
