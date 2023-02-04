#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /*
        N = numero de dias
        I = indice do primeiro dia
        M = numero de tipos de vodka
        P = preco da vodka
        C = custo de producao de cada tipo de vodka
        V = quantidade de vodka produzida por dia de cada tipo de vodka
        S = tabela de solucoes
        T = tabela de decisoes
        i = variavel auxiliar
        j = variavel auxiliar
        v1 = variavel auxiliar
        v2 = variavel auxiliar
        flag = variavel auxiliar
    */
    int N, I, M, P, C[2000], V[2001], **S, **T, i, j, v1, v2, flag;
    
    // leitura dos dados
    while (scanf("%d %d %d %d", &N, &I, &M, &P) != EOF)
    {
        // leitura dos dados
        for (i = 0; i < M; i++)
            scanf("%d", &C[i]);
        
        // leitura dos dados
        for (i = 1; i <= M; i++)
            scanf("%d", &V[i]);
        
        // inicializacao da tabela de solucoes
        S = (int **)malloc((N + 2) * sizeof(int *));
        for (i = 1; i <= N + 1; i++)
            S[i] = (int *)malloc((M + 1) * sizeof(int));

        // inicializacao da tabela de decisoes
        T = (int **)malloc((N + 2) * sizeof(int *));
        for (i = 1; i <= N + 1; i++)
            T[i] = (int *)malloc((M + 1) * sizeof(int));
        
        // calculo da tabela de solucoes
        for (j = 0; j <= M; j++)
            S[N + 1][j] = 0;
        for (i = N; i >= 1; i--)
        {
            for (j = 0; j < M; j++)
            {
                v1 = P + C[0] - V[j] + S[i + 1][1]; //caso j = 0
                v2 = C[j] + S[i + 1][j + 1]; //caso j > 0

                // escolha da melhor solucao
                if (v1 <= v2)
                {
                    S[i][j] = v1;
                    T[i][j] = 1;
                }
                else
                {
                    S[i][j] = v2;
                    T[i][j] = 0;
                }
            }
            v1 = P + C[0] - V[j] + S[i + 1][1]; //caso j = M
            S[i][j] = v1; // caso j = M
            T[i][j] = 1; // caso j = M
        }

        // impressao da solucao
        printf("%d\n", S[1][I]);
        flag = 1;

        // impressao da tabela de decisoes
        for (i = 1, j = I; i <= N; i++)
        {
            if (T[i][j] == 1)
            {  
                if (!flag)
                    printf(" ");
                flag = 0;
                printf("%d", i);
                j = 1;
            }
            else
                j++;
        }
        if (flag)
            printf("0");
        printf("\n");

        // liberacao da memoria
        for (i = 1; i <= N + 1; i++)
            free(S[i]);
        free(S);
        for (i = 1; i <= N + 1; i++)
            free(T[i]);
        free(T);
    }
    return 0;
}
