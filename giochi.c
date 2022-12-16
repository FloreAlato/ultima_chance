//
// Created by davyf on 12/12/2022.
//

#include "giochi.h"






void area_gioco(int numero_eventi, game_cell *eventi) {

    // cornice superiore
    printf("|");
    for(int i = 0; i < LARGHEZZA; i++) {
        printf("=");
    }
    printf("|\n");




    // parte centrale
    int conto = 0, j, spazio = 0;
    for(int i = 0; i < ALTEZZA; i++) {
        printf("|");
        if(conto < numero_eventi && i == eventi[conto].y) {
            for(j = 0; j < eventi[conto].x; j++) {
                printf(" ");
            }

            // stampa la roba importante
            printf("%s", eventi[conto].content);

            for(j = 0; j < LARGHEZZA - strlen(eventi[conto].content) - eventi[conto].x; j++) {
                printf(" ");
            }

            conto++;
        } else {
            for(j = 0; j < LARGHEZZA; j++) {
                printf(" ");
            }
        }
        printf("|\n");
    }
}











void nome_gioco(game_cell *lista_eventi, giochi gioco) {

    switch (gioco) {
        case INDOVINA:
            lista_eventi[0].content = "Stai giocanco a INDOVINA IL NUMERO";
            break;
        case PARI_DISPARI:
            lista_eventi[0].content = "Stai giocanco a PARI O DISPARI";
            break;
        default:
            break;
    }

    lista_eventi[0].y = 0;
    lista_eventi[0].x = SPAZIO_SINISTRA;
}









void layout_turni(game_cell *lista_eventi, Elenco *giocatori, int numero_giocatori, int pos, int id) {

    char spazio[5] = "    ";

    lista_eventi[id].y = pos;
    lista_eventi[id].content = "Tocca a:";

    lista_eventi[id + 1].y = pos + 1;

    char *nome = (char *) malloc(sizeof(char) * 60);
    strcpy(nome, print_player(giocatori[0]));

    for(int i = 1; i < numero_giocatori; i++) {
        nome = strcat(nome, spazio);
        nome = strcat(nome, print_player(giocatori[i]));
    }
    lista_eventi[id + 1].content = nome;

    lista_eventi[id + 2].y = pos + 2;
    lista_eventi[id + 2].content = "^";

    lista_eventi[id].x = lista_eventi[id + 1].x = lista_eventi[id + 2].x = SPAZIO_SINISTRA;

}




void prossimo_turno(game_cell *evento, Elenco *giocatori, int numero_giocatori, int turno) {

    if(turno == numero_giocatori) {
        evento->x = SPAZIO_SINISTRA;
    } else {
        evento->x += (int)strlen(print_player(giocatori[turno - 1])) + 4;
    }
}
