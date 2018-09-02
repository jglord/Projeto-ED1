#include "funcoes_estruturas.h"


tElemento* inicializarListaComCabeca() {

    tElemento* cabecaDaLista = (tElemento*) calloc(1, sizeof(tElemento));
    cabecaDaLista->id = 1;

    cabecaDaLista->img = NULL;

    cabecaDaLista->proxElemento = NULL;

    return cabecaDaLista;
}

void inserirElementoInicio(tElemento* cabeca, ALLEGRO_BITMAP** img) {

    tElemento* novoElemento = (tElemento*) calloc(1, sizeof(tElemento));

    // Inserindo valores no novo elemento
    novoElemento->img = *img;
    novoElemento->id = cabeca->id;

    cabeca->id++;

    // Anexando elementos
    novoElemento->proxElemento = cabeca->proxElemento;
    cabeca->proxElemento = novoElemento;
}

void removerFinal(tElemento* cabeca) {

    int i = 0;
    tElemento* p = cabeca->proxElemento;
    tElemento *anteriorP = NULL;

    while(p != NULL) {
        i++;
        anteriorP = p;
        p = p->proxElemento;
    }

    anteriorP->proxElemento = NULL;
}