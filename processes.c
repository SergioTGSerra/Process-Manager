#include "processes.h"

/**
 * @desc Get size from list
 */
int getsizeP(ELEM_PROCESS *iniList){
    int size = 0;
    ELEM_PROCESS *aux = NULL;
    for (aux = iniList; aux != NULL; aux=aux->next) size++;
    return size;
}

/**
 * @desc Listing Processes
 */

void listProcesses(ELEM_PROCESS *iniList){
    ELEM_PROCESS *aux;
    for(aux = iniList; aux != NULL; aux=aux->next) printf("\t%d - %s \n",aux->info.pid, aux->info.name);
}

void listReverseProcesses(ELEM_PROCESS *endList){
    ELEM_PROCESS *aux;
    for(aux = endList; aux != NULL; aux=aux->previous) printf("\t%d - %s \n",aux->info.pid, aux->info.name);
}


int listProcessesUser(ELEM_PROCESS *iniList, int uid){
    ELEM_PROCESS *aux;
    int flag = 0;
    for(aux = iniList; aux != NULL; aux=aux->next) if(aux->info.owner == uid){
        printf("\t %d - %s \n",aux->info.pid, aux->info.name);
        flag = 1;
    }
    if(flag == 1) return 1;
    else return 0;
}

PROCESS infoProcess(ELEM_PROCESS *iniList, int pid){
    ELEM_PROCESS *aux;
    for(aux = iniList; aux != NULL; aux=aux->next) if(aux->info.pid == pid){
            printf("\nNome: %s", &aux->info.name);
            printf("\nDescirção: %s", &aux->info.desc);
            printf("\nTipo: ");
            if(aux->info.type == 1) printf("Urgente");
            if(aux->info.type == 0) printf("Normal");
            if(aux->info.type == -1) printf("Recusado");
            if(aux->info.type == 2) printf("Processado");
            printf("\nCriado em: %d do %d de %d as %d horas e %d minutos", &aux->info.created_at->tm_min, &aux->info.created_at->tm_mon, &aux->info.created_at->tm_year, &aux->info.created_at->tm_hour, &aux->info.created_at->tm_min);
        return aux->info;
    }
}

/**
 * @desc Processes
 */

int insertEndList(ELEM_PROCESS **iniList, ELEM_PROCESS **endList, PROCESS newProcess){
    ELEM_PROCESS *new=NULL;
    new=(ELEM_PROCESS *) calloc(1, sizeof(ELEM_PROCESS));
    if(new == NULL){
        printf("OUT OF MEMORY!\n");
        return -1;
    }
    new->info = newProcess;
    new->previous = NULL;
    new->next = NULL;
    if(*endList == NULL){
        *iniList = new;
        *endList = new;
    } else{
        new->previous=*endList;
        (*endList)->next=new;
        *endList=new;
    }
    return 0;
}

int insertIniList(ELEM_PROCESS **iniList, ELEM_PROCESS **endList, PROCESS newProcess){
    ELEM_PROCESS *new=NULL;
    new=(ELEM_PROCESS *) calloc(1, sizeof(ELEM_PROCESS));
    if(new==NULL){
        printf("Out of memory\n");
        return -1;
    }
    new->info = newProcess;
    new->previous = NULL;
    new->next = NULL;
    if(*iniList==NULL){
        *iniList=new;
        *endList=new;
    } else{
        new->next = *iniList;
        (*iniList)->previous=new;
        *iniList=new;
    }
    return 0;
}

PROCESS frontEndProcesses(int *n_processes, int uid){
    time_t rawtime;
    time( &rawtime );
    PROCESS aux;
    char auxs[10];
    (*n_processes)++;
    aux.pid = *n_processes;
    printf("Intruza o nome do processo: ");
    scanf("%s", &aux.name);
    printf("Intruza a descrição do processo: ");
    scanf("%s", &aux.desc);
    aux.owner = uid;
    aux.created_at = localtime( &rawtime );
    aux.executed_at = NULL;
    printf("Urgente? (Sim | Não): ");
    scanf("%s", &auxs);
    if(strcmp(auxs, "Sim") == 0) aux.type = 1; else aux.type = 0;
    return aux;
}

int removeListP(ELEM_PROCESS **iniList, ELEM_PROCESS **endList, int num){
    ELEM_PROCESS *aux=*iniList;
    while (aux!=NULL && aux->info.pid != num) aux = aux->next;
    if(aux == NULL) return -1;
    if(aux->previous == NULL){
        *iniList = aux->next;
        if(*iniList!=NULL) (*iniList)->previous=NULL;
    } else {aux->previous->next = aux->next;}
    if(aux->next == NULL){
        *endList=aux->previous;
        if(*endList!=NULL) (*endList)->next=NULL;
    } else{aux->next->previous = aux->previous;}
    free(aux); return 0;
}

int readProcesses(ELEM_PROCESS **iniList, ELEM_PROCESS **endList, int type){
    PROCESS aux;
    FILE *fp = fopen("processes.dat", "rb");
    if(!fp) return -1;
    while(fread(&aux, sizeof(PROCESS), 1,fp)) if(aux.type == type) insertEndList(iniList, endList ,aux);
    fclose(fp);
    return 0;
}

int saveProcesses(ELEM_PROCESS *iniListP, ELEM_PROCESS *iniListU, ELEM_PROCESS *iniListN, ELEM_PROCESS *iniListR){
    ELEM_PROCESS *aux = NULL;
    FILE *fp = NULL;
    fp=fopen("processes.dat", "wb");
    if(fp==NULL) return -1;
    for(aux = iniListP; aux != NULL; aux=aux->next) fwrite((&aux->info), sizeof(PROCESS), 1, fp);
    for(aux = iniListU; aux != NULL; aux=aux->next) fwrite((&aux->info), sizeof(PROCESS), 1, fp);
    for(aux = iniListN; aux != NULL; aux=aux->next) fwrite((&aux->info), sizeof(PROCESS), 1, fp);
    for(aux = iniListR; aux != NULL; aux=aux->next) fwrite((&aux->info), sizeof(PROCESS), 1, fp);
    fclose(fp);
    return 0;
}

/**
 * @desc Main function processes
 */

int printMenuP(int isadmin){
    system("cls");
    int op;
    printf("**********************************\n");
    printf("*****     Gerir Processos    *****\n");
    printf("**********************************\n");
    printf("\n\t1 - Adicionar processo\n");
    printf("\n\t2 - Listar meus processos\n");
    if(isadmin == 1) printf("\n\t3 - Listar todos os processos\n");
    if(isadmin == 1) printf("\n\t4 - Executar processos\n");
    if(isadmin == 1) printf("\n\t5 - Listar processos recusados\n");
    printf("\n\t0 - Voltar\n");
    printf("> ");
    scanf("%d", &op);
    system("cls");
    return op;
}

void header(int type){
    if(type == 2) printf("\n*****************************\n*** Processos Processados ***\n*****************************\n");
    if(type == 1) printf("\n*****************************\n**** Processos  Urgentes ****\n*****************************\n");
    if(type == 0) printf("\n*****************************\n***** Processos Normais *****\n*****************************\n");
    if(type == -1) printf("\n*****************************\n**** Processos Recusados ****\n*****************************\n");
}

void processes(int uid, int isadmin){

    //List Processes
    ELEM_PROCESS *iniListP=NULL, *endListP=NULL; readProcesses(&iniListP, &endListP, 2);
    ELEM_PROCESS *iniListU=NULL, *endListU=NULL; readProcesses(&iniListU, &endListU, 1);
    ELEM_PROCESS *iniListN=NULL, *endListN=NULL; readProcesses(&iniListN, &endListN, 0);
    ELEM_PROCESS *iniListR=NULL, *endListR=NULL; readProcesses(&iniListR, &endListR, -1);

    int op, n_processes;
    char auxs[20];
    n_processes = getsizeP(iniListP) + getsizeP(iniListU) + getsizeP(iniListN) + getsizeP(iniListR);
    PROCESS newProcess;

    do {
        op = printMenuP(isadmin);
        switch (op) {
            case 1:
                newProcess = frontEndProcesses(&n_processes, uid);
                if(newProcess.type == 0 && getsizeP(iniListN) >= 3){
                    printf("\nLista de processos normais cheia (max: 15)! A inserir processo em recusados... \n");
                    newProcess.type = -1;
                    insertEndList(&iniListR, &endListR, newProcess);
                }
                if(newProcess.type == 1 && getsizeP(iniListU) >= 3){
                    printf("\nLista de processos urgentes cheia (max: 15)! A inserir processo em recusados... \n");
                    newProcess.type = -1;
                    insertEndList(&iniListR, &endListR, newProcess);
                }
                if(newProcess.type == 0 && getsizeP(iniListN) < 3) insertIniList(&iniListN, &endListN, newProcess);
                if(newProcess.type == 1 && getsizeP(iniListU) < 3) insertIniList(&iniListU, &endListU, newProcess);
                saveProcesses(iniListP, iniListU, iniListN, iniListR);
                system("pause");
                break;
            case 2:
                header(2);
                if(!listProcessesUser(iniListP, uid)) printf("\tNão existem processos processados!\n");
                header(1);
                if(!listProcessesUser(iniListU, uid)) printf("\tNão existem processos urgentes!\n");
                header(0);
                if(!listProcessesUser(iniListN, uid)) printf("\tNão existem processos normais!\n");
                header(-1);
                if(!listProcessesUser(iniListR, uid)) printf("\tNão existem processos recusados!\n\n");
                system("pause");
                break;
            case 3:
                if(n_processes != 0){
                    header(2);
                    listProcesses(iniListP);
                    header(1);
                    listReverseProcesses(endListU);
                    header(0);
                    listReverseProcesses(endListN);
                    header(-1);
                    listProcesses(iniListR);
                } else printf("Não existem processos!\n");
                system("pause");
                break;
            case 4:
                break;
            case 5:
                header(-1);
                listProcesses(iniListR);
                printf("\nDeseja inserir um processo recusado para uma lista de espera? (Sim|Não): ");
                scanf("%s", &auxs);
                if(strcmp(auxs, "Sim") == 0){
                    printf("\n Insira o numero de um processo acima para inserir numa lista de espera: ");
                    scanf("%d", &op);
                    infoProcess(iniListR, op);
                    system("pause");
                }
                system("pause");
                break;
            case 0:
                break;
            default:
                printf("Inseriu a opção errada!\n");
                break;
        }
    } while (op != 0);
}