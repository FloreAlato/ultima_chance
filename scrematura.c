//
// Created by davyf on 06/12/2022.
//

#include "scrematura.h"




Elenco **scrematura(int numero_giocatori, int target, Elenco **giocatori, int numero_profili, ProfiloGiocatore *profili) {

    int dim_gruppetti = numero_giocatori / target;
    int totale = numero_giocatori - 1;
    int segnaposto;

    int risultati[target];

    int pos_frontman = -1;
    Elenco **risultato_scrematura = (Elenco **) calloc(target, sizeof(Elenco *));

    // genera "target" gruppetti di dimensione "dim_gruppetti + 1"
    Elenco ***gruppetti = (Elenco ***) malloc(target * sizeof(Elenco **));
    for(int i = 0; i < target; i++) {
        gruppetti[i] = (Elenco **) malloc((dim_gruppetti + 1) * sizeof(Elenco *));
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
                if(is_player(*gruppetti[i][j])) {
                    pla[i] = true;
                    if(strcmp(gruppetti[i][j]->p->nome, "Riccardo Scateni") == 0) {
                        pos_frontman = i;
                    }
                }

                giocatori[segnaposto] = giocatori[totale];
                totale--;
            } else {
                gruppetti[i][j] = &bianco;
            }
        }

    }



    printf("\n\nGruppetti:");
    for(int i = 0; i < target; i++) {
        printf("\n%do gruppo: ( ", i);
        for(int j = 0; j < dim_gruppetti + 1; j++) {
            if(gruppetti[i][j] != NULL) {
                printf("%s ", print_player(*gruppetti[i][j]));
            }
        }
        printf(")");
    }
    getchar();

    printf("\n\nChe la scrematura abbia inizio!!! (invio)");
    getchar();



    int winner, dim;

    // gioca e riduci il numero
    for(int i = 0; i < target; i++) {
        if(pla[i]) {
            printf("\n\nIl %do gruppo gioca a INDOVINA IL NUMERO!!! (invio)", i);
            getchar();

            if(gruppetti[i][dim_gruppetti]->id == -1) {
                dim = dim_gruppetti - 1;
            } else {
                dim = dim_gruppetti;
            }

            // GIOCA A INDOVINA IL NUMERO CON IL GRUPPETTO DI DIMENSIONE DIM
            //winner = indovina_il_numero();
            winner = rand_int(0, dim);




            // FRONTMAN DELLO SPR1D GAME
            if(pos_frontman == i) {
                // fai vincere Riccardo Scateni
                // trova Riccardo Scateni nel gruppetto e lo fa vincere
                int d = 0;
                bool found = false;
                while(d < dim && !found) {
                    if(strcmp(giocatori[i][d].p->nome, "Riccardo Scateni") == 0) {
                        winner = d;
                        found = true;
                    }
                    d++;
                }
            }

            // AGGIORNA I DATI GIOCATORE (rivedere)
            for(int j = 0; j <= dim; j++) {
                if(j == winner) {       // vincitore
                    if(is_player(*gruppetti[i][j])) {
                        gruppetti[i][j]->p->tot_giochi_giocati++;
                        gruppetti[i][j]->p->tot_giochi_vinti++;
                    }
                } else {        // perdente
                    if(is_player(*gruppetti[i][j])) {
                        gruppetti[i][j]->p->tot_giochi_giocati++;
                    }
                    gruppetti[i][j]->vivo = false;
                }
            }

        } else {

            if(gruppetti[i][dim_gruppetti]->id == -1) {
                dim = dim_gruppetti - 1;
            } else {
                dim = dim_gruppetti;
            }
            winner = rand_int(0, dim);

            printf("\nIl %do gruppo ha giocato, e ha vinto %s!!", i, print_player(*gruppetti[i][winner]));

            // uccide i giocatori perdenti
            for(int j = 0; j <= dim; j++) {
                if(j != winner) {       // aggiorna il vincitore
                    gruppetti[i][j]->vivo = false;
                }
            }
        }


        risultato_scrematura[i] = gruppetti[i][winner];

        // CHIEDI DI SALVARE
        printf("\n\nUna partita si e' conclusa, vuoi salvare la partita? (si / no)");
        bool scelta = si_no("\nScelta: ");

        if(scelta) {
            bool fin = save_short(numero_profili, profili);
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
