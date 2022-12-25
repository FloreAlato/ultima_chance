//
// Created by davyf on 23/12/2022.
//

#ifndef DAVIDE_FLORE_66174_FINALE_H
#define DAVIDE_FLORE_66174_FINALE_H


#include "giochi.h"

#define STEP 4


typedef enum {cuori, quadri, fiori, picche}semi;


typedef struct {
    semi seme;
    int valore;
}carta;


int black_jack(Elenco *);
void area_gioco_black(Elenco *, int *, carta **, int *);
void stampa_carte(carta *, int, int);
void ricorsione_stampa_carte(carta *, int, int);


#endif //DAVIDE_FLORE_66174_FINALE_H
