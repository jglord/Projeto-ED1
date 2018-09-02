#!bin/sh
echo "Compilando e executando projeto da disciplina ESTRUTURA DE DADOS I"
echo "Desenvolvido por João Goulart e Washigton Gomes"
echo "VERSÃO DE TESTE"

echo "Inicializando compilação!"
gcc  src/funcoes/funcoes_estruturas.c src/funcoes/funcoes_colisao.c src/funcoes/funcoes_anim.c src/funcoes/funcoes_basicas_init.c src/game.c -o Jogo -lallegro -lallegro_primitives -lallegro_image -lallegro_dialog -g
echo "Compilação finalizada!"

echo "Executando o game!"
./Jogo
echo "Jogo finalizado!"
