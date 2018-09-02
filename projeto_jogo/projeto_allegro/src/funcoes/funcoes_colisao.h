#pragma once
#ifndef PROJETO_ALLEGRO_FUNCOES_COLISAO_H
#define PROJETO_ALLEGRO_FUNCOES_COLISAO_H

#endif //PROJETO_ALLEGRO_FUNCOES_COLISAO_H

#include "funcoes_anim.h"

typedef struct retangulo {
    int X, Y; // Posicao
    int W, H; // Largura e Altura
} tRetangulo;

// Gera um retangulo que irá ser usado no teste de colisão
tRetangulo gerarRetangulo(tSprite* personagem);
// Testa se há colisão entre dois retangulos
bool colisao(tRetangulo A, tRetangulo B);
// Trata as diferentes maneiras de dois retangulos se colidirem
void tratamentoDeColisao(tSprite* boneco, tSprite* inimigo);
