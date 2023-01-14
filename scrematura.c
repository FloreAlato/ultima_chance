//
// Created by davyf on 06/12/2022.
//

#include "scrematura.h"



// SCREMATURA

// prende l'array dei giocatori e la ridimensiona con il gioco "indovina il numero"
// fa cio' riempiendo fin dall' inizio un numero target di gruppetti di giocatori
// e poi facendo sfidare a turno questi gruppetti fino al raggiungimento della quota
// man mano i vincitori sono salvati nell'array che la funzione ritornera'



Elenco *scrematura(int numero_giocatori, int target, Elenco *giocatori, int numero_profili, ProfiloGiocatore *profili, Elenco *originali) {

    // calcola la dimensione dei gruppetti

    int dim_gruppetti = numero_giocatori / target;
    int totale = numero_giocatori - 1;
    int segnaposto;



    int pos_frontman = -1;      // posizione di Riccardo Scateni nel gruppetto (se presente)
    Elenco *risultato_scrematura = (Elenco *) calloc(target, sizeof(Elenco));       // array risultato

    // genera "target" gruppetti di dimensione "dim_gruppetti + 1"
    // quel "+ 1" serve per dare flessibilita' ai gruppetti, che non sono tutti delle stesse dimensioni

    Elenco **gruppetti = (Elenco **) malloc(target * sizeof(Elenco *));
    for(int i = 0; i < target; i++) {
        gruppetti[i] = (Elenco *) malloc((dim_gruppetti + 1) * sizeof(Elenco));
    }

    Elenco bianco = {
            -1,
            NULL,
            false
    };

    // genera un array di booleani che poi usera' per capire quali gruppetti contengono almeno un giocatore utente
    // risparmia un sacco di iterazioni

    bool *pla = (bool *) calloc(target, sizeof(bool));

    // riempie i gruppetti
    // prende elementi random dall' array in input e li mette nei gruppetti
    // riempie prima le prime file, poi le seconde, etc.
    // poi riempie le ultime posizioni con i giocatori rimanenti, fino a finirli
    // otteniamo cosi' (eventualmente) un paio di gruppetti piu' grandi, tutti all'inizio

    for(int j = 0; j < dim_gruppetti + 1; j++) {

        for(int i = 0; i < target; i++) {
            if(totale >= 0) {
                segnaposto = rand_int(0, totale);
                gruppetti[i][j] = giocatori[segnaposto];

                // controlla se ci sono utenti
                // e se questi sono Riccardo Scateni
                // usa due funzioni apposite
                // is_player() -> funzioni_utili.c (controlla che il giocatore sia un utente, vedi descrizione sopra la funzione)
                // is_frontman() -> funzioni_utili.c (controlla che il giocatore sia utente E che il suo nome sia Riccardo Scateni)

                if(is_player(gruppetti[i][j])) {
                    pla[i] = true;
                    if(is_frontman(gruppetti[i][j])) {
                        pos_frontman = i;
                    }
                }

                // ogni giocatore scelto a caso viene sostituito dall'ultimo in classifica\
                // poi l'array si restringe (non letteralmente) per non scegliere mai lo stesso giocatore

                giocatori[segnaposto] = giocatori[totale];
                totale--;
            } else {

                // i giocatori bianchi hanno id -1
                // il programma usera' questa loro caratteristica per decidere la dimensione del gruppetto
                // infatti questi giocatori sono tutti quelli che, in ultima posizione, non sono riempiti

                gruppetti[i][j] = bianco;
            }
        }

    }


    // stampa i gruppetti
    // sempre debug, ma estetico

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




    int winner, dim;        // id del vincitore e dimensione del gruppetto
    bool found, fin;

    // in questo loop avviene la scrematura vera e propria
    // per ogni gruppetto, il programma ottiene la sua dimensione e poi ricava l'id del vincitore con un gioco

    for(int i = 0; i < target; i++) {

        // la partita avviene solo se ci sono utenti

        if(pla[i]) {
            printf("\n\nIl %do gruppo gioca a INDOVINA IL NUMERO!!! (invio)", i);
            getchar();
            getchar();

            // se l'ultimo giocatore del gruppetto ha id -1, quella posizione e' vuola, e il gruppetto e' uno di quelli piccoli

            if(gruppetti[i][dim_gruppetti].id == -1) {
                dim = dim_gruppetti;
            } else {
                dim = dim_gruppetti + 1;
            }


            // GIOCA A INDOVINA IL NUMERO CON IL GRUPPETTO DI DIMENSIONE DIM

            // qui avviene il gioco
            // indovina_il_numero() -> scrematura.c (priorio come dice il nome)

            winner = indovina_il_numero(dim, gruppetti[i]);


            // FRONTMAN DELLO SPR1D GAME

            // se il gruppetto contiene Riccardo Scateni, viene trovato e sovrascritto il vincitore

            if(pos_frontman == i) {

                found = false;

                for(int d = 0; d < dim && !found; d++) {
                    if(is_frontman(gruppetti[i][d])) {
                        winner = d;
                        found = true;
                    }
                }
            }



            // AGGIORNA I DATI GIOCATORE

            // dopo che un giocatore ha vinto il gioco, lui e gli altri ricevono un boost alle loro statistiche
            // vengono cambiati anche i valori di "originali", che rimanda all'array principale nel main
            // questo serve a rendere universali i risultati della partita

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

            // se il gruppetto non contiene giocatori, il vincitore e' scelto a caso
            // facendo attenzione alla dimensione del gruppetto

            if(gruppetti[i][dim_gruppetti].id == -1) {
                dim = dim_gruppetti - 1;
            } else {
                dim = dim_gruppetti;
            }
            winner = rand_int(0, dim);



            // uccide i giocatori perdenti

            for(int j = 0; j <= dim; j++) {
                if(j != winner) {       // aggiorna il vincitore
                    gruppetti[i][j].vivo = false;

                    originali[gruppetti[i][j].id].vivo = false;
                }
            }
        }


        // l'array finale viene riempina passo passo

        risultato_scrematura[i] = gruppetti[i][winner];



        // STAMPA IL VINCITORE E SALVA LA PARTITA

        // tutte queste funzioni sono estetiche e si trovano in games.c
        // per ora non ce ne preoccupiamo

        printf("\n\n");
        layout();
        stampa_riga_vuota(1);
        stampa_riga(SPAZIO_SINISTRA, 1, 2, "Ha vinto", print_player(gruppetti[i][winner]));
        stampa_riga_vuota(1);
        layout();

        // CHIEDE DI SALVARE

        // la scelta viene raccolta con si_no()
        // si_no() -> funzioni_utili.c (caso particolare di choice_string)

        printf("vuoi salvare la partita? (si / no)");
        bool scelta = si_no("\nScelta: ");

        // se il giocatore vuole salvare, la partita viene salvata con save_short()
        // e se vuole uscire, il programma libera prima tutta la memoria dinamica
        // save_short() -> files.c (salva la partita)

        if(scelta) {
            //fin = save_short(numero_profili, profili);
            fin = save_short(6, numero_profili, profili, false);
            if(fin) {
                printf("\n\nAddio allora! (invio)");
                getchar();
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



    // LIBERA LA MEMORIA

    free(gruppetti);
    free(pla);

    return risultato_scrematura;
}








// GIOCO INDOVINA IL NUMERO


int indovina_il_numero(int numero_giocatori, Elenco *giocatori) {

    // range dei numero da indovinare
    // si restringe per sendere i giocatori cpu un minimo intelligenti

    int max = MAX_INDOVINA;
    int min = MIN_INDOVINA;

    // sceglie il numero random

    int numero = rand_int(min, max);

    // riempie la riga
    // fa parte del layout del gioco

    char *riga = riga_indovina();

    // variabili per far girare la partita

    int winner, tentativo, turno = 0;
    bool vinto = false;

    // il ciclo si ripete fino alla vittoria di un giocatore

    while(!vinto) {

        // stampa il layout del gioco, puramente estetico

        printf("\n\n");
        area_gioco_indovina(numero_giocatori, giocatori, turno, riga, min, max);

        // prende il tentativo dall'utente o lo sceglie a caso
        // a seconda che il giocatore di turno sia utente o meno
        // comunque prende un carattere per far procedere il gioco alla velocita' dell'utente

        printf("[%s]: ", print_player(giocatori[turno]));
        if(is_player(giocatori[turno])) {
            tentativo = get_int("", MIN_INDOVINA, MAX_INDOVINA);
            getchar();
        } else {
            tentativo = rand_int(min, max);
            printf("%d", tentativo);
            getchar();
        }

        // controlla se il numero e' stato indovinato e ferma il gioco
        // altrimenti restringe il campo e marchia la riga

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


        // passa al turno successivo
        // torna a capo una volta finito il giro

        if(turno < numero_giocatori - 1) {
            turno++;
        } else {
            turno = 0;
        }
    }


    return winner;
}










// funzione di layout del gioco indovina il numero
// ne vedrete molte cosi'
// tutte le funzioni contenute qui sono in games.c

void area_gioco_indovina(int numero_giocatori, Elenco *giocatori, int turno, char *riga, int min, int max) {

    layout();
    stampa_riga(SPAZIO_SINISTRA, 1, 2, "Stai giocando a\0", "INDOVINA IL NUMERO\0");        // occupa una riga
    stampa_riga_vuota(2);       // occupa due righe
    stampa_intervallo_indovina(riga, min, max);     // occupa due righe
    stampa_riga_vuota(3);       // occupa tre righe
    stampa_turno(numero_giocatori, giocatori, turno);       // occupa tre righe
    stampa_riga_vuota(ALTEZZA - 11);     // arriva a fine pagina

}





// funzione che riempie la riga per il layout di indovina il numero
// questa riga viene stampata per dare un'idea grafica della posizione del numero da indovinare
// e' solo una stringa di 100 caratteri piena di punti

char *riga_indovina() {

    char *riga = (char *) calloc(100, sizeof(char));

    for(int i = 0; i < 99; i++) {
        riga[i] = '.';
    }
    riga[99] = '\0';

    return riga;
}




// funzione che stampa la riga e il range
// insieme danno una buona idea della posizione del numero segreto

void stampa_intervallo_indovina(char *riga, int min, int max) {
    stampa_riga(SPAZIO_SINISTRA, 0, 3, "[0]", riga, "[999]");
    stampa_riga(SPAZIO_SINISTRA, 0, 5, "[", int_to_string(min), "] < X < [", int_to_string(max), "]");
}
