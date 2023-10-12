/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_5.c
 */
#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int fd;
int pid;
int running = 1;

void stop_handler(int sig) {
    printf("\nSending end of communication message\n");
    int end_msg[3] = {-1, -1, -1};
    write(fd, end_msg, sizeof(end_msg));
    close(fd);
    printf("%d || %d\n", getpid(), sig);
    running = 0;
}

void exit_message() {
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

    fd = open(argv[1], O_WRONLY);

    pid = getpid();
    printf("Started server %d\n", pid);

    if (write(fd, &pid, sizeof(pid)) == -1) {
        perror("writing ");
        exit(EXIT_FAILURE);
    }
    sleep(1);

    int r[3];

    while (running) {
        r[0] = pid;
        r[1] = getpgrp();
        r[2] = rand(); 
        if (write(fd, &r, sizeof(r)) == -1) {
            perror("writing\n");
            exit(EXIT_FAILURE);
        }
        sleep(1);
    }

    close(fd);
}