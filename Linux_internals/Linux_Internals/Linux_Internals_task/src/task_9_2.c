/*
Author: Nidhi Goswami
Date: 18/06/2026
Description: write another C program ProcessInfo.c that gets the following information specific to a 
process. The program takes the pid of the process as a command line argument. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"header.h"

void cmdline(char *pid)
{
    char path[100];
    char buf[1024];

    FILE *fp;


    sprintf(path,"/proc/%s/cmdline",pid);


    fp=fopen(path,"r");

    if(fp==NULL)
    {
        perror("cmdline");
        return;
    }


    fread(buf,sizeof(char),sizeof(buf),fp);


    printf("\n---- Command line ----\n");

    printf("%s\n",buf);


    fclose(fp);
}



void cpu_time(char *pid)
{
    char path[100];
    char line[1024];


    FILE *fp;


    sprintf(path,"/proc/%s/stat",pid);


    fp=fopen(path,"r");


    if(fp==NULL)
    {
        perror("stat");
        return;
    }


    fgets(line,sizeof(line),fp);


    /*
       /proc/pid/stat format:

       field 14 = user time
       field 15 = kernel time
    */


    char comm[200];
    char state;

    unsigned long user, kernel;


    sscanf(line,"%*d %s %c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu",comm,&state,&user,&kernel);



    printf("\n---- CPU Time ----\n");

    printf("User mode time   : %lu\n",user);

    printf("Kernel mode time : %lu\n",kernel);


    fclose(fp);
}

void sched_info(char *pid)
{
    char path[100];

    FILE *fp;


    sprintf(path,"/proc/%s/schedstat",pid);


    fp=fopen(path,"r");


    if(fp==NULL)
    {
        perror("schedstat");
        return;
    }


    unsigned long run, wait, slice;


    fscanf(fp,"%lu %lu %lu",&run,&wait,&slice);

    printf("\n---- Scheduling Information ----\n");

    printf("Running time : %lu\n",run);

    printf("Waiting time : %lu\n",wait);



    fclose(fp);
}

void environment(char *pid)
{
    char path[100];
    char buf[200];


    FILE *fp;


    sprintf(path,"/proc/%s/environ",pid);


    fp=fopen(path,"r");


    if(fp==NULL)
    {
        perror("environ");
        return;
    }


    printf("\n---- Environment ----\n");


    while(fread(buf,1,sizeof(buf)-1,fp))
    {
        for(int i=0;i<sizeof(buf);i++)
        {
            if(buf[i]=='\0')
                buf[i]='\n';
        }

        printf("%s",buf);
    }


    fclose(fp);
}



void address_space(char *pid)
{
    char path[100];
    char line[300];


    FILE *fp;


    sprintf(path,"/proc/%s/maps",pid);


    fp=fopen(path,"r");


    if(fp==NULL)
    {
        perror("maps");
        return;
    }


    printf("\n---- Address Space ----\n");


    while(fgets(line,sizeof(line),fp))
    {
        printf("%s",line);
    }


    fclose(fp);
}



void process_info(int argc,char *argv[])
{

    if(argc != 2)
    {
        printf("Usage: %s <pid>\n",argv[0]);
        return 1;
    }



    char *pid = argv[3];


    cmdline(pid);

    sched_info(pid);

    cpu_time(pid);

    environment(pid);

    address_space(pid);
}
