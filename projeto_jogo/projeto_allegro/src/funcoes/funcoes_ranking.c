#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "funcoes_ranking.h"


void shellSort(player* players, int size) {

    int h = 1;
    int i, j;
    player eleito;

    while(h < size) {
        h = 3 * h + 1;
    }

    while(h > 1) {
        h = h / 3;

        for(i = h; i < size; i++) {
            eleito = players[i];
            j = i - h;

            while (j >= 0 && eleito.pontuacao > players[j].pontuacao) {
                players[j + h] = players[j];
                j = j - h;
            }
            players[j + h] = eleito;
        }
    }
}

void selectSort(player* players, int size) {

    int i, j;
    int menor;
    player temporario;

    for(i = 0; i < size - 1; i++) {
        menor = i;
        for(j = i + 1; j < size - 1; j++) {
            if( players[j].pontuacao < players[menor].pontuacao ) {
                menor = j;
            }
        }

        if( i != menor ) {
            temporario = players[i];
            players[i] = players[menor];
            players[menor] = temporario;
        }
    }
}

void insertSort(player* players, int size) {
    int i, j;
    player eleito;

    for(i = 1; i < size-1; i++) {
        eleito = players[i];
        j = i -1;

        while( j>=0 && eleito.pontuacao < players[j].pontuacao ) {
            players[j+1] = players[j];
            j--;
        }
        players[j+1] = eleito;
    }

}

int lerArquivo(player* players) {
    FILE* arquivo = fopen("/home/jglord/Workspace/Projeto-ED1/projeto_jogo/projeto_allegro/src/funcoes/ranking.bin", "r");

    if(arquivo == NULL) {
        printf("Erro ao abrir arquivo!");
        return 0;
    }

    int tam = 0;
    while( fscanf( arquivo, "%s %i\n", players[tam].nome, &players[tam].pontuacao ) != EOF ){
        tam++;
    }

    fclose(arquivo);

    return tam;
}

void escreveArquivo(player* players, int size) {
    FILE* arquivo = fopen("/home/jglord/Workspace/Projeto-ED1/projeto_jogo/projeto_allegro/src/funcoes/ranking.bin", "w");

    int i;
    for(i = 0; i < size; i++) {
        fprintf(arquivo, "%s %i\n",players[i].nome, players[i].pontuacao );
    }
    fclose(arquivo);

}