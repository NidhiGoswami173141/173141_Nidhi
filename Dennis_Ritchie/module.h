#ifndef MODULE_H
#define MODULE_H
#include <stdint.h>
#include <stdlib.h>
void hello_world();
void Hello_world();
void fehrenhit_celsius();
void celsius_fehrenheit();
void reverse_tem_table();
int verify_EOF();
int8_t value_of_EOF();
void count_blank_tabs_newline();
void removeblank();
void replace_tab_backspace_backslash();
void word_count();
void  word_per_line();
void histogram_lenght_of_words();
void entab();
void fold_line();
void convertToFahrenheit();
void remove_comments();
void check_C_program();
void range_of_char_short_int_long();
void loop();
void htoi();
void squeeze();
void return_location();
void lowercase();
void deletes_rightmost();
void rightrot();
void invert();
void setbits();
void binary_search();
void escape(char Input[], char Output[]);
void expand(char ip[], char op[]);
void itoa(int32_t number, char s[]);
void itob(int32_t n, char str[], int32_t base);
void itoa_width(int32_t num, char Str[], int32_t min_width);
void strindex();
void error_checking() ;
void a_atof();
void calculator();
void RPN_calculator();
void fun_calculator();
void variable_handling();
void swap_arguments();
void recursive_reverse();
void itoa_recursive_function();
void ungets(char s[]);
void single_pushback_calculator();
void eof_handling();
void calculator_getline();
void calculator_static_getop();
int getfloat(double *pn);
int getint(int *pn);
void strcat_string();
void strend_function();
void strn_function();
void functions();
char *read_line_common();
void my_getline();
void my_atoi_func();
void my_itoa_func();
void my_reverse_func();
void my_strindex_func();
void my_getop_func();
void day_month_function();
void read_lines();
void expr(int argc, char *argv[]);
void detab_entab(int32_t argc, char *argv[]);
void tail_function(int argc, char *argv[]);
void handle_flag_RN(int32_t argc, char *argv[]);
void handle_flag_RNF(int32_t argc, char *argv[]);
void handle_flag_RNFD(int32_t argc , char *argv[]);
void alphabatical_to_group(int32_t argc, char *argv[]);
void handle_field_sort(int32_t argc, char *argv[]);
void dcl_fun();
void undcl_fun();
void handle_arg_type();
void getwords_ver();
void cross_referntial();
void decreasing_order_word_frequency();
void hash_table();
void define_processer();
void upper_lower(int argc, char *argv[]);
void print_non_graphic_character_in_hex_or_octal();
void min_printf();
void min_scanf();
void postfix_calculator_using_scanf();
#define MAXOP 100
#define NUMBER '0'

/* stack variables */
extern int sp;
extern double val[];

/* stack functions */
void push(double);
double pop(void);

/* input functions */
int getop(char []);
int getch(void);
void ungetch(int);
#define MAXLINES 5000
#define MAXLEN   1000

extern char *line_ptr[MAXLINES];

/* function declarations */
int32_t readlines_fun(char *line_ptr[], int32_t maxlines);
void writelines_fun(char *line_ptr[], int32_t nlines);
void my_qsort_fun(char *v[], int32_t left, int32_t right,
                 int32_t (*comp)(void *, void *), int32_t reverse);
int32_t strcmp_fold(char *, char *);
int32_t numcmp(char *, char *);
int32_t getline1(char *, int32_t);
char *alloc(int);
void swap_fun(char *v[], int32_t i, int32_t j);
#endif
