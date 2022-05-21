#include <stdio.h>
#include <windows.h>
#include "users.h"
#include "processes.h"

void menuAdmin(ELEM_USER **iniListU, ELEM_PROCESS **iniListP, ELEM_PROCESS **endListP, int uid){
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
                processes(iniListP, endListP, uid);
                break;
            case 2:
                users(iniListU);
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

    int uid; //User ID
    do{
        int isadmin = login(&iniListU, &uid); // 1 = Admin | 0 = User
        if(isadmin == 1){
            menuAdmin(&iniListU, &iniListP, &endListP, uid);
        }else{
            processes(&iniListP, &endListP, uid);
        }
    }while(1);
}