#include<stdio.h>
int main(){

    void p1_function1();
    void p1_function2();
    void p1_function3();

    int func;
    printf("1 2 3:");
    if (scanf("%d", &func) == 0){
        printf("Failed to take user input\n");
        return 0;
    }

    switch(func){
          case 1:
               p1_function1();
               break;
          case 2:
               p1_function2();
               break;
          case 3:
               p1_function3();
               break;
    };
    return 0;

}
