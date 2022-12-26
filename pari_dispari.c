//
// Created by davyf on 26/12/2022.
//


#include "giochi.h"


int pari_o_dispari(Elenco *giocatori) {

    bool i = false;
    char opzioni[2][10] = {"pari", "dispari"};
    int dita[2] = {0, 0};
    int winner;

    if(!is_player(giocatori[i])) {
        i = !i;
    }

    layout_pari(giocatori, "non assegnato...", "non assegnato...", "Scegli se essere pari o dispari (pari / dispari)", i);
    printf("%s", print_player(giocatori[(int)i]));
    bool scelta = choice_string(": ", 2, opzioni);

    printf("\n\n");
    layout_pari(giocatori, opzioni[(int)i], opzioni[(int)!i], "Quante dita vuoi buttare? (da 0 a 5)", i);
    printf("%s: ", print_player(giocatori[(int)i]));
    dita[(int)i] = get_int("", 0, 5);
    getchar();

    printf("\n\n");
    layout_pari(giocatori, opzioni[(int)i], opzioni[(int)!i], "Quante dita vuoi buttare? (da 0 a 5)", i);

    if(is_player(giocatori[(int)!i])) {
        dita[(int)!i] = get_int("", 0, 5);
    } else {
        dita[(int)!i] = rand_int(0, 5);
        printf("%s: %s", print_player(giocatori[(int)!i]), int_to_string(dita[(int)!i]));
        getchar();
    }

    printf("\n\n\nLa somma e' %s", opzioni[(dita[(int)i] + dita[(int)!i]) == 0]);


    return 0;
}






void layout_pari(Elenco *giocatori, char *frase1, char *frase2, char *frase3, bool i) {
    layout();
    stampa_riga(SPAZIO_SINISTRA, 1, 2, "Stai giocando a", "PARI O DISPARI");     // occupa una riga
    stampa_riga_vuota(3);       // occupa tre righe
    stampa_riga(SPAZIO_SINISTRA, 1, 3, print_player(giocatori[(int)i]), "->", frase1);        // occupa una riga
    stampa_riga(SPAZIO_SINISTRA, 1, 3, print_player(giocatori[(int)!i]), "->", frase2);        // occupa una riga
    stampa_riga_vuota(5);       // occupa cinque righe
    stampa_riga(SPAZIO_SINISTRA, 0, 1, frase3);       // occupa una riga
    stampa_riga_vuota(ALTEZZA - 12);
}
