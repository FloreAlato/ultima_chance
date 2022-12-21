//
// Created by davyf on 06/12/2022.
//

#ifndef DAVIDE_FLORE_66174_SCREMATURA_H
#define DAVIDE_FLORE_66174_SCREMATURA_H

#include "giochi.h"


#define MIN_INDOVINA 0
#define MAX_INDOVINA 999

#define DIM_INIZIO 4
#define  DIM_FINE 6



Elenco **scrematura(int, int, Elenco **, int, ProfiloGiocatore *);
int indovina_il_numero(int, Elenco **);

char *riga_indovina();
void layout_riga(game_cell *, char *, int);
void aggiorna_riga(game_cell *, int, int);


char *make_string(char *base, int numero_argomenti, ...);

#endif //DAVIDE_FLORE_66174_SCREMATURA_H
