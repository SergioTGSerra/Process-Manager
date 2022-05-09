#include "users.h"

USER insertUser(int *n_users){
    char auxs[100];
    int flag = 0;
    USER aux;
    (*n_users)++;
    aux.id = (*n_users);
    fflush(stdin);
    printf("Introduza o nome de utilizador: ");
    gets(aux.user);
    printf("Administrador (Sim | Não): ");
    fflush(stdin);
    gets(auxs);
    if(strcmp(auxs, "Sim") == 0) aux.type = 1; else aux.type = 0;
    do{
        if(flag == 1) printf("Erro ao introduzir password!\n");
        printf("Introduza o palavra-passe: ");
        gets(auxs);
        printf("Volte a introduzir a palavra-passe: ");
        gets(aux.pass);
        if(strcmp(auxs, aux.pass) != 0) flag = 1;
    }while(strcmp(auxs, aux.pass) != 0);
    system("pause");
    system("cls");
    return aux;
}

int insertEndList(ELEM_USER **iniListU, USER newUser){
    ELEM_USER *new = NULL, *aux=NULL;
    new = (ELEM_USER *) calloc(1, sizeof(ELEM_USER));
    if(new == NULL){
        printf("OUT OF MEMORY!\n");
        return -1;
    }
    new->info = newUser;
    new->next = NULL;
    if(*iniListU == NULL) *iniListU = new;
    else{
        aux =*iniListU;
        while(aux->next != NULL) aux=aux->next;
        aux->next=new;
    }
    return 0;
}

int saveUsers(ELEM_USER *iniList){
    ELEM_USER *aux = NULL;
    FILE *fp = NULL;
    fp=fopen("users.dat", "wb");
    if(fp==NULL) return -1;
    for(aux = iniList; aux != NULL; aux=aux->next) fwrite(aux, sizeof(USER), 1, fp);
    system("pause");
    fclose(fp);
    return 0;
}

int readUsers(ELEM_USER **iniListU){
    USER aux;
    FILE *fp = fopen("users.dat", "rb");
    if(!fp) return -1;
    while(fread(&aux, sizeof(USER), 1,fp)) insertEndList(iniListU,aux);
    fclose(fp);
    return 0;
}

void listUsers(ELEM_USER *iniList){
    ELEM_USER *user = NULL;
    if(iniList==NULL) printf("Erro: Não existem dados de utilizadores!\n");
    else{
        for(user = iniList; user != NULL; user=user->next) {
            printf("Id: %i, Tipo: %i,  Nome: %s, Pass: %s\n", user->info.id, user->info.type, user->info.user, user->info.pass);
        }
    }
    system("pause");
    system("cls");
}

int getSizeU(ELEM_USER *iniList){
    int size=0;
    ELEM_USER *aux = NULL;
    for(aux = iniList; aux != NULL; aux= aux->next){
        size++;
    }
    return size;
}

int verifyLogin(ELEM_USER *iniList){
    ELEM_USER *users = NULL;
    for(users = iniList; users != NULL; users=users->next){
        printf("%s", users->info.user);
    }
    return 1;
}

int login(ELEM_USER *iniList){
    char name[100], pass[100];
    int result, flag = 0;
    do{
        if(flag) printf("Dados incorretos\n");
        printf("Insira o nome de utilizador: ");
        gets(name);
        printf("Insira a password: ");
        gets(pass);
        result = verifyLogin(&iniList);
        if(result == 0) flag = 1;
    }while(flag);
    return result; // 1 - success | 0 - failure
}

int printMenu(){
    int op;
    printf("Gerir Utilizadores\n");
    printf("1 - Adicionar Utilizador\n");
    printf("2 - Listar Utilizadores\n");
    printf("0 - Voltar\n");
    printf("> ");
    scanf("%i", &op);
    system("cls");
    return op;
}

void menuUsers(){
    int op, n_users;
    ELEM_USER *iniListU=NULL;
    USER newUser;
    readUsers(&iniListU);
    n_users = getSizeU(iniListU);
    do{
        op = printMenu();
        switch (op) {
            case 1:
                newUser = insertUser(&n_users);
                insertEndList(&iniListU, newUser);
                break;
            case 2:
                listUsers(iniListU);
                break;
            case 0:
                saveUsers(iniListU);
                break;
            default:
                printf("Erro ao escolher opção");
                break;
        }
    }while(op != 0);
}