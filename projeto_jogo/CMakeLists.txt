cmake_minimum_required(VERSION 3.2)
project(projeto_allegro)

set(CMAKE_C_STANDARD 11)

include_directories(projeto_allegro/src/funcoes)

INCLUDE_DIRECTORIES( allegro5/include )

LINK_DIRECTORIES( /usr/lib/ )

add_executable(projeto_allegro
        projeto_allegro/src/funcoes/funcoes_basicas_init.c
        projeto_allegro/src/funcoes/funcoes_basicas_init.h
        projeto_allegro/src/funcoes/funcoes_anim.c
        projeto_allegro/src/funcoes/funcoes_anim.h
        projeto_allegro/src/funcoes/funcoes_colisao.c
        projeto_allegro/src/funcoes/funcoes_colisao.h
        projeto_allegro/src/game.c
        projeto_allegro/BaR.sh)


add_library(lallegro SHARED /usr/lib/liballegro.so)

set_target_properties(lallegro PROPERTIES LINKER_LANGUAGE C)

TARGET_LINK_LIBRARIES(projeto_allegro
        allegro_acodec
        allegro_audio
        allegro_color
        allegro_dialog
        allegro_image
        allegro_main
        allegro_memfile
        allegro_physfs
        allegro_primitives
        allegro_ttf
        allegro_font
        allegro)
