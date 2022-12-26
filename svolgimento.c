//
// Created by davyf on 25/12/2022.
//

#include "svolgimento.h"







int svolgimento(int numero_giocatori) {

    int numero = numero_giocatori;
    int r;

    while(numero > 2) {
        r = rand_int(0, 1);
        if(r && numero > 4) {

            // GIOCO DA 4 GIOCATORI
            numero -= 3;
        } else {

            // GIOCO DA 2 GIOCATORI
            numero -=1;
        }

        printf("\n%d", numero);
    }

    return 0;
}
