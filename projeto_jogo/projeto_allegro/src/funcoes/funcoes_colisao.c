#include "funcoes_anim.h"
#include "funcoes_colisao.h"

//bool colisao(tRetangulo A, tRetangulo B){
//
//    if ( A.X + A.W > B.X && A.Y + A.H > B.Y ){
//        if ( A.X < B.X + B.W && A.Y < B.Y + B.H ){
//            // Houve Colisão!
//            return true;
//        }
//    }
//    // Não Houve Colisão
//    return false;
//}

bool colisao(tRetangulo A, tRetangulo B){

    if ( A.X + (A.W/2) > B.X && A.Y + (A.H/2) > B.Y ){
        if ( A.X < B.X + (B.W/2) && A.Y < B.Y + (B.H/2) ){
            // Houve Colisão!
            return true;
        }
    }
    // Não Houve Colisão
    return false;
}

tRetangulo gerarRetangulo(tSprite* personagem) {

    tRetangulo retangulo;

    retangulo.W = personagem->largura_sprite;
    retangulo.H = personagem->altura_sprite;

    retangulo.X = personagem->pos_x_sprite;
    retangulo.Y = personagem->pos_y_sprite;

    return retangulo;
}

// Função pra acabar
// Ainda nao trata a colisão em que o boneco é negativo e o inimigo é positivo
void tratamentoDeColisao(tSprite* boneco, tSprite* inimigo) {

    if( boneco->vel_x_sprite > 0 && inimigo->vel_x_sprite < 0 ) {

        boneco->vel_x_sprite = -boneco->vel_x_sprite;
        inimigo->vel_x_sprite = abs(inimigo->vel_x_sprite);
    }
    else if( boneco->vel_x_sprite > 0 && inimigo->vel_x_sprite > 0 ) {

        boneco->vel_x_sprite = -boneco->vel_x_sprite;
        inimigo->vel_x_sprite = inimigo->vel_x_sprite;
    }
}