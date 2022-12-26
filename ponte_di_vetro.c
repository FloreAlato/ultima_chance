//
// Created by davyf on 26/12/2022.
//


#include "giochi.h"


char casella_ponte[5][11] = {
        " _______ \0",
        "|       |\0",
        "|       |\0",
        "|       |\0",
        " ------- \0"
};






int ponte_di_vetro(Elenco *giocatori) {

    // array delle 3 risposte corrette
    bool giusti[3];
    giusti[0] = (bool) rand_int(0, 1);
    giusti[1] = (bool) rand_int(0, 1);
    giusti[2] = (bool) rand_int(0, 1);


    // genera e riempie il ponte
    char ****ponte = (char ****) calloc(3, sizeof(char ***));
    for(int i = 0; i < 3; i++) {
        ponte[i] = (char ***) calloc(2, sizeof(char **));

        for(int j = 0; j < 2; j++) {
            ponte[i][j] = (char **) calloc(5, sizeof(char *));

            for(int a = 0; a < 5; a++) {
                ponte[i][j][a] = (char *) malloc(sizeof(char) * 10);

                strcpy(ponte[i][j][a], casella_ponte[a]);
            }
        }
    }


    bool finito = false;
    int turno = 0, caselle = 2, numero_giocatori_vivi = 4, scelta, winner;
    char opzioni[2][10] = {"sinistra", "destra"};


    layout_ponte(giocatori, ponte, turno);



    while(caselle >= 0 && numero_giocatori_vivi > 0) {

        printf("\nQuale casella vuoi tentare? (destra / sinistra)\n%s", print_player(giocatori[turno]));
        if(is_player(giocatori[turno])) {
            scelta = choice_string(": ", 2, opzioni);
            getchar();
        } else {
            scelta = rand_int(0, 1);
            printf(": %s", opzioni[scelta]);
            getchar();
        }

        if(giusti[caselle] == scelta) {         // casella giusta

            // casella giusta
            casella_giusta(ponte[caselle][scelta]);

            // avanza
            caselle--;

        } else {        // casella sbagliata

            // casella sbagliata
            casella_sbagliata(ponte[caselle][scelta]);

            // uccidi il giocatore
            giocatori[turno].vivo = false;
            numero_giocatori_vivi--;

            // nuovo giocatore
            turno++;

            // avanza
            caselle--;
        }
        printf("\n\n");
        layout_ponte(giocatori, ponte, turno);
    }
    winner = turno;


    free(ponte);

    return winner;
}










void casella_sbagliata(char **casella) {
    casella[1][1] = casella[1][7] = casella[2][4] = casella[3][1] = casella[3][7] = 'X';
}

void casella_giusta(char **casella) {
    casella[1][7] = casella[2][2] = casella[2][6] = casella[3][4] = 'V';
}

void stampa_ponte(char ****ponte) {

    for(int j = 2; j >= 0; j--) {
        for(int i = 0; i < 5; i++) {
            stampa_riga((LARGHEZZA / 2) - 9, 0, 2, ponte[j][0][i], ponte[j][1][i]);
        }
    }
}

void layout_ponte(Elenco *giocatori, char ****ponte, int turno) {

    layout();
    stampa_riga(SPAZIO_SINISTRA, 1, 2, "Stai giocando a", "PONTE DI VETRO");        // occupa una riga
    stampa_riga_vuota(1);       // occupa una riga
    stampa_ponte(ponte);        // occupa quindici righe
    stampa_turno(4, giocatori, turno);      // occupa tre righe
}
