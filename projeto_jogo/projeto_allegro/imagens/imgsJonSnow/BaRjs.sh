#!bin/sh
echo "Compilando e executando projeto da disciplina ESTRUTURA DE DADOS I"
echo "Desenvolvido por João Goulart e Washigton Gomes"
echo "VERSÃO DE TESTE"

echo "Inicializando compilação!"
gcc /home/jglord/eclipse-workspace/UfersaEstudos/Ufersa/src/UfersaCC/terceiro_periodo/ED1/terceira_unidade/projeto_jogo/projeto_allegro/src/funcoes/funcoes_basicas_init.c jon_snow_teste.c -o JonSnow -lallegro -lallegro_image -lallegro_dialog -g
echo "Compilação finalizada!"

echo "Executando o game!"
./JonSnow
echo "Jogo finalizado!"