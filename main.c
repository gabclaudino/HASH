#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "hash.h"

#define M 11
#define MAX 20

void main(){
    /*inicializa as 2 tabelas*/
    int v1[M];
    int v2[M];
    /*inicializa a tabela da juncao*/
    int v3[2*M];
    /*zera todas tabelas com -1*/
    zeraVetor(v1);
    zeraVetor(v2);
    zeraVetor2(v3);
    /*recebe a entrada*/
    char opcao;
    char *escolha;
    int valor;
    char vaux[MAX];
    while(fgets(vaux, MAX, stdin) != NULL)
    {
        opcao = vaux[0];
        escolha = malloc(sizeof(char)*(MAX-2));
        memcpy(escolha, vaux+2, MAX-2);
        valor = atoi(escolha);
        if(opcao == 'i')
            insereHash(valor,v1,v2);
        if(opcao == 'r')
            removeHash(valor,v1,v2);
        free(escolha);
    }
    /*faz a juncao das tabelas 1 e 2*/
    juntaVetor(v1,v2,v3);
    int x = 2*M;
    /*ordena o vetor da juncao das duas tabelas*/
    selection_sort(v3,x);
    /*imprime a saida*/
    imprimeHash(v1,v2,v3);
}