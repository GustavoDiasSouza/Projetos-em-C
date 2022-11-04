#include <stdio.h>


/*
    Atividade feita em aula

 [X] - Criar uma arvore.
 [X] - Aplicar uma rotacao no elemento que foi escolhido pelo usuario(Rotacao escolhida: rotacao a esquerda).
 
 #Problemas:
 Quando o numero nao existe ele apresenta erro;

*/

typedef struct arvore{
    
    int chave;
    struct arvore *direita, *esquerda;
    short altura;

} arvore;

arvore* PUSH( arvore *raiz, int chave );
arvore* CREATE(int chave);
arvore* rotacaoEsquerda( arvore *raiz );
arvore* procuraNumero(arvore *raiz, int alvo);
void imprimir(arvore *raiz, int nivel);


int main(){

    int entradas[] = {8,1,7,3,10,5,6,2,4};
    int numeroEscolhido;
    arvore *raiz;
    raiz = NULL;

    for ( int i = 0; i < sizeof(entradas)/sizeof(entradas[0]) ; i++ ){
        
        raiz = PUSH(raiz, entradas[i]);

    }

    imprimir(raiz, 0);
    printf("\n\n");


    do{
        printf("Escolha um numero para fazer uma rotacaoEsquerda: ");
        scanf("%d", &numeroEscolhido);

        raiz = procuraNumero(raiz, numeroEscolhido);
        imprimir(raiz, 0);
        printf("\n\n");

    }while(numeroEscolhido != 99);


    return 0;
}

/* Methodos */

arvore* CREATE(int chave){

    arvore *newArvore = malloc(sizeof(arvore));

    if(newArvore){

        newArvore->chave = chave;
        newArvore->direita = NULL;
        newArvore->esquerda = NULL;

    } else {
        printf("Falta de memoria");
    }

    
    return newArvore;
}

arvore* PUSH( arvore *raiz, int chave ){

    if ( raiz == NULL )
       return CREATE(chave);

    if ( raiz->chave > chave){
        //Cai para esquerda. 
        raiz->esquerda = PUSH( raiz->esquerda, chave);        
    }
    else if ( raiz->chave < chave){
        //Cai para direita.
        raiz->direita = PUSH( raiz->direita, chave);
    } 

    return raiz;
}

void imprimir(arvore *raiz, int nivel) {

    if (raiz) {
        imprimir(raiz->direita, nivel + 1);
        printf("\n");

        for (int i = 0; i < nivel; i++)
        {
            printf("\t");
        }

        printf("%d", raiz->chave);
        imprimir(raiz->esquerda, nivel + 1);
    }
}

arvore* procuraNumero(arvore *raiz, int alvo){

    if ( raiz->chave == alvo){
        raiz = rotacaoEsquerda( raiz );
    }

    if ( raiz->chave > alvo){
        procuraNumero(raiz->esquerda, alvo);
    }

    if ( raiz->chave < alvo){
        procuraNumero(raiz->direita, alvo);
    } 

    return raiz;
}


arvore* rotacaoEsquerda( arvore *raiz ){

    arvore *ping, *pong;
    
    //Nao pode ser removido se nao tiver alguem a sua direita
    if( raiz->direita != NULL  ){

        ping = raiz->direita;
        pong = ping->esquerda;

        ping->esquerda = raiz;
        raiz->direita = pong;
    } 

    return raiz;
}

