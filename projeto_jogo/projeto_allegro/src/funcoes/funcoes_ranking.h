#pragma once

#include <stdbool.h>

typedef struct sPlayer {
    char nome[50];
    int pontuacao;
} player;

typedef struct sRanking {
    player players[5];
    int tam;
} ranking;

void shellSort(player* players, int size);
void selectSort(player* players, int size);
void insertSort(player* players, int size);
int lerArquivo(player* players);
void escreveArquivo(player* players, int size);