//
// Created by davyf on 28/12/2022.
//



#include "giochi.h"



// GIOCO MURRA

int murra(Elenco *giocatori) {

    // dita buttate e pronostici della somma

    int dita[2];
    int somma[2];

    // booleani per il controllo del loop di partita

    bool turno = false;

    // se il primo non e' utente, comincia il secondo

    if(!is_player(giocatori[(int) turno])) {
        turno = true;
    }




    do {
        // azzera dita e somme

        dita[0] = 0;
        dita[1] = 0;
        somma[0] = 0;
        somma[1] = 0;

        // spero che a questo punto i passaggi successivi siano abbastanza intuitivi

        // primo turno (dita)
        printf("\n\n");
        layout_murra(giocatori, turno, dita, somma);
        printf("Quante dita vuoi buttare? (da 1 a 5)");
        printf("\n%s", print_player(giocatori[(int) turno]));
        dita[(int) turno] = get_int(": ", 1, 5);
        getchar();

        // primo turno (somma)
        printf("\n\n");
        layout_murra(giocatori, turno, dita, somma);
        printf("Dai un pronostico della somma (da 2 a 10)");
        printf("\n%s", print_player(giocatori[(int) turno]));
        somma[(int) turno] = get_int(": ", 2, 10);
        getchar();

        // secondo turno (dita)
        printf("\n\n");
        layout_murra(giocatori, turno, dita, somma);
        printf("Quante dita vuoi buttare? (da 1 a 5)");
        printf("\n%s", print_player(giocatori[(int) !turno]));
        if(is_player(giocatori[(int) !turno])) {
            dita[(int) !turno] = get_int(": ", 1, 5);
            getchar();
        } else {
            dita[(int) !turno] = rand_int(1, 5);
            printf(": %d", dita[(int) !turno]);
            getchar();
        }

        // secondo turno (somma)
        printf("\n\n");
        layout_murra(giocatori, turno, dita, somma);
        printf("Dai un pronostico della somma (da 2 a 10)");
        printf("\n%s", print_player(giocatori[(int) !turno]));
        if(is_player(giocatori[(int) !turno])) {
            somma[(int) !turno] = get_int(": ", 2, 10);
            getchar();
        } else {
            somma[(int) !turno] = rand_int(1, 5);
            printf(": %d", somma[(int) !turno]);
            getchar();
        }

        // controlla che un giocatore abbia indovinato e l'altro no
        // niente eccezioni, senno' conta come pareggio

        if((dita[(int) turno] + dita[(int) !turno]) == somma[(int) turno] && (dita[(int) turno] + dita[(int) !turno]) != somma[(int) !turno]) {
            return (int) turno;
        } else if((dita[(int) turno] + dita[(int) !turno]) == somma[(int) !turno] && (dita[(int) turno] + dita[(int) !turno]) != somma[(int) turno]) {
            return (int) !turno;
        } else {
            layout_murra(giocatori, turno, dita, somma);
            printf("\n\nPareggio! Riproviamo\n");
        }
    } while(true);
}






// layout di murra, per estetica

void layout_murra(Elenco *giocatori, bool turno, int *dita, int *somma) {

    layout();
    stampa_riga(SPAZIO_SINISTRA, 1, 2, "Stai giocando a", "MURRA");      // occupa una riga
    stampa_riga_vuota(2);       // occupa due righe
    stampa_riga(SPAZIO_SINISTRA, 1, 2, print_player(giocatori[(int) turno]), ":");     // occupa una riga
    stampa_riga(SPAZIO_SINISTRA, 1, 3, "Ha buttato", int_to_string(dita[(int) turno]), "dita");     // occupa una riga
    stampa_riga(SPAZIO_SINISTRA, 1, 3, "Ha anticipato", int_to_string(somma[(int) turno]), "come somma");       // occupa una riga
    stampa_riga_vuota(1);       // occupa tre righe
    stampa_riga(SPAZIO_SINISTRA, 1, 2, print_player(giocatori[(int) !turno]), ":");        // occupa una riga
    stampa_riga(SPAZIO_SINISTRA, 1, 3, "Ha buttato", int_to_string(dita[(int) !turno]), "dita");        // occupa una riga
    stampa_riga(SPAZIO_SINISTRA, 1, 3, "Ha anticipato", int_to_string(somma[(int) !turno]), "come somma");      // occupa una riga
    stampa_riga_vuota(1);       // occupa tre righe
    stampa_turno(2, giocatori, turno);      // occupa tre righe
    stampa_riga_vuota(ALTEZZA - 14);
}
