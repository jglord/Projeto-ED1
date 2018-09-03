#include "funcoes_estruturas.h"


tElemento* inicializarListaComCabeca() {

    tElemento* cabecaDaLista = (tElemento*) calloc(1, sizeof(tElemento));
    cabecaDaLista->id = 0;

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

tElemento* removerFinalLista(tElemento *cabeca) {

    tElemento* p = cabeca->proxElemento;
    tElemento* anteriorP = NULL;

    if( p == NULL ) {
        return NULL;
    } else if( p->proxElemento == NULL ) {
        cabeca->proxElemento = NULL;
        return p;
    }

    while(p->proxElemento != NULL) {
        anteriorP = p;
        p = p->proxElemento;
    }

    anteriorP->proxElemento = NULL;
    return p;
}

