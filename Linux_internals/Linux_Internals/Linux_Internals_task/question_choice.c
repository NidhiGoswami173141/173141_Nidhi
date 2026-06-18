#include<stdio.h>
#include<stdint.h>
#include"header.h"
/*void question_choice(int argc, char *argv[])
{
    int32_t choice;

    printf("1. sparse file\n");
    printf("2. copy one file into another file\n");
    printf("3. display the content of directory\n");
    printf("4. add flags\n");
    printf("5. check file descriptor\n");

    printf("enter your choice:\n");


    if(scanf("%d",&choice) != 1)
    {
        printf("Invalid choice input\n");
        return;
    }


    switch(choice)
    {
        case 1:
            sparse_file();
            break;

        case 2:
            copy_file(argc,argv);
            break;

        case 3:
            display_dir_content(argc,argv);
            break;

        case 4:
            add_flag();
            break;

        case 5:
            check_file_descriptor();
            break;
        case 6:
            ex_5_2();
            break;

        default:
            printf("Invalid choice\n");
    }
}
*/

void question_choice(int argc, char *argv[])
{
    int32_t choice;


    if(argc < 2)
    {
        printf("Usage: %s <question_number>\n", argv[0]);
        return;
    }


    choice = atoi(argv[1]);


    switch(choice)
    {
        case 1:
            sparse_file();
            break;


        case 2:
            copy_file(argc, argv);
            break;


        case 3:
            display_dir_content(argc, argv);
            break;


        case 4:
            add_flag();
            break;


        case 5:
            if(argc < 3){
                 printf("usage : %s 5 <question number>\n", argv[0]);
                 break;
            }
            int32_t que = atoi(argv[2]);
            switch(que){
              case 1:
                 check_file_descriptor();
                 break;
              case 2:
                 ex_5_2();
                 break;
            }break;
        case 6:
            if(argc < 3){
               printf("usage: %s 6 <question number>\n", argv[0]);
               break;
            }
            int32_t queno = atoi(argv[2]);
            switch(queno){
                case 1:
                   simpcat1();
                   break;
                case 2:
                   simpcat2();
                   break;
                case 3:
                   simpcat3();
                   break;
                case 4:
                   simpcat4(argc , argv);
                   break;
            }break;
         case 7:
             if(argc < 3){
                  printf("usage : %s 7 <question number>\n",argv[0]);
                  break;
             }
             int32_t question = atoi(argv[2]);
              switch(question){
                  case 1:
                     cat_using_stdio(argc,argv);
                     break;
                  case 2:
                     cat_using_systemcall(argc, argv);
                     break;
                  case 3:
                     getchar_fun();
                     break;
              }break;
          case 8:
              if(argc < 3){
                 printf("usage : %s 8 <question number>\n", argv[0]);
                 break;
              }
              int32_t que_no = atoi(argv[2]);
              switch(que_no){
                  case 1:
                     ls_command_using_stat();
                     break;
                  case 2:
                     ls_command_f();
                     break;
                  case 3:
                     cal_size_of_all();
                     break;
                  case 4:
                     cal_size_of_all_file_folder(argc,argv);
                     break;
              }break;
        case 9:
             if(argc < 3){
                printf("usage : %s 9<question number>\n",argv[0]);
                break;
             }
             int32_t q = atoi(argv[2]);
             switch(q){
                 case 1:
                    cpu_info();
                    break;
             }break;

        default:
            printf("Invalid choice\n");
    }
}
