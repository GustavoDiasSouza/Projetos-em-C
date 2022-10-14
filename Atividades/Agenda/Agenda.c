#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Gustavo Dias Souza
https://github.com/GustavoDiasSouza/Projetos-em-C

#-TRABALHO da Agenda:
-Continuar a sua implementação da agenda (exercício 3) semana 1 dentro dos mesmo parâmetros, mas incluir o seguinte.
-Nenhuma variável pode ser declarada em todo o programa, somente ponteiros. Todos os dados do programa devem ser guardados dentro do pBuffer.
-Nem mesmo como parâmetro de função. Só ponteiros que apontam para dentro do pBuffer.
-Exemplo do que não pode: int c; char a; int v[10];  void Funcao(int parametro)
-Não pode usar struct em todo o programa.
-Usar fila ordenada (heap) para armazenar as pessoas em ordem alfabética sempre que o usuário incluir uma nova pessoa.
-Implementar a base de dados da agenda usando lista duplamente ligada
-Somente essa base de dados pode ficar fora do buffer principal, ou seja, pode usar um malloc para cada nodo.
*/

#define MAX_NOME 20
#define MAX_IDADE 4
#define MAX_TELEFONE 16

//Espaco minimo para cadastro
#define PERSON ( sizeof(char) * MAX_NOME + sizeof(char) * MAX_IDADE + sizeof(char) * MAX_TELEFONE + sizeof(void **) * 2)

//Primeiro da Lista
#define TOP_OF_LIST ( sizeof(int) + sizeof(void **) )

//Ultimo da Lista
#define BACK_OF_LIST ( sizeof(int) )

//Aponta para o proximo
#define NEXT ((sizeof(char) * MAX_NOME) + (sizeof(char) * MAX_IDADE) + (sizeof(char) * MAX_TELEFONE) + sizeof(void **))

//Anterior
#define LAST ((sizeof(char) * MAX_NOME) + (sizeof(char) * MAX_IDADE) + (sizeof(char) * MAX_TELEFONE))

//Faz as operacoes
#define WORKER ( sizeof(void **) )

// %19[^\n]%*c | Pega apenas 20 caracter e pega os espacos

int menu();
void PUSH();
void POP();
void SEARCH();
void LIST();
void CLEAR();

int main(){

    //Aloca espaco para adicionar 1 pessoa.
    void *pBuffer = (void *)calloc( 1, sizeof(void **) + sizeof(int) + MAX_NOME * sizeof(char) );
    void *Sentinela = (void *)calloc( 1, sizeof(int) + sizeof(void **) * 2);

    if ( !pBuffer || !Sentinela){
        printf("Sem memoria disponivel para executar!");
        return (-1);
    }

    *(int *)Sentinela = 0;
    *(void **)(pBuffer) = NULL;
    *(void **)(Sentinela + sizeof(int) + sizeof(void **) ) = NULL;
    *(void **)(Sentinela + sizeof(int) ) = NULL;

        do{

            *(int *)(pBuffer + WORKER) = menu(pBuffer);

            switch ( *(int *)( pBuffer + WORKER ) ){
                case 1:

                    PUSH( pBuffer, Sentinela );

                    break;
                case 2:

                    POP( pBuffer, Sentinela );

                    break;
                case 3:

                    SEARCH( pBuffer, Sentinela );

                    break;
                case 4:

                    LIST( pBuffer, Sentinela );

                    break;
                case 5:

                    CLEAR(pBuffer, Sentinela);

                    *(int *)Sentinela = 0;
                    *(void **)(pBuffer) = NULL;
                    *(void **)(Sentinela + sizeof(int) + sizeof(void **) ) = NULL;
                    *(void **)(Sentinela + sizeof(int) ) = NULL;

                    break;
                case 0:

                    free(pBuffer);
                    free(Sentinela);

                    return 0;
            }

        } while ( *(int *)( pBuffer + WORKER ) != 0 );

    return 0;
}

int menu(void *pBuffer){

    *(int *)(pBuffer + WORKER) = 0;

    printf("\n\n1 - Adicionar");
    printf("\n2 - Apagar");
    printf("\n3 - Buscar");
    printf("\n4 - Listar");
    printf("\n5 - Limpar");
    printf("\n0 - Sair");
    printf("\nEscolha:");
    scanf("%d", &*(int *)(pBuffer + WORKER));
    getchar();

    return *(int *)(pBuffer + WORKER);

}

void PUSH( void *pBuffer, void *Sentinela ){

    void *Pointer;
    void *NEW_PERSON = (void *)malloc( PERSON );

    if ( !NEW_PERSON ){
        printf("\nSEM MEMORIA");
        return;
    }

    printf("#-- Nova pessoa --#");

    printf("\nNome: ");
    scanf("%19[^\n]%*c", (char *)NEW_PERSON );
    
    printf("\nIdade: ");
    scanf("%s", (char *)( NEW_PERSON + sizeof(char) * MAX_NOME ) );
    getchar();

    printf("\nTelefone: ");
    scanf("%s", (char *)( NEW_PERSON + (sizeof(char) * MAX_NOME) + (sizeof(char) * MAX_IDADE)) );
    getchar();

    *(void **)( NEW_PERSON + (sizeof(char) * MAX_NOME) + (sizeof(char) * MAX_IDADE) + (sizeof(char) * MAX_TELEFONE) ) = NULL;
    *(void **)( NEW_PERSON + (sizeof(char) * MAX_NOME) + (sizeof(char) * MAX_IDADE) + (sizeof(char) * MAX_TELEFONE) + sizeof(void **) ) = NULL;

    //Caso seja o primeiro a ser cadastrado
    if ( *(int *)Sentinela == 0 ){

        *(void **)( Sentinela + BACK_OF_LIST ) = NEW_PERSON;
        *(void **)( Sentinela + TOP_OF_LIST ) = NEW_PERSON;

        *(int *)Sentinela += 1;

        return;
    }

    pBuffer = *(void **)( Sentinela + TOP_OF_LIST );

    do{

        if ( strcmp( (char *)NEW_PERSON, (char *)pBuffer )  < 0 ){

            *(void **)(NEW_PERSON + LAST) = *(void **)(pBuffer + LAST);
            *(void **)(NEW_PERSON + NEXT) = pBuffer;

            if ( *(int *)Sentinela > 1 && *(void **)(pBuffer + LAST) != NULL ){

                Pointer = *(void **)(pBuffer + LAST);
                *(void **)(Pointer + NEXT) = NEW_PERSON;
            }

            *(void **)(pBuffer + LAST) = NEW_PERSON;

            if (*(void **)(NEW_PERSON + LAST) == NULL){
                *(void **)(Sentinela + TOP_OF_LIST) = NEW_PERSON;
            }

            *(int *)Sentinela += 1;
            return;
        }

        if (*(void **)(pBuffer + NEXT) == NULL){
            break;
        }

        pBuffer = *(void **)(pBuffer + NEXT);

    } while (pBuffer != NULL);

    *(void **)(NEW_PERSON + LAST) = pBuffer;
    *(void **)(pBuffer + NEXT) = NEW_PERSON;
    *(void **)(Sentinela + BACK_OF_LIST) = NEW_PERSON;

    *(int *)Sentinela += 1;
    return;
}

void POP( void *pBuffer, void *Sentinela ){

   void *WORKER3;

    if (*(int *)Sentinela == 0){
        printf("\nNinguém foi cadastrado ainda.\n");
        return;
    }

    printf("\nNome para ser removido da agenda: ");
    scanf("%19[^\n]%*c", (char *)(pBuffer + sizeof(void **) + sizeof(int)));
    

    void *TARGET = (char *)(pBuffer + (sizeof(void **) + sizeof(int)) );

    pBuffer = *(void **)(Sentinela + TOP_OF_LIST);

    do{
        if ( strcmp((char *)pBuffer, (char *)TARGET) == 0 ){

            if (*(void **)(pBuffer + LAST) != NULL){

                WORKER3 = *(void **)(pBuffer + LAST);

                *(void **)(WORKER3 + NEXT) = *(void **)(pBuffer + NEXT);

            } else{

                *(void **)(Sentinela + TOP_OF_LIST) = *(void **)(pBuffer + NEXT);

            }
            if (*(void **)(pBuffer + NEXT) != NULL){

                WORKER3 = *(void **)(pBuffer + NEXT);

                *(void **)(WORKER3 + LAST) = *(void **)(pBuffer + LAST);

            } else{

                *(void **)(Sentinela + BACK_OF_LIST) = *(void **)(pBuffer + LAST);

            }

            *(int *)Sentinela -= 1;

            free(pBuffer);
            
            printf("\nIndivíduo removido com sucesso.\n");
            return;
        }
        pBuffer = *(void **)(pBuffer + NEXT);

    } while (pBuffer != NULL);

    printf("\nNome não encontrado.\n");

    //free(TARGET);
}

void LIST( void *pBuffer, void *Sentinela ){

   if (*(int *)Sentinela == 0){
        printf("\nNinguém foi cadastrado ainda.\n");
        return;
    }

    pBuffer = *(void **)(Sentinela + TOP_OF_LIST);

    printf("\nCADASTROS ENCONTRADOS: %d\n", *(int *)Sentinela);

    do{

        printf("\n------------------\n\nNome: %s\nIdade: %s\nTelefone: %s\n\n",
               (char *)pBuffer,
                (char *)(pBuffer + MAX_NOME),
                 (char *)(pBuffer + MAX_NOME + MAX_IDADE)
                 );

        pBuffer = *(void **)(pBuffer + NEXT);

    } while (pBuffer != NULL);

    return;
}

void SEARCH( void *pBuffer, void *Sentinela ){

    if ( *(int *)Sentinela == 0 ){
        printf("\nNenhuma pessoa na agenda ainda.\n");
        return;
    }

    printf("\nNome da pessoa que deseja buscar: ");

    scanf("%19[^\n]%*c", (char *)(pBuffer + sizeof(void **) + sizeof(int)) );

    void *WORKER2 = ( pBuffer + sizeof(void **) + sizeof(int) );

    pBuffer = *(void **)(Sentinela + TOP_OF_LIST);

    while (pBuffer != NULL){

        if ( strcmp((char *) WORKER2, pBuffer ) == 0 ){

            printf("\n------------------\n\nNome: %s\nIdade: %s\nTelefone: %s\n------------------\n",
                   (char *)pBuffer,
                    (char *)(pBuffer + sizeof(char) * MAX_NOME),
                     (char *)(pBuffer + sizeof(char) * MAX_NOME + sizeof(char) * MAX_IDADE)
                     );

            return;
        } else{
            pBuffer = *(void **)(pBuffer + NEXT);
        }
    }
    printf("\nNome nao encontrado.\n");

    return;

}

void CLEAR( void *pBuffer, void *Sentinela ){

    void *WORKER2;

    pBuffer = *(void **)(Sentinela + TOP_OF_LIST);

    while (pBuffer != NULL){

        WORKER2 = *(void **)(pBuffer + NEXT);

        free(pBuffer);

        pBuffer = WORKER2;
    }

    
    printf("\nLista limpa com sucesso!.\n");

    return;
}

