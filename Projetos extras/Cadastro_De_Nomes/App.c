#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int menu();
void listaNomes();
void removeNome();
char adicionaNome();

char nome[1000] = "";

int main(){

    system("cls");
    /* Inicializacao das variaveis */
    int opMenu = 0;    

    while (opMenu != 4){

        opMenu = menu();    

        switch (opMenu)
        {
        case 1:
            adicionaNome(nome);
            break;
        case 2:
            removeNome(nome);
            break;
        case 3:
            listaNomes(nome);
            break;
        }
    }
    return 0;
}


int menu(){

    int opMenu = 0;

    printf("\n\n*--- App Menu ---*\n");
    printf("1 - Adicionar nome\n");
    printf("2 - Remover nome\n");
    printf("3 - Listar \n");
    printf("4 - Sair \n");
    printf("escolha:");
    scanf("%d", &opMenu);

    return opMenu;
}

char adicionaNome( char nome[] ){

    printf("\n+--- Adicionar nome ---+");

    char nomeProvisorio[100];
    
    printf("\nNovo nome:");
    scanf("%s", nomeProvisorio);

    //Deixa a primeira letra maiuscula.
    nomeProvisorio[0] = toupper(nomeProvisorio[0]);
    
    for ( int i = 0; i < strlen(nomeProvisorio); i++ ) {

        /* Deixar todas as letras minusculas menos a primeira. */                
        if(nomeProvisorio[i] != '\0' && i != 0){
            nomeProvisorio[i] = tolower(nomeProvisorio[i]);
        }
    }

    if(strlen(nome) < 1){
        strcat(nome, nomeProvisorio);

    } else {
        strcat(nome, ",");
        strcat(nome, nomeProvisorio);

    }
}

void listaNomes( char nome[] ){

    printf("\n+--- Lista ---+");

    int userNumber = 1;
    char virgula[1] = ",";

    printf("\nUser 1:");

    for ( int i = 0; i < strlen(nome); i++ ){

        if( nome[i] == virgula[0] ){
            userNumber++;
            printf("\nUser %d:", userNumber); 

        } else {
            printf("%c", nome[i]); 

        }
    }

}

void removeNome( char nome[] ){

    printf("\n+--- Remover nome ---+");
            
    for ( int i = 0; i < strlen(nome);i++ ){
        
        printf("\nLetra: %c",nome[i]);
    }
}

