/*
Author: Nidhi Goswami
Date: 11/06/2026
Description: 
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"header.h"
void check_file_descriptor(void)
{
    int i, r, w;
    char msg[12];
    char buf[2] = {0, 0};

    for (i = 0; i < 3; i ++) {
      if ((r = read(i,buf,1))<0) {
         sprintf(msg,"read  f%d:%s",i,buf);
         perror(msg);
      }
      if ((w = write(i,buf,1))<0) {
         sprintf(msg,"write f%d:%s",i,buf);
         perror(msg);
      }
      fprintf(stderr,"%d, r = %d, w = %d, char = %d\n",i,r,w,(int)(buf[0]));
    }

}
