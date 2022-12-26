//
// Created by davyf on 25/12/2022.
//

#include "svolgimento.h"




char nomi_giochi[NUMERO_GIOCHI_DA_QUATTRO][20] = {
        "Pari o Dispari",
        "Ponte di Vetro"
};







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
    int pos_frontman;

    int id_gioco, winner, min, max;

    // loop partita
    while(numero > 2) {

        min = 0;
        max = 0;

        pla = false;
        frontman = false;

        // SCEGLIE IL NUMERO DI GIOCATORI DA FAR GIOCARE
        r = rand_int(0, 1);
        if(r && numero > 4) {
            // GIOCO DA 4 GIOCATORI
            dim_gruppetto = 4;
            min = NUMERO_GIOCHI_DA_DUE;
            max = NUMERO_GIOCHI_DA_QUATTRO;
            numero -= 3;
        } else {
            // GIOCO DA 2 GIOCATORI
            dim_gruppetto = 2;
            min = 0;
            max = NUMERO_GIOCHI_DA_DUE;
            numero -=1;
        }

        // GENERA IL GRUPPETTO DI GIOCATORI
        for(int i = 0; i < dim_gruppetto; i++) {
            segnaposto = rand_int(0, numero_giocatori_vivi - 1);
            gruppetto[i] = giocatori[giocatori_vivi[segnaposto]];

            // salva la presenza di giocatori utente e di Riccardo Scateni
            if(is_player(gruppetto[i])) {
                pla = true;

                if(is_frontman(gruppetto[i])) {
                    pos_frontman = i;
                    frontman = true;
                }
            }

            giocatori_vivi[segnaposto] = giocatori_vivi[numero_giocatori_vivi - 1];
            numero_giocatori_vivi--;
        }


        // SCEGLIE IL GIOCO
        if(frontman) {

            // fa scegliere a Riccardo Scateni il gioco da fare
            printf("\n\nA quale dei seguenti giochi vuoi giocare?");
            for(int i = min; i < max; i++) {
                printf("[%d] -> %s", i, nomi_giochi[i]);
            }
            printf("\n\nRiccardo Scateni");

            id_gioco = get_int(": ", min, max - 1);
        } else {
            id_gioco = rand_int(min, max - 1);
        }


        // GIOCA LA PARTITA
        if(pla) {

            printf("\n\nSi gioca a %s!! (invio)", nomi_giochi[id_gioco]);
            getchar();
            printf("\n\n");

            switch(id_gioco) {
                case PARI_DISPARI:
                    // rivedere
                    winner = pari_o_dispari(gruppetto);
                    break;
                case DADI:
                    winner = dadi(gruppetto);
                    break;
                case PONTE_DI_VETRO:
                    // gioca a ponte di vetro
                    winner = ponte_di_vetro(gruppetto);
                    break;
                default:
                    break;
            }
        } else {
            winner = rand_int(0, dim_gruppetto - 1);
        }


        // FRONTMAN
        if(frontman) {
            for(int i = 0; i < dim_gruppetto; i++) {
                if(is_frontman(gruppetto[i])) {
                    winner = i;
                }
            }
        }


        // AGGGIORNA I DATI DEL VINCITORE
        for(int i = 0; i < dim_gruppetto; i++) {
            if(i == winner) {
                if(is_player(gruppetto[i])) {
                    gruppetto[i].p->tot_giochi_giocati++;
                    gruppetto[i].p->tot_giochi_vinti++;

                    originali[gruppetto[i].id].p->tot_giochi_giocati++;
                    originali[gruppetto[i].id].p->tot_giochi_vinti++;
                }
            } else {
                if(is_player(gruppetto[i])) {
                    gruppetto[i].p->tot_giochi_giocati++;

                    originali[gruppetto[i].id].p->tot_giochi_giocati++;
                }
                gruppetto[i].vivo = false;

                originali[gruppetto[i].id].vivo = false;
            }
        }


        // STAMPA IL VINCITORE E SALVA LA PARTITA
        layout();
        stampa_riga_vuota(1);
        stampa_riga(SPAZIO_SINISTRA, 1, 2, "Ha vinto", print_player(gruppetto[winner]));
        stampa_riga_vuota(1);
        layout();
        printf("Vuoi salvare la partita? (si / no)");

    }



    free(giocatori_vivi);
    free(gruppetto);

    // la coppia di finalisti e' riempita con i due giocatori rimasti in vita
    finalisti[0] = giocatori[0];
    finalisti[1] = giocatori[1];

    return true;
}


