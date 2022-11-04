#include <string.h>
#include <stdio.h>
#include <time.h>

/* Gustavo Dias Souza

    #- Arvore binaria AVL com balanceamento -#
    - Objetivo eh criar uma estrutura de arvore com apenas 2 ramificacoes(binaria) que se mantenha balanceada(tenha o mesmo numero de elemento de cada lado) a cada insercao feita.

*/

typedef struct Leaf{
    int valor;
    struct Leaf *LeafLeft, *LeafRight;
    short altura;
} Leaf;

Leaf *PUSH(Leaf *raiz, int valor);
Leaf *createLeaf(int newValor);
short maior(int a, int b);
short alturaLeaf(Leaf *raiz);
short fatorBalenceamento(Leaf *raiz);
Leaf *rotacaoEsquerda(Leaf *raiz);
Leaf *rotacaoDireita(Leaf *raiz);
Leaf *rotacaoEsquerdaDireita(Leaf *raiz);
Leaf *rotacaoDireitaEsquerda(Leaf *raiz);
Leaf *balancear(Leaf *raiz);
Leaf *POP(Leaf *raiz, int chave);
void imprimir(Leaf *raiz, int nivel);

int main(){

    Leaf *raiz;
    raiz = NULL;
    int totalNumerosInseridos = 20;

    int ranvals[totalNumerosInseridos];

    srand(18);

    for (int i = 0; i < totalNumerosInseridos; i++)
    {
        ranvals[i] = rand() % totalNumerosInseridos;
    }

    for (int i = 0; i < sizeof(ranvals) / sizeof(ranvals[0]); i++)
    {
        raiz = PUSH(raiz, ranvals[i]);
        printf("\n\nMAPA\n\n");
            imprimir(raiz, 0);

    }



    printf("\n");
    return 0;
}

Leaf *PUSH(Leaf *raiz, int newValor){

    // Arvore vazia
    if (raiz == NULL)
        return createLeaf(newValor);

    // Define se vai ser a esquerda ou direita
    if (newValor < raiz->valor)
    {
        raiz->LeafLeft = PUSH(raiz->LeafLeft, newValor);
    }
    else if (newValor > raiz->valor)
    {
        raiz->LeafRight = PUSH(raiz->LeafRight, newValor);
    }
    else
    {
        printf("\nO elemento ja existe");
    }

    raiz->altura = maior(alturaLeaf(raiz->LeafLeft), alturaLeaf(raiz->LeafRight)) + 1;

    raiz = balancear(raiz);

    return raiz;
}

Leaf *createLeaf(int newValor){
    Leaf *newLeaf = malloc(sizeof(Leaf));

    if (newLeaf)
    {

        newLeaf->valor = newValor;
        newLeaf->LeafLeft = NULL;
        newLeaf->LeafRight = NULL;
        newLeaf->altura = 0;
    }
    else
    {
        printf("\nFalta de Memory");
        return NULL;
    }

    return newLeaf;
}

// Qual lado eh maior
short maior(int a, int b){
    return (a < b) ? a : b;
}

// Retorna a altura da LEAF ou -1 caso seja null
short alturaLeaf(Leaf *raiz){
    if (raiz == NULL)
    {
        return -1;
    }
    else
    {
        return raiz->altura;
    }
}

short fatorBalenceamento(Leaf *raiz){

    if (raiz)
    {
        return (alturaLeaf(raiz->LeafLeft) - alturaLeaf(raiz->LeafRight));
    }
    else
    {
        return 0;
    }
}

Leaf *rotacaoEsquerda(Leaf *raiz){
    Leaf *ping, *pong;

    ping = raiz->LeafRight;
    pong = ping->LeafLeft;

    ping->LeafLeft = raiz;
    raiz->LeafRight = pong;

    raiz->altura = maior(alturaLeaf(raiz->LeafLeft), alturaLeaf(raiz->LeafRight) + 1);
    ping->altura = maior(alturaLeaf(ping->LeafLeft), alturaLeaf(ping->LeafRight) + 1);

    return ping;
}

Leaf *rotacaoDireita(Leaf *raiz){
    Leaf *ping, *pong;

    ping = raiz->LeafLeft;
    pong = ping->LeafRight;

    ping->LeafRight = raiz;
    raiz->LeafLeft = pong;

    raiz->altura = maior(alturaLeaf(raiz->LeafLeft), alturaLeaf(raiz->LeafRight) + 1);
    ping->altura = maior(alturaLeaf(ping->LeafLeft), alturaLeaf(ping->LeafRight) + 1);

    return ping;
}

Leaf *rotacaoDireitaEsquerda(Leaf *raiz){
    raiz->LeafRight = rotacaoDireita(raiz->LeafRight);
    return rotacaoEsquerda(raiz);
}

Leaf *rotacaoEsquerdaDireita(Leaf *raiz){
    raiz->LeafLeft = rotacaoEsquerda(raiz->LeafLeft);
    return rotacaoDireita(raiz);
}

Leaf *balancear(Leaf *raiz){
    short fb = fatorBalenceamento(raiz);

    // Rotacao ah esquerda
    if (fb < -1 && fatorBalenceamento(raiz->LeafRight) <= 0)
    {
        raiz = rotacaoEsquerda(raiz);

        // Rotacao ah direita
    }
    else if (fb > 1 && fatorBalenceamento(raiz->LeafLeft) >= 0)
    {
        raiz = rotacaoDireita(raiz);

        // Rotacao dupla ah esquerda
    }
    else if (fb > 1 && fatorBalenceamento(raiz->LeafLeft) < 0)
    {
        raiz = rotacaoEsquerdaDireita(raiz);

        // Ratacao dupla ah direita
    }
    else if (fb < -1 && fatorBalenceamento(raiz->LeafRight) > 0)
    {
        raiz = rotacaoDireitaEsquerda(raiz);
    }

    return raiz;
}

Leaf *POP(Leaf *raiz, int chave){

    if (raiz == NULL)
        return NULL;

    if (raiz->valor == chave)
    {

        // 1 caso
        if (raiz->LeafLeft == NULL && raiz->LeafRight == NULL)
        {

            free(raiz);
            printf("\nElemento removido %d \n", chave);
            return NULL;
        }

        // 2 caso
        if (raiz->LeafRight != NULL && raiz->LeafLeft != NULL)
        {

            Leaf *aux = raiz->LeafLeft;

            while (aux->LeafRight != NULL)
            {
                aux = aux->LeafRight;
            }

            raiz->valor = aux->valor;
            aux->valor = chave;
            printf("\nElemento Trocado!");

            raiz->LeafLeft = POP(raiz->LeafLeft, chave);
            return raiz;
        }
        // 3 caso
        Leaf *aux;
        if (raiz->LeafLeft != NULL)
        {
            aux = raiz->LeafLeft;
        }
        else
        {
            aux = raiz->LeafRight;
        }

        free(raiz);
        printf("\nElemento com 1 filho removido");
        return aux;
    }
    else
    {
        if (chave < raiz->valor)
        {
            raiz->LeafLeft = POP(raiz->LeafLeft, chave);
        }
        else
        {
            raiz->LeafRight = POP(raiz->LeafRight, chave);
        }
    }

    raiz->altura = maior(alturaLeaf(raiz->LeafLeft), alturaLeaf(raiz->LeafRight) + 1);
    raiz = balancear(raiz);

    return raiz;
}

void imprimir(Leaf *raiz, int nivel) {


    if (raiz) {

        imprimir(raiz->LeafRight, nivel + 1);
        printf("\n");

        for (int i = 0; i < nivel; i++)
        {
            printf("\t");
        }

        printf("%d", raiz->valor);
        imprimir(raiz->LeafLeft, nivel + 1);
    }

}