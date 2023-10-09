/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_3.c
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

volatile bool running = true;
char is_parent[256];
pid_t cpid;

void stop_handler(int sig) {
    printf("%s || %d\n", is_parent, sig);
    running = false;
    if (cpid) kill(cpid, SIGTERM);
}

void exit_message() {
    printf("Process %s killed\n", is_parent);
}

int main()
{

    cpid = fork();

    strncpy(is_parent, cpid ? "child " : "parent", 256);

    printf("Hello there %s!\n", is_parent);
    srand(999);

    struct sigaction sig;   
    sig.sa_handler = &stop_handler;
    sig.sa_flags = 0;

    sigaction(SIGINT, &sig, NULL);   
    sigaction(SIGTERM, &sig, NULL); 
    sigaction(SIGCHLD, &sig, NULL);

    atexit(exit_message);

    while (running) {
        printf("%s || pid : %d | ppid : %d | grp : %d | %d\n", is_parent, getpid(), getppid(), getpgrp(), rand());
        sleep(1);
    }

    printf("Loop exited\n");
    return EXIT_SUCCESS;
}

