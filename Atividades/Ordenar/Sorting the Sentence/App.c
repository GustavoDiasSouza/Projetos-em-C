/* 
    - Gustavo Dias Souza - 
    Atividade de leetCode

A sentence is a list of words that are separated by a single space with no leading or trailing spaces. Each word consists of lowercase and uppercase English letters.

A sentence can be shuffled by appending the 1-indexed word position to each word then rearranging the words in the sentence.

For example, the sentence "This is a sentence" can be shuffled as "sentence4 a3 is2 This1" or "is2 sentence4 This1 a3".
Given a shuffled sentence s containing no more than 9 words, reconstruct and return the original sentence.

*/

#include <stdio.h>
#include <string.h>

int checkNumber(char *s, int i){
    if ( s[i] == '1' || s[i] == '2' || s[i] == '3' || s[i] == '4' || s[i] == '5' || s[i] == '6' || s[i] == '7' || s[i] == '8' || s[i] == '9' ){
        return 1;
    } 
    return 0;
}

void Imprimir(char vetorPontoDaString[] , int vetorNumero[] , int vetorComeco[]){
    printf("\n");
    for ( int i = 0; i < 9; i++ ){
        
        if( vetorPontoDaString[i] != NULL){
            printf("\nComeco: %d Fim:%d Ordem:%c", vetorComeco[i], vetorNumero[i], vetorPontoDaString[i]);
        }
    }
    printf("\n");

}


char * sortSetence(char * s){
    printf("\nComo a palavra Chegou: %s ", s);

    char *PalavraCorreta = malloc( strlen(s) );
    int nVetor = 0;
    int nPalavra = 0;
    int nComeco = 0; 
    int X = 0;
    char vetorPontoDaString[9];
    int vetorNumero[9];
    int vetorComeco[9];

    //Desmontador
    for ( int i=0; i <= strlen(s); i++ ){

        if( checkNumber(s, i) == 1  ){
            vetorPontoDaString[nVetor] = s[i];
            vetorNumero[nVetor] = i;
            vetorComeco[nVetor] = nComeco;
            nVetor++;
            nComeco = i+1;
        }
    }

    Imprimir( vetorPontoDaString , vetorNumero, vetorComeco);

    //Ordenador
    for (int i = 0; i < 9; i++) {
        for ( int j = 0; j < 8; j++) {
            
            if( vetorPontoDaString[j] != NULL ){

                int Y = (int)(vetorPontoDaString[j])-48;
                int K = (int)(vetorPontoDaString[j+1])-48;
                char Temp;
                int TempNumber;
                int TempComeco;
                if(Y > K){
                    Temp = vetorPontoDaString[j];
                    vetorPontoDaString[j] = vetorPontoDaString[j+1];
                    vetorPontoDaString[j+1] = Temp;

                    TempNumber = vetorNumero[j];
                    vetorNumero[j] = vetorNumero[j+1];
                    vetorNumero[j+1] = TempNumber;

                    TempComeco = vetorComeco[j];
                    vetorComeco[j] = vetorComeco[j+1];
                    vetorComeco[j+1] = TempComeco;
                }
            }
        }
    }

    
    for ( int i = 0; i < 9; i++){
        if( vetorPontoDaString[i] != NULL ){
            
            for (int C = vetorComeco[i]; C < vetorNumero[i]; C++){
               
                if( s[C] == ' '  ){
                    continue;
                }
                PalavraCorreta[X] = s[C];
                X++;
                
            }

            PalavraCorreta[X] = ' ';
            X++;
        }
    }
   
    Imprimir( vetorPontoDaString , vetorNumero, vetorComeco);

    s = PalavraCorreta;
    return s; 
} 



int main(){

    char *Frase = "is2 sentence4 This1 a3";

    char *fraseCompleta;
    fraseCompleta = sortSetence(Frase);

    printf("%s", fraseCompleta);


    return 0;
}