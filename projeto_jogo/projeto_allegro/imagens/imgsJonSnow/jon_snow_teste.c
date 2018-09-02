#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#include <string.h>

#include "/home/jglord/eclipse-workspace/UfersaEstudos/Ufersa/src/UfersaCC/terceiro_periodo/ED1/terceira_unidade/projeto_jogo/projeto_allegro/src/funcoes/funcoes_basicas_init.h"

ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;

ALLEGRO_DISPLAY* windowPrincipal = NULL;
ALLEGRO_BITMAP* fundoPrincipal = NULL;
ALLEGRO_BITMAP* about = NULL;
ALLEGRO_BITMAP* exxit = NULL;
ALLEGRO_BITMAP* howToPLay = NULL;
ALLEGRO_BITMAP* loadGame = NULL;
ALLEGRO_BITMAP* newGame = NULL;

int main(){

    bool sair = false;
    char jon_snow[] = "/home/jglord/eclipse-workspace/UfersaEstudos/Ufersa/src/UfersaCC/terceiro_periodo/ED1/terceira_unidade/projeto_jogo/projeto_allegro/imagens/imgsJonSnow/imgs/JON_SNOW.jpeg";
    char new_game[] =  "/home/jglord/eclipse-workspace/UfersaEstudos/Ufersa/src/UfersaCC/terceiro_periodo/ED1/terceira_unidade/projeto_jogo/projeto_allegro/imagens/imgsJonSnow/imgs/NEW_GAME.png";
    char load_game[] = "/home/jglord/eclipse-workspace/UfersaEstudos/Ufersa/src/UfersaCC/terceiro_periodo/ED1/terceira_unidade/projeto_jogo/projeto_allegro/imagens/imgsJonSnow/imgs/LOAD_GAME.png";
    char how_to_play[] = "/home/jglord/eclipse-workspace/UfersaEstudos/Ufersa/src/UfersaCC/terceiro_periodo/ED1/terceira_unidade/projeto_jogo/projeto_allegro/imagens/imgsJonSnow/imgs/HOW_TO_PLAY.png";
    char about[] = "/home/jglord/eclipse-workspace/UfersaEstudos/Ufersa/src/UfersaCC/terceiro_periodo/ED1/terceira_unidade/projeto_jogo/projeto_allegro/imagens/imgsJonSnow/imgs/ABOUT.png";
    char exit[] = "/home/jglord/eclipse-workspace/UfersaEstudos/Ufersa/src/UfersaCC/terceiro_periodo/ED1/terceira_unidade/projeto_jogo/projeto_allegro/imagens/imgsJonSnow/imgs/EXIT.png";



    inicializarWindow(&windowPrincipal);

    fila_eventos = al_create_event_queue();
    if(!fila_eventos) {
        error_msg("Falha ao criar fila de eventos", windowPrincipal);
        al_destroy_display(windowPrincipal);
        return false;
    }
    al_register_event_source(fila_eventos, al_get_display_event_source(windowPrincipal));

    carregarImgP(&windowPrincipal, &fundoPrincipal, jon_snow, 0, 0);
    carregarImgP(&windowPrincipal, &fundoPrincipal, new_game, 630, 360);
    carregarImgP(&windowPrincipal, &fundoPrincipal, load_game, 630, 485);
    carregarImgP(&windowPrincipal, &fundoPrincipal, how_to_play, 630, 595);
    carregarImgP(&windowPrincipal, &fundoPrincipal, about, 630, 705);
    carregarImgP(&windowPrincipal, &fundoPrincipal, exit, 630, 815);
    al_flip_display();

    while(!sair) {
        ALLEGRO_EVENT evento;
        al_wait_for_event(fila_eventos, &evento);

        //al_flip_display();

        if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            sair = true;
        }

    }

    
    return 0;
}
