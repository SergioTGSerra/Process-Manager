//
// Created by Tiago on 5/6/2022.
//

#include "processes.h"

int getsizeP(ELEM_PROCESS *iniListP){
    int size = 0;
    ELEM_PROCESS *aux = NULL;
    for (aux = iniListP; aux != NULL; aux=aux->next) size++;
    return size;
}

PROCESS frontEndProcesses(int *n_processes, int uid){
    time_t rawtime;
    time( &rawtime );
    PROCESS aux;
    char auxs[10];
    aux.pid = (*n_processes)++;
    printf("Intruza o nome do processo: ");
    scanf("%s", &aux.name);
    printf("Intruza a descrição do processo: ");
    scanf("%s", &aux.desc);
    printf("Urgente? (Sim | Não): ");
    scanf("%s", &auxs);
    if(strcmp(auxs, "Sim") == 0) aux.urgency = 1; else aux.urgency = 0;
    aux.owner = uid;
    aux.created_at = localtime( &rawtime );
    aux.executed_at = NULL;
    return aux;
}

int insertEndListP(ELEM_PROCESS **iniListP, ELEM_PROCESS **endListP, PROCESS newProcess){
    ELEM_PROCESS *new=NULL;
    new=(ELEM_PROCESS *) calloc(1, sizeof(ELEM_PROCESS));
    if(new == NULL){
        printf("OUT OF MEMORY!\n");
        return -1;
    }
    new->info = newProcess;
    new->previous = NULL;
    new->next = NULL;
    if(*endListP == NULL){
        *iniListP = new;
        *endListP = new;
    } else{
        new->previous=*endListP;
        (*endListP)->next=new;
        *endListP=new;
    }
    return 0;
}

int readProcesses(ELEM_PROCESS **iniListP, ELEM_PROCESS **endListP){
    PROCESS aux;
    FILE *fp = fopen("processes.dat", "rb");
    if(!fp) return -1;
    while(fread(&aux, sizeof(PROCESS), 1,fp)) insertEndListP(iniListP, endListP ,aux);
    fclose(fp);
    return 0;
}

int saveProcesses(ELEM_PROCESS *iniListP){
    ELEM_PROCESS *aux = NULL;
    FILE *fp = NULL;
    fp=fopen("processes.dat", "wb");
    if(fp==NULL) return -1;
    for(aux = iniListP; aux != NULL; aux=aux->next) fwrite(aux, sizeof(PROCESS), 1, fp);
    fclose(fp);
    return 0;
}

void listProcesses(ELEM_PROCESS *iniListP){
    ELEM_PROCESS *aux;
    for(aux = iniListP; aux != NULL; aux=aux->next) printf("%s \n", aux->info.name);
}

int printMenuP(){
    system("cls");
    int op;
    printf("**********************************\n");
    printf("*****     Gerir Processos    *****\n");
    printf("**********************************\n");
    printf("\n\t1 - Adicionar Processo\n");
    printf("\n\t2 - Listar Processos\n");
    printf("\n\t0 - Voltar\n");
    printf("> ");
    scanf("%d", &op);
    system("cls");
    return op;
}

void processes(ELEM_PROCESS **iniListP, ELEM_PROCESS **endListP, int uid){
    int op, n_processes;
    n_processes = getsizeP(*iniListP);
    PROCESS newProcess;
    do {
        op = printMenuP();
        switch (op) {
            case 1:
                newProcess = frontEndProcesses(&n_processes, uid);
                insertEndListP(iniListP, endListP, newProcess);
                saveProcesses(*iniListP);
                break;
            case 2:
                listProcesses(*iniListP);
                system("pause");
                break;
            case 0:
                break;
            default:
                printf("Inseriu a opção errada!");
                break;
        }
    } while (op != 0);
}