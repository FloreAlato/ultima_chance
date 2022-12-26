//
// Created by davyf on 25/12/2022.
//

#include "svolgimento.h"







bool svolgimento(int numero_giocatori, Elenco *giocatori, Elenco *originali, Elenco *finalisti) {

    int numero = numero_giocatori;
    int numero_giocatori_vivi = numero_giocatori;
    int r, dim_gruppetto, segnaposto;

    // array di interi che contiene i giocatori ancora vivi, per fare i gruppetti
    int *giocatori_vivi = (int *) calloc(numero_giocatori_vivi, sizeof(int));
    for(int i = 0; i < numero; i++) {
        giocatori_vivi[i] = i;
    }

    // elenco che conterra' i giocatori di ogni gioco
    Elenco *gruppetto = (Elenco *) calloc(4, sizeof(Elenco));

    // coppia di finalisti rimanenti
    finalisti = (Elenco *) calloc(2, sizeof(Elenco));


    bool pla = false;
    bool frontman = false;

    int id_gioco, winner;

    // loop partita
    while(numero > 2) {

        pla = false;
        frontman = false;

        // SCEGLIE IL NUMERO DI GIOCATORI DA FAR GIOCARE
        r = rand_int(0, 1);
        if(r && numero > 4) {
            // GIOCO DA 4 GIOCATORI
            dim_gruppetto = 4;
            numero -= 3;
        } else {
            // GIOCO DA 2 GIOCATORI
            dim_gruppetto = 2;
            numero -=1;
        }

        // GENERA IL GRUPPETTO DI GIOCATORI
        for(int i = 0; i < dim_gruppetto; i++) {
            segnaposto = rand_int(0, numero_giocatori_vivi - 1);
            gruppetto[i] = giocatori[giocatori_vivi[segnaposto]];

            // salva la presenza di giocatori utente e di Riccardo Scateni
            if(is_player(gruppetto[i])) {
                pla = true;

                if(strcmp(print_player(gruppetto[i]), "Riccardo Scateni") == 0) {
                    frontman = true;
                }
            }

            giocatori_vivi[segnaposto] = giocatori_vivi[numero_giocatori_vivi - 1];
            numero_giocatori_vivi--;
        }


        // SCEGLIE IL GIOCO
        if(dim_gruppetto == 4) {
            if(frontman) {
                printf("\n\nA quale dei seguenti giochi vuoi giocare? (da %d a %d)", NUMERO_GIOCHI_DA_DUE, NUMERO_GIOCHI_DA_QUATTRO - 1);

                // stampare i giochi disponibili

                id_gioco = get_int(": ", NUMERO_GIOCHI_DA_DUE, NUMERO_GIOCHI_DA_QUATTRO - 1);
            } else {
                id_gioco = rand_int(NUMERO_GIOCHI_DA_DUE, NUMERO_GIOCHI_DA_QUATTRO - 1);
            }
        } else {
            if(frontman) {
                printf("\n\nA quale dei seguenti giochi vuoi giocare? (da 0 a %d)", NUMERO_GIOCHI_DA_DUE - 1);

                // stampare i giochi disponibili

                id_gioco = get_int(": ", 0, NUMERO_GIOCHI_DA_DUE - 1);
            } else {
                id_gioco = rand_int(0, NUMERO_GIOCHI_DA_DUE - 1);
            }
        }

        // GIOCA LA PARTITA
        switch(id_gioco) {
            case PONTE_DI_VETRO:
                // gioca a ponte di vetro
                winner = ponte_di_vetro(gruppetto);
                break;
            default:
                break;
        }


        // FRONTMAN
        if(frontman) {
            for(int i = 0; i < dim_gruppetto; i++) {
                if(strcmp(print_player(gruppetto[i]), "Riccardo Scateni") == 0) {
                    winner = i;
                }
            }
        }


        // AGGGIORNA I DATI DEL VINCITORE
        //


        // SALVA LA PARTITA

    }



    free(giocatori_vivi);
    free(gruppetto);

    // la coppia di finalisti e' riempita con i due giocatori rimasti in vita
    finalisti[0] = giocatori[0];
    finalisti[1] = giocatori[1];

    return true;
}


