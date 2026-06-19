/* server.c
Author      : Nidhi Goswami
Date        : 15-04-2026
Description : Server process for IPC Chat Application.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#define SERVER_FIFO "server_pipe"
#define BUFFER_SIZE 1024
#define PORT 5000
#define MAX_CLIENTS 100
#define LISTEN_BACKLOG 5

//int lock_fd;

typedef struct {
    char username[2024];
    char message[2024];
    char target[50];
    int type;
} Packet;

typedef struct Client {
    char username[50];
    int socket_fd;
    //pid_t pid;
    //char fifo_name[100];
    struct Client *next;
} Client;

Client *client_head = NULL;
int server_socket = -1;/* initially no socket is exist so initalize with 1 */

/* this function is for making socket blockig mode to non blocking mode */
void make_non_blocking(int sockfd){
   int flags = fcntl(sockfd, F_GETFL , 0);
   fcntl(sockfd, F_SETFL , flags | O_NONBLOCK);
}

//void add_client(char *username, pid_t pid, char *fifo)
void add_client(int client_socket, const char *username)
{

    Client *temp = client_head;
    while (temp != NULL) {
       /* if (temp->pid == pid || strcmp(temp->username, username) == 0) {
            printf("Client already exists: %s\n", username);
            return;
        }*/
        if(strcmp(temp -> username,username)==0){
           printf("client already exists: %s\n",username);
           close(client_socket);
           return;
        }
        temp = temp->next;
    }

    Client *new_client = (Client*)malloc(sizeof(Client));
    new_client->socket_fd = client_socket;
    strcpy(new_client->username, username);
    //new_client->pid = pid;
    //strcpy(new_client->fifo_name, fifo);
    new_client->next = client_head;
    client_head = new_client;

    //printf("Client Registered: %s | PID: %d | FIFO: %s\n", username, pid, fifo);
    printf("client connected : %s | socket FD: %d\n",username,client_socket);

    FILE *fp = fopen("chat_history.txt", "r");
    if (fp != NULL) {
        char line[300];
        Packet history_pkt = {0};
        strcpy(history_pkt.username, "HISTORY");

        while (fgets(line, sizeof(line), fp)) {
            strcpy(history_pkt.message, line);
            strcpy(history_pkt.target, username);
            history_pkt.type = 1;
            /*Client *t = client_head;
              while (t != NULL) {
                if (strcmp(t->username, username) == 0) {
                    int fd = open(t->fifo_name, O_WRONLY | O_NONBLOCK);
                    if (fd >= 0) {
                        write(fd, &history_pkt, sizeof(Packet));
                        close(fd);
                    }
                    break;
                }
                t = t->next;
            }*/
          if(send(client_socket, &history_pkt,sizeof(Packet),0)<0){
              perror("send history");
          }
        }
        fclose(fp);
    }
}

void remove_client(/*char *username*/int client_socket)
{
    Client *temp = client_head;
    Client *prev = NULL;

    while (temp != NULL) {
       // if (strcmp(temp->username, username) == 0) {
          if(temp -> socket_fd == client_socket){
            if (prev == NULL){
                client_head = temp->next;
            }
            else{
                prev->next = temp->next;
            }

           // free(temp);
           // printf("Client removed: %s\n", username);
           printf("client removed: %s\n",temp->username);
           free(temp);
           return;
        }
        prev = temp;
        temp = temp->next;
    }
}

Client *find_client_by_username(const char *username){
    Client *temp = client_head;
    while (temp != NULL) {
        if (strcmp(temp->username, /*pkt->target*/username)==0){
            //int fd = open(temp->fifo_name, O_WRONLY | O_N>
            /*if (fd >= 0) {
                write(fd, pkt, sizeof(Packet));
                close(fd);
            }*/
            return temp;
        }
        temp = temp->next;
    }
   return NULL;
}

//void send_to_client(Packet *pkt)
void send_to_client(const char *target_username, Packet *pkt)
{
   Client *target = find_client_by_username(target_username);
   if(target != NULL){
     if(send(target->socket_fd, pkt , sizeof(Packet),0)<0){
        perror("send to client");
     }
   }
   else
   {
       printf("user not found: %s\n", target_username);
   }
}

void broadcast_message(Packet *pkt)
{
    FILE *fp = fopen("chat_history.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%s: %s\n", pkt->username, pkt->message);
        fclose(fp);
    }

    Client *temp = client_head;
    while (temp != NULL) {
        //int fd = open(temp->fifo_name, O_WRONLY | O_NONBLOCK);
        /*if (fd >= 0) {
            write(fd, pkt, sizeof(Packet));
            close(fd);
        }*/
        if(send(temp->socket_fd,pkt,sizeof(Packet),0)<0){
           perror("broadcast send");
        }
        temp = temp->next;
    }
}

void handle_server_exit(int sig)
{
    printf("\n[SERVER]: Shutting down...\n");

    Packet pkt = {0};
    strcpy(pkt.username, "SYSTEM");
    strcpy(pkt.message, "Server is shutting down. Please reconnect later.");
    strcpy(pkt.target, "ALL");
    pkt.type = 1;

    Client *temp = client_head;
    while (temp != NULL) {
       // int fd = open(temp->fifo_name, O_WRONLY | O_NONBLOCK);
        send(temp -> socket_fd , &pkt , sizeof(pkt),0);
        /*if (fd >= 0) {
            write(fd, &pkt, sizeof(pkt));
            close(fd);
        }*/
        close(temp-> socket_fd);
        temp = temp->next;
    }
    if(server_socket >= 0){
       close(server_socket);
    }
    //close(lock_fd);
    //unlink("server.lock");
    //unlink(SERVER_FIFO);
    exit(0);
}

/*int main() {
  //  signal(SIGINT, handle_server_exit);

    lock_fd = open("server.lock", O_CREAT | O_RDWR, 0666);
    if (lock_fd < 0) {
        perror("Lock file open failed");
        exit(1);
    }

    struct flock lock = {0};
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    if (fcntl(lock_fd, F_SETLK, &lock) == -1) {
        printf("Server already running!\n");
        close(lock_fd);
        exit(1);
    }

    if (mkfifo(SERVER_FIFO, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
    }

    printf("Server started. Waiting for clients...\n");

    int fd = open(SERVER_FIFO, O_RDWR);
    if (fd < 0) {
        perror("Failed to open server FIFO");
        return 1;
    }

    Packet pkt;
    while (1) {
        ssize_t bytes = read(fd, &pkt, sizeof(pkt));

        if (bytes == 0) {
            close(fd);
            fd = open(SERVER_FIFO, O_RDWR);
            continue;
        }
        if (bytes != sizeof(pkt)) {
            continue;
        }

        if (pkt.type == 0) {
            char fifo[100];
            pid_t pid;
            sscanf(pkt.message, "%d %s", &pid, fifo);
            add_client(pkt.username, pid, fifo);
        }
        else if (pkt.type == 1) {
            if (strcmp(pkt.target, "ALL") != 0 && strlen(pkt.target) > 0) {
                send_to_client(&pkt);
            } else {
                strcpy(pkt.target, "ALL");
                broadcast_message(&pkt);
            }
        }
        else if (pkt.type == 2) {
            remove_client(pkt.username);

            Packet sys_pkt = {0};
            strcpy(sys_pkt.username, "SYSTEM");
            sprintf(sys_pkt.message, "%s left the chat", pkt.username);
            strcpy(sys_pkt.target, "ALL");
            sys_pkt.type = 1;

            broadcast_message(&sys_pkt);
        }
    }

    return 0;
}
*/

int main() {
    signal(SIGINT, handle_server_exit);

    /* Create server socket */
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        exit(1);
    }

    /* Allow reusing address */
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(1);
    }

    /* Bind socket to port */
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(1);
    }

    /* Listen for connections */
    if (listen(server_socket, LISTEN_BACKLOG) < 0) {
        perror("listen");
        exit(1);
    }

    printf("Server started on localhost:%d. Waiting for clients...\n", PORT);
    /* Main server loop */
    while (1) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(server_socket, &readfds);

        int max_fd = server_socket;
        Client *temp = client_head;
        while (temp != NULL) {
            FD_SET(temp->socket_fd, &readfds);
            if (temp->socket_fd > max_fd) {
                max_fd = temp->socket_fd;
            }
            temp = temp->next;
        }

        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        int activity = select(max_fd + 1, &readfds, NULL, NULL, &timeout);

        if (activity < 0) {
            perror("select");
            break;
        }

        /* Check for new client connections */
        if (FD_ISSET(server_socket, &readfds)) {
            struct sockaddr_in client_addr = {0};
            socklen_t addr_len = sizeof(client_addr);
            int client_socket = accept(server_socket,(struct sockaddr *)&client_addr, &addr_len);
            if (client_socket >= 0) {
                Packet pkt = {0};
                if (recv(client_socket, &pkt, sizeof(Packet), 0) > 0) {
                    add_client(client_socket, pkt.username);
                    Packet join_msg = {0};
                    strcpy(join_msg.username, "SYSTEM");
                    sprintf(join_msg.message, "%s joined the chat", pkt.username);
                    strcpy(join_msg.target, "ALL");
                    join_msg.type = 1;
                    broadcast_message(&join_msg);
                }
            }
        }

        /* Check for messages from clients */
        temp = client_head;
        Client *prev = NULL;
        while (temp != NULL) {
            Client *next = temp->next;
            if (FD_ISSET(temp->socket_fd, &readfds)) {
                Packet pkt = {0};
                ssize_t bytes = recv(temp->socket_fd, &pkt, sizeof(Packet), 0);

                if (bytes <= 0) {
                    /* Client disconnected */

                    printf("client removed : %s | socket FD : %d\n",temp->username,temp->socket_fd);

                    int disc_socket = temp->socket_fd;
                    close(disc_socket);

                    char username[50];
                    strcpy(username, temp->username);

                    if (prev == NULL){
                       client_head = temp->next;
                    }
                    else{
                       prev->next = temp->next;
                    }

                    free(temp);

                    Packet leave_msg = {0};
                    strcpy(leave_msg.username, "SYSTEM");
                    sprintf(leave_msg.message, "%s left the chat", username);
                    strcpy(leave_msg.target, "ALL");
                    leave_msg.type = 1;

                    broadcast_message(&leave_msg);

                    temp = next;
                    continue;
                }

                /* Handle message types */
                if (pkt.type == 1) {
                    if (strcmp(pkt.target, "ALL") != 0 && strlen(pkt.target) > 0) {
                        /* Direct message */
                        send_to_client(pkt.target, &pkt);
                    } else {
                        /* Broadcast */
                        strcpy(pkt.target, "ALL");
                        broadcast_message(&pkt);
                    }
                }
            }
            prev = temp;
            temp = next;
        }
    }

    close(server_socket);
    return 0;
}
