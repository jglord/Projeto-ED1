cmake_minimum_required(VERSION 3.12)
project(projeto_allegro C)

set(CMAKE_C_STANDARD 11)

include_directories(src/funcoes)

add_executable(projeto_allegro
        src/funcoes/funcoes_anim.c
        src/funcoes/funcoes_anim.h
        src/funcoes/funcoes_basicas_init.c
        src/funcoes/funcoes_basicas_init.h
        src/funcoes/funcoes_colisao.c
        src/funcoes/funcoes_colisao.h
        src/funcoes/funcoes_estruturas.c
        src/funcoes/funcoes_estruturas.h
        src/funcoes/funcoes_ranking.c
        src/funcoes/funcoes_ranking.h
        src/game.c)
