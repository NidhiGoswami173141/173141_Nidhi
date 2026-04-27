/*
Author : Nidhi Goswami
Description : Compare two files and print first differing line
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

void compare_files(int32_t argc, char *argv[])
{
    FILE *fp1, *fp2;
    char line1[MAXLINE], line2[MAXLINE];
    int32_t lineNum = 1;
    int32_t differ = 0;

    if (argc != 3)
    {
        printf("Usage: file1 file2\n");
        return;
    }

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "r");

    if (!fp1 || !fp2)
    {
        printf("Error opening files\n");
        return;
    }

    while (1)
    {
        char *r1 = fgets(line1, MAXLINE, fp1);
        char *r2 = fgets(line2, MAXLINE, fp2);

        if (r1 == NULL && r2 == NULL)
            break;

        if (r1 == NULL || r2 == NULL)
        {
            printf("Files have different lengths.\n");
            fclose(fp1);
            fclose(fp2);
            return;
        }

        if (strcmp(line1, line2) != 0)
        {
            printf("Files differ at line %d:\n", lineNum);
            printf("[%s:]%s", argv[1], line1);
            printf("[%s:]%s", argv[2], line2);
            differ = 1;
            break;
        }

        lineNum++;
    }

    if (!differ)
    {
        printf("Files are identical.\n");
    }

    fclose(fp1);
    fclose(fp2);
}
