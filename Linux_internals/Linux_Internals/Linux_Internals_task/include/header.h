#ifndef HEADER_H
#define HEADER_H
void question_choice(int argc,char *argv[]);
//typedef void (*task_func)(int argc, char *argv[]);
void select_function(int argc, char *argv[]);
void sparse_file();
void copy_file(int argc,char *argv[]);
void display_dir_content(int argc,char *argv[]);
void ex_5_2(void);
void add_flag();
void simpcat1();
void check_file_descriptor();
void simpcat2();
void simpcat3();
void simpcat4(int argc, char **argv);
void cat_using_stdio(int argc, char *argv[]);
void cat_using_systemcall(int argc, char *argv[]);
int getchar_fun(void);
void ls_command_using_stat();
void ls_command_f();
void cal_size_of_all();
void cal_size_of_all_file_folder(int argc, char *argv[]);
void cpu_info();
#endif
