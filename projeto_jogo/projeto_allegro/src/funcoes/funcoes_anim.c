#include "funcoes_anim.h"


void mudarSprite(tSprite* boneco) {
    // Se alcancar a quantidade de frames necessaria pra mudar o sprite
    if(boneco->cont_frames >= boneco->frames_sprite) {

        // Reseta o contador de frames e incrementa a coluna 
        // atual da folha pra mostrar o proximo sprite
        boneco->cont_frames = 0;
        boneco->coluna_atual++;

        // Se chegou na ultima coluna da folha de sprites
        if( boneco->coluna_atual >= boneco->colunas_folha) {
            // Coluna inicial
            boneco->coluna_atual = 0;

            //incrementa a linha, se passar da ultima, volta pra primeira
            boneco->linha_atual = (boneco->linha_atual+1) % boneco->linhas_folha;
            
            //calcula a posicao Y da folha que sera mostrada
            boneco->regiao_y_folha = boneco->linha_atual * boneco->altura_sprite;
        }
        //calcula a regiao X da folha que sera mostrada
        boneco->regiao_x_folha = boneco->coluna_atual * boneco->largura_sprite;
    }
}


void desenhaPersonagem(tSprite* personagem, ALLEGRO_BITMAP* folha_sprites_personagem) {

    // Movendo para a direita, positivo
    if(personagem->vel_x_sprite > 0) {
        al_draw_bitmap_region(folha_sprites_personagem,
                              personagem->regiao_x_folha,
                              personagem->regiao_y_folha,
                              personagem->largura_sprite,
                              personagem->altura_sprite,
                              personagem->pos_x_sprite,
                              personagem->pos_y_sprite,0);
    }
    else {
        al_draw_scaled_bitmap(folha_sprites_personagem,
                              personagem->regiao_x_folha,
                              personagem->regiao_y_folha,
                              personagem->largura_sprite,
                              personagem->altura_sprite,
                              personagem->pos_x_sprite + personagem->largura_sprite,
                              personagem->pos_y_sprite,
                              -personagem->largura_sprite,
                              personagem->altura_sprite,0);
    }
}


void variaveisBoneco(tSprite* boneco) {
    // largura e altura de cada sprite dentro da folha
    boneco->altura_sprite=140, boneco->largura_sprite=108;
    // quantos sprites tem em cada linha da folha, e a atualmente mostrada
    boneco->colunas_folha=4, boneco->coluna_atual=0;
    // quantos sprites tem em cada coluna da folha, e a atualmente mostrada
    boneco->linha_atual=0, boneco->linhas_folha=2;
    // posicoes X e Y da folha de sprites que serao mostradas na tela
    boneco->regiao_x_folha=0, boneco->regiao_y_folha=0;
    // quantos frames devem se passar para atualizar para o proximo sprite
    boneco->frames_sprite=5, boneco->cont_frames=0;
    // posicao X Y da janela em que sera mostrado o sprite
    boneco->pos_x_sprite=50, boneco->pos_y_sprite=420;
    // velocidade X Y que o sprite ira se mover pela janela
    boneco->vel_x_sprite=5, boneco->vel_y_sprite=0;
}

void variaveisInimigo(tSprite* inimigo) {
    // largura e altura de cada sprite dentro da folha
    inimigo->altura_sprite=140, inimigo->largura_sprite=108;
    // quantos sprites tem em cada linha da folha, e a atualmente mostrada
    inimigo->colunas_folha=4, inimigo->coluna_atual=0;
    // quantos sprites tem em cada coluna da folha, e a atualmente mostrada
    inimigo->linha_atual=0, inimigo->linhas_folha=2;
    // posicoes X e Y da folha de sprites que serao mostradas na tela
    inimigo->regiao_x_folha=0, inimigo->regiao_y_folha=0;
    // quantos frames devem se passar para atualizar para o proximo sprite
    inimigo->frames_sprite=5, inimigo->cont_frames=0;
    // posicao X Y da janela em que sera mostrado o sprite
    inimigo->pos_x_sprite=500, inimigo->pos_y_sprite=420;
    // velocidade X Y que o sprite ira se mover pela janela
    inimigo->vel_x_sprite=5, inimigo->vel_y_sprite=0;
}