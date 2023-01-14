//
// Created by davyf on 23/12/2022.
//

#include "finale.h"


// matrice con l'aspetto delle carte per la stampa ordinata

char card_img[5][11] = {
        " _______ ",
        "|      %s|",
        "|   %s  |",
        "|%s      |",
        " ------- "
};





// GIOCO BLACKJACK

int black_jack(Elenco *finalisti) {

    // variabili utili

    int dim_mazzo;
    int dim[2];
    int punti[2];
    int segnaposto, winner;


    // il ciclo si ripete in caso di pareggio

    do {

        // la dimensione dei mazzi parte da 2
        // quella del mazzo a 52
        // i punti da 0

        dim[0] = dim[1] = 2;
        punti[0] = punti[1] = 0;
        dim_mazzo = 52;

        // alloca e riempie il mazzo principale

        carta *mazzo = (carta *) calloc(dim_mazzo, sizeof(carta));
        int c = 0;
        for(int i = 0; i < 4; i++) {
            for(int j = 1; j <= 13; j++) {
                mazzo[c].seme = (semi)i;
                mazzo[c].valore = j;
                c++;
            }
        }

        // alloca i due mazzi dei giocatori

        carta **mazzi = (carta **) calloc(2, sizeof(carta *));
        mazzi[0] = (carta *) malloc(sizeof(carta) * dim[0]);
        mazzi[1] = (carta *) malloc(sizeof(carta) * dim[1]);

        // riempie i mazzi con le prime due carte
        // estratte casualmente con il solito metodo

        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                segnaposto = rand_int(0, dim_mazzo);
                mazzi[i][j] = mazzo[segnaposto];
                mazzo[segnaposto] = mazzo[dim_mazzo - 1];
                dim_mazzo--;

                // per le prime due carte, l'asso vale sempre 11

                if(mazzi[i][j].valore == 1) {
                    punti[i] += 11;
                } else if(mazzi[i][j].valore > 10) {
                    punti[i] += 10;
                } else {
                    punti[i] += mazzi[i][j].valore;
                }
            }
        }

        // COMINCIA LA PARTITA

        // va avnati finche' entrambi i giocatori proseguono

        int risposta;
        bool continua[2] = {true, true};
        bool i = false, altra_carta;

        while(continua[0] || continua[1]) {

            // per ogni turno stampa il layout e chiede all'utente se vuole una nuova carta

            printf("\n\n");
            area_gioco_black(finalisti, dim, mazzi, punti);
            printf("Vuoi un'altra carta, %s? (si / no)", print_player(finalisti[(int)i]));

            // il computer vuole rischiare
            // rifiuta una carta solo se raggiunge 20
            // altrimenti vincerebbe sempre (si', parlo per esperienza)

            if(is_player(finalisti[(int)i])) {
                altra_carta = si_no("\nRisposta: ");
                getchar();
            } else {
                if(punti[(int)i] < 20) {
                    altra_carta = true;
                    printf("\nRisposta: si");
                } else {
                    altra_carta = false;
                    printf("\nRisposta: no");
                }
                getchar();
            }

            // la nuova carta viene aggiunta con il metodo che uso un po' ovunque
            // i mazzi vengono riallocati e riempiti casualmente
            // con il mazzo principale che si riduce pian piano (non letteralmente)

            if(altra_carta) {
                dim[(int)i] += 1;
                mazzi[(int)i] = (carta *) realloc(mazzi[(int)i], dim[(int)i] * sizeof(carta *));


                segnaposto = rand_int(0, dim_mazzo - 1);
                mazzi[(int)i][dim[(int)i] - 1] = mazzo[segnaposto];
                mazzo[segnaposto] = mazzo[dim_mazzo - 1];
                dim_mazzo--;

                // controlla il punteggio

                if(mazzi[(int)i][dim[(int)i - 1]].valore == 1) {

                    // se e' giocatore, fa scegliere il valore dell' asso
                    // altrimenti vale sempre 1

                    if(is_player(finalisti[(int)i])) {

                        layout();
                        stampa_riga(SPAZIO_SINISTRA, 1, 6, "Che valore vuoi dare all'asso? (1 / 11)");
                        stampa_riga_vuota(1);
                        do {
                            risposta = get_int("\nRisposta: ", 1, 11);

                            if (risposta == 1) {
                                punti[(int)i] += 1;
                            } else if (risposta == 11) {
                                punti[(int)i] += 11;
                            } else {
                                printf("\nIl valore puo' essere solo 1 o 11!");
                            }

                        } while (risposta != 1 && risposta != 11);
                    } else {
                        punti[(int)i] += 1;
                    }

                    // se non e' asso, differenzia per le figure
                    // o assegna semplicemente il valore

                } else if(mazzi[(int)i][dim[(int)i] - 1].valore > 10) {
                    punti[(int)i] += 10;
                } else {
                    punti[(int)i] += mazzi[(int)i][dim[(int)i] - 1].valore;
                }

            } else {
                continua[(int)i] = false;
            }


            // controlla il punteggio
            // se uno dei giocatori supera 21, entrambi si fermano
            // e vince l'avversario

            if(punti[(int)i] > 21) {
                winner = (int)!i;
                continua[0] = false;
                continua[1] = false;
            }


            // ad ogni turno i si inverte per far giocare l'avversario

            if(continua[(int)!i]) {
                i = !i;
            }
        }


        printf("\n\n");

        // stampa vincitore

        if(punti[0] == punti[1]) {      // se i giocatori pareggiano
            printf("\n\n");
            layout();
            stampa_riga_vuota(1);
            stampa_riga(SPAZIO_SINISTRA, 0, 1, "Pareggio! Giochiamo di nuovo!");
            stampa_riga_vuota(1);
            layout();

        } else {        // se vince uno dei due
            layout();
            stampa_riga_vuota(1);
            stampa_riga(SPAZIO_SINISTRA, 0, 3, "Ha vinto ", print_player(finalisti[winner]), "!!!!!");
            stampa_riga_vuota(1);
            stampa_riga(SPAZIO_SINISTRA, 1, 4, "Punti", print_player(finalisti[0]), "->", int_to_string(punti[0]));
            stampa_riga(SPAZIO_SINISTRA, 1, 4, "Punti", print_player(finalisti[1]), "->", int_to_string(punti[1]));
            stampa_riga_vuota(1);
            layout();
        }

        free(mazzo);
        free(mazzi);

    } while(punti[0] == punti[1]);


    return winner;
}






// funzione di layout di blackjack
// nomenclatura diversa perche' e' la prima che ho scritto

void area_gioco_black(Elenco *finalisti, int *dim, carta **mazzi, int *punti) {

    layout();
    stampa_riga_vuota(3);       // occupa 3 righe
    stampa_riga(SPAZIO_SINISTRA, 0, 5, "Carte di ", print_player(finalisti[0]), " (", int_to_string(punti[0]), " punti)");       // occupa una riga
    ricorsione_stampa_carte(mazzi[0], 0, dim[0]);       // occupa 5 righe
    stampa_riga(SPAZIO_SINISTRA, 0, 5, "Carte di ", print_player(finalisti[1]), " (", int_to_string(punti[1]), " punti)");       // occupa una riga
    ricorsione_stampa_carte(mazzi[1], 0, dim[1]);       // occupa 5 righe
    stampa_riga_vuota(ALTEZZA - 15);
}




// stampa le carte in modo ordinato
// itera fra le righe dell'immaggine della carta a inizio file
// e stampa i valori corrispondenti tramite un lunghissimo gioco di switch e valori
// prende anche misure per far si che le carte siano sempre della stessa larghezza

void stampa_carte(carta *carta, int inizio, int fine) {


    int i, j;
    char scrivi[4] = "13\0";


    for(j = 0; j < 5; j++) {
        printf("|  ");
        for(i = inizio; i < fine; i++) {

            if(j == 2) {
                if(carta[i].valore > 1 && carta[i].valore < 11) {
                    if(carta[i].valore == 10) {
                        strcpy(scrivi, "10\0");
                    } else {
                        scrivi[0] = (char)(carta[i].valore + 48);
                        scrivi[1] = ' ';
                        scrivi[2] = '\0';
                    }
                } else {

                    switch (carta[i].valore) {
                        case 1:
                            strcpy(scrivi, "A \0");
                            break;
                        case 11:
                            strcpy(scrivi, "J \0");
                            break;
                        case 12:
                            strcpy(scrivi, "Q \0");
                            break;
                        case 13:
                            strcpy(scrivi, "K \0");
                            break;
                    }
                }
            } else {
                // i semi vengono stampati come le figure
                switch (carta[i].seme) {
                    case cuori:
                        strcpy(scrivi, "C\0");
                        break;
                    case quadri:
                        strcpy(scrivi, "Q\0");
                        break;
                    case fiori:
                        strcpy(scrivi, "F\0");
                        break;
                    case picche:
                        strcpy(scrivi, "P\0");
                        break;
                }
            }

            printf(card_img[j], scrivi);
            printf("   ");
        }
        for(int a = 0; a < LARGHEZZA - (13 * (fine - inizio)); a++) {
            printf(" ");
        }
        // poi si va a capo
        printf("|\n");
    }
}



// usata insieme alla funzione presedente, stampa le carte in modo ricorsivo
// stampa STEP carte poi va a capo


void ricorsione_stampa_carte(carta *carta, int inizio, int fine) {

    if(fine <= inizio + STEP) {
        stampa_carte(carta, inizio, fine);
    } else {
        stampa_carte(carta, inizio, inizio + STEP);
        ricorsione_stampa_carte(carta, inizio + STEP, fine);
    }
}

