/*
Author: Nidhi Goswami
Date: 22-04-2026
Description : Modify the pattern finding program of Chapter 5 to take its input from a set of named files or, if no files are named as arguments, from the standard input. Should the file name be printed when a matching line is found?
*/


#include<stdio.h>
#include<stdint.h>
#include"module.h"
#include<string.h>

#define MAXLINE 1000

int32_t searchpatterninFile(FILE *fp , char *pattern , char *filename){

      char line[MAXLINE];
      int32_t line_number = 1;
      int found =0;

      while(fgets(line , MAXLINE , fp) != NULL){


          if(strstr(line , pattern) != NULL){
                printf("%s:%d:%s", filename , line_number , line);
                found++;
          }
          line_number++;


      }
      return found;

}
void pattern_finding(int32_t argc , char *argv[]){


      int32_t index , found = 0;
      if(argc == 2){
         found = searchpatterninFile(stdin ,argv[1] ,"");
      }
      else{
         for(index = 2;index < argc ;index++){
             FILE *fp = fopen(argv[index],"r");
             if(fp == NULL){
                printf("file opening error here %s\n",argv[index]);
                continue;
             }
             found += searchpatterninFile(fp ,argv[1] , argv[index]);
             fclose(fp);
         }
      }
      return found;

}
