#pragma once

#include "funcoes_basicas_init.h"

void variaveisBoneco(tSprite* boneco);
void variaveisInimigo(tSprite* inimigo);
void mudarSprite(tSprite* boneco);
void desenhaPersonagem(tSprite *personagem, ALLEGRO_BITMAP *folha_sprites_personagem);
void gameOver(ALLEGRO_BITMAP** gameOver);