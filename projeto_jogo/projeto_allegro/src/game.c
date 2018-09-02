/** ---- BUGS E PROBLEMAS ----
 * Pulo não está pousando certo, continua descendo para o infinito - !!FIXED!!
 * Mover imagem ao invés do personagem, tentar carregar as imagens fora do display - !!JOGO AGE DE OUTRA FORMA AGORA!!
 * e ir mostrando aos poucos
 *
**/ 
// Bibliotecas nativas do C
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Bibliotecas da ALLEGRO 5
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

// Bibliotecas do projeto
#include "funcoes/funcoes_basicas_init.h"
#include "funcoes/funcoes_anim.h"
#include "funcoes/funcoes_colisao.h"

ALLEGRO_DISPLAY* window = NULL;
ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
ALLEGRO_TIMER* timer = NULL;
ALLEGRO_BITMAP* folha_sprites_personagem = NULL;
ALLEGRO_BITMAP* folha_sprites_inimigo = NULL;
ALLEGRO_BITMAP* fundo = NULL;

int main(void) {

    int desenha = 1;
    bool sair = false;
    long pontuacao = 0;

    int LEX, LDX;
    int LSY, LIY;

    tSprite boneco;
    tSprite inimigo;

    tRetangulo retanguloBoneco;
    tRetangulo retanguloInimigo;

    variaveisInimigo(&inimigo);
    variaveisBoneco(&boneco);
    if( !inicializarSprite(&window, &timer, &fila_eventos, &folha_sprites_personagem, &folha_sprites_inimigo, &fundo) ) {
        return -1;
    };



    while(!sair) {
        ALLEGRO_EVENT evento;
        al_wait_for_event(fila_eventos, &evento);



        // Mudando a velocidade do boneco quando aperta RSHIFT
        if( evento.type == ALLEGRO_EVENT_KEY_DOWN ) {

            if( evento.keyboard.keycode == ALLEGRO_KEY_LSHIFT ) {
                boneco.vel_x_sprite *= 2;
                boneco.frames_sprite -= 2;
                printf("LSHIFT PRESSIONADO\n");
            }

            if( evento.keyboard.keycode == ALLEGRO_KEY_SPACE ) {
                if(boneco.pos_y_sprite >= 420) {
                    boneco.vel_y_sprite -= 6;
                    printf("SPACE PRESSIONADO\n");
                }
            }

        } else if( evento.type == ALLEGRO_EVENT_KEY_UP ) {

            if( evento.keyboard.keycode == ALLEGRO_KEY_LSHIFT ) {
                boneco.vel_x_sprite /= 2;
                boneco.frames_sprite += 2;
                printf("LSHIFT SOLTO\n");
            }
            /*
            if( evento.keyboard.keycode == ALLEGRO_KEY_SPACE ) {
                boneco.vel_y_sprite += 12;
            }*/
        }


        /*- EVENTOS -*/
        if(evento.type == ALLEGRO_EVENT_TIMER) {

            // A cada disparo do timer o contador de frames incrementa
            boneco.cont_frames++;
            inimigo.cont_frames++;

            mudarSprite(&boneco);
            mudarSprite(&inimigo);
            
            // Verifica se os sprite ta perto das bordas X da tela
            if( boneco.pos_x_sprite > LARGURA_TELA - 150 || boneco.pos_x_sprite < 20) {
                // Inverte o sentido da velocidade X pra andar ao contrario
                boneco.vel_x_sprite = -boneco.vel_x_sprite;
            } 

            if( inimigo.pos_x_sprite > LARGURA_TELA - 150 || inimigo.pos_x_sprite < 20) {
                // Inverte o sentido da velocidade X pra andar ao contrario
                inimigo.vel_x_sprite = -inimigo.vel_x_sprite;
            } 
            
            // PULO
            if( boneco.pos_y_sprite > POS_INICIAL_BONECO ) {
                boneco.vel_y_sprite = 0;
                boneco.pos_y_sprite = POS_INICIAL_BONECO;
            } 
            else if ( boneco.pos_y_sprite <= ALTURA_MAXIMA_PULO ) {
                boneco.vel_y_sprite += 12;
            }

            //atualiza as posicoes X Y do sprite de acordo com a velocidade, positiva ou negativa
            boneco.pos_x_sprite += boneco.vel_x_sprite;
            boneco.pos_y_sprite += boneco.vel_y_sprite;

            inimigo.pos_x_sprite += inimigo.vel_x_sprite;
            inimigo.pos_y_sprite += inimigo.vel_y_sprite;

            // Pontuacao baseada no quanto o usuario conseguiu percorrer sem morrer
            pontuacao += abs(boneco.vel_x_sprite);

            printf("%i\n",pontuacao);

            // Gera retangulos que vao ser usados na colisao.
            retanguloBoneco  = gerarRetangulo(&boneco);
            retanguloInimigo = gerarRetangulo(&inimigo);

            // Testa colisao, se colidir repele os objetos
            if( colisao(retanguloBoneco, retanguloInimigo) ) {

                tratamentoDeColisao(&boneco, &inimigo);

//                boneco.vel_x_sprite = -boneco.vel_x_sprite;
//                inimigo.vel_x_sprite = -inimigo.vel_x_sprite;
            }


            desenha = 1;
        }
        else if( evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) {
            sair = true;
        }

        /* -- ATUALIZA TELA -- */
        if( desenha ) {
            al_draw_bitmap_region(fundo,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
            
            desenhaPersonagem(&inimigo, folha_sprites_inimigo);
            desenhaPersonagem(&boneco, folha_sprites_personagem);
            
            desenha = 0;

//            LDX = boneco.pos_x_sprite + (boneco.largura_sprite);
//            LIY = boneco.pos_y_sprite - (boneco.altura_sprite/100);
//            LEX = boneco.pos_x_sprite - (boneco.largura_sprite/2);
//            LSY = boneco.pos_y_sprite + (boneco.altura_sprite/2);
//
//            // CALCULAR CORRETAMENTE ESSES VALORES COM WASHIGTONk
//            //                 L.D.X / L.I.Y / L.E.X / L.S.Y
//            //al_draw_rectangle(  LDX,    LIY,    LEX,    LSY, al_map_rgb(255,0,0), 1 );
//
//            //al_draw_rectangle(inicioX, inicioY, fimX, fimY, al_map_rgb(255, 0,0), 1.0);
//
//            //al_draw_rectangle()
            al_flip_display();
        }

    }
        
    printf("PONTUACAO: %i\n", pontuacao);
    al_destroy_display(window);
    al_destroy_event_queue(fila_eventos);
    al_destroy_timer(timer);
    al_destroy_bitmap(folha_sprites_personagem);
    al_destroy_bitmap(fundo);   
   
   return 0;  
}
