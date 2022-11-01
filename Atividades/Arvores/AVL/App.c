#include <string.h>
#include <stdio.h>
#include <time.h>

/* Gustavo Dias Souza

    #- Arvore binaria AVL com balanceamento -#
    - Objetivo eh criar uma estrutura de arvore com apenas 2 ramificacoes(binaria) que se mantenha balanceada(tenha o mesmo numero de elemento de cada lado) a cada insercao feita. 


Remover um nó de uma arvore 
*/


typedef struct Leaf{
    int valor;
    struct Leaf *LeafLeft, *LeafRight;
    short altura;
} Leaf;


Leaf * PUSH(Leaf *leaf, int valor);
Leaf * createLeaf(int newValor);
short maior(int a, int b);
short alturaLeaf(Leaf *leaf);
short fatorBalenceamento(Leaf *leaf);
Leaf* rotacaoEsquerda( Leaf *leaf);
Leaf* rotacaoDireita( Leaf *leaf);
Leaf* rotacaoEsquerdaDireita( Leaf *leaf);
Leaf* rotacaoDireitaEsquerda( Leaf *leaf);
Leaf* balancear( Leaf *leaf );
Leaf* POP(Leaf *leaf, int chave);
void imprimir(Leaf *leaf, int nivel);

int main(){

    

    Leaf *raiz;
    raiz = NULL;


    int ranvals[20];

    srand(18);

    for ( int i = 0 ; i < 20; i++ ){
        ranvals[i] = rand() % 20;
    }


    for (int i = 0; i <  sizeof(ranvals)/sizeof(ranvals[0]) ; i++){
        raiz = PUSH(raiz, ranvals[i]);        
    }

    imprimir(raiz , 0);


    printf("\n");
    return 0;
}


Leaf * PUSH( Leaf *raiz, int newValor ){

    //Arvore vazia
    if (raiz == NULL) return createLeaf(newValor);

    //Define se vai ser a esquerda ou direita
    if ( newValor < raiz->valor ){
        raiz->LeafLeft = PUSH(raiz->LeafLeft, newValor);
    } else  if (newValor > raiz->valor){
        raiz->LeafRight = PUSH(raiz->LeafRight, newValor);
    } else {
        printf("\nO elemento ja existe");
    }

    raiz->altura = maior( alturaLeaf(raiz->LeafLeft ), alturaLeaf(raiz->LeafRight)) +1;

    raiz = balancear(raiz);

    return raiz;    
}

Leaf *createLeaf(int newValor){
    Leaf *newLeaf = malloc( sizeof(Leaf) );

    if(newLeaf){

        newLeaf->valor = newValor;
        newLeaf->LeafLeft = NULL;
        newLeaf->LeafRight = NULL;
        newLeaf->altura = 0;

    } else {
        printf("\nFalta de Memory");
        return NULL;
    }

    return newLeaf;
}


//Qual lado eh maior
short maior(int a , int b){
    return (a < b ) ? a : b;
}


//Retorna a altura da LEAF ou -1 caso seja null
short alturaLeaf(Leaf *leaf){
    if( leaf== NULL){
        return -1;
    } else {
        return leaf->altura;
    }
}

short fatorBalenceamento(Leaf *leaf){

    if(leaf){
        return ( alturaLeaf(leaf->LeafLeft) - alturaLeaf(leaf->LeafRight) );
    } else {
        return 0;
    }

}

Leaf* rotacaoEsquerda(Leaf *leaf){
    Leaf *auxA, *auxB;


    auxA = leaf->LeafRight;
    auxB = auxA->LeafLeft;

    auxA->LeafLeft = leaf;
    leaf->LeafRight = auxB;

    leaf->altura = maior( alturaLeaf(leaf->LeafLeft ), alturaLeaf(leaf->LeafRight) +1 );
    auxA->altura = maior( alturaLeaf(auxA->LeafLeft), alturaLeaf(auxA->LeafRight) +1 );


    return auxA;
}

Leaf* rotacaoDireita(Leaf *leaf){
    Leaf *auxA, *auxB;

    auxA = leaf->LeafLeft;
    auxB = auxA->LeafRight;

    auxA->LeafRight = leaf;
    leaf->LeafLeft = auxB;

    leaf->altura = maior( alturaLeaf(leaf->LeafLeft ), alturaLeaf(leaf->LeafRight) +1 );
    auxA->altura = maior( alturaLeaf(auxA->LeafLeft), alturaLeaf(auxA->LeafRight) +1 );


    return auxA;
}

Leaf* rotacaoDireitaEsquerda(Leaf *leaf){
    leaf->LeafRight = rotacaoDireita(leaf->LeafRight);
    return rotacaoEsquerda(leaf);
}

Leaf* rotacaoEsquerdaDireita(Leaf *leaf){
    leaf->LeafLeft = rotacaoEsquerda(leaf->LeafLeft);
    return rotacaoDireita(leaf);
}

Leaf* balancear(Leaf *leaf){
    short fb = fatorBalenceamento(leaf);

    //Rotacao ah esquerda
    if ( fb < -1 && fatorBalenceamento(leaf->LeafRight) <= 0 ){
        leaf = rotacaoEsquerda(leaf);

    //Rotacao ah direita
    } else if ( fb > 1 && fatorBalenceamento(leaf->LeafLeft) >= 0 ){
        leaf = rotacaoDireita(leaf);

    //Rotacao dupla ah esquerda
    } else if ( fb > 1 && fatorBalenceamento(leaf->LeafLeft) < 0 ){
        leaf = rotacaoEsquerdaDireita(leaf);

    //Ratacao dupla ah direita
    } else if ( fb < -1 && fatorBalenceamento(leaf->LeafRight) > 0 ){
        leaf = rotacaoDireitaEsquerda(leaf);
    } 

    return leaf;
}

Leaf* POP(Leaf *leaf, int chave){

    if ( leaf == NULL ) return NULL;

    if ( leaf->valor == chave ){
        
        //1 caso
        if ( leaf->LeafLeft == NULL && leaf->LeafRight == NULL ){
            
            free(leaf);
            printf("Elemento removido %d \n", chave);
            return NULL;
        } 


        //2 caso
        if ( leaf->LeafRight != NULL && leaf->LeafLeft != NULL ){

            Leaf *aux = leaf->LeafLeft;

            while ( aux->LeafRight != NULL ){
                aux = aux->LeafRight;
            }

            leaf->valor = aux->valor;
            aux->valor = chave;
            printf("Elemento Trocado!");

            leaf->LeafLeft = POP(leaf->LeafLeft, chave);
            return leaf;
        }

        //3 caso
        Leaf *aux;
        if ( leaf->LeafLeft != NULL ){
            aux = leaf->LeafLeft;
        } else {
            aux = leaf->LeafRight;
        }

        free(leaf);
        printf("Elemento com 1 filho removido");
        return aux;

    } else {
        if ( chave < leaf->valor ){
            leaf->LeafLeft = POP(leaf->LeafLeft, chave);
        } else {
            leaf->LeafRight = POP(leaf->LeafRight, chave);
        }
    }

    leaf->altura = maior(alturaLeaf(leaf->LeafLeft), alturaLeaf(leaf->LeafRight) +1);

    leaf = balancear(leaf);

 return leaf;
}

void imprimir(Leaf *leaf, int nivel){
    int i;
    if ( leaf ){
        imprimir(leaf->LeafRight, nivel +1);
        printf("\n\n");

        for ( i = 0; i < nivel; i++ ){
            printf("\t");
        }

        printf("%d", leaf->valor);
        imprimir(leaf->LeafLeft, nivel +1);
    }

}