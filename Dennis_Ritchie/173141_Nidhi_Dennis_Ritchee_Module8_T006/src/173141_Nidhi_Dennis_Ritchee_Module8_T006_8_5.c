/*
Author: Nidhi Goswami
Date : 28-04-2026
Description : Modify the fsize program to print inode details
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<stdint.h>
#include"module.h"
#define NAME_MAX 14
#define DIRSIZ 14
#define MAX_PATH 1024

typedef struct {
    long ino;
    char name[NAME_MAX + 1];
} MY_Dirent;

typedef struct {
    int32_t fd;
    MY_Dirent d;
} MY_DIR;

struct direct {
    ino_t d_ino;
    char d_name[DIRSIZ];
};

MY_DIR *my_opendir(char *dirname);
MY_Dirent *my_readdir(MY_DIR *dfd);
void my_closedir(MY_DIR *dfd);
void dirwalk(char *dir, void (*fcn)(char *));
void fsize(char *name);

/*
Author: Nidhi Goswami
Date:28-04-2026
Description:
*/

void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }

    if (S_ISDIR(stbuf.st_mode)) {
        dirwalk(name, fsize);
    }

    printf("name: %s\n", name);
    printf("device of inode: %ld\n", stbuf.st_dev);
    printf("mode bits: %d\n" , stbuf.st_mode);
    printf("inode: %ld\n", stbuf.st_ino);
    printf("size: %ld bytes\n", stbuf.st_size);
    printf("links: %ld\n", stbuf.st_nlink);
    printf("UID: %d\n", stbuf.st_uid);
    printf("GID: %d\n", stbuf.st_gid);
    printf("last access: %ld\n", stbuf.st_atime);
    printf("last modified: %ld\n", stbuf.st_mtime);
    printf("last status change: %ld\n", stbuf.st_ctime);
}

/*
Author: Nidhi Goswami
Date: 28-04-2026
Description:
*/

void f_size(int32_t argc, char *argv[])
{
    if (argc == 1) {
        fsize(".");
    } else {
        while (--argc > 0) {
            fsize(*++argv);
        }
    }
}

/*
Author: Nidhi Goswami
Date: 28-04-2026
Description:
*/

void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[MAX_PATH];
    MY_Dirent *dp;
    MY_DIR *dfd;

    if ((dfd = my_opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }

    while ((dp = my_readdir(dfd)) != NULL) {

        if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, "..") == 0)
            continue;

        if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name)) {
            fprintf(stderr, "dirwalk: name too long %s/%s\n", dir, dp->name);
        } else {
            sprintf(name, "%s/%s", dir, dp->name);
            (*fcn)(name);
        }
    }

    my_closedir(dfd);
}

/*
Author: Nidhi Goswami
Date: 28-04-2026
Description:
*/

MY_DIR *my_opendir(char *dirname)
{
    int32_t fd;
    struct stat stbuf;
    MY_DIR *dp;

    if ((fd = open(dirname, O_RDONLY)) == -1)
        return NULL;

    if (fstat(fd, &stbuf) == -1)
        return NULL;

    if (!S_ISDIR(stbuf.st_mode))
        return NULL;

    if ((dp = (MY_DIR *)malloc(sizeof(MY_DIR))) == NULL)
        return NULL;

    dp->fd = fd;
    return dp;
}

/*
Author: Nidhi Goswami
Date: 28-04-2026
Description:
*/

void my_closedir(MY_DIR *dp)
{
    if (dp) {
        close(dp->fd);
        free(dp);
    }
}

/*
Author: Nidhi Goswami
Date:28-04-2026
Dsecription:
*/

MY_Dirent *my_readdir(MY_DIR *dp)
{
    struct direct dirbuf;
    static MY_Dirent d;

    while (read(dp->fd, (char *)&dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
        if (dirbuf.d_ino == 0)
            continue;

        d.ino = dirbuf.d_ino;
        strncpy(d.name, dirbuf.d_name, DIRSIZ);
        d.name[DIRSIZ] = '\0';

        return &d;
    }

    return NULL;
}
