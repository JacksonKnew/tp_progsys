/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_1.c
 */

// for printf()
#include <stdio.h>
// For rand(), srand(), sleep(), EXIT_SUCCESS
#include <stdlib.h>
// For time()
#include <time.h>
// For getpid(), getppid()
#include <unistd.h>

int main()
{
    printf("Hello there!\n");
    srand(999);
    while (1) {
        printf("pid : %d | ppid : %d | grp : %d\n", getpid(), getppid(), getpgrp());
        printf("%d\n", rand());
        sleep(1);
    }
    printf("Loop exited\n");
    return EXIT_SUCCESS;
}

