//
// Created by davyf on 26/12/2022.
//


#include "giochi.h"





// GIOCO DADI

int dadi(Elenco *giocatori) {

    // fa cominciare il giocatore

    bool turno = false;

    if(!is_player(giocatori[(int) turno])) {
        turno = true;
    }

    int lanci[2][2];


    do {
        // azzera i lanci per ogni partita

        lanci[0][0] = 0;
        lanci[0][1] = 0;
        lanci[1][0] = 0;
        lanci[1][1] = 0;

        // primo turno
        printf("\n\n");
        layout_dadi(giocatori, turno, lanci[(int) turno], lanci[(int) !turno]);
        printf("Lancia i dadi (invio)");
        getchar();

        // quando assegna i lanci, sposta in basso il precedente
        // serve per stampare sempre in cima il lancio piu' recente
        // i dadi non sono due, ma i numeri tornano

        lanci[(int) turno][0] = lanci[(int) turno][1];
        lanci[(int) turno][1] = rand_int(2, 12);


        // per ongi turno, se il lancio e' peggiore del precendente, vince l'avversarop

        if(lanci[(int) turno][0] > lanci[(int) turno][1]) {
            return (int) !turno;
        }



        // secondo turno
        printf("\n\n");
        layout_dadi(giocatori, turno, lanci[(int) turno], lanci[(int) !turno]);
        printf("Lancia i dadi (invio)");
        getchar();

        lanci[(int) !turno][0] = lanci[(int) !turno][1];
        lanci[(int) !turno][1] = rand_int(2, 12);


        if(lanci[(int) turno][0] > lanci[(int) turno][1]) {
            return (int) !turno;
        }
    } while(true);
}







// layout dadi

void layout_dadi(Elenco *giocatori, bool turno, int *lancio1, int *lancio2) {

    layout();
    stampa_riga(SPAZIO_SINISTRA, 1, 2, "Stai giocando a", "DADI");      // occupa una riga
    stampa_riga_vuota(2);       // occupa due righe
    stampa_riga(SPAZIO_SINISTRA, 1, 2, print_player(giocatori[(int) turno]), ":");     // occupa una riga
    stampa_riga(SPAZIO_SINISTRA, 1, 2, "Ultimo lancio:", int_to_string(lancio1[1]));     // occupa una riga
    stampa_riga(SPAZIO_SINISTRA, 1, 2, "Lancio precedente:", int_to_string(lancio1[0]));       // occupa una riga
    stampa_riga_vuota(1);       // occupa tre righe
    stampa_riga(SPAZIO_SINISTRA, 1, 2, print_player(giocatori[(int) !turno]), ":");        // occupa una riga
    stampa_riga(SPAZIO_SINISTRA, 1, 2, "Ultimo lancio:", int_to_string(lancio2[1]));     // occupa una riga
    stampa_riga(SPAZIO_SINISTRA, 1, 2, "Lancio precedente:", int_to_string(lancio2[0]));       // occupa una riga
    stampa_riga_vuota(1);       // occupa tre righe
    stampa_turno(2, giocatori, turno);      // occupa tre righe
    stampa_riga_vuota(ALTEZZA - 14);
}





