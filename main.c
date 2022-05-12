#include <stdio.h>
#include <windows.h>
#include "users.h"

void menuAdmin(ELEM_USER **iniListU){
    int op;
    do {
        system("cls");
        printf("**************************\n");
        printf("*****   Menu Admin   *****\n");
        printf("**************************\n");
        printf("\n\t 1 - Menu Processos\n");
        printf("\n\t 2 - Menu Users\n");
        printf("\n\t 0 - Sair\n");
        printf("> "); scanf("%i", &op);
        switch (op) {
            case 1:
                //menuProcessos
                break;
            case 2:
                menuUsers(iniListU);
                break;
            case 0:
                break;
            default:
                printf("Erro ao escolher opção!\n");
                break;
        }
    } while (op != 0);
    system("cls");
}


int main() {
    SetConsoleOutputCP(CP_UTF8);

    printf("░█▀█░█▀▄░█▀█░█▀▀░█▀▀░█▀▀░█▀▀░█▀▀░█▀▀░░░█▄█░█▀█░█▀█░█▀█░█▀▀░█▀▀░█▄█░█▀▀░█▀█░▀█▀\n"
           "░█▀▀░█▀▄░█░█░█░░░█▀▀░▀▀█░▀▀█░█▀▀░▀▀█░░░█░█░█▀█░█░█░█▀█░█░█░█▀▀░█░█░█▀▀░█░█░░█░\n"
           "░▀░░░▀░▀░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀▀▀░░░▀░▀░▀░▀░▀░▀░▀░▀░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀░▀░░▀░\n");
    printf("░█▀▄░█░█░░░█▀▀░█▀▀░█▀▄░█▀▀░▀█▀░█▀█░░░█▀▀░█▀▀░█▀▄░█▀▄░█▀█\n"
           "░█▀▄░░█░░░░▀▀█░█▀▀░█▀▄░█░█░░█░░█░█░░░▀▀█░█▀▀░█▀▄░█▀▄░█▀█\n"
           "░▀▀░░░▀░░░░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░▀▀▀░░░▀▀▀░▀▀▀░▀░▀░▀░▀░▀░▀\n");
    system("pause");
    system("cls");

    int uid; //User ID

    //Lists Users
    ELEM_USER *iniListU=NULL;
    readUsers(&iniListU);

    do{
        fflush(stdin);
        if(login(&iniListU, &uid) == 1){
            menuAdmin(&iniListU);
        }else{
            //Menu Processos (Para User)
        }
    } while (1);

    return 0;
}