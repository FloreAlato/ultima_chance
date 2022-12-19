//
// Created by davyf on 12/12/2022.
//

#ifndef DAVIDE_FLORE_66174_GIOCHI_H
#define DAVIDE_FLORE_66174_GIOCHI_H

#include "files.h"

#define LARGHEZZA 110
#define ALTEZZA 20
#define SPAZIO_SINISTRA 2

typedef enum {
    INDOVINA,
    PARI_DISPARI
} giochi;


typedef struct {
    int y;
    int x;
    int n;
    char **content;
} game_cell;



// code
void area_gioco(int, game_cell *);
void stampa_riga(game_cell);

void nome_gioco(game_cell *, giochi);
void layout_turni(game_cell *, Elenco *, int, int pos);
void prossimo_turno(game_cell *, Elenco *, int numero, int turno);

#endif //DAVIDE_FLORE_66174_GIOCHI_H
