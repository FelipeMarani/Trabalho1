#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mergesort.h"

int merge(int v[], int l, int r)
{

    int i, j, k, m;
    m = (l + r) / 2;      // cálculo do ponto médio do vetor
    int size = r - l + 1; // tamanho do vetor a ser mesclado
    i = l;                // inicialização do índice i para a metade esquerda
    j = m + 1;            // inicialização do índice j para a metade direita
    k = 0;                // inicialização do índice k para o vetor temporário
    if (l >= r)
    {
        return 0; // caso o vetor tenha apenas um elemento ou esteja vazio, não há nada a fazer
    }

    int *temp = malloc(size * sizeof(int)); // alocação de memória para o vetor temporário
    if (temp == NULL)                       // verificação se a alocação foi bem sucedida
    {
        printf("Erro ao alocar memória.\n");
        return -1; // erro na alocação de memória
    }

    while (i <= m && j <= r)
    {
        if (v[i] < v[j])
        {
            temp[k++] = v[i++]; // se o elemento da esquerda for menor, adiciona ao vetor temporário
        }
        else
        {
            temp[k++] = v[j++]; // se o elemento da direita for menor, adiciona ao vetor temporário
        }
    }
    while (i <= m)
    {
        temp[k++] = v[i++]; // adiciona os elementos restantes da esquerda ao vetor temporário
    }
    while (j <= r)
    {
        temp[k++] = v[j++]; // adiciona os elementos restantes da direita ao vetor temporário
    }

    for (i = l, k = 0; i <= r; i++, k++) // copia os elementos do vetor temporário de volta para o vetor original
    {
        v[i] = temp[k];
    }

    free(temp); // libera a memória alocada para o vetor temporário
    return 0;   // retorna 0 para indicar que a função foi executada com sucesso
}

int mergesort(int v[], int l, int r)
{
    if (l >= r)
    {
        return 0; // caso o vetor tenha apenas um elemento ou esteja vazio, não há nada a fazer
    }
    int m = (l + r) / 2;    // cálculo do ponto médio do vetor
    mergesort(v, l, m);     // chamada recursiva para a metade esquerda do vetor
    mergesort(v, m + 1, r); // chamada recursiva para a metade direita do vetor
    merge(v, l, r);         // chamada para a função de mesclagem
    return 0;               // retorna 0 para indicar que a função foi executada com sucesso
}
