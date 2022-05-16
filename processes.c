//
// Created by Tiago on 5/6/2022.
//

#include "processes.h"

PROCESSES insertProcess(int *n_processes, int uid){
    char auxs[100];
    PROCESSES aux;
    (*n_processes)++;
    aux.pid = (*n_processes);
    fflush(stdin);
    printf("Introduza o nome do processo: ");
    gets(aux.name);
    printf("Introduza a descrição do processo: ");
    gets(aux.desc);
    printf("Urgente (Sim | Não): ");
    fflush(stdin);
    gets(auxs);
    if(strcmp(auxs, "Sim") == 0) aux.urgency = 1; else aux.urgency = 0;

    //printf("Time = %s", time(&aux.created_at));

    aux.owner = uid;

    system("pause");
    system("cls");
    return aux;
}

int insertEndListP(ELEM_PROCESS **iniListU, PROCESSES newProcess){
    ELEM_PROCESS *new = NULL, *aux=NULL;
    new = (ELEM_PROCESS *) calloc(1, sizeof(ELEM_PROCESS));
    if(new == NULL){
        printf("OUT OF MEMORY!\n");
        return -1;
    }
    new->info = newProcess;
    new->next = NULL;
    if(*iniListU == NULL) *iniListU = new;
    else{
        aux =*iniListU;
        while(aux->next != NULL) aux=aux->next;
        aux->next=new;
    }
    return 0;
}

int saveProcesses(ELEM_PROCESS *iniList){
    ELEM_PROCESS *aux = NULL;
    FILE *fp = NULL;
    fp=fopen("processes.dat", "wb");
    if(fp==NULL) return -1;
    for(aux = iniList; aux != NULL; aux=aux->next) fwrite(aux, sizeof(PROCESSES), 1, fp);
    fclose(fp);
    return 0;
}

int readProcesses(ELEM_PROCESS **iniListP){
    PROCESSES aux;
    FILE *fp = fopen("processes.dat", "rb");
    if(!fp) return -1;
    while(fread(&aux, sizeof(PROCESSES), 1,fp)) insertEndListP(iniListP,aux);
    fclose(fp);
    return 0;
}

void listProcesses(ELEM_PROCESS *iniList){
    ELEM_PROCESS *process = NULL;
    if(iniList==NULL) printf("Erro: Não existem dados de utilizadores!\n");
    else{
        for(process = iniList; process != NULL; process=process->next) {
            printf("Name: %s\n", process->info.name);
        }
    }
    system("pause");
    system("cls");
}

int getSizeP(ELEM_PROCESS *iniList){
    int size=0;
    ELEM_PROCESS *aux = NULL;
    for(aux = iniList; aux != NULL; aux= aux->next){
        size++;
    }
    return size;
}

int printMenuP(){
    system("cls");
    int op;
    printf("**********************************\n");
    printf("*****     Gerir Processos    *****\n");
    printf("**********************************\n");
    printf("1 - Adicionar Processo\n");
    printf("2 - Listar Processos\n");
    printf("0 - Voltar\n");
    printf("> ");
    scanf("%i", &op);
    system("cls");
    return op;
}

void menuProcesses(ELEM_PROCESS **iniListP,int *uid){
    int op, n_processes;
    PROCESSES newProcess;
    n_processes = getSizeP(*iniListP);
    do{
        op = printMenuP();
        switch (op) {
            case 1:
                newProcess = insertProcess(&n_processes, *uid);
                insertEndListP(iniListP, newProcess);
                saveProcesses(*iniListP);
                break;
            case 2:
                listProcesses(*iniListP);
                break;
            case 0:
                break;
            default:
                printf("Erro ao escolher opção");
                break;
        }
    }while(op != 0);
}
