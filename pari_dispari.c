//
// Created by davyf on 26/12/2022.
//


#include "giochi.h"


int pari_o_dispari(Elenco *giocatori) {

    bool pla[2] = {false, false};
    char opzioni[2][10] = {"pari", "dispari"};
    int dita[2];
    int winner;

    // se il primo giocatore non e' utente, inizia il secondo
    if(!is_player(giocatori[(int)pla[0]])) {
        pla[0] = !pla[0];
    }

    printf("\n\n");
    layout_pari(giocatori, "non assegnato...", "non assegnato...", "Vuoi essere pari o dispari? (pari / dispari)", pla[0], 0, 0);
    printf("%s: ", print_player(giocatori[(int)pla[0]]));
    pla[1] = (bool) choice_string("", 2, opzioni);

    printf("\n\n");
    layout_pari(giocatori, opzioni[(int)pla[1]], opzioni[(int)!pla[1]], "Quante dita vuoi buttare? (da 0 a 5)", pla[0], 0, 0);
    printf("%s: ", print_player(giocatori[(int)pla[0]]));
    dita[0] = get_int("", 0, 5);

    printf("\n\n");
    layout_pari(giocatori, opzioni[(int)pla[1]], opzioni[(int)!pla[1]], "Quante dita vuoi buttare? (da 0 a 5)", pla[0], dita[0], 0);
    printf("%s: ", print_player(giocatori[(int)!pla[0]]));
    if(is_player(giocatori[(int)!pla[0]])) {
        dita[1] = get_int("", 0, 5);
        getchar();
        getchar();
    } else {
        dita[1] = rand_int(0, 5);
        printf("%c", int_to_string(dita[1])[2]);
        getchar();
        getchar();
    }

    printf("\n\n");
    layout_pari(giocatori, opzioni[(int)pla[1]], opzioni[(int)!pla[1]], "La partita si conclude", pla[0], dita[0], dita[1]);
    printf("La somma vale %d (invio)", dita[0] + dita[1]);
    getchar();

    if((dita[0] + dita[1]) % 2 == 0) {       // la somma e' pari
        if(!pla[1]) {
            winner = (int)pla[0];
        } else {
            winner = (int)!pla[1];
        }
    } else {
        if(pla[1]) {
            winner = (int)pla[0];
        } else {
            winner = (int)!pla[0];
        }
    }

    return winner;
}






void layout_pari(Elenco *giocatori, char *frase1, char *frase2, char *frase3, bool i, int dita1, int dita2) {
    layout();
    stampa_riga(SPAZIO_SINISTRA, 1, 2, "Stai giocando a", "PARI O DISPARI");     // occupa una riga
    stampa_riga_vuota(3);       // occupa tre righe
    stampa_riga(SPAZIO_SINISTRA, 1, 3, print_player(giocatori[(int)i]), "->", frase1);        // occupa una riga
    stampa_riga(SPAZIO_SINISTRA, 1, 2, "Dita buttate:", int_to_string(dita1));      // occupa una riga
    stampa_riga_vuota(2);       // occupa due righe
    stampa_riga(SPAZIO_SINISTRA, 1, 3, print_player(giocatori[(int)!i]), "->", frase2);        // occupa una riga
    stampa_riga(SPAZIO_SINISTRA, 1, 2, "Dita buttate:", int_to_string(dita2));      // occupa una riga
    stampa_riga_vuota(6);       // occupa sei righe
    stampa_riga(SPAZIO_SINISTRA, 0, 1, frase3);       // occupa una riga
    stampa_riga_vuota(ALTEZZA - 17);
}
