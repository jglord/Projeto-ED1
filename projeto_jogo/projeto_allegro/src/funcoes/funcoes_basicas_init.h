#pragma once

// Bibliotecas da ALLEGRO 5
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#include "funcoes_estruturas.h"

#define FPS 60.0
#define LARGURA_TELA 800
#define ALTURA_TELA 600
#define POS_INICIAL_BONECO 420
#define ALTURA_MAXIMA_PULO 250

typedef struct sprite {
    //largura e altura de cada sprite dentro da folha
    int altura_sprite, largura_sprite;
    //quantos sprites tem em cada linha da folha, e a atualmente mostrada
    int colunas_folha, coluna_atual;
    //quantos sprites tem em cada coluna da folha, e a atualmente mostrada
    int linha_atual, linhas_folha;
    //posicoes X e Y da folha de sprites que serao mostradas na tela
    int regiao_x_folha, regiao_y_folha;
    //quantos frames devem se passar para atualizar para o proximo sprite
    int frames_sprite, cont_frames;
    //posicao X Y da janela em que sera mostrado o sprite
    double pos_x_sprite, pos_y_sprite;
    //velocidade X Y que o sprite ira se mover pela janela
    double vel_x_sprite, vel_y_sprite;
} tSprite;

// Exibe uma mensagem de erro na tela e diz qual foi o problema
void error_msg(char* text, ALLEGRO_DISPLAY* window);

// Inicializa a aplicação
bool inicializarSprite(ALLEGRO_DISPLAY** window, 
                 ALLEGRO_TIMER** timer1,
                 ALLEGRO_EVENT_QUEUE** fila_eventos,
                 ALLEGRO_BITMAP** folha_sprites_personagem,
                 ALLEGRO_BITMAP** folha_sprites_inimigo,
                 ALLEGRO_BITMAP** fundo,
                 ALLEGRO_BITMAP** gameOver

                );

bool initAllegro();

bool inicializarWindow(ALLEGRO_DISPLAY** window);

bool carregarImgP(ALLEGRO_DISPLAY** window, ALLEGRO_BITMAP** img, float px, float py);

char* catPath(char* path);

bool inicializaCoracoesMorte(ALLEGRO_BITMAP **coracoes, ALLEGRO_DISPLAY **window);
bool inicializaCoracoesVida(tElemento* cabeca, ALLEGRO_DISPLAY **window);