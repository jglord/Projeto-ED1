// Bibliotecas da ALLEGRO 5
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#include <string.h>
#include <stdio.h>

#include "funcoes_basicas_init.h"
#include "funcoes_estruturas.h"

// Macros

void error_msg(char* text, ALLEGRO_DISPLAY* window) {
    al_show_native_message_box(window, "ERRO",
        "Ocorreu o seguinte erro e o programa será finalizado:",
        text, NULL, ALLEGRO_MESSAGEBOX_ERROR);
}    

bool inicializarSprite(ALLEGRO_DISPLAY** window, 
                 ALLEGRO_TIMER** timer,
                 ALLEGRO_EVENT_QUEUE** fila_eventos,
                 ALLEGRO_BITMAP** folha_sprites_personagem,
                 ALLEGRO_BITMAP** folha_sprites_inimigo,
                 ALLEGRO_BITMAP** fundo
                )
{
    if( !al_init() ) {
        error_msg("Falha ao inicializar a Allegro!", *window);
        return false;
    }

    if( !al_install_keyboard() ) {
        error_msg("Falha ao inicializar teclado!", *window);
        return false;
    }

    if( !al_init_image_addon() ) {
        error_msg("Falha ao inicializar o addon de imagens!", *window);
        return false;
    }

    if( !al_init_primitives_addon() ) {
        error_msg("Falha ao inicializar o addon de primitivas!", *window);
    }

    *timer = al_create_timer(1.0/FPS);
    if(!*timer) {
        error_msg("Erro ao criar o timer!", *window);
        return false;
    }

    *window = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if(!*window) {
        error_msg("Erro ao inicializar a janela", *window);
        al_destroy_timer(*timer);
        return false;
    }

    al_set_window_title(*window, "Testanto sprite");

    *fila_eventos = al_create_event_queue();
    if(!*fila_eventos) {
        error_msg("Falha ao criar fila de eventos", *window);
        al_destroy_timer(*timer);
        al_destroy_display(*window);
        return false;
    }

    // Carrega a folha de sprites na variavel
    *folha_sprites_inimigo = al_load_bitmap("/home/jglord/Workspace/Projeto-ED1/projeto_jogo/projeto_allegro/imagens/INIMIG.png");
    if(!*folha_sprites_inimigo) {
        error_msg("Falha ao criar folha de sprite inimigo", *window);
        al_destroy_timer(*timer);
        al_destroy_display(*window);
        al_destroy_event_queue(*fila_eventos);
        return false;
    }

    *folha_sprites_personagem = al_load_bitmap("/home/jglord/Workspace/Projeto-ED1/projeto_jogo/projeto_allegro/imagens/boneco.bmp");
    if(!*folha_sprites_personagem) {
        error_msg("Falha ao criar folha de sprite personagem", *window);
        al_destroy_timer(*timer);
        al_destroy_display(*window);
        al_destroy_event_queue(*fila_eventos);
        return false;
    }

    al_convert_mask_to_alpha(*folha_sprites_personagem, al_map_rgb(255, 0, 255));
    al_convert_mask_to_alpha(*folha_sprites_inimigo, al_map_rgb(0, 255, 0));


    //carrega o fundo
    *fundo = al_load_bitmap("/home/jglord/Workspace/Projeto-ED1/projeto_jogo/projeto_allegro/imagens/Cenario1.png");
    if (!*fundo){
        error_msg("Falha ao carregar fundo", *window);
        al_destroy_timer(*timer);
        al_destroy_display(*window);
        al_destroy_event_queue(*fila_eventos);
        al_destroy_bitmap(*folha_sprites_personagem);
        return 0;
    }

    al_register_event_source(*fila_eventos, al_get_display_event_source(*window));
    al_register_event_source(*fila_eventos, al_get_timer_event_source(*timer));
    al_register_event_source(*fila_eventos, al_get_keyboard_event_source());
    al_start_timer(*timer);

    return true;
}

bool inicializarWindow(ALLEGRO_DISPLAY** window) {

    if(!al_init()) {
        error_msg("Erro ao inicializar a allegro5", *window);
        return false;
    }

    if(!al_init_image_addon()) {
        error_msg("Erro ao inicializar addon de image", *window);
        return false;
    }

    *window = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if(!*window) {
        error_msg("Falha ao inicializar window", *window);
        return false;
    }

    return true;
}

// Carrega imagem posicionada em algum ponto da tela
bool carregarImgP(ALLEGRO_DISPLAY** window, ALLEGRO_BITMAP** img, float px, float py) {

    // Carrega o bitmap em *img
    if(!*img) {
        error_msg("Erro ao carregar a imagem!", *window);
        return false;
    }

    al_convert_mask_to_alpha(*img, al_map_rgb(255, 0, 255));
    
    // Posiciona na tela no local esperado
    al_draw_bitmap(*img, px, py, 0);

    return true;
}

bool inicializaCoracoesMorte(ALLEGRO_BITMAP** coracoes, ALLEGRO_DISPLAY **window) {

    int i;
    for(i = 0; i < 5; i++) {
        ALLEGRO_BITMAP* coracaoMorte = al_load_bitmap("/home/jglord/Workspace/Projeto-ED1/projeto_jogo/projeto_allegro/imagens/morte.png");
        if(!coracaoMorte) {
            error_msg("ERRO ao carregar o CORACAO", *window);
            printf("ERRO AO CARREGAR O CORACAO %i\n", i);
            return false;
        }
        coracoes[i] = coracaoMorte;
    }

    return true;
}

bool inicializaCoracoesVida(tElemento* cabeca, ALLEGRO_DISPLAY **window) {

    int i;
    for(i = 0; i < 5; i++) {
        ALLEGRO_BITMAP* coracaoVida = al_load_bitmap("/home/jglord/Workspace/Projeto-ED1/projeto_jogo/projeto_allegro/imagens/vida.png");
        if(!coracaoVida) {
            error_msg("ERRO ao carregar o CORACAO", *window);
            printf("ERRO AO CARREGAR O CORACAO %i\n", i);
            return false;
        }
        inserirElementoInicio(cabeca, &coracaoVida);
    }

    return true;
}