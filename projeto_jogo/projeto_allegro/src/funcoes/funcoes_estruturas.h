#pragma once

// Bibliotecas da ALLEGRO 5
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

typedef struct sElemento {
    int id;
    ALLEGRO_BITMAP* img;
    struct sElemento* proxElemento;
} tElemento;

tElemento* inicializarListaComCabeca();
void inserirElementoInicio(tElemento* cabeca, ALLEGRO_BITMAP** img);
bool verificarVidas(tElemento* cabeca);      // Percorre a lista, exibe os itens e retorna a quantidade;
tElemento* removerFinalLista(tElemento *cabeca);
ALLEGRO_BITMAP* retornarImgLista(tElemento*cabeca, int idBuscado);