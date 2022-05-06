//
// Created by Tiago on 5/6/2022.
//

#include "users.h"

USER getAdmins(){
    USER users;
    return users;
}

int createDefaultAdmin(){
    USER user;
    user.id = 1;
    strcpy(user.user, "Admin");
    user.type = 1;
    strcpy(user.pass, "admin");
    FILE *fp = NULL;
    fp = fopen("db.data", "ab");
    if(fp == NULL){
        printf("Erro ao abrir ficheiro");
        return -1;
    }
    fwrite(&user, sizeof(USER), 1, fp);
    fclose(fp);
}

int checkLogin(){

}

void loginFrom(){
    char user[30], pass[30];
    printf("------- Login -------\n");
    printf("Insira o nome de utilizador:");
    scanf("%s", &user);
    printf("Insira a password:");
    scanf("%s", &pass);
    printf("%s, %s", sizeof(user), pass);
}