#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*      
    -#- Gustavo Dias Souza -#-  
    
    Atividade pratica 4

    [X] - Dado um vetor de inteiros nums, mova todos os inteiros pares no início do vetor seguido por todos os inteiros ímpares.
    [X] - Retorne qualquer vetor que satisfaça essa condição.
    [X] - Resolva o problema usando um algoritmo de ordenação visto em aula.


    Exemplo 1:
    Entrada: nums = [3,1,2,4]
    Saída: [2,4,3,1]
*/


int * Ordenador( int *nums, int max ){
    int i, j, temp;
    int newNums[max];

    for (i = 0; i < max; i++){
        for (j = i; j < max; j++){
            if (nums[j] % 2 == 0  ){
                temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
    }
    return nums;
}

void imprimir( int nums[], int max){

    printf("\nIMPRIMINDO");
    for (int i = 0; i < max; i++){
        printf(" %d ", nums[i]);
    }
    printf("\n\n\n");
}

int main(){

    // int dados[]= {2,1,4,6,3,8,9,5};
    // int dados[]= {8,5,4,6,3,0,9,5};
    int dados[] = {0};

    int max = sizeof(dados) / sizeof(dados[0]);

    imprimir( dados, max);
    Ordenador( dados, max );
    imprimir(dados, max);

    return 0;
}