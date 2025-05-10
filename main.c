// A importação das bibliotecas é feita no início do código
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mergesort.h"

// inicialização da função main
int main()
{

    char passo[100]; // criação do vetor de caracteres passo com tamanho 100

    FILE *fp = fopen("/home/fels/Documentos/POD/Trabalho1/dados.txt", "r"); // Abertura do arquivo em modo leitura
    if (fp == NULL)
    {                                         // verificação se o arquivo foi aberto de maneira correta
        printf("Erro ao abrir o arquivo.\n"); // caso não tenha sido, retorna erro e encerra o programa
        exit(1);
    }
    else{
        printf("Arquivo de dados aberto com sucesso.\n"); // caso tenha sido, imprime mensagem de sucesso
    }

    int m;                           // criação da variável m
    printf("Digite o valor de m: "); // solicitação do valor de m ao usuário para definir o tamanho do vetor
    scanf("%d", &m);
    if (m <= 0)
    {
        printf("Valor inválido para m. O programa será encerrado.\n"); // verificação se o valor de m é válido
        fclose(fp); // fechamento do arquivo
        exit(1);    // caso não seja, retorna erro e encerra o programa
    }
    

    int v[m];               // inicialização do vetor v com o tamanho definido por m
    int num = 0, ch, i = 0; // inicialização das variáveis num, ch e i

    while ((ch = fgetc(fp)) != EOF && i < m) // leitura do arquivo até preencher o vetor ou até finalizar o arquivo
    // fgetc lê um caractere do arquivo e retorna o valor lido
    {
        if (ch >= '0' && ch <= '9')
        {                                // verificação se o caractere lido é um número
            num = num * 10 + (ch - '0'); // conversão do caractere para inteiro
        }
        else if (ch == ';')
        { // verificação se o caractere lido é um ponto e vírgula se for o caso o numero é adicionado ao vetor
            v[i++] = num;
            num = 0;
        }
    }
    fclose(fp); // fechamento do arquivo após a leitura

    int numTxt = 0; // inicialização da variável numTxt

    while (numTxt < (m * 2))//while usado para criação dos arquivos sendo o dobro da variavel m fornecida
    {
        sprintf(passo, "/home/fels/Documentos/POD/Trabalho1/passo%d.txt", numTxt); // criação do nome do arquivo a ser aberto, de acordo com o número do passo

        FILE *nwfp = (fopen(passo, "w+")); // abertura do arquivo em modo leitura e escrita
        if (nwfp == NULL)
        {                                            // verificação se o arquivo foi aberto de maneira correta
            printf("Erro ao abrir o arquivo %s\n", passo); // caso não tenha sido, retorna erro e encerra o programa
            exit(1);
        }
        fclose(nwfp); // fechamento do arquivo após a leitura
        // A função sprintf é usada para formatar a string e armazená-la na variável passo
        numTxt++; // incremento da variável numTxt
    }
}
