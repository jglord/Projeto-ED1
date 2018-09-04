#include <stdio.h>
#include <string.h>

typedef struct sPlayer {
    char nome[50];
    int pontuacao;
} player;

void shellSort(player* players, int size); 

int main() {

    FILE* arquivo;
    player players[10];

    arquivo = fopen("ranking.bin", "r");

    if(arquivo == NULL) {
        printf("Erro ao abrir arquivo!");
        return 1;
    }

    int tam = 0;
    printf("Lendo arquivo...\n");
    while( fscanf( arquivo, "%s %i\n", &players[tam].nome, &players[tam].pontuacao ) != EOF ){
        tam++;
    }
    fclose(arquivo);

    printf("Cadastrando novo jogador...\n");
    players[tam].pontuacao = 73;
    strcpy(players[tam].nome, "joaozim");
    tam++;

    int i;
    printf("Antes de ordenar...\n");
    for(i = 0; i < tam; i++) {
        printf(" Player %i\n Nome: %s \n Pontuacao: %i \n ----------------\n",
              (i+1), players[i].nome, players[i].pontuacao ) ;
    }

    shellSort(players, 10);

    arquivo = fopen("ranking.bin", "w");
    printf("\n\n\n\n");
    for(i = 0; i < tam; i++) {
        printf(" Player %i\n Nome: %s \n Pontuacao: %i \n ----------------\n",
              (i+1), players[i].nome, players[i].pontuacao );
        fprintf(arquivo, "%s %i\n",players[i].nome, players[i].pontuacao );
    }

    fclose(arquivo);

    return 0;
}

void shellSort(player* players, int size) {

    int h = 1;
    int i, j;
    player eleito;

    while(h < size) {
        h = 3 * h + 1;
    }

    while(h > 1) {
        h = h / 3;

        for(i = h; i < size-1; i++) {
            eleito = players[i];
            j = i - h;

            while (j >= 0 && eleito.pontuacao > players[j].pontuacao) {
                players[j + h] = players[j];
                j = j - h;
            }
            players[j + h] = eleito;
        }
    }
}
