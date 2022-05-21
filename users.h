#ifndef TP_PROG1_USERS_H
#define TP_PROG1_USERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user{
    int id;
    int type; //  1 - Admin | 2 - User
    char user[50];
    char pass[50];
}USER;

typedef struct Elem_user{
    USER info;
    struct Elem_user *next;
}ELEM_USER;

void users(ELEM_USER **iniListU);
int login(ELEM_USER **iniListU, int *uid);
int readUsers(ELEM_USER **iniListU);

#endif //TP_PROG1_USERS_H