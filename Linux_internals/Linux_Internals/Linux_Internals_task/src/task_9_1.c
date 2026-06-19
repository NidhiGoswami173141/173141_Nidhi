/*
Author:Nidhi Goswami
Date:18/06/2026
Description:SystemInfo.c Read information from /proc filesystem
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include"header.h"

void cpu()
{
    FILE *fp;
    char line[256];

    int cpus = 0;
    int cores = 0;
    double mhz = 0;


    fp = fopen("/proc/cpuinfo", "r");

    if(fp == NULL)
    {
        perror("cpuinfo");
        return;
    }


    while(fgets(line, sizeof(line), fp))
    {

        if(strncmp(line,"processor",9)==0)
            cpus++;


        if(strncmp(line,"cpu MHz",7)==0)
        {
            sscanf(line,"cpu MHz : %lf",&mhz);
        }


        if(strncmp(line,"cpu cores",9)==0)
        {
            sscanf(line,"cpu cores : %d",&cores);
        }

    }


    fclose(fp);


    printf("\nCPU INFORMATION\n");

    printf("Number of CPUs : %d\n",cpus);

    printf("Clock Speed    : %.2lf MHz\n",mhz);

    printf("Number of cores: %d\n",cores);

}

void kernel()
{
    FILE *fp;
    char line[200];

    fp=fopen("/proc/version","r");

    printf("\nkernel version\n");

    fgets(line,sizeof(line),fp);

    printf("%s",line);

    fclose(fp);
}


void boot()
{
    FILE *fp;
    char line[256];

    long boot=0;


    fp=fopen("/proc/stat","r");


    while(fgets(line,sizeof(line),fp))
    {
        if(strncmp(line,"btime",5)==0)
        {
            sscanf(line,"btime %ld",&boot);
            break;
        }
    }


    fclose(fp);



    time_t t=boot;


    printf("\nBOOT TIME\n");

    printf("System booted at : %s",ctime(&t));

}

void load()
{
    FILE *fp;
    float a,b,c;

    fp=fopen("/proc/loadavg","r");


    fscanf(fp,"%f %f %f",&a,&b,&c);


    printf("\n15 minute load : %.2f\n",c);


    fclose(fp);
}



void memory()
{
    FILE *fp;
    char line[200];

    long total=0,free=0;


    fp=fopen("/proc/meminfo","r");


    while(fgets(line,sizeof(line),fp))
    {
        if(strncmp(line,"MemTotal",8)==0)
            sscanf(line,"MemTotal: %ld",&total);


        if(strncmp(line,"MemAvailable",12)==0)
            sscanf(line,"MemAvailable: %ld",&free);
    }


    printf("\nMemory\n");

    printf("Total : %ld KB\n",total);
    printf("Free  : %ld KB\n",free);


    fclose(fp);
}



void swap()
{
    FILE *fp;
    char line[200];

    long total=0,free=0;


    fp=fopen("/proc/meminfo","r");


    while(fgets(line,sizeof(line),fp))
    {
        if(strncmp(line,"SwapTotal",9)==0)
            sscanf(line,"SwapTotal: %ld",&total);

        if(strncmp(line,"SwapFree",8)==0)
            sscanf(line,"SwapFree: %ld",&free);
    }


    fclose(fp);


    printf("\nSwap\n");

    printf("Total : %ld KB\n",total);

    printf("Used : %ld KB\n",total-free);



    fp=fopen("/proc/swaps","r");

    printf("\nswap partitions:\n");


    while(fgets(line,sizeof(line),fp))
    {
        if(line[0]=='/')
            printf("%s",line);
    }


    fclose(fp);
}



void cpu_time()
{
    FILE *fp;
    char line[200];

    unsigned long user,system;


    fp=fopen("/proc/stat","r");


    fgets(line,sizeof(line),fp);

    sscanf(line , "cpu %lu %lu", &user ,&system);

    printf("\nCPU time\n");

    printf("user mode : %lu\n",user);

    printf("kernel mode : %lu\n",system);


    fclose(fp);
}



void context()
{
    FILE *fp;
    char line[200];


    fp=fopen("/proc/stat","r");


    while(fgets(line,sizeof(line),fp))
    {
        if(strncmp(line,"ctxt",4)==0)
        {
            printf("\ncontext switches\n");
            printf("%s",line);
            break;
        }
    }


    fclose(fp);
}

void interrupt()
{
    FILE *fp;
    char line[200];

    int total=0;


    fp=fopen("/proc/interrupts","r");


    while(fgets(line,sizeof(line),fp))
    {
        total++;
    }


    printf("\nInterrupts handled : %d lines\n",total);


    fclose(fp);
}

void cpu_info()
{

    int ch;
        printf("1 CPU\n");
        printf("2 Kernel\n");
        printf("3 Boot time\n");
        printf("4 Load\n");
        printf("5 Memory\n");
        printf("6 Swap\n");
        printf("7 CPU time\n");
        printf("8 Context switch\n");
        printf("9 Interrupts\n");
        printf("10 All\n");

    printf("enter your choice \n");
    scanf("%d",&ch);


    switch(ch)
    {

        case 1:
            cpu();
            break;

        case 2:
            kernel();
            break;

        case 3:
            boot();
            break;

        case 4:
            load();
            break;

        case 5:
            memory();
            break;

        case 6:
            swap();
            break;

        case 7:
            cpu_time();
            break;

        case 8:
            context();
            break;

        case 9:
            interrupt();
            break;


        case 10:

            cpu();
            kernel();
            boot();
            load();
            memory();
            swap();
            cpu_time();
            context();
            interrupt();

            break;


        default:

            printf("Wrong option\n");
    }
}
