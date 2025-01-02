#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"

#define M 11


/*funcao hash h1*/
int h1(int k){
    return (k % M);
}


/*funcao hash h2*/
int h2(int k){
    int temp1 = floor(k * 0.9);
    int temp2 = floor(M * (k * 0.9 - temp1));
    return temp2;
}


/*selection sort usado para ordenar o vetor
e facilitar a saida*/
void selection_sort (int vetor[],int max) {
  int i, j, min, aux;
  
  for (i = 0; i < (max - 1); i++) {
    min = i;
    for (j = i+1; j < max; j++) {
      if (vetor[j] < vetor[min]) {
   min = j;
      }
    }
    if (i != min) {
      aux = vetor[i];
      vetor[i] = vetor[min];
      vetor[min] = aux;
    }
  }
}

/*inicializa as tabelas hash com -1 para 
informar que esta vazio*/
void zeraVetor(int v[]){
    int i;
    for(i=0; i<M; i++)
        v[i] = -1;
}

/*inicializa com -1 a juncao das duas tabelas
hash para depois ordenala com o selection sort*/
void zeraVetor2(int v[]){
    int i;
    for(i=0; i<(2*M); i++)
        v[i] = -1;
}


/*juntas as duas tabelas hash em um so vetor*/
void juntaVetor(int v1[], int v2[], int v3[]){
    int i;
    for(i=0; i<M; i++)
    {
        v3[i] = v1[i];
        v3[i+M] = v2[i];
    }
}

/*realiza a busca pelo indice da chave na tabela hash*/
int BuscaHash(int k, int v1[], int v2[]){
    /*se for -1 significa vazio, a chave nao existe*/
    if(v1[h1(k)] == -1)
        return -1;
    /*se o valor no indice for igual ao da funcao h1 retorna o indice 
    da primeira tabela hash*/
    else if(v1[h1(k)] == k)
        return(h1(k));
    /*se o valor no indice for igual o da funcao h2 retora o
    indice da segunda tabela hash*/
    else if(v2[h2(k) == k])
        return(h2(k));
    /*ultima opcao possivel eh o valor ter sido deletado e marcado com -2
    assim retorna -1 para mostrar que o valor nao existe mais*/
    else
        return -1;
}


/*funcao de inserir no hash*/
void insereHash(int k, int v1[], int v2[]){
    /*se a posicao estiver com -1(vazio) ou -2(excluido) ele salva o valor no indice*/
    if((v1[h1(k)] == -1) || (v1[h1(k)] == -2))
        v1[h1(k)] = k;
    else
    {
        /*caso ja esteja ocupado aplica a propiedade do cuckoo hash e 
        joga a chave antiga para segunda tabela hash e salva a nova na primeira*/
        int temp = h1(k);
        v2[h2(v1[temp])] = v1[temp];
        v1[h1(k)] = k;
    }
}


/*funcao de remover do hash*/
void removeHash(int k, int v1[], int v2[]){
    /*faz a busca na primeira tabela hash e substitui por -2*/
    if(v1[BuscaHash(k,v1,v2)] == k)
        v1[BuscaHash(k,v1,v2)] = -2;
    /*caso nao esteja na primeira, busca na segunda e substitui por -2*/
    else
        v2[BuscaHash(k,v1,v2)] = -2;
}


/*imprime a saida conforme planejado*/
void imprimeHash(int v1[], int v2[], int v3[]){
    int i;
    for (i=0; i<(2*M); i++)
    {
        /*como vetor esta ordenado, busca os valores != de -1 e -2 e imprime seu valor,
        em qual tabela esta e seu indice na tabela*/
        if ((v3[i] != -1) && (v3[i] != -2))
        {
            int temp = BuscaHash(v3[i],v1,v2);
            /*verifica em qual tabela o valor esta*/
            if(v3[i] == v1[temp])
                printf("%d,T1,%d\n", v3[i], temp);
            else
                printf("%d,T2,%d\n", v3[i], temp);
        }
    }
}

/*funcao auxiliar usada apenas para testes*/
void imprimevetor(int v[]){
    int i;
    for(i=0; i<M; i++)
        printf("%d ", v[i]);
    printf("\n");
}

/*funcao auxiliar usada apenas para testes*/
void imprimevetor2(int v[]){
    int i;
    for(i=0; i<(2*M); i++)
        printf("%d ", v[i]);
    printf("\n");
}


