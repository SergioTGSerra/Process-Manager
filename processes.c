#include "processes.h"

/**
 * @desc Listagens de processos
 */

void listProcesses(ELEM_PROCESS *iniList, int n_processes){
    ELEM_PROCESS *aux;
    if(n_processes != 0) for(aux = iniList; aux != NULL; aux=aux->next) printf("%d - %s \n",aux->info.pid, aux->info.name);
    else printf("\n\tSem nenhum processo registado no momento!\n\n");
}

void listProcessesUser(ELEM_PROCESS *iniList, int uid){
    ELEM_PROCESS *aux;
    int flag = 0;
    for(aux = iniList; aux != NULL; aux=aux->next) if(aux->info.owner == uid){
            printf("%d - %s \n",aux->info.pid, aux->info.name);
            flag = 1;
    }
    if (flag == 0) printf("\n\tUtilizador sem processos no momento!\n\n");
}

void infoProcess(ELEM_PROCESS *iniList, int pid){

}

/**
 * @desc List Processes
 */

int getsizeP(ELEM_PROCESS *iniList){
    int size = 0;
    ELEM_PROCESS *aux = NULL;
    for (aux = iniList; aux != NULL; aux=aux->next) size++;
    return size;
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
    if(strcmp(auxs, "Sim") == 0) aux.urgency = 1; else aux.urgency = 0;

    //se é urgente insere na queue de urgentes
    //se n é urgente isere nos normais
    //queues insere no inicio remove do fim

    return aux;
}

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
    if(new==NULL) printf("Out of memory\n");
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

int readProcesses(ELEM_PROCESS **iniList, ELEM_PROCESS **endList){
    PROCESS aux;
    FILE *fp = fopen("processes.dat", "rb");
    if(!fp) return -1;
    while(fread(&aux, sizeof(PROCESS), 1,fp)){
        if(aux.created_at != NULL){
            insertEndList(iniList, endList ,aux);
        }else{
            if(aux.urgency == 0) insertEndList(iniList, endList ,aux);
            if(aux.urgency == 1) insertEndList(iniList, endList ,aux);
        }
    }
    fclose(fp);
    return 0;
}

int saveProcesses(ELEM_PROCESS *iniListP, ELEM_PROCESS *iniListU, ELEM_PROCESS *iniListN){
    ELEM_PROCESS *aux = NULL;
    FILE *fp = NULL;
    fp=fopen("processes.dat", "wb");
    if(fp==NULL) return -1;
    for(aux = iniListP; aux != NULL; aux=aux->next) fwrite((&aux->info), sizeof(PROCESS), 1, fp);
    for(aux = iniListU; aux != NULL; aux=aux->next) fwrite((&aux->info), sizeof(PROCESS), 1, fp);
    for(aux = iniListN; aux != NULL; aux=aux->next) fwrite((&aux->info), sizeof(PROCESS), 1, fp);
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
    printf("\n\t0 - Voltar\n");
    printf("> ");
    scanf("%d", &op);
    system("cls");
    return op;
}

void processes(ELEM_PROCESS **iniList, ELEM_PROCESS **endList, int uid, int isadmin){
    int op, n_processes;
    n_processes = getsizeP(*iniList);
    PROCESS newProcess;
    do {
        op = printMenuP(isadmin);
        switch (op) {
            case 1:
                newProcess = frontEndProcesses(&n_processes, uid);
                insertendList(iniList, endList, newProcess);
                saveProcesses(*iniList);
                break;
            case 2:
                listProcessesUser(*iniList, uid);
                system("pause");
                break;
            case 3:
                listProcesses(*iniList, n_processes);
                system("pause");
                break;
            case 4:
                break;
            case 0:
                break;
            default:
                printf("Inseriu a opção errada!");
                break;
        }
    } while (op != 0);
}