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
            winner = indovina_il_numero(dim, *gruppetti[i]);


            printf("\n\n\nIl frontman si trova nel %do gruppetto", pos_frontman);


            // FRONTMAN DELLO SPR1D GAME
            if(pos_frontman == i) {

                // trova riccardo e lo fa vincere
                bool found = false;

                for(int d = 0; d < dim && !found; d++) {
                    if(is_player(*gruppetti[i][d]) && strcmp(gruppetti[i][d]->p->nome, "Riccardo Scateni") == 0) {
                        winner = d;
                        found = true;
                    }
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















int indovina_il_numero(int numero_giocatori, Elenco *giocatori) {

    game_cell *eventi = (game_cell *) calloc(9, sizeof(game_cell));



    char *riga = riga_indovina();


    // inizializza le componenti della partita
    nome_gioco(&eventi[0], INDOVINA);
    layout_riga(&eventi[1], riga, 3);
    layout_turni(&eventi[3], giocatori, numero_giocatori, 9);

    area_gioco(6, eventi);


    getchar();
    //prossimo_turno(eventi, giocatori, numero_giocatori, 1);
    aggiorna_riga(eventi, 700, 500);

    area_gioco(6, eventi);



    free(eventi);

    return rand_int(0, numero_giocatori - 1);
}








char *riga_indovina() {

    char *riga = (char *) calloc(100, sizeof(char));

    for(int i = 0; i < 99; i++) {
        riga[i] = '.';
    }
    riga[99] = '\0';

    return riga;
}






void layout_riga(game_cell *evento, char *riga, int pos) {

    char **frasi_riga = (char **) calloc(3, sizeof(char *));
    frasi_riga[0] = (char *) malloc(sizeof(char) * 4);
    strcpy(frasi_riga[0], "[0]\0");
    frasi_riga[1] = riga;
    frasi_riga[2] = (char *) malloc(sizeof(char) * 6);
    strcpy(frasi_riga[2], "[999]\0");

    char **frasi_conteggio = (char **) calloc(5, sizeof(char *));

    for(int i = 0; i < 5; i++) {
        frasi_conteggio[i] = (char *) malloc(sizeof(char) * 10);
    }

    strcpy(frasi_conteggio[0], "[");
    strcpy(frasi_conteggio[2], "] < X < [");
    strcpy(frasi_conteggio[4], "]");

    frasi_conteggio[1] = int_to_string(MIN_INDOVINA);
    frasi_conteggio[3] = int_to_string(MAX_INDOVINA);

    evento->y = pos;
    evento->n = 3;
    evento->x = SPAZIO_SINISTRA;
    evento->content = frasi_riga;

    (evento + 1)->y = pos + 1;
    (evento + 1)->n = 5;
    (evento + 1)->x = SPAZIO_SINISTRA;
    (evento + 1)->content = frasi_conteggio;
}







void aggiorna_riga(game_cell *lista_eventi, int tentativo, int numero) {

    if(tentativo < numero) {
        lista_eventi[1].content[1][tentativo / 10] = 'B';

        lista_eventi[2].content[1] = int_to_string(tentativo);

    } else if(tentativo > numero) {
        lista_eventi[1].content[1][tentativo / 10] = 'A';

        lista_eventi[2].content[3] = int_to_string(tentativo);

    } else {
        lista_eventi[1].content[1][tentativo / 10] = 'X';
    }
}