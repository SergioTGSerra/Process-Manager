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

void menuUsers(ELEM_USER **iniListU);
void login(ELEM_USER *iniList);
int readUsers(ELEM_USER **iniListU);

#endif //TP_PROG1_USERS_H
