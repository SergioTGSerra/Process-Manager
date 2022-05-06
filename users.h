//
// Created by Tiago on 5/6/2022.
//

#ifndef TP_PROG1_USERS_H
#define TP_PROG1_USERS_H

#include <stdio.h>
#include <string.h>

typedef struct user{
    int id;
    int type; //  1 - Admin | 2 - User
    char user[50];
    char pass[50];
}USER;

void loginFrom();

#endif //TP_PROG1_USERS_H
