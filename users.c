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

int insertEndListU(ELEM_USER **iniListU, USER newUser){
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
    fclose(fp);
    return 0;
}

int readUsers(ELEM_USER **iniListU){
    USER aux;
    FILE *fp = fopen("users.dat", "rb");
    if(!fp) return -1;
    while(fread(&aux, sizeof(USER), 1,fp)) insertEndListU(iniListU,aux);
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

int verifyLogin(ELEM_USER *iniList, char name[100], char pass[100], int *uid){
    ELEM_USER *users = NULL;
    for(users = iniList; users != NULL; users=users->next){
        if((strcmp(users->info.user, name) == 0) && (strcmp(users->info.pass, pass)) == 0 && users->info.type == 1){
            *uid = users->info.id;
            return 1;
        }
        if((strcmp(users->info.user, name) == 0) && (strcmp(users->info.pass, pass)) == 0 && users->info.type == 0){
            *uid = users->info.id;
            return 0;
        }
    }
    return -1;
}

int login(ELEM_USER **iniListU, int *uid){
    char name[100], pass[100];
    int result, flag = 0;
    USER newUser;
    if(getSizeU(*iniListU) == 0){
        printf("------ Dados Paradão ------\n\n");
        printf("\t Utilizador: admin\n");
        printf("\t Password: admin\n\n");
        printf("\t Nota: Após o primeiro login a password deve ser alterada!\n\n");
        newUser.id = 1;
        newUser.type = 1;
        strcpy(newUser.user, "admin");
        strcpy(newUser.pass, "admin");
        insertEndListU(iniListU, newUser);
    }
    do{
        if(flag){
            system("cls");
            printf("Dados incorretos\n");
            system("pause");
            system("cls");
        }
        printf("\n\tInsira o nome de utilizador: ");
        gets(name);
        printf("\n\tInsira a password: ");
        gets(pass);
        result = verifyLogin(*iniListU, name, pass, uid); // -1 no login | 0 - user | 1 - admin
        if(result == -1) flag = 1;
        else flag = 0;
    }while(flag);
    system("cls");
    return result;
}

int printMenu(){
    system("cls");
    int op;
    printf("**********************************\n");
    printf("*****   Gerir Utilizadores   *****\n");
    printf("**********************************\n");
    printf("1 - Adicionar Utilizador\n");
    printf("2 - Listar Utilizadores\n");
    printf("0 - Voltar\n");
    printf("> ");
    scanf("%i", &op);
    system("cls");
    return op;
}

void menuUsers(ELEM_USER **iniListU){
    int op, n_users;
    USER newUser;
    n_users = getSizeU(*iniListU);
    do{
        op = printMenu();
        switch (op) {
            case 1:
                newUser = insertUser(&n_users);
                insertEndListU(iniListU, newUser);
                saveUsers(*iniListU);
                break;
            case 2:
                listUsers(*iniListU);
                break;
            case 0:
                break;
            default:
                printf("Erro ao escolher opção");
                break;
        }
    }while(op != 0);
}