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
    char line[200];
    int count=0, cores=0;

    fp=fopen("/proc/cpuinfo","r");

    if(fp==NULL)
    {
        perror("cpuinfo");
        return;
    }

    printf("\nCPU information\n");

    while(fgets(line,sizeof(line),fp))
    {
        if(strstr(line,"processor"));
            count++;

        if(strstr(line,"cpu cores"));
            sscanf(line,"cpu cores : %d",&cores);

        if(strstr(line,"cpu MHz"))
            printf("%s",line);
    }

    printf("CPUs : %d\n",count);
    printf("Cores : %d\n",cores);

    fclose(fp);
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
    double uptime;

    fp = fopen("/proc/uptime","r");

    if(fp == NULL)
    {
        perror("uptime");
        return;
    }


    fscanf(fp,"%lf",&uptime);

    fclose(fp);


    long seconds = (long)uptime;


    printf("\nSystem running time\n");

    printf("%ld days %ld hours %ld minutes %ld seconds\n",seconds/86400,(seconds%86400)/3600,(seconds%3600)/60,seconds%60);
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
        if(strstr(line,"MemTotal"))
            sscanf(line,"MemTotal: %ld",&total);


        if(strstr(line,"MemAvailable"))
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
        if(strstr(line,"SwapTotal"))
            sscanf(line,"SwapTotal: %ld",&total);

        if(strstr(line,"SwapFree"))
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

    unsigned long user,system,nice;


    fp=fopen("/proc/stat","r");


    fgets(line,sizeof(line),fp);

    sscanf(line , "cpu %lu %lu %lu", &user , &nice , &system);

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
    char line[300];

    long total=0;
    long value;


    fp=fopen("/proc/interrupts","r");

    if(fp==NULL)
    {
        perror("interrupts");
        return;
    }


    while(fgets(line,sizeof(line),fp))
    {
        char *p=line;


        while(*p)
        {
            if(sscanf(p,"%ld",&value)==1)
            {
                total += value;
                break;
            }

            p++;
        }
    }


    fclose(fp);


    printf("\nInterrupts handled\n");
    printf("Total interrupts : %ld\n",total);
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
