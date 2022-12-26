//
// Created by davyf on 12/12/2022.
//

#include "giochi.h"






void stampa_riga(int sinistra, int spazio, int args, ...) {

    int space = 0;
    char *segnaposto;

    va_list lista;
    va_start(lista, args);

    printf("|");
    for(int i = 0; i < sinistra; i++) {
        printf(" ");
        space++;
    }
    for(int i = 0; i < args; i++) {

        segnaposto = va_arg(lista, char *);

        printf("%s", segnaposto);

        if(i < args - 1) {
            for(int j = 0; j < spazio; j++) {
                printf(" ");
                space++;
            }
        }

        space += (int) strlen(segnaposto);
    }
    for(int i = 0; i < LARGHEZZA - space; i++) {
        printf(" ");
    }
    printf("|\n");

    va_end(lista);
}


void stampa_riga_elenco(int spazio, int dim, Elenco *array) {

    int space = 0;

    printf("|");
    for(int i = 0; i < SPAZIO_SINISTRA; i++) {
        printf(" ");
        space++;
    }
    for(int i = 0; i < dim; i++) {
        printf("%s", print_player((array[i])));

        space += (int) strlen(print_player(array[i]));

        for(int j = 0; j < spazio; j++) {
            printf(" ");
            space++;
        }
    }
    for(int i = 0; i < LARGHEZZA - space; i++) {
        printf(" ");
    }
    printf("|\n");
}



void stampa_riga_stringhe(int spazio, int dim, char **stringhe) {

    int space = 0;

    printf("|");
    for(int i = 0; i < SPAZIO_SINISTRA; i++) {
        printf(" ");
        space++;
    }
    for(int i = 0; i < dim; i++) {
        printf("%s", stringhe[i]);

        space += (int) strlen(stringhe[i]);

        for(int j = 0; j < spazio; j++) {
            printf(" ");
            space++;
        }
    }
    for(int i = 0; i < LARGHEZZA - space; i++) {
        printf(" ");
    }
    printf("|\n");
}





void stampa_riga_vuota(int num) {
    for(int j = 0; j < num; j++) {
        printf("|");
        for(int i = 0; i < LARGHEZZA; i++) {
            printf(" ");
        }
        printf("|\n");
    }
}





void stampa_turno(int numero_giocatori, Elenco *giocatori, int turno) {

    int distanza = 0;
    for(int i = 0; i < turno; i++) {
        distanza += (int) strlen(print_player(giocatori[i])) + 4;
    }

    stampa_riga(SPAZIO_SINISTRA, 1, 1, "Tocca a:\0");       // occupa una riga
    stampa_riga_elenco(4, numero_giocatori, giocatori);      // occupa una riga
    stampa_riga(SPAZIO_SINISTRA, distanza, 2, "\0", "^\0");     // occupa una riga
}




void layout() {
    printf("|");
    for(int i = 0; i < LARGHEZZA; i++) {
        printf("=");
    }
    printf("|\n");
}