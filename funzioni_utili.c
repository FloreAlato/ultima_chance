//
// Created by davyf on 30/11/2022.
//

#include "funzioni_utili.h"




int choice_string(char *query, int num, char options[num][DIM_OPZIONE]) {
    int i;
    char risposta[20];

    while(true) {
        printf("%s", query);
        scanf(" %s", risposta);

        for(i = 0; i < num; i++) {
            if(strcmp(risposta, options[i]) == 0) {
                return i;
            }
        }
        printf("\nLa risposta inserita non e' fra le opzioni\n");
    }
}










int get_int(char *query, int min, int max) {

    char num[4];
    int number;
    bool check = true;

    do {
        //pone la domanda e raccoglie la risposta sotto forma di stringa
        printf("%s", query);
        scanf(" %s", num);

        //controlla che la stringa sia numerica con is_numeric()
        if(is_numeric(num) == true) {
            //se lo è, la converte in un intero con string_to_int()
            number = string_to_int(num);
            check = true;
            //poi controlla che sia incluso nell'intervallo
            if(number < min) {
                printf("\nIl numero deve essere maggiore di o uguale a %d\n", min);
                printf("Dai, ritenta...\n\n");
                check = false;
            } else if(number > max) {
                printf("\nIl numero deve essere maggiore di o uguale a %d\n", max);
                printf("Dai, ritenta...\n\n");
                check = false;
            }
        } else {
            printf("\nNon numero!!\nRitenta...\n\n");
            check = false;
        }
        //in ogni altro caso ripete il loop
    } while(check == false);

    // poi ritorna il numero ottenuto
    return number;
}




int string_to_int(char *str) {

    int k, p, total = 0;

    //itera per la stringa da destra verso sinistra escludendo il carattere di fine stringa
    for(k = (int)strlen(str) - 1, p = 0; k >= 0; k--, p++) {

        //calcola il calore di ogni cifra e lo aggiunde al risultato
        total += ((int) str[k] - 48) * (int)pow(10, p);
    }

    // restituisce l'intero corrispondente
    return total;
}




char *int_to_string(int numero) {

    char *result = (char *) calloc(4, sizeof(char));

    if(numero >= 0) {
        // altrimenti converte l'id in stringa e ci mette "Giocatore " davanti
        int powers[3] = {100, 10, 1};
        int num = numero;
        for(int i = 0; i < 3; i++) {
            result[i] = (char)((num / powers[i]) + 48);
            num %= powers[i];
        }
    }
    return result;
}





bool is_numeric(char *num) {

    // itera fra i caratteri e controlla dove sono nell'ordine ascii
    for(int i = 0; i < strlen(num); i++) {
        if((int)num[i] < 48 || (int)num[i] > 57) {
            return false;
        }
    }

    return true;
}





Elenco *componi_elenco(int dim) {

    int i;
    Elenco *players = NULL;

    // alloca l'Elenco
    players = (Elenco *) calloc(dim, sizeof(Elenco));

    // riempie gli id progressivamente, i profili a NULL, e lo stato vitale a true
    for(i = 0; i < dim; i++) {
        players[i].id = i;
        players[i].p = NULL;
        players[i].vivo = true;
    }

    // ritorna l'array
    return players;
}


bool is_player(Elenco player) {
    if(player.p == NULL) {
        return false;
    } else {
        return true;
    }
}



char *print_player(Elenco player) {

    char *ret = calloc(14, sizeof(char));

    // se ha un profilo, restituisce il nome
    if(is_player(player)) {
        return player.p->nome;
    } else {
        strcpy(ret, "Giocatore \0");
        ret = strcat(ret, int_to_string(player.id));

        /*if(player.id >= 0) {
            // altrimenti converte l'id in stringa e ci mette "Giocatore " davanti
            int powers[3] = {100, 10, 1};
            int num = player.id;
            strcpy(ret, "Giocatore \0");
            for(int i = 0; i < 3; i++) {
                ret[i + 10] = (char)((num / powers[i]) + 48);
                //printf("%d", num / powers[i]);
                num %= powers[i];
            }
            ret[14] = '\0';
        }*/

        return ret;
    }
}




int si_no(char *query) {

    char si_o_no[2][10] = {"no", "si"};

    return choice_string(&query[0], 2, si_o_no);
}


int rand_int(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}




int rand_int_between(int num1, int num2) {

    // prende un numero a caso fra i due e ritorna l'estremo più vicino
    int mid = rand_int(0, 10);

    if(mid > 5) {
        return num2;
    } else {
        return num1;
    }
}
