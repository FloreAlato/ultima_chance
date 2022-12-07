//
// Created by davyf on 30/11/2022.
//

#ifndef DAVIDE_FLORE_66174_FILES_H
#define DAVIDE_FLORE_66174_FILES_H

#include "funzioni_utili.h"


FILE *fopen_secure(char *, char *);
char *make_path(char[], char[]);
char **trova_nomi(FILE *, int);
void leggi_profili(FILE *, int, ProfiloGiocatore *);
void scrivi_profili(FILE *, int, ProfiloGiocatore *);
void save_nogame(int, ProfiloGiocatore *, FILE *);
void add_file(char *);




void restore();


#endif //DAVIDE_FLORE_66174_FILES_H
