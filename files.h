//
// Created by davyf on 30/11/2022.
//

#ifndef DAVIDE_FLORE_66174_FILES_H
#define DAVIDE_FLORE_66174_FILES_H

#include "funzioni_utili.h"

// funzioni

FILE *fopen_secure(char *, char *);
char *make_path(char[], char[]);
char **trova_nomi(FILE *, int);
void leggi_profili(FILE *, int, ProfiloGiocatore *);
void scrivi_profili(FILE *, int, ProfiloGiocatore *);
void save_nogame(int, ProfiloGiocatore *, FILE *);
void save_game(FILE *, int, int, Elenco *);
void add_file(char *);
bool save_short(int, ...);



// funzione mia per lo svilupo

void restore();


#endif //DAVIDE_FLORE_66174_FILES_H
