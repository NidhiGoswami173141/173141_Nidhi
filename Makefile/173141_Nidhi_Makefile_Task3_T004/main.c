#include<stdio.h>
int main(){
    void p1_function1();
    void p1_function2();
    void p1_function3();
    void p2_function1();
    void p2_function2();
    void p2_function3();
    void p3_function1();
    void p3_function2();
    void p3_function3();

    int funct;
    printf("1 2 3:");
    if (scanf("%d", &funct) == 0){
        printf("Failed to take user input\n");
        return 0;
    }
    switch(funct){
          case 1:
               p1_function1();
               p2_function1();
               p3_function1();
               break;
          case 2:
               p1_function2();
               p2_function2();
               p3_function2();
               break;
          case 3:
               p1_function3();
               p2_function3();
               p3_function3();
               break;
    };
    return 0;
}

