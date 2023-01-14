//
// Created by davyf on 28/12/2022.
//



#include "giochi.h"



// enum con i segni del gioco

typedef enum {paper, scissors, rock} segno;

// struttura per gestire le relazioni fra segni

typedef struct {
    segno s;
    segno batte;
    segno perde;
}butta;




// GIOCO MORRA CINESE

int morra_cinese(Elenco *giocatori) {

    // definisce le relazioni fra i segni

    butta sengi[3] = {
            {paper, rock, scissors},
            {scissors, paper, rock},
            {rock, scissors, paper}
    };

    bool turno = false;
    bool pareggio = false;

    // fa cominciare il giocatore utente

    if(!is_player(giocatori[(int) turno])) {
        turno = true;
    }

    segno giocate[2];

    char scelte[3][10] = {"carta", "forbici", "sasso"};


    do {
        // azzera dall'inizio tutti i valori
        // poi prosegue con i turni dove assegna i segni e li confronta
        // spero sia abbastanza intuitivo

        giocate[0] = paper;
        giocate[1] = paper;
        pareggio = false;

        // primo turno
        printf("\n\n");
        layout_morra_cinese(giocatori, turno, "non ha buttato...", "non ha buttato...");
        printf("Butta un segno: (carta / forbici / sasso)");
        printf("\n%s", print_player(giocatori[(int) turno]));
        giocate[(int) turno] = (segno) choice_string(": ", 3, scelte);
        getchar();

        // secondo turno
        printf("\n\n");
        layout_morra_cinese(giocatori, turno, scelte[giocate[(int) turno]], "non ha buttato...");
        printf("Butta un segno: (carta / forbici / sasso)");
        printf("\n%s", print_player(giocatori[(int) !turno]));
        if(is_player(giocatori[(int) !turno])) {
            giocate[(int) !turno] = (segno) choice_string(": ", 3, scelte);
            getchar();
        } else {
            giocate[(int) !turno] = (segno) rand_int(paper, rock);
            printf(": %s", scelte[giocate[(int) !turno]]);
            getchar();
        }

        // verdetto
        printf("\n\n");
        layout_morra_cinese(giocatori, turno, scelte[giocate[(int) turno]], scelte[giocate[(int) !turno]]);
        if(giocate[0] == giocate[1]) {
            printf("Pareggio! Riproviamo! (invio)");
            getchar();
            pareggio = true;
        } else {
            for(int i = 0; i < 3; i++) {
                if(giocate[(int) turno] == sengi[i].s) {
                    if(giocate[(int) !turno] == sengi[i].batte) {
                        return (int) turno;
                    } else {
                        return (int) !turno;
                    }
                }
            }
        }
        getchar();

    } while(pareggio);

    return 0;
}



// layout del gioco morra cinese

void layout_morra_cinese(Elenco *giocatori, bool turno, char *frase1, char *frase2) {

    layout();
    stampa_riga(SPAZIO_SINISTRA, 1, 2, "Stai giocando a", "MORRA CINESE");      // occupa una riga
    stampa_riga_vuota(2);       // occupa due righe
    stampa_riga(SPAZIO_SINISTRA, 1, 3, print_player(giocatori[(int) turno]), "->", frase1);     // occupa una riga
    stampa_riga_vuota(3);       // occupa tre righe
    stampa_riga(SPAZIO_SINISTRA, 1, 3, print_player(giocatori[(int) !turno]), "->", frase2);        // occupa una riga
    stampa_riga_vuota(3);       // occupa tre righe
    stampa_turno(2, giocatori, turno);      // occupa tre righe
    stampa_riga_vuota(ALTEZZA - 14);
}