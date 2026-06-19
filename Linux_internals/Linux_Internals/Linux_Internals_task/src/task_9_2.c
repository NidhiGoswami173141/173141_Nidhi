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
#include <unistd.h>


void command_line(char *pid)
{
    char path[100];
    char buffer[4096];


    sprintf(path,"/proc/%s/cmdline",pid);


    FILE *fp=fopen(path,"r");


    if(fp==NULL)
    {
        perror("cmdline");
        return;
    }


    int n=fread(buffer,1,sizeof(buffer)-1,fp);

    buffer[n]='\0';


    printf("\n===== COMMAND LINE =====\n");


    /*
       cmdline separates arguments by NULL,
       replace NULL by space
    */

    for(int i=0;i<n;i++)
    {
        if(buffer[i]=='\0')
            printf(" ");
        else
            printf("%c",buffer[i]);
    }


    printf("\n");


    fclose(fp);
}





void process_stat(char *pid)
{

    char path[100];
    char buffer[4096];


    sprintf(path,"/proc/%s/stat",pid);


    FILE *fp=fopen(path,"r");


    if(fp==NULL)
    {
        perror("stat");
        return;
    }


    fgets(buffer,sizeof(buffer),fp);


    fclose(fp);



    char comm[200];
    char state;


    unsigned long utime;
    unsigned long stime;

    long priority;
    unsigned long vsize;


    /*
    /proc/pid/stat format:

    pid
    comm
    state
    ...
    utime
    stime
    ...
    */

    sscanf(buffer, "%*d %s %c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu",comm,&state,&utime,&stime);

    printf("\n===== PROCESS TIME =====\n");


    printf("Process state : %c\n",state);


    printf("User mode time   : %lu ticks\n",utime);

    printf("Kernel mode time : %lu ticks\n",stime);



    printf("\nRunning time + Waiting time information\n");


    char sched[100];

    sprintf(sched,"/proc/%s/schedstat",pid);


    fp=fopen(sched,"r");


    if(fp)
    {
        unsigned long run,wait;


        fscanf(fp,"%lu %lu",&run,&wait);


        printf("Running time : %lu ns\n",run);

        printf("Waiting time : %lu ns\n",wait);


        fclose(fp);
    }


}


void environment(char *pid)
{

    char path[100];

    char buffer[4096];


    sprintf(path,"/proc/%s/environ",pid);


    FILE *fp=fopen(path,"r");


    if(fp==NULL)
    {
        perror("environ");
        return;
    }


    printf("\n===== ENVIRONMENT =====\n");


    int n;


    while((n=fread(buffer,1,sizeof(buffer),fp))>0)
    {

        for(int i=0;i<n;i++)
        {
            if(buffer[i]=='\0')
                printf("\n");
            else
                printf("%c",buffer[i]);
        }

    }


    fclose(fp);

}

void address_space(char *pid)
{

    char path[100];

    char line[512];


    sprintf(path,"/proc/%s/maps",pid);



    FILE *fp=fopen(path,"r");


    if(fp==NULL)
    {
        perror("maps");
        return;
    }



    printf("\n===== ADDRESS SPACE =====\n");


    while(fgets(line,sizeof(line),fp))
    {
        printf("%s",line);
    }


    fclose(fp);

}


void process_info()
{
    char pid[20];
    int choice;


    printf("Enter PID: ");
    scanf("%s", pid);



    printf("\n===== PROCESS INFORMATION MENU =====\n");

    printf("1. Command Line\n");
    printf("2. Process Time (stat + schedstat)\n");
    printf("3. Environment\n");
    printf("4. Address Space (maps)\n");
    printf("5. All Information\n");
    printf("0. Exit\n");


    printf("\nEnter choice: ");
    scanf("%d",&choice);



    switch(choice)
    {

        case 1:

            command_line(pid);

            break;



        case 2:

            process_stat(pid);

            break;



        case 3:

            environment(pid);

            break;



        case 4:

            address_space(pid);

            break;



        case 5:

            command_line(pid);

            process_stat(pid);

            environment(pid);

            address_space(pid);

            break;



        case 0:

            printf("Exit\n");

            break;



        default:

            printf("Invalid choice\n");

    }

}
