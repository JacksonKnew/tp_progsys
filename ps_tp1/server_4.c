/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_4.c
 */


#define _XOPEN_SOURCE 700

// for printf()
#include <stdio.h>
// For rand(), srand(), sleep(), EXIT_SUCCESS
#include <stdlib.h>
// For time()
#include <time.h>
// For getpid(), getppid()
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>

volatile bool running = true;
pid_t cpid;
int pipefd[2];

void stop_handler(int sig) {
    printf("%d || %d\n", getpid(), sig);
    running = false;
}

void exit_message() {
    close(pipefd[cpid != 0]);
    printf("Process %d killed\n", getpid());
}

int main()
{

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    int r[4];

    printf("Hello there %d\n", getpid());

    struct sigaction sig;   
    sig.sa_handler = &stop_handler;
    sig.sa_flags = 0;

    sigaction(SIGINT, &sig, NULL);   
    sigaction(SIGTERM, &sig, NULL); 
    sigaction(SIGCHLD, &sig, NULL);

    atexit(exit_message);

    if (cpid) {
        close(pipefd[0]);
        srand(666);
        while (running) {
            if (cpid) {
                r[0] = cpid;
                r[1] = getpid();
                r[2] = getpgrp();
                r[3] = rand(); 
                if (write(pipefd[1], &r, sizeof(r)) == -1) {
                    perror("writing\n");
                    exit(EXIT_FAILURE);
                }
            }
            sleep(1);
        }
    } else {
        close(pipefd[1]);
        int status;
        while ((status = read(pipefd[0], &r, sizeof(r))) > 0 && running) {
            if (status == -1) {
                perror("reading\n");
                exit(EXIT_FAILURE);
            } 
            printf("child || pid : %d | ppid : %d | grp : %d | %d\n", r[0], r[1], r[2], r[3]);
            sleep(1);
        }
    }

    printf("Loop exited %d\n", getpid());
    return EXIT_SUCCESS;
}

