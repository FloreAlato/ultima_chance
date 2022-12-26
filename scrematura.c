//
// Created by davyf on 06/12/2022.
//

#include "scrematura.h"




Elenco *scrematura(int numero_giocatori, int target, Elenco *giocatori, int numero_profili, ProfiloGiocatore *profili, Elenco *originali) {

    // calcola la dimensione dei gruppetti
    int dim_gruppetti = numero_giocatori / target;
    int totale = numero_giocatori - 1;
    int segnaposto;



    // posizione frontman e risultato finale
    int pos_frontman = -1;
    Elenco *risultato_scrematura = (Elenco *) calloc(target, sizeof(Elenco));

    // genera "target" gruppetti di dimensione "dim_gruppetti + 1"
    Elenco **gruppetti = (Elenco **) malloc(target * sizeof(Elenco *));
    for(int i = 0; i < target; i++) {
        gruppetti[i] = (Elenco *) malloc((dim_gruppetti + 1) * sizeof(Elenco));
    }

    Elenco bianco = {
            -1,
            NULL,
            false
    };

    // genera l'array di booleani che salveranno i profili con giocatori utente
    bool *pla = (bool *) calloc(target, sizeof(bool));

    // riempie i gruppetti
    for(int j = 0; j < dim_gruppetti + 1; j++) {
        // prendi esempio dal vecchio
        for(int i = 0; i < target; i++) {
            if(totale >= 0) {
                segnaposto = rand_int(0, totale);
                gruppetti[i][j] = giocatori[segnaposto];

                // controlla utenti e posizione frontman
                if(is_player(gruppetti[i][j])) {
                    pla[i] = true;
                    if(strcmp(gruppetti[i][j].p->nome, "Riccardo Scateni") == 0) {
                        pos_frontman = i;
                    }
                }

                giocatori[segnaposto] = giocatori[totale];
                totale--;
            } else {
                gruppetti[i][j] = bianco;
            }
        }

    }


    // stampa i gruppetti
    printf("\n\nGruppetti:");
    for(int i = 0; i < target; i++) {
        printf("\n%do gruppo: ( ", i);
        for(int j = 0; j < dim_gruppetti + 1; j++) {
            if(gruppetti[i][j].id > -1) {
                printf("%s ", print_player(gruppetti[i][j]));
            }
        }
        printf(")");
    }
    getchar();

    printf("\n\nChe la scrematura abbia inizio!!! (invio)");
    getchar();




    int winner, dim;
    bool found, fin;

    // gioca e riduci il numero
    for(int i = 0; i < target; i++) {
        if(pla[i]) {
            printf("\n\nIl %do gruppo gioca a INDOVINA IL NUMERO!!! (invio)", i);
            getchar();
            getchar();

            if(gruppetti[i][dim_gruppetti].id == -1) {
                dim = dim_gruppetti;
            } else {
                dim = dim_gruppetti + 1;
            }

            /*printf("\n\n");
            for(int a = 0; a < dim; a++) {
                printf("%s ", print_player(gruppetti[i][a]));
            }
            printf("\n\n");*/


            // GIOCA A INDOVINA IL NUMERO CON IL GRUPPETTO DI DIMENSIONE DIM
            winner = indovina_il_numero(dim, gruppetti[i]);


            // FRONTMAN DELLO SPR1D GAME
            if(pos_frontman == i) {

                // trova riccardo e lo fa vincere
                found = false;

                for(int d = 0; d < dim && !found; d++) {
                    if(is_frontman(gruppetti[i][d])) {
                        winner = d;
                        found = true;
                    }
                }
            }



            // AGGIORNA I DATI GIOCATORE (rivedere)
            for(int j = 0; j < dim; j++) {
                if(j == winner) {       // vincitore
                    if(is_player(gruppetti[i][j])) {
                        gruppetti[i][j].p->tot_giochi_giocati++;
                        gruppetti[i][j].p->tot_giochi_vinti++;

                        originali[gruppetti[i][j].id].p->tot_giochi_giocati++;
                        originali[gruppetti[i][j].id].p->tot_giochi_vinti++;
                    }
                } else {        // perdente
                    if(is_player(gruppetti[i][j])) {
                        gruppetti[i][j].p->tot_giochi_giocati++;

                        originali[gruppetti[i][j].id].p->tot_giochi_giocati++;
                    }
                    gruppetti[i][j].vivo = false;

                    originali[gruppetti[i][j].id].vivo = false;
                }
            }


        } else {

            if(gruppetti[i][dim_gruppetti].id == -1) {
                dim = dim_gruppetti - 1;
            } else {
                dim = dim_gruppetti;
            }
            winner = rand_int(0, dim);

            //printf("\nIl %do gruppo ha giocato, e ha vinto %s!!", i, print_player(gruppetti[i][winner]));

            // uccide i giocatori perdenti
            for(int j = 0; j <= dim; j++) {
                if(j != winner) {       // aggiorna il vincitore
                    gruppetti[i][j].vivo = false;

                    originali[gruppetti[i][j].id].vivo = false;
                }
            }
        }


        risultato_scrematura[i] = gruppetti[i][winner];



        // STAMPA IL VINCITORE E SALVA LA PARTITA
        printf("\n\n");
        layout();
        stampa_riga_vuota(1);
        stampa_riga(SPAZIO_SINISTRA, 1, 2, "Ha vinto", print_player(gruppetti[i][winner]));
        stampa_riga_vuota(1);
        layout();

        // CHIEDI DI SALVARE
        printf("vuoi salvare la partita? (si / no)");
        bool scelta = si_no("\nScelta: ");

        if(scelta) {
            fin = save_short(numero_profili, profili);
            if(fin) {
                printf("\n\nAddio allora! (invio)");
                getchar();
                free(profili);
                free(giocatori);
                free(gruppetti);
                free(pla);
                free(risultato_scrematura);
                exit(0);
            }
        } else {
            printf("\n\nVa bene, allora continuiamo");
        }
    }




    free(gruppetti);
    free(pla);

    return risultato_scrematura;
}










int indovina_il_numero(int numero_giocatori, Elenco *giocatori) {

    int max = MAX_INDOVINA;
    int min = MIN_INDOVINA;

    int numero = rand_int(min, max);

    char *riga = riga_indovina();

    int winner, tentativo, turno = 0;
    bool vinto = false;

    while(!vinto) {

        // stampa la partita
        printf("\n\n");
        area_gioco_indovina(numero_giocatori, giocatori, turno, riga, min, max);

        // prende il tentativo dall'utente o lo sceglie a caso
        printf("[%s]: ", print_player(giocatori[turno]));
        if(is_player(giocatori[turno])) {
            tentativo = get_int("", MIN_INDOVINA, MAX_INDOVINA);
            getchar();
        } else {
            tentativo = rand_int(min, max);
            printf("%d", tentativo);
            getchar();
        }

        // controlla se ci ha preso
        if(tentativo == numero) {
            vinto = true;
            winner = turno;

        } else if(tentativo < numero) {
            min = tentativo;

            riga[tentativo / 10] = 'B';
        } else {
            max = tentativo;

            riga[tentativo / 10] = 'A';
        }


        // aggiorna il turno
        if(turno < numero_giocatori - 1) {
            turno++;
        } else {
            turno = 0;
        }
    }


    return winner;
}












void area_gioco_indovina(int numero_giocatori, Elenco *giocatori, int turno, char *riga, int min, int max) {

    // inizio
    printf("|");
    for(int i = 0; i < LARGHEZZA; i++) {
        printf("=");
    }
    printf("|\n");

    // mezzo
    stampa_riga(SPAZIO_SINISTRA, 1, 2, "Stai giocando a\0", "INDOVINA IL NUMERO\0");        // occupa una riga
    stampa_riga_vuota(2);       // occupa due righe
    stampa_intervallo_indovina(riga, min, max);     // occupa due righe
    stampa_riga_vuota(3);       // occupa tre righe
    stampa_turno(numero_giocatori, giocatori, turno);       // occupa tre righe
    stampa_riga_vuota(ALTEZZA - 11);     // arriva a fine pagina

}




char *riga_indovina() {

    char *riga = (char *) calloc(100, sizeof(char));

    for(int i = 0; i < 99; i++) {
        riga[i] = '.';
    }
    riga[99] = '\0';

    return riga;
}




void stampa_intervallo_indovina(char *riga, int min, int max) {
    stampa_riga(SPAZIO_SINISTRA, 0, 3, "[0]", riga, "[999]");
    stampa_riga(SPAZIO_SINISTRA, 0, 5, "[", int_to_string(min), "] < X < [", int_to_string(max), "]");
}
