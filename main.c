#include <stdio.h>
#include <windows.h>
#include "users.h"
#include "processes.h"

void menuAdmin(ELEM_USER **iniListU, ELEM_PROCESS **iniListP, ELEM_PROCESS **endListP, int uid, int isadmin){
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
                processes(iniListP, endListP, uid, isadmin);
                break;
            case 2:
                users(iniListU);
                break;
            case 0:
                break;
            default:
                printf("Erro ao escolher opção!\n");
                system("pause");
                break;
        }
    } while (op != 0);
    system("cls");
}

void hello(){
    printf("\n"
           "░█▀█░█▀▄░█▀█░█▀▀░█▀▀░█▀▀░█▀▀░█▀▀░█▀▀░░░█▄█░█▀█░█▀█░█▀█░█▀▀░█▀▀░█▄█░█▀▀░█▀█░▀█▀\n"
           "░█▀▀░█▀▄░█░█░█░░░█▀▀░▀▀█░▀▀█░█▀▀░▀▀█░░░█░█░█▀█░█░█░█▀█░█░█░█▀▀░█░█░█▀▀░█░█░░█░\n"
           "░▀░░░▀░▀░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀▀▀░░░▀░▀░▀░▀░▀░▀░▀░▀░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀░▀░░▀░\n"
           "░█▀▄░█░█░░░█▀▀░█▀▀░█▀▄░█▀▀░▀█▀░█▀█░░░█▀▀░█▀▀░█▀▄░█▀▄░█▀█\n"
           "░█▀▄░░█░░░░▀▀█░█▀▀░█▀▄░█░█░░█░░█░█░░░▀▀█░█▀▀░█▀▄░█▀▄░█▀█\n"
           "░▀▀░░░▀░░░░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░▀▀▀░░░▀▀▀░▀▀▀░▀░▀░▀░▀░▀░▀\n\n");
    system("pause");
    system("cls");
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    hello();

    //List Users
    ELEM_USER *iniListU=NULL; readUsers(&iniListU);

    //List Processes
    ELEM_PROCESS *iniListP=NULL, *endListP=NULL; readProcesses(&iniListP, &endListP);
    ELEM_PROCESS *iniListPU=NULL, *endListPU=NULL; readProcesses(&iniListPU, &endListPU);
    ELEM_PROCESS *iniListPN=NULL, *endListPN=NULL; readProcesses(&iniListPN, &endListPN);

    int uid, isadmin; //User ID
    while(TRUE){
        isadmin = login(&iniListU, &uid); // 1 = Admin | 0 = User
        if(isadmin == 1){
            menuAdmin(&iniListU, &iniListP, &endListP, uid, isadmin);
        }else{
            processes(&iniListP, &endListP, uid, isadmin);
        }
    }
}