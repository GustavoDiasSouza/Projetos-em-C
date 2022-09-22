#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

    char *p;

    p = (char *) malloc(sizeof(char) * 10);

    printf("Nome:");
    scanf("%s",p);

    for(int i = 0; i < strlen(p); i++ ){

        printf("%c",p[i]);
    }
    printf("\n");

    strcat(p, ",");

    printf(p);



	system("pause");
	free(p);
}