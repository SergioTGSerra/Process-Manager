//
// Created by Tiago on 5/6/2022.
//

#ifndef TP_PROG1_PROCESSES_H
#define TP_PROG1_PROCESSES_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct processes{
    int pid;
    char name[50];
    char desc[250];
    int urgency; // 1 - urgent | 0 - normal
    int owner;
    struct tm created_at;
    struct tm executed_at;
}PROCESSES;

typedef struct Elem_process{
    PROCESSES info;
    struct Elem_process *next;
}ELEM_PROCESS;

void menuProcesses(ELEM_PROCESS **iniListP, int *uid);
int readProcesses(ELEM_PROCESS **iniListP);


#endif //TP_PROG1_PROCESSES_H
