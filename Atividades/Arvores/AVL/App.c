#include <string.h>
#include <stdio.h>

/* Gustavo Dias Souza

    #- Arvore binaria AVL com balanceamento -#
    - Objetivo eh criar uma estrutura de arvore com apenas 2 ramificacoes(binaria) que se mantenha balanceada(tenha o mesmo numero de elemento de cada lado) a cada insercao feita. 


*/


typedef struct Leaf{
    int valor;
    struct Leaf *LeafLeft, *LeafRight;
    short altura;
} Leaf;


Leaf * PUSH();
Leaf * createLeaf();
short maior();
short alturaLeaf();
short fatorBalenceamento();
Leaf* rotacaoEsquerda();
Leaf* rotacaoDireita();
Leaf* rotacaoEsquerdaDireita();
Leaf* rotacaoDireitaEsquerda();
Leaf* balancear();


int main(){

    /* DEBUG */
    Leaf *raiz;
    raiz = NULL;
    int data[] = {5,8};

    

    for (int i = 0; i < 2; i++){


        
    }

    /* --- */

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


//Balanceamento
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