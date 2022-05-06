//
// Created by Tiago on 5/6/2022.
//

#ifndef TP_PROG1_PROCESSES_H
#define TP_PROG1_PROCESSES_H

#include <time.h>

typedef struct processes{
    int pid;
    int urgency; // 1 - urgent | 0 - normal
    int owner;
    struct tm created_at;
    struct tm executed_at;
}PROCESSES;

#endif //TP_PROG1_PROCESSES_H
