/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * client_5.c
 */

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int fd;
int spid;
int running = 1;

void stop_handler(int sig) {
    running = 0;
    printf("\nTerminating server %d\n", spid);
    kill(spid, SIGTERM);
    printf("%d || %d\n", getpid(), sig);
}

void exit_message() {
    close(fd);
    printf("Process %d killed\n", getpid());
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage : %s <fifo_file>\n", argv[0]);
        return 1;
    }

    struct sigaction sig;
    sig.sa_handler = &stop_handler;
    sig.sa_flags = 0;

    sigaction(SIGINT, &sig, NULL);   
    sigaction(SIGTERM, &sig, NULL);

    atexit(exit_message);

    fd = open(argv[1], O_RDONLY);

    if (read(fd, &spid, sizeof(spid)) == -1) {
        perror("reading\n");
        exit(EXIT_FAILURE);
    }
    printf("Communicating with server %d\n", spid);

    int r[3];

    while (running) {
        if ((read(fd, &r, sizeof(r)) == -1) && running) {
            perror("reading\n");
            exit(EXIT_FAILURE);
        }
        if (r[0] == -1) {
            printf("Ended communication with %d\n", spid);
            exit(EXIT_SUCCESS);
        }
        if (running) printf("FIFO || %d | %d | %d \n", r[0], r[1], r[2]);
    }

    close(fd);
}