#include <stdio.h>
#include <stdint.h>
#include "module.h"

void module_question_choice(int argc, char *argv[])
{
    int module, question;

    printf("module: ");
    scanf("%d", &module);

    printf("question: ");
    scanf("%d", &question);

    switch (module)
    {
        case 1:
            switch (question)
            {
                case 1:
                    hello_world();
                    break;

                case 2:
                    Hello_world();
                    break;

                case 3:
                    fehrenhit_celsius();
                    break;

                case 4:
                    celsius_fehrenheit();
                    break;

                case 5:
                    reverse_tem_table();
                    break;

                case 6:
                    verify_EOF();
                    break;

                case 7:
                    value_of_EOF();
                    break;
                case 8:
                    count_blank_tabs_newline();
                    break;
                case 9:
                    removeblank();
                    break;
                case 10:
                    replace_tab_backspace_backslash();
                    break;
                case 11:
                    word_count();
                    break;
                case 12:
                    word_per_line();
                    break;
                case 13:
                    histogram_lenght_of_words();
                    break;
                case 14:
                    histogram_frequencies_of_characters();
                    break;
                case 15:
                    convertToFahrenheit();
                    break;
                case 16:
                    longest_line();
                    break;
                case 17:
                    print_long_lines();
                    break;
                case 18:
                    remove_trailing_blanks();
                    break;
                case 19:
                    reverse_string_s();
                    break;
                case 20:
                    detab();
                    break;
                case 21:
                    entab();
                    break;
                case 22:
                    fold_line();
                    break;
                case 23:
                   remove_comments();
                   break;
                case 24:
                   check_C_program();
                   break;
                default:
                    printf("Invalid question\n");
            }
            break;
            case 2:
              switch (question)
              {
                case 1:
                   range_of_char_short_int_long();
                   break;
                case 2:
                   loop();
                   break;
                case 3:
                   htoi();
                   break;
                case 4:
                   squeeze();
                   break;
                case 5:
                   return_location();
                   break;
                case 6:
                  setbits();
                   break;
                case 7:
                   invert();
                   break;
                case 8:
                   rightrot();
                   break;
                case 9:
                   deletes_rightmost();
                   break;
                case 10:
                   lowercase();
                   break;
              }break;
        case 3:
              switch (question)
              {
                case 1:
                  binary_search();
                  break;
                case 2:
                  char input[1000];
                  char output[1000];
                  escape(input, output);
                  break;
                case 3:
                  char ip[1000];
                  char op[1000];
                  expand(ip, op);
                  break;
               case 4:
                  char s[1000];
                  int32_t number;
                  itoa(number,s);
                  break;
               case 5:
                  int32_t n,base;
                  char str[100];
                  itob(n,str,base);
                  break;
               case 6:
                  int32_t num,min_width;
                  char Str[100];
                  itoa_width(num,Str,min_width);
              }break;
         case 4:
            switch(question){
               case 1:
               strindex();
               break;
               case 2:
               a_atof();
               break;
               case 3:
               calculator();
               break;
               case 4:
               RPN_calculator();
               break;
               case 5:
               fun_calculator();
               break;
               case 6:
               variable_handling();
               break;
               case 7:
               char s[100];
               ungets(s);
               break;
               case 8:
               single_pushback_calculator();
               break;
               case 9:
               eof_handling();
               break;
               case 10:
               calculator_getline();
               break;
               case 11:
               calculator_static_getop();
               break;
               case 12:
               itoa_recursive_function();
               break;
               case 13:
               recursive_reverse();
               break;
               case 14:
               swap_arguments();
               break;
            }break;
        case 5:
             switch(question){
              case 1:
                 int i;
                 getint(&i);
                 break;
              case 2:
                 double d;
                 getfloat(&d);
                 break;
              case 3:
                 strcat_string();
                 break;
              case 4:
                 strend_function();
                 break;
              case 5:
                 strn_function();
                 break;
              case 6:
                 functions();
                 break;
              case 7:
                 read_lines();
                 break;
              case 8:
                 error_checking() ;
                 break;
              case 9:
                 day_month_function();
                 break;
              case 10:
                 expr(argc, argv);
                 break;
               case 11:
                    detab_entab(argc, argv);
                    break;
              case 13:
                   tail_function(argc,argv);
                   break;
              case 14:
                   handle_flag_RN(argc, argv);
                   break;
              case 15:
                   handle_flag_RNF(argc,argv);
                   break;
              case 16:
                   handle_flag_RNFD(argc ,argv);
                   break;
              case 17:
                   handle_field_sort(argc,argv);
                   break;
              case 18:
                   dcl_fun();
                   break;
              case 19:
                  undcl_fun();
                  break;
              case 20:
                  handle_arg_type();
                  break;
             }break;
           case 6:
               switch(question){
               case 1:
                 getwords_ver();
                 break;
              case 2:
                 alphabatical_to_group(argc ,argv);
                 break;
              case 3:
                 cross_referntial();
                 break;
              case 4:
                 decreasing_order_word_frequency();
                 break;
              case 5:
                 hash_table();
                 break;
              case 6:
                 define_processer();
                 break;
             }break;
         case 7:
            switch(question){
               case 1:
                 upper_lower(argc,argv);
                 break;
               case 2:
                 print_non_graphic_character_in_hex_or_octal();
                 break;
               case 3:
                 min_printf();
                 break;
               case 4:
                 min_scanf();
                 break;
               case 5:
                 postfix_calculator_using_scanf();
                 break;
            }
    }
}


