#include <stdio.h>
#include <stdlib.h>

/* Gustavo Dias Souza

[X] - Faça um programa que solicita do usuário o tamanho de um vetor.
[X] - Crie um vetor com esse tamanho, utilizando memória dinâmica, onde números inteiros serão armazenados.
[@] - Preencha esse vetor com números inteiros gerados com a função “int rand()” e imprima o vetor.
[X] - Em seguida solicite um número inteiro do usuário.
[X] - O programa deve procurar esse número dentro do vetor e indicar se foi encontrado ou não.
[!] - Caso encontre o número esse deve ser removido do vetor e o vetor deve encolher.
[X] - Caso não encontre procure dois números que somados geram o número sendo buscado, caso encontrado ambos devem ser impressos na tela e removidos do vetor e esse deve encolher.
[X] - Todas essas operações devem ser feitas com notação de ponteiros (aritmética de ponteiros) e não com notação de vetores (vetor[10], por exemplo). 

*/

void mostraResultado();
int encontraSomaDeDoisNumeros();

int main(){

    int *Pvetor, *Pn, *Ptamanho;
    Ptamanho = (int *)malloc( sizeof(int) );

    //define o tamanho do vetor
    printf("Tamanho do vetor que deseja:");
    scanf("%d",Ptamanho);

    Pvetor = (int *)malloc( sizeof(int) * (*Ptamanho)+1);
    Pn = (int *)malloc( sizeof(int) );

    //Alimenta o vetor
    for (int i = 0; i <= *Ptamanho; i++){

        Pvetor[i] = rand() % *Ptamanho;
    }
    mostraResultado( Pvetor, Ptamanho );



    //Pega a escolha do usuario
    printf("\n\nEscolha um numero:");
    scanf("%d",Pn);

    
    //Mostra o resultado e a nova estrutura
    for (int i = 0; i <= *Ptamanho; i++){

        if(*Pn == Pvetor[i]){

            printf("%d Encontrado!\n\n", *Pn);
            Pvetor[i] = 101;

            
            printf("#- Nova Estrutura -#\n");
            mostraResultado( Pvetor, Ptamanho);
            
            
            printf("\n\n");
            free( Pvetor );
            return 0;    
        }
    }


    int resultado = encontraSomaDeDoisNumeros(Pvetor, Ptamanho, Pn);

    if(resultado == 1){
        free( Pvetor );
        return 0;
    }
    
    printf("\nNao encontrado!\n");
    free( Pvetor );
    return 0;
}

void mostraResultado(int *p, int *tamanho){

    for (int i = 0; i <= *tamanho; i++){

        if ( i == 0 ){
            printf("%d", p[i]);
        } else {
            printf(" | %d", p[i]);
        }
    }
}

int encontraSomaDeDoisNumeros(int *p, int *tamanho, int *escolha){
    
    int somaDosNumeros;
    for (int i = 0; i <= *tamanho; i++){
        for (int j = 0; j <= *tamanho; j++){
            somaDosNumeros = p[i] + p[j];

            if(somaDosNumeros == *escolha){
                printf("\nPrimeiro Valor: %d", p[i]);
                printf("\nSegundo Valor: %d", p[j]);
                printf("\nCombina: %d", somaDosNumeros);

                printf("\n\n");
                return 1;
            }
        }
    }
    return 0;
}

