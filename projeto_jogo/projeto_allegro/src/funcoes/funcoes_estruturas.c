#include "funcoes_estruturas.h"

// Inicializa a cabeca da lista
tElemento* inicializarListaComCabeca() {

    tElemento* cabecaDaLista = (tElemento*) calloc(1, sizeof(tElemento));
    cabecaDaLista->id = 0;

    cabecaDaLista->img = NULL;

    cabecaDaLista->proxElemento = NULL;

    return cabecaDaLista;
}

// Insera elementos no inicio da lista
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

// Remove elementos do final da lista
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

// Busca alguma imagem e a retorna
ALLEGRO_BITMAP* retornarImgLista(tElemento*cabeca, int idBuscado) {

    tElemento* p = cabeca->proxElemento;

    while(p != NULL) {

        if(p->id == idBuscado) {
            return p->img;
        }
        p = p->proxElemento;

    }

    return NULL;
}



