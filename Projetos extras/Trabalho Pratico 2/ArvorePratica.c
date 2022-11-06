#include <stdio.h>


/*  Gustavo Dias Souza
    Atividade feita em aula


 #Feitos:
 [X] - Criar uma arvore.
 [X] - Aplicar uma rotacao no elemento que foi escolhido pelo usuario(Rotacao escolhida: rotacao a esquerda).
 
 #Problemas:
 Quando o numero nao existe ele apresenta erro.


 #Resolvidos Depois:
  Fazer a rotacao a esquerda.
  Nao deixar fazer uma rotacao se nao for possivel.



 https://github.com/GustavoDiasSouza/Projetos-em-C/tree/master/Projetos%20extras/Trabalho%20Pratico%202
*/

typedef struct arvore{
    
    int chave;
    struct arvore *direita, *esquerda;

} arvore;

arvore* PUSH( arvore *raiz, int chave );
arvore* CREATE(int chave);
arvore* rotacaoEsquerda( arvore *raiz );
arvore* procuraNumero(arvore *raiz, int alvo);
void imprimir(arvore *raiz, int nivel);


int main(){

    int entradas[] = {5,2,6,3,1,8,6,4};
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
        
        if ( numeroEscolhido == 100 ){
            imprimir(raiz, 0);
        } else {
            raiz = procuraNumero(raiz, numeroEscolhido);
            imprimir(raiz, 0);
            printf("\n\n");
        }

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
        free(newArvore);
        return NULL;
    }

    
    return newArvore;
}

arvore* PUSH( arvore *raiz, int chave ){

    //Vazia
    if ( raiz == NULL )
       return CREATE(chave);

    if (chave < raiz->chave  ){
        //Cai para esquerda. 
        raiz->esquerda = PUSH( raiz->esquerda, chave);        
    }
    else if ( chave > raiz->chave ){
        //Cai para direita.
        raiz->direita = PUSH( raiz->direita, chave);
    } else {
        printf("\n Elemento ja existe");
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

    if ( raiz->esquerda != NULL && raiz->esquerda->chave == alvo && raiz->esquerda->esquerda != NULL && raiz->esquerda->direita != NULL){

        raiz->esquerda = rotacaoEsquerda( raiz->esquerda );

    } else {

        if ( raiz->chave > alvo && raiz->esquerda != NULL){

            procuraNumero(raiz->esquerda, alvo);

        } else if ( raiz->chave < alvo && raiz->direita != NULL){

            procuraNumero(raiz->direita, alvo);
        }
    }

    return raiz;
}


arvore* rotacaoEsquerda( arvore *raiz ){

    printf("\nEscolhido: %d", raiz->chave);

    arvore *ping, *pong;
    
    //Nao pode ser removido se nao tiver alguem a sua direita
    
    ping = raiz->direita;
    pong = ping->esquerda;

    ping->esquerda = raiz;
    raiz->direita = pong;

    return ping;
}

