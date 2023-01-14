//
// Created by davyf on 30/11/2022.
//

#ifndef DAVIDE_FLORE_66174_MAIN_H
#define DAVIDE_FLORE_66174_MAIN_H


#include "scrematura.h"

// macro con il numero massimo di giocatori

#define MAX_GIOCATORI 999

// macro estetiche per rendere la switch nel main piu' estetica

#define CONTINUA 0
#define SALVA 1
#define INIZIA 2
#define ESCI 3


// funzioni del main

ProfiloGiocatore *crea_profili(int *, int *);
ProfiloGiocatore *leggi_file(int *, bool *, FILE *);
Elenco *aggiunte(int *, int *, ProfiloGiocatore *, FILE *);
char *scegli_file();
void scegli_id(int, int, int, ProfiloGiocatore *, Elenco *, int *);




#endif //DAVIDE_FLORE_66174_MAIN_H
