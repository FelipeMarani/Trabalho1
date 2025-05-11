// A importação das bibliotecas é feita no início do código
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void mergePassos(const char *comp1, const char *comp2, const char *ext){

    FILE *op1 = fopen(comp1, "r"); // Abertura do arquivo em modo leitura
    FILE *op2 = fopen(comp2, "r"); // Abertura do arquivo em modo leitura
    FILE *out = fopen(ext, "w+"); // Abertura do arquivo em modo leitura e escrita

    if (!op1 || !op2 || !out)// vericação se os arquivos foram abertos corretamente
    {
        printf("Erro ao abrir os arquivos.\n"); // caso não tenha sido, retorna erro e encerra o programa
        exit(1);
    }

    int a, b;
    int aV = fscanf(op1, "%d", &a); // leitura do primeiro arquivo
    int bV = fscanf(op2, "%d", &b); // leitura do segundo arquivo
    while (aV == 1 && bV == 1)// enquanto os dois arquivos tiverem números
    {
        if (a < b)
        {
            fprintf(out, "%d ", a); // se o número do primeiro arquivo for menor, escreve no arquivo de saída
            aV = fscanf(op1, "%d", &a); // lê o próximo número do primeiro arquivo
        }
        else
        {
            fprintf(out, "%d ", b); // se o número do segundo arquivo for menor, escreve no arquivo de saída
            bV = fscanf(op2, "%d", &b); // lê o próximo número do segundo arquivo
        }
        
    }
    while(aV == 1)//enquanto o primeiro arquivo tiver numeros
    {
        fprintf(out, "%d ", a);// escreve o número no arquivo de saída
        aV = fscanf(op1, "%d", &a); // lê o próximo número do primeiro arquivo
    }
    while(bV == 1)//enquanto o segundo arquivo tiver numeros
    {
        fprintf(out, "%d ", b); // escreve o número no arquivo de saída
        bV = fscanf(op2, "%d", &b); // lê o próximo número do segundo arquivo
    }
    fclose(op1); // fechamento do arquivo após a leitura
    fclose(op2); // fechamento do arquivo após a leitura
    fclose(out); // fechamento do arquivo após a leitura
    printf("Arquivos mesclados com sucesso.\n"); // caso tenha sido, imprime mensagem de sucesso
    printf("Arquivo de saída: out.txt"); // imprime o nome do arquivo de saída
    
}

void mergeAll(int ttPassos){   // função para mesclar todos os arquivos
     int t = 0;// inicialização do número de arquivos a serem mesclados
     int qtd = ttPassos;// quantidade de arquivos a serem mesclados
     char comp1[100], comp2[100], ext[100];// vetores de caracteres para os nomes dos arquivos

     while (qtd > 1)
     {
        int nw = 0; // inicialização do número de arquivos a serem mesclados
        for (int i = 0; i < qtd; i += 2)//loop para mesclar os arquivos
        {
            sprintf(comp1, "/home/fels/Documentos/POD/Trabalho1/passo%d.txt", t == 0 ? "passo" : "merge", i);// criação do nome do arquivo a ser aberto, de acordo com o número do passo
            sprintf(comp2, "/home/fels/Documentos/POD/Trabalho1/passo%d.txt", t == 0 ? "passo" : "merge", i + 1);// criação do nome do arquivo a ser aberto, de acordo com o número do passo

            FILE *tst = fopen(comp2, "r"); // Abertura do arquivo em modo leitura
            if (!tst)// verificação se o arquivo foi aberto de maneira correta
            {
              fclose(fopen(comp1, "r"));// fechamento do arquivo
              sprintf(ext, "/home/fels/Documentos/POD/Trabalho1/Merge%d.txt", nw);// criação do nome do arquivo a ser aberto, de acordo com o número do passo
              rename(comp1, ext);// renomeia o arquivo
              continue;// continua o loop
            }
            fclose(tst);// fechamento do arquivo
            sprintf(ext, "/home/fels/Documentos/POD/Trabalho1/Merge%d.txt", nw++);// criação do nome do arquivo a ser aberto, de acordo com o número do passo
            mergePassos(comp1, comp2, ext);// chamada da função mergePassos para mesclar os arquivos
        }
        qtd = (qtd + 1) / 2; // atualização da quantidade de arquivos a serem mesclados
        t++;// incremento do número de arquivos a serem mesclados

     }

     rename("/home/fels/Documentos/POD/Trabalho1/Merge0.txt", "home/fels/Documentos/POD/Trabalho1/out.txt");// renomeia o arquivo final
     printf("Arquivo final: out.txt\n"); // imprime o nome do arquivo final
     printf("Mesclagem concluída com sucesso.\n"); // imprime mensagem de sucesso
     
}

// inicialização da função main
int main()
{

    char passo[100]; // criação do vetor de caracteres passo com tamanho 100             // inicialização do vetor v com o tamanho definido por m
    int num = 0, ch, i = 0;
    int numTxt = 0; // inicialização das variáveis num, ch e i

    FILE *fp = fopen("/home/fels/Documentos/POD/Trabalho1/dados.txt", "r"); // Abertura do arquivo em modo leitura
    if (fp == NULL)
    {                                         // verificação se o arquivo foi aberto de maneira correta
        printf("Erro ao abrir o arquivo.\n"); // caso não tenha sido, retorna erro e encerra o programa
        exit(1);
    }
    else
    {
        printf("Arquivo de dados aberto com sucesso.\n"); // caso tenha sido, imprime mensagem de sucesso
    }

    int m;                           // criação da variável m
    printf("Digite o valor de m: "); // solicitação do valor de m ao usuário para definir o tamanho do vetor
    scanf("%d", &m);
    if (m <= 0)
    {
        printf("Valor inválido para m. O programa será encerrado.\n"); // verificação se o valor de m é válido
        fclose(fp);                                                    // fechamento do arquivo
        exit(1);                                                       // caso não seja, retorna erro e encerra o programa
    }
    int v[m];

    while ((ch = fgetc(fp)) != EOF) // leitura do arquivo
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

        if (i == m)
        {
            mergesort(v, 0, m - 1);                                                      // chamada da função mergesort para ordenar o vetor
            sprintf(passo, "/home/fels/Documentos/POD/Trabalho1/passo%d.txt", numTxt++); // criação do nome do arquivo a ser aberto, de acordo com o número do passo
            FILE *nw = fopen(passo, "w+");                                               // abertura do arquivo em modo leitura e escrita
            for (int j = 0; j < i; j++)
            {
                fprintf(nw, "%d ", v[j]); // impressão do vetor ordenado
            }
            fclose(nw); // fechamento do arquivo após a leitura
            i = 0;      // reinicialização do índice i para o próximo vetor
        }
    }
    if (i > 0) // verificação se o vetor tem elementos restantes
    {
        mergesort(v, 0, i - 1);                                                      // chamada da função mergesort para ordenar o vetor
        sprintf(passo, "/home/fels/Documentos/POD/Trabalho1/passo%d.txt", numTxt++); // criação do nome do arquivo a ser aberto, de acordo com o número do passo
        FILE *nw = fopen(passo, "w+");                                               // abertura do arquivo em modo leitura e escrita
        for (int j = 0; j < i; j++)
        {
            fprintf(nw, "%d ", v[j]); // impressão do vetor ordenado
        }
    }

    fclose(fp); // fechamento do arquivo após a leitura
    mergeAll(numTxt); // chamada da função mergeAll para mesclar os arquivos
    return 0;   // retorno da função main
}
