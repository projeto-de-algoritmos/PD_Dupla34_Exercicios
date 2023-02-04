#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

// Macros
#define FOR(i, j, k)for(int i=j;i<k;++i)
#define ii pair<int, int>
#define iii pair<int, ii >

/*
    x = linha
    y = coluna
    t = tempo
    dp[i][j][k] = numero maximo de maças que posso pegar a partir da posicao (j, k) no tempo i
*/
vector<int> mys[3];
int dp[110][110][110];

// função para resolver o problema
short solve(int q0, int q1, int q2)
{
    // se eu cheguei no final, retorno 1
    if (q0==mys[0].size() && q1==mys[1].size() && q2==mys[2].size())
        return 1;

    // se eu cheguei no final de alguma pilha, retorno 0
    if (q0>mys[0].size() || q1>mys[1].size() || q2>mys[2].size())
        return 0;

    // se ja calculei, retorno o valor
    if (dp[q0][q1][q2] != -1)
        return dp[q0][q1][q2];

    
    /*
        ans = resposta
        item0 = tamanho da pilha 0
        item1 = tamanho da pilha 1
        item2 = tamanho da pilha 2
        myv = vetor com todas as possibilidades de retirar uma pilha
    */
    short ans = 0;
    int item0=mys[0][q0], item1=mys[1][q1], item2=mys[2][q2];
    vector<iii> myv {iii(1,ii(0,0)),iii(0,ii(1,0)),iii(0,ii(0,1)),iii(1,ii(1,0)),iii(1,ii(0,1)),iii(0,ii(1,1)),iii(1,ii(1,1)) };
    
    // para cada possibilidade, vejo se eh multiplo de 3
    for (auto it : myv) {
        int idx = 0;

        // se eu pego a pilha 0, adiciono o tamanho dela
        if (it.first) {
            idx+=item0;
        }

        // se eu pego a pilha 1, adiciono o tamanho dela
        if (it.second.first) {
            idx+=item1;
        }

        // se eu pego a pilha 2, adiciono o tamanho dela
        if (it.second.second) {
            idx+=item2;
        }

        // se for multiplo, adiciono a resposta
        if (idx%3==0) {
            // printf("idx %d eh multiplo!!!\n", idx);
            ans=max(ans, solve(q0+it.first, q1+it.second.first, q2+it.second.second));
        }
            // printf("idx %d nao multiplo..\n", idx);
    }

    // retorno a resposta e salvo no dp para nao calcular novamente
    return dp[q0][q1][q2] = ans;
}

int main()
{
    /*
        n = numero de pilhas
        a = tamanho da pilha 0
        b = tamanho da pilha 1
        c = tamanho da pilha 2
    */
    int n, a, b, c;

    // leio o numero de pilhas
    while (scanf("%d", &n) != EOF) {

        // se for 0, termino o programa
        if (not n)
            return 0;

        // limpo os vetores e o dp
        mys[0].clear();
        mys[1].clear();
        mys[2].clear();
        memset(dp, -1, sizeof dp);

        // leio os tamanhos das pilhas
        FOR(i, 0, n) {
            scanf("%d", &a);
            scanf("%d", &b);
            scanf("%d", &c);
            mys[0].push_back(a);
            mys[1].push_back(b);
            mys[2].push_back(c);
        }

        // chamo a função para resolver o problema
        printf("%d\n", solve(0,0,0));
    }

    return 0;
}