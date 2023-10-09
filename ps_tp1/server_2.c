/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_2.c
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

#include <stdbool.h>

volatile bool running = true;

void stop_handler(int sig) {
    printf("%d\n", sig);
    running = false;
}

int main()
{
    printf("Hello there!\n");
    srand(999);

    struct sigaction sig;   
    sig.sa_handler = &stop_handler;
    sig.sa_flags = 0;

    sigaction(SIGINT, &sig, NULL);   
    sigaction(SIGTERM, &sig, NULL); 

    while (running) {
        printf("pid : %d | ppid : %d | grp : %d\n", getpid(), getppid(), getpgrp());
        printf("%d\n", rand());
        sleep(1);
    }

    printf("Loop exited\n");
    return EXIT_SUCCESS;
}

