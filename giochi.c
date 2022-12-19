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
    int conto = 0;
    for(int i = 0; i < ALTEZZA; i++) {
        printf("|");
        if(conto < numero_eventi && i == eventi[conto].y) {
            stampa_riga(eventi[conto]);

            conto++;
        } else {
            for(int j = 0; j < LARGHEZZA; j++) {
                printf(" ");
            }
        }
        printf("|\n");
    }
}








void stampa_riga(game_cell evento) {

    int spazio = 0;

    for(int i = 0; i < evento.x; i++) {
        printf(" ");
    }
    for(int i = 0; i < evento.n; i++) {
        printf("%s", evento.content[i]);
        spazio += (int)strlen(evento.content[i]);
    }
    for(int i = 0; i <LARGHEZZA - spazio - evento.x; i++) {
        printf(" ");
    }
}











void nome_gioco(game_cell *evento, giochi gioco) {

    char **nome = (char **) malloc(sizeof(char) * 2);
    nome[0] = (char *) malloc(sizeof(char) * 10);
    nome[1] = (char *) malloc(sizeof(char) * 30);
    nome[0] = "Stai giocanco a \0";

    switch(gioco) {
        case INDOVINA:
            nome[1] = "INDOVINA IL NUMERO\0";
            break;
        case PARI_DISPARI:
            nome[1] = "PARI O DISPARI\0";
            break;
        default:
            break;
    }

    evento->y = 0;
    evento->n = 2;
    evento->content = nome;
    evento->x = SPAZIO_SINISTRA;
}









void layout_turni(game_cell *evento, Elenco *giocatori, int numero_giocatori, int pos) {

    // prima riga (tocca a:)
    char **intro = (char **) calloc(2, sizeof(char *));
    intro[0] = (char *) malloc(sizeof(char) * 10);
    intro[1] = (char *) malloc(sizeof(char) * 10);
    intro[0] = "Tocca a\0";
    intro[1] = ":\0";


    // seconda riga (nomi giocatori)
    char *segnaposto = (char *) malloc(sizeof(char) * 9);
    segnaposto = "    \0";

    char **turni = (char **) calloc((numero_giocatori * 2) - 1, sizeof(char *));

    int counter = 0;
    for(int i = 0; i < (numero_giocatori * 2) - 1; i++) {
        if(i % 2 == 0) {
            turni[i] = print_player(giocatori[counter]);
            counter++;
        } else {
            turni[i] = segnaposto;
        }
    }


    // terza riga (freccia)
    char **fine = (char **) calloc(2, sizeof(char *));
    fine[0] = (char *) malloc(sizeof(char) * 2);
    fine[1] = (char *) malloc(sizeof(char) * 2);
    fine[0] = "^\0";
    fine[1] = " \0";


    evento->y = pos;
    evento->n = 2;
    evento->x = SPAZIO_SINISTRA;
    evento->content = intro;

    (evento + 1)->y = pos + 1;
    (evento + 1)->n = (numero_giocatori * 2) - 1;
    (evento + 1)->x = SPAZIO_SINISTRA;
    (evento + 1)->content = turni;

    (evento + 2)->y = pos + 2;
    (evento + 2)->n = 1;
    (evento + 2)->x = SPAZIO_SINISTRA;
    (evento + 2)->content = fine;
}




// controlla
void prossimo_turno(game_cell *evento, Elenco *giocatori, int numero_giocatori, int turno) {

    if(turno == 0) {
        evento->x = SPAZIO_SINISTRA;
    } else {
        evento->x += (int)strlen(print_player(giocatori[turno - 1])) + 4;
    }
}
