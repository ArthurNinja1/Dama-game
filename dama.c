/**********************************************
Código de autoria de: Arthur Andriolli Hilario
Inicio 19/03/26

a trabalhar ainda:{
    melhorar sistema de movimento.
    mover apenas a frente.
    sistema captura de peças.
    condição de vitória.
    melhorar e otimizar código.
    melhor interface.
    limitar o acesso da matriz.
    tratamento de erro.
}
***********************************************/

#include <stdio.h>

#define TAMANHO 8 // define constante do tamanho

char tabuleiro[TAMANHO][TAMANHO]; // cria o tabuleiro

// -------------- TABULEIRO_INICIADOR -------------//
void organizador(char tabuleiro[TAMANHO][TAMANHO]){
    int linha, coluna;

    for (linha = 0; linha < TAMANHO; linha++) {
        for (coluna = 0; coluna < TAMANHO; coluna++) {
            
            // testa as posições, e coloca as peças
            if (linha < 3 && (linha + coluna) % 2 == 1) {
                // peças pretas(black)
                tabuleiro[linha][coluna] = 'B';

            } else if (linha > 4 && (linha + coluna) % 2 == 1) {
                // peças brancas(white)
                tabuleiro[linha][coluna] = 'W';

            } else {
                // as casas vazias
                tabuleiro[linha][coluna] = '.';
            }
        }
    }
}


// -------------- TABULEIRO_MOSTRAR -------------//
void mostrar_tabuleiro(char tabuleiro[TAMANHO][TAMANHO]) {
    int linha, coluna;

    // organiza as cordenada das colunas
    printf("\n  ");
    for (coluna = 0; coluna < TAMANHO; coluna++) {
        printf("%d ", coluna + 1);
    }
    printf("\n");
    printf("  ");

    // divisão para ficar mais organizado
    for (coluna = 0; coluna < TAMANHO; coluna++) {
        printf("- ");
    }
    printf("\n");

    // organiza cordenadas de linhas e cria uma divisão
    for (linha = 0; linha < TAMANHO; linha++) {
        printf("%d|", linha + 1);
        for (coluna = 0; coluna < TAMANHO; coluna++) {
            printf("%c ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    } 
}

// -------------- MOVIMENTAÇÂO -------------//
//inicia a função e recebe as variaveis importante de funcionamento
int movimento(char tabuleiro[TAMANHO][TAMANHO],
              int linha_atual, int coluna_atual,
              int linha_destino, int coluna_destino,
              char jogador) {

    //checa se a peça é do jogador atual
    if (tabuleiro[linha_atual][coluna_atual] != jogador) {
        printf("\nErro: não há peça sua nessa posição!\n");
        return 0;//retorna 0, e fecha a função sem passar o turno
    }

    //checa se o destino tá ocupado
    if (tabuleiro[linha_destino][coluna_destino] != '.') {
        printf("\nErro: destino ocupado!\n");
        return 0;//retorna 0, e fecha a função sem passar o turno
    }

    //variaveis para verificar se está movendo apenas 1 casa
    int verifica_linha = linha_destino - linha_atual;
    int verifica_coluna = coluna_destino - coluna_atual;

    //verifica se ira mover apenas uma casa, distancia==1
    if ((verifica_linha == 1 || verifica_linha == -1) &&
    (verifica_coluna == 1 || verifica_coluna == -1)) {

        //coloca a peça na casa de destino
        tabuleiro[linha_destino][coluna_destino] = tabuleiro[linha_atual][coluna_atual];

        //desocupa a casa anterior
        tabuleiro[linha_atual][coluna_atual] = '.';
        return 1; //retorna 1, oque valida o if para passar o turno
    }

    printf("\nerro: movimento invalido!\n");
    return 0; //retorna 0, fecha a função sem passar o turno
}

// -------------- GAMEPLAY -------------//
int main() {
    //declaração de variavel de jogo
    int linha_atual, coluna_atual, linha_destino, coluna_destino;
    char jogador = 'B';

    //organiza o tabuleiro para inicio de jogo
    organizador(tabuleiro);

    //loop dos turnos de jogo
    while (1) {

        //mostra a interface do tabuleiro
        mostrar_tabuleiro(tabuleiro);

        //escaneia a peça desejada do jogador para mover
        printf("\njogador (%c): digite linha e coluna da peça a mover: ", jogador);
        scanf("%d %d", &linha_atual, &coluna_atual);

        //escaneia a casa de destino do jogador
        printf("jogador (%c): digite linha e coluna de destino: ", jogador);
        scanf("%d %d", &linha_destino, &coluna_destino);

        //pequeno ajuste de acessibilidade das cordenadas
        linha_atual --; coluna_atual --;
        linha_destino --; coluna_destino --;

        //se a função de movimento retornar 1, passa o turno ao próximo jogador
        if (movimento(tabuleiro, linha_atual, coluna_atual, linha_destino, coluna_destino, jogador)) {
                // alterna jogador, jogador recebe w se for igual a B, e não, recebe B
                jogador = (jogador == 'B') ? 'W' : 'B';
        }
    }
}