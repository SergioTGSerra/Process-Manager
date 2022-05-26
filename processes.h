#ifndef TP_PROG1_PROCESSES_H
#define TP_PROG1_PROCESSES_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct process{
    int pid;
    char name[50];
    char desc[250];
    int type; // 1 - urgent | 0 - normal | -1 recused | 2 - processed
    int owner;
    struct tm *created_at;
    struct tm *executed_at;
}PROCESS;

/**
 * @desc Processes
 */

typedef struct Elem_process{
    PROCESS info;
    struct Elem_process *next;
    struct Elem_process *previous;
}ELEM_PROCESS;

void processes(int uid, int isadmin);

#endif //TP_PROG1_PROCESSES_H
