//
// Created by davyf on 12/12/2022.
//

#include "giochi.h"





// stampa una riga del layout dei giochi
// fondamentalmente stampa una serie di stringhe con spazi definiti
// la funzione prende un numero indefinito di parametri per poter stampare quante stringhe voglio

void stampa_riga(int sinistra, int spazio, int args, ...) {

    int space = 0;
    char *segnaposto;

    va_list lista;
    va_start(lista, args);

    // stampa prima "sinistra" spazi a sinistra

    printf("|");
    for(int i = 0; i < sinistra; i++) {
        printf(" ");
        space++;
    }

    // poi in mezzo stampa le stringhe alternate a spazi e salva il numero di caratteri stampati

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

    // poi usa quel numero per arrivare esattamente a fine linea

    for(int i = 0; i < LARGHEZZA - space; i++) {
        printf(" ");
    }
    printf("|\n");

    va_end(lista);
}



// eccezione alla funzione precedente
// stampa i nomi di un Elenco di giocatori
// molto piu' facile che passare nella funzione i singoli nomi

void stampa_riga_elenco(int spazio, int dim, Elenco *array) {

    int space = 0;

    // stampa sempre lo stamzio a sinistra

    printf("|");
    for(int i = 0; i < SPAZIO_SINISTRA; i++) {
        printf(" ");
        space++;
    }

    // alterna nomi e stazi

    for(int i = 0; i < dim; i++) {
        printf("%s", print_player((array[i])));

        space += (int) strlen(print_player(array[i]));

        for(int j = 0; j < spazio; j++) {
            printf(" ");
            space++;
        }
    }

    // e chiude la linea

    for(int i = 0; i < LARGHEZZA - space; i++) {
        printf(" ");
    }
    printf("|\n");
}



// stampa num numero num di righe vuote

void stampa_riga_vuota(int num) {
    for(int j = 0; j < num; j++) {
        printf("|");
        for(int i = 0; i < LARGHEZZA; i++) {
            printf(" ");
        }
        printf("|\n");
    }
}




// stampa il turno corrente
// occupa tre righe

void stampa_turno(int numero_giocatori, Elenco *giocatori, int turno) {

    // fondamentalmente stampa il riga i nomi dei giocatori
    // con un piccolo messaggio sopra
    // e una freccetta sotto per indicare il turno corrente
    // la freccetta si muove modificando il suo spazio a sinistra

    int distanza = 0;
    for(int i = 0; i < turno; i++) {
        distanza += (int) strlen(print_player(giocatori[i])) + 4;
    }

    stampa_riga(SPAZIO_SINISTRA, 1, 1, "Tocca a:\0");       // occupa una riga
    stampa_riga_elenco(4, numero_giocatori, giocatori);      // occupa una riga
    stampa_riga(SPAZIO_SINISTRA, distanza, 2, "\0", "^\0");     // occupa una riga
}



// inizio del layout, per non riscriverlo ogni volta
// e' solo la prima riga

void layout() {
    printf("|");
    for(int i = 0; i < LARGHEZZA; i++) {
        printf("=");
    }
    printf("|\n");
}