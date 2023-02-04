#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

// Macros
#define FOR(i, j, k)for(int i=j;i<k;++i)
#define ii pair<int, int>

/*
    x = linha
    y = coluna
    t = tempo
    dp[i][j][k] = numero maximo de maças que posso pegar a partir da posicao (j, k) no tempo i
*/
int x[1005];
int y[1005];
int t[1005];
int dp[1005][22][22];

int main()
{
    /*
        n = numero de linhas
        m = numero de colunas
        k = numero de maças
        x_pos = linha da posicao inicial
        y_pos = coluna da posicao inicial
    */ 
    int n, m, k, x_pos, y_pos;

    // leio o numero de linhas, colunas, maças e posicao inicial
    while (cin >> n >> m >> k) {

        // se nao tiver linhas, colunas ou maças, termino o programa
        if (not(n|m|k))
            return 0;

        // leio as maças
        FOR(i, 0, k) {
            scanf("%d", &x[i]);
            scanf("%d", &y[i]);
            scanf("%d", &t[i]);
            x[i] -= 1;
            y[i] -= 1;
        }

        // leio a posicao inicial
        scanf("%d", &x_pos);
        scanf("%d", &y_pos);
        memset(dp, 0, sizeof dp);

        // as maças estao em tempo crescente
        // caso base eh que no ultimo tempo (que no caso é t[k-1])
        // a resposta é 1 se ha uma maçã em x, y com tempo t[i],
        // ou 0 se nao tiver maçã lá
        for (int i=k-1; i>=0; i--) {
            if (t[i] != t[k-1]) {
                break;
            } else {
                dp[t[i]][x[i]][y[i]] = 1;
            }
        }

        // vou de trás pra frente, pois a resposta é a maior quantidade de maças
        for (int idx=(t[k-1]-1); idx>=0; idx--) {

            // vou percorrer todas as posições possíveis
            FOR(linha, 0, n) {
                FOR(coluna, 0, m) {
                    vector<ii> myv { make_pair(linha+1, coluna), make_pair(linha+1, coluna-1), make_pair(linha+1, coluna+1),
                        make_pair(linha-1, coluna), make_pair(linha-1, coluna+1), make_pair(linha-1, coluna-1),
                        make_pair(linha, coluna), make_pair(linha, coluna+1), make_pair(linha, coluna-1) };
                    
                    // vou pegar a maior quantidade de maças que posso pegar
                    int sol = 0;
                    for (auto pos : myv) {
                        if (pos.first < 0 || pos.second < 0 || pos.first >= n || pos.second >= m)
                            continue;
                        sol = max(sol, dp[idx+1][pos.first][pos.second]);
                    }

                    // percorro as maças
                    for (int maca=k-1; maca >= 0; maca--) {

                        // se a maçã estiver na posição (linha, coluna) e no tempo idx, eu adiciono 1
                        if (x[maca] == linha && y[maca] == coluna && t[maca] == idx) {
                            sol += 1;
                            break;
                        }
                        // se a maçã estiver no tempo idx, eu paro de procurar
                        else
                        if (t[maca] < idx)
                            break;
                    }
                    // a resposta é a maior quantidade de maças que posso pegar a partir da posição (linha, coluna) no tempo idx
                    dp[idx][linha][coluna] = sol;
                }
            }
        }

        // imprimo a resposta
        printf("%d\n", dp[0][x_pos-1][y_pos-1]);
    }
    return 0;
}