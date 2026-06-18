#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/file.h>

#define LOG_FILE "/home/nidhi/logfile"

void write_to_file_log(void)
{
    char *username;
    time_t t;
    int fd;
    char buffer[256];

    username = getenv("USER");

    if (username == NULL)
    {
        username = "unknown";
    }

    t = time(NULL);

    fd = open(LOG_FILE,
              O_WRONLY | O_CREAT | O_APPEND | O_SYNC,
              0644);

    if (fd == -1)
    {
        perror("open");
        return;
    }

    /* Acquire exclusive lock */
    if (flock(fd, LOCK_EX) == -1)
    {
        perror("flock");
        close(fd);
        return;
    }

    snprintf(buffer,
             sizeof(buffer),
             "%s %ld\n",
             username,
             (long)t);

    if (write(fd, buffer, strlen(buffer)) == -1)
    {
        perror("write");
    }

    /* Release lock */
    if (flock(fd, LOCK_UN) == -1)
    {
        perror("flock unlock");
    }

    close(fd);
}

int main(void)
{
    write_to_file_log();

    printf("Log entry written\n");

    return 0;
}
