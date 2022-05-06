//
// Created by Tiago on 5/5/2022.
//

#include "stack.h"

int push(char stack[], int *tos, char c){
    if(*tos >= MAX){
        printf("stack overflow\n");
        return -1;
    }
    stack[*tos] = c;
    (*tos)++;
    return 0;
}

int size(int tos){
    return tos;
}

int isEmpty(int tos){
    return (tos==0);
}

char top(char stack[], int tos){
    char aux='\0';
    if(tos <= 0){
        printf("stack vazia");
    } else{
        aux=stack[tos-1];
    }
    return aux;
}

char pop(char stack[], int *tos){
    char aux="\0";
    if((*tos) <= 0){
        printf("Stack vazia");
    } else{
        aux=stack[(*tos)-1];
        (*tos)--;
    }
    return aux;
}