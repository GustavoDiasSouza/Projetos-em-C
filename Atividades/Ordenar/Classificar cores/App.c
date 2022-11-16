/*
    !- Gustavo Dias Souza -! 
     
    #Atividade de LeetCode 

- Dada uma matriz numscom nobjetos coloridos em vermelho, 
  branco ou azul, classifique-os no local para que os objetos da mesma cor sejam adjacentes, 
  com as cores na ordem vermelho, branco e azul.
- Usaremos os inteiros 0, 1, e 2para representar a cor vermelha, branca e azul, respectivamente.
- Você deve resolver esse problema sem usar a função de classificação da biblioteca.

*/
#include <stdio.h>

#include <string.h>


int * ordenador(int * nums,int numsSize ) {
    int i, c[3];
    
    for (i = c[0] = c[1] = c[2] = 0; i < numsSize; i++)
        c[nums[i]]++;
    
    for (i = 0; i < c[0]; i++)
        nums[i] = 0;
    while (i < c[0] + c[1])
        nums[i++] = 1;
    while (i < numsSize)
        nums[i++] = 2;
}

void imprimir(int c[], int max){

    printf("\n\nImprimindo: ");
    for (int i =0; i < max; i++){
        printf("%d", c[i] );
        if(i != max-1) printf(", ");
    } 

}



int main() {
    int Pointer[] = {0,2,1,0,2,2,1,1,1,0};
    int Tamanho = (int) sizeof(Pointer) / sizeof(Pointer[0]);
    imprimir(Pointer, Tamanho);  
    ordenador(Pointer, Tamanho);
    imprimir(Pointer, Tamanho);
    printf("\n\n");
}
