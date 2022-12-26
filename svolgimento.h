//
// Created by davyf on 25/12/2022.
//

#ifndef DAVIDE_FLORE_66174_SVOLGIMENTO_H
#define DAVIDE_FLORE_66174_SVOLGIMENTO_H

#include "finale.h"

#define NUMERO_GIOCHI_DA_DUE 2
#define NUMERO_GIOCHI_DA_QUATTRO 3


typedef enum{PARI_DISPARI, DADI, PONTE_DI_VETRO} giochi_vari;


bool svolgimento(int, Elenco *, Elenco *, Elenco *);


#endif //DAVIDE_FLORE_66174_SVOLGIMENTO_H
