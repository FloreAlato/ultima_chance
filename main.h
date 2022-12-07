//
// Created by davyf on 30/11/2022.
//

#ifndef DAVIDE_FLORE_66174_MAIN_H
#define DAVIDE_FLORE_66174_MAIN_H


#include "scrematura.h"

#define MAX_GIOCATORI 999

#define CONTINUA 0
#define SALVA 1
#define INIZIA 2
#define ESCI 3


ProfiloGiocatore *crea_profili(int *, int *);
ProfiloGiocatore *leggi_file(int *, bool *, FILE *);
Elenco *aggiunte(int *, int *, ProfiloGiocatore *, FILE *);
char *scegli_file();
void scegli_id(int, int, int, ProfiloGiocatore *, Elenco *, int *);




#endif //DAVIDE_FLORE_66174_MAIN_H
