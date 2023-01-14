//
// Created by davyf on 12/12/2022.
//

#ifndef DAVIDE_FLORE_66174_GIOCHI_H
#define DAVIDE_FLORE_66174_GIOCHI_H

#include "files.h"


// macro per la stampa opridata dei giochi

#define LARGHEZZA 110
#define ALTEZZA 20
#define SPAZIO_SINISTRA 2






// funzioni per la stampa dei giochi

void layout();
void stampa_riga(int, int, int, ...);
void stampa_riga_elenco(int, int, Elenco *);
void stampa_riga_vuota(int);
void stampa_turno(int, Elenco *, int);



// sezione giochi
// tutte le funzioni inizializzate qui sono definite nei rispettivi files

// PARI O DISPARI (finito)
int pari_o_dispari(Elenco *);
void layout_pari(Elenco *, char *, char *, char *, bool, int, int);

// DADI
int dadi(Elenco *);
void layout_dadi(Elenco *, bool, int *, int *);

// MORRA CINESE
int morra_cinese(Elenco *);
void layout_morra_cinese(Elenco *, bool, char *, char *);

// MURRA
int murra(Elenco *);
void layout_murra(Elenco *, bool, int *, int *);

// PONETE DI VETRO
int ponte_di_vetro(Elenco *);
void layout_ponte(Elenco *, char ****, int);
void casella_sbagliata(char **);
void casella_giusta(char **);
void stampa_ponte(char ****);


#endif //DAVIDE_FLORE_66174_GIOCHI_H
