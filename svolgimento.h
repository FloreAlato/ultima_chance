//
// Created by davyf on 25/12/2022.
//

#ifndef DAVIDE_FLORE_66174_SVOLGIMENTO_H
#define DAVIDE_FLORE_66174_SVOLGIMENTO_H

#include "finale.h"

// macro per il numero di giochi da giocare in due e in quattro

#define NUMERO_GIOCHI_DA_DUE 4
#define NUMERO_GIOCHI_DA_QUATTRO 5

// enum con i giochi usata nella switch dello svolgimento

typedef enum{PARI_DISPARI, DADI, MORRA_CINESE, MURRA, PONTE_DI_VETRO} giochi_vari;


// svolgimento
Elenco *svolgimento(int, Elenco *, int, Elenco *, int, ProfiloGiocatore *, int);


#endif //DAVIDE_FLORE_66174_SVOLGIMENTO_H
