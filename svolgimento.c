//
// Created by davyf on 25/12/2022.
//

#include "svolgimento.h"



// matrice con i nomi dei giochi

char nomi_giochi[NUMERO_GIOCHI_DA_QUATTRO][20] = {
        "Pari o Dispari",
        "Dadi",
        "Morra Cinese",
        "Murra",
        "Ponte di Vetro"
};







// FUNZIONE SVOLGIMENTO

// prende una array di giocatori e li elimina con vari giochi finche' ne restano due
// salva anche la partita e controlla il frontman dello spr1d game



Elenco *svolgimento(int numero_giocatori, Elenco *giocatori, int numero_giocatori_originali, Elenco *originali, int numero_profili, ProfiloGiocatore *profili, int numero_giocatori_veri) {

    int numero_giocatori_vivi = numero_giocatori;
    int r, dim_gruppetto, segnaposto;

    // array di interi che contiene i giocatori ancora vivi, per fare i gruppetti (provvisorio)

    int *giocatori_vivi = (int *) calloc(numero_giocatori_vivi, sizeof(int));
    for(int i = 0; i < numero_giocatori_vivi; i++) {
        giocatori_vivi[i] = i;
    }

    // gruppetto, come nella scrematura

    Elenco *gruppetto = (Elenco *) calloc(4, sizeof(Elenco));


    // variabili per il controllo del loop e del frontman

    bool pla = false;
    bool frontman = false;
    bool trovato = false;
    int pos_frontman;

    int id_gioco, winner, min, max;

    // PARTITA

    while(numero_giocatori_vivi > 2) {

        pla = false;
        frontman = false;
        trovato = false;

        // SCEGLIE SE FAR GIOCARE DUE O QUATTRO GIOCATORI

        // questa decisione avviene casualmente e precede l'eventuale scelta del gioco da parte del frontman
        // vengono settati i limiti del range che verranno usati per scegliere il gioco
        // viene anche decisa la dimensione del gruppetto

        r = rand_int(0, 1);
        if(r && numero_giocatori_vivi > 4) {
            dim_gruppetto = 4;

            min = NUMERO_GIOCHI_DA_DUE;
            max = NUMERO_GIOCHI_DA_QUATTRO - 1;
        } else {
            dim_gruppetto = 2;

            min = 0;
            max = NUMERO_GIOCHI_DA_DUE - 1;
        }


        // GENERA IL GRUPPETTO DI GIOCATORI PER LA PARTITA IMMINENTE

        // proprio come nella scrematura
        // qui pla ci dice se il gruppetto contiene almeno un giocatore
        // e frontman se uno di quei giocatori e' Riccardo Scateni

        for(int i = 0; i < dim_gruppetto; i++) {
            segnaposto = rand_int(0, numero_giocatori_vivi - 1);
            gruppetto[i] = giocatori[giocatori_vivi[segnaposto]];

            if(is_player(gruppetto[i])) {
                pla = true;
                if(is_frontman(gruppetto[i])) {
                    frontman = true;
                    pos_frontman = i;
                }
            }

            giocatori_vivi[segnaposto] = giocatori_vivi[numero_giocatori_vivi - 1];
            numero_giocatori_vivi--;
        }


        // SCEGLIE IL GIOCO DA GIOCARE

        // se il gruppetto contiene Scateni, gli lascia decidere il gioco
        // entro i limiti del numero di giocatori per gruppetto

        if(frontman) {
            printf("\n\n");
            layout();
            stampa_riga_vuota(1);
            stampa_riga(LARGHEZZA / 2 - 30 , 0, 1, "FRONTMAN DELLO SPRID GAME!!!!!");
            stampa_riga_vuota(1);
            layout();

            // funziona come tutte le altre scelte in questo programma

            printf("\nQuale dei seguenti giochi vuoi scegliere?");
            printf("\n\nGiochi disponibili: ");
            if(min == 4 && max == 4) {
                printf("\n[4] -> %s", nomi_giochi[4]);
            }
            for(int i = min; i < max; i++) {
                printf("\n[%d] -> %s", i, nomi_giochi[i]);
            }
            id_gioco = get_int("\nRiccardo Scateni: ", min, max);
        } else {

            // se non lo fa Scateni, il programma sceglie il gioco a caso

            id_gioco = rand_int(min, max);
        }




        // GIOCA LA PARTITA E OTTIENE IL VINCITORE

        // il winner viene assegnato al vincitore di uno dei giochi
        // il programma stampa un piccolo messaggio introduttivo e avvia la partita
        // ma solo se il gruppetto contiene un giocatore utente, altrimenti risparmia tempo e lo sceglie a caso

        if(pla) {
            switch (id_gioco) {
                case PARI_DISPARI:
                    printf("\n\nSi gioca a %s! (invio)", nomi_giochi[PARI_DISPARI]);
                    getchar();
                    printf("\n\n");
                    winner = pari_o_dispari(gruppetto);
                    break;
                case DADI:
                    printf("\n\nSi gioca a %s! (invio)", nomi_giochi[DADI]);
                    getchar();
                    printf("\n\n");
                    winner = dadi(gruppetto);
                    break;
                case MORRA_CINESE:
                    printf("\n\nSi gioca a %s! (invio)", nomi_giochi[MORRA_CINESE]);
                    getchar();
                    printf("\n\n");
                    winner = morra_cinese(gruppetto);
                    break;
                case MURRA:
                    printf("\n\nSi gioca a %s! (invio)", nomi_giochi[MURRA]);
                    getchar();
                    printf("\n\n");
                    winner = murra(gruppetto);
                    break;
                case PONTE_DI_VETRO:
                    printf("\n\nSi gioca a %s! (invio)", nomi_giochi[PONTE_DI_VETRO]);
                    getchar();
                    printf("\n\n");
                    winner = ponte_di_vetro(gruppetto);
                    break;
                default:
                    break;
            }
        } else {
            winner = rand_int(0, dim_gruppetto - 1);
        }



        // CONTROLLA IL FRONTMAN

        // se c'e' Scateni, il vincitore e' lui

        if(frontman) {
            winner = pos_frontman;
        }


        // AGGIORNA I DATI DEI GIOCATORI

        // pari pari a quello della scrematura

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

        // idem che per la scrematura
        // cambia pero' il salvataggio della partita
        // dato che il file conterra' una partita in corso
        // ma la funzione e' la stessa, vedi files.c

        printf("\n\n");
        layout();
        stampa_riga_vuota(1);
        stampa_riga(SPAZIO_SINISTRA, 1, 2, "Ha vinto", print_player(gruppetto[winner]));
        stampa_riga_vuota(1);
        layout();

        // CHIEDI DI SALVARE
        printf("vuoi salvare la partita? (si / no)");
        bool scelta = si_no("\nScelta: ");

        if(scelta) {
            // salva il gioco con la partita in corso (funzione da scrivere)
            bool fin = save_short(6, numero_profili, profili, true, numero_giocatori_originali, numero_giocatori_veri, originali);

            if(fin) {
                printf("\n\nAddio allora! (invio)");
                getchar();
                free(profili);
                free(giocatori);
                free(gruppetto);
                free(giocatori_vivi);
                exit(0);
            }
        } else {
            printf("\n\nVa bene, allora continuiamo");
        }


        // IMMETTE DI NUOVO IL VINCITORE NELL'ARRAY PRINCIPALE

        // dato che i giocatori presi dai gruppetti vengono rimossi dall'array di partenza
        // gisogna reintrodurre il vincitore
        // nell'ultima posizione

        numero_giocatori_vivi += 1;
        for(int i = 0; i < numero_giocatori && !trovato; i++) {
            if(giocatori[i].id == gruppetto[winner].id) {
                giocatori_vivi[numero_giocatori_vivi - 1] = i;
                trovato = true;
            }
        }


        // STAMPA I GIOCATORI IN VITA (debug)

        printf("\n\nGiocatori in vita:");
        for(int i = 0; i < numero_giocatori_vivi; i++) {
            printf("\n%d", giocatori[giocatori_vivi[i]].id);
        }
        getchar();
    }






    // ALLOCA E POPOLA LA COPPIA DI FINALISTI

    Elenco *finalisti = (Elenco *) calloc(2, sizeof(Elenco));

    for(int i = 0; i < numero_giocatori_vivi; i++) {
        finalisti[i] = giocatori[giocatori_vivi[i]];
    }


    // LIBERA LA MEMORIA DINAMICA

    free(giocatori_vivi);
    free(gruppetto);

    return finalisti;
}


