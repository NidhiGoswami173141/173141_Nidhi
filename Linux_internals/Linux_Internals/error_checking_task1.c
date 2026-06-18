#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define LOG_FILE "/home/nidhi/logfile"

void write_to_file_log()
{
    char *username;
    long t;
    int fd;
    char buffer[100];

    username = getenv("USER");
    t = time(NULL);

    fd = open(LOG_FILE,O_WRONLY | O_CREAT | O_APPEND | O_SYNC,0644);

    if(fd == -1)
    {
        perror("open");
        return;
    }

    snprintf(buffer,sizeof(buffer),"%s %ld\n",username,t);

    write(fd, buffer,strlen(buffer));

    close(fd);
}

int main(void)
{
    write_to_file_log();

    printf("Log entry written successfully.\n");

    return 0;
}
