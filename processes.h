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
    int urgency; // 1 - urgent | 0 - normal
    int owner;
    struct tm *created_at;
    struct tm *executed_at;
}PROCESS;

/**
 * @desc Processed processes
 */

typedef struct Elem_process{
    PROCESS info;
    struct Elem_process *next;
    struct Elem_process *previous;
}ELEM_PROCESS;

/**
 * @desc Queue Urgency
 */
typedef struct Elem_processU{
    PROCESS info;
    struct Elem_process *next;
    struct Elem_process *previous;
}ELEM_PROCESSU;

/**
 * @desc Queue Normal
 */

typedef struct Elem_processN{
    PROCESS info;
    struct Elem_process *next;
    struct Elem_process *previous;
}ELEM_PROCESSN;

void processes(ELEM_PROCESS **iniListP, ELEM_PROCESS **endListP, int uid, int isadmin);
int readProcesses(ELEM_PROCESS **iniListP, ELEM_PROCESS **endListP);

#endif //TP_PROG1_PROCESSES_H
