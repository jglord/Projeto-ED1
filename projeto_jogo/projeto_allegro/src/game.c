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
#include "funcoes/funcoes_estruturas.h"
#include "funcoes/funcoes_ranking.h"

ALLEGRO_DISPLAY* window = NULL;
ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
ALLEGRO_EVENT_QUEUE* fila_eventos2 = NULL;
ALLEGRO_TIMER* timer = NULL;

ALLEGRO_BITMAP* folha_sprites_personagem = NULL;
ALLEGRO_BITMAP* folha_sprites_inimigo = NULL;
ALLEGRO_BITMAP* fundo = NULL;
ALLEGRO_BITMAP* gameOverImg = NULL;

ALLEGRO_BITMAP* coracaoVermelho = NULL;

int main(void) {

    // Variaveis de controle
    bool desenhaGame = true;
    bool sair = false;
    bool primeiraVez = true;
    int pontuacao = 0, dificuldade = -1, colisoes = 0;
    int i, tam;
    
    // Array usado para posicionar corretamento os coracoes cinza na tela
    int valoresPosicaoCoracaoCinza[] = { 30, 100, 170, 240, 310 };
    // Vetor estático utilizado para guardar os coracoes cinzas
    ALLEGRO_BITMAP* coracoes[5];

    // Ranking
    player players[100];
    player playerAtual;
    strcpy(playerAtual.nome, "Player Atual");
    // Tamanho do ranking
    tam = lerArquivo(players);

    // Cabeca da lista que guarda os coracoes vermelhos
    tElemento* vidas = inicializarListaComCabeca();

    tSprite boneco;
    tSprite inimigo;

    // Retangulos utilizados para analisar colisão
    tRetangulo retanguloBoneco;
    tRetangulo retanguloInimigo;

    // Inicializando as variaveis de controle dos sprites
    variaveisInimigo(&inimigo);
    variaveisBoneco(&boneco);
    if( !inicializarSprite(&window, &timer, &fila_eventos, &folha_sprites_personagem, &folha_sprites_inimigo, &fundo, &gameOverImg) ) {
        return -1;
    };

    // Carrega os coracoes vermelhos e cinzas dentro das estruturas( vetor e lista)
    inicializaCoracoesMorte(coracoes, &window);
    inicializaCoracoesVida(vidas, &window);

    // Looping principal do game
    while(!sair) {
        ALLEGRO_EVENT evento, evento2;
        al_wait_for_event(fila_eventos, &evento);

        // Verifica se alguma tecla foi pressionada
        if( evento.type == ALLEGRO_EVENT_KEY_DOWN ) {
            // Se for LSHIFT, então aumenta a velocidade do boneco
            if( evento.keyboard.keycode == ALLEGRO_KEY_LSHIFT ) {
                boneco.vel_x_sprite *= 2;
                boneco.frames_sprite -= 2;
            }

            // Se for SPACE, então faz o personagem pular
            if( evento.keyboard.keycode == ALLEGRO_KEY_SPACE ) {
                if(boneco.pos_y_sprite >= 420) {
                    boneco.vel_y_sprite -= 6;
                }
            }

        // Verifica se alguma tecla foi solta
        } else if( evento.type == ALLEGRO_EVENT_KEY_UP ) {
            // Se for LSHIFT, então volta a velocidade do boneco para o normal
            if( evento.keyboard.keycode == ALLEGRO_KEY_LSHIFT ) {
                boneco.vel_x_sprite /= 2;
                boneco.frames_sprite += 2;
            }
        }

        // Calculo da dificuldade
        dificuldade = pontuacao % 1000;
        if( !dificuldade ) {
            if( inimigo.vel_x_sprite > 0 ) {
                inimigo.vel_x_sprite += 0.5;
            }
            else {
                inimigo.vel_x_sprite -= 0.5;
            }

            if( inimigo.frames_sprite > 2 ) {
                inimigo.frames_sprite--;
            }
        }


        /*- EVENTOS -*/
        if(evento.type == ALLEGRO_EVENT_TIMER) {

            // A cada disparo do timer o contador de frames incrementa
            boneco.cont_frames++;
            inimigo.cont_frames++;

            mudarSprite(&boneco);
            mudarSprite(&inimigo);
            
            // Verifica se os sprite ta perto das bordas X da tela
            if( boneco.pos_x_sprite > LARGURA_TELA - 120 || boneco.pos_x_sprite < 20) {
                // Inverte o sentido da velocidade X pra andar ao contrario
                boneco.vel_x_sprite = -boneco.vel_x_sprite;
            } 

            if( inimigo.pos_x_sprite > LARGURA_TELA - 120 || inimigo.pos_x_sprite < 20) {
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

            //Atualiza as posicoes X Y do sprite de acordo com a velocidade, positiva ou negativa
            boneco.pos_x_sprite += boneco.vel_x_sprite;
            boneco.pos_y_sprite += boneco.vel_y_sprite;

            inimigo.pos_x_sprite += inimigo.vel_x_sprite;
            inimigo.pos_y_sprite += inimigo.vel_y_sprite;

            // Pontuacao baseada no quanto o usuario conseguiu percorrer sem morrer
            pontuacao += abs(boneco.vel_x_sprite);
            
            // Gera retangulos que vao ser usados na colisao.
            retanguloBoneco  = gerarRetangulo(&boneco);
            retanguloInimigo = gerarRetangulo(&inimigo);

            // Testa colisao, se colidir repele os objetos
            if( colisao(retanguloBoneco, retanguloInimigo) ) {
                colisoes++;
                tratamentoDeColisao(&boneco, &inimigo);
                removerFinalLista(vidas);
            }

            // Verifica se o usuário perdeu todas as vidas.
            if( colisoes <= 5 ) {
                desenhaGame = true;
            } else {
                desenhaGame = false;
                gameOver(&gameOverImg);
            }
        }
        else if( evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) {
            sair = true;
        }

        /* -- ATUALIZA TELA -- */
        if( desenhaGame ) {
            al_draw_bitmap_region(fundo,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);

            desenhaPersonagem(&inimigo, folha_sprites_inimigo);
            desenhaPersonagem(&boneco, folha_sprites_personagem);

            // Carrega imagem dos coraçoes cinzas e vermelhos
            for(i = 0; i < 5; i++) {
                carregarImgP(&window, &coracoes[i], valoresPosicaoCoracaoCinza[i], 30);

                    coracaoVermelho = retornarImgLista(vidas, i);
                    if( coracaoVermelho != NULL) {
                        carregarImgP(&window, &coracaoVermelho, valoresPosicaoCoracaoCinza[i], 30);
                    }
            }

            desenhaGame = false;
            al_flip_display();
        }
    }

    // Calculando a pontuação
    pontuacao = pontuacao/100;
    playerAtual.pontuacao = pontuacao;
    // Salvando player atual dentro do vetor ranking
    players[tam] = playerAtual;
    tam++;

    // Ordenando com shell sort e escrevendo o ranking dentro do arquivo.
    shellSort(players, tam);
    //escreveArquivo(players, tam);

    int x;
    printf("\n\n ---------------------------\n");
    printf("|          RANKING          |\n");
    printf(" ---------------------------\n");
    for(x = 0; x < tam; x++) {
        printf("%i | Nome: %s\n", x, players[x].nome);
        printf("    Pontuacao: %i\n", players[x].pontuacao);
    }

    al_destroy_display(window);
    al_destroy_event_queue(fila_eventos);
    al_destroy_timer(timer);
    al_destroy_bitmap(folha_sprites_personagem);
    al_destroy_bitmap(folha_sprites_inimigo);
    al_destroy_bitmap(fundo);   
       
   return 0;  
}
