#include <stdio.h>
#include"module.h"
void module_question_choice();

int main(int argc, char *argv[])
{
    char choice;

    do
    {
        module_question_choice(argc,argv);
        getchar();
        printf("\nDo you want to continue or exit?(yes or no)");
        scanf("%c", &choice);


    } while (choice == 'y' || choice == 'Y');
    return 0;
}

