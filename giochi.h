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
void layout();
void stampa_riga(int, int, int, ...);
void stampa_riga_elenco(int, int, Elenco *);
void stampa_riga_stringhe(int, int, char**);
void stampa_riga_vuota(int);



void stampa_turno(int, Elenco *, int);




// PARI O DISPARI
int pari_o_dispari(Elenco *);
void layout_pari(Elenco *, char *, char *, char *, bool);

// PONETE DI VETRO
int ponte_di_vetro(Elenco *);
void layout_ponte(Elenco *, char ****, int);
void casella_sbagliata(char **);
void casella_giusta(char **);
void stampa_ponte(char ****);


#endif //DAVIDE_FLORE_66174_GIOCHI_H
