//
// Created by davyf on 06/12/2022.
//

#ifndef DAVIDE_FLORE_66174_SCREMATURA_H
#define DAVIDE_FLORE_66174_SCREMATURA_H

#include "svolgimento.h"


// macro con il range per indovina il numero

#define MIN_INDOVINA 0
#define MAX_INDOVINA 999


// funzioni principali

Elenco *scrematura(int, int, Elenco *, int, ProfiloGiocatore *, Elenco *);
int indovina_il_numero(int, Elenco *);

// funzioni estetiche

void area_gioco_indovina(int, Elenco *, int, char *, int, int);
void stampa_intervallo_indovina(char *, int, int);
char *riga_indovina();

#endif //DAVIDE_FLORE_66174_SCREMATURA_H
