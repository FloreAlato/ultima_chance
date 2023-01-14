//
// Created by davyf on 30/11/2022.
//

#include "files.h"




// apre un file in mofo sicuto

FILE *fopen_secure(char *filename, char *mode) {

    FILE *file = NULL;
    file = fopen(filename, mode);
    if(file == NULL) {
        printf("\nERRORE! Impossibile aprire il file!\n");
        exit(1);
    }

    return file;
}





// genera il nome dell apath del file che si vuole aprire
// servead essere precisi quando si apre un file

char *make_path(char filename[], char extention[]) {

    char *path = NULL;

    path = (char *) calloc(63, sizeof(char));
    if(path == NULL) {
        printf("\n\nERRORE! Allocazione fallita!");
        exit(-1);
    }

    // in pratica pone la base per il percorso e ci aggiunge il nome e l'estensione

    strcpy(path, "../cmake-build-debug/Save_Files/");
    strcat(path, filename);
    strcat(path, extention);

    return path;
}




// legge una matrice di nomi da un file

char **trova_nomi(FILE *file, int numero) {

    char **nomi = NULL;

    // alloca la matrice dei nomi

    nomi = (char **) calloc(numero, sizeof(char *));

    // alloca le singole stringhe

    for(int k = 0; k < numero; k++) {
        nomi[k] = (char *) calloc(sizeof(char), 32);

        // legge le stringhe dal file

        fread(nomi[k], sizeof(char), 32, file);
    }

    // infine ritorna la matrice

    return nomi;
}




// legge un numero num di profili da un file

void leggi_profili(FILE *file, int num, ProfiloGiocatore *player) {

    for(int i = 0; i < num; i++) {
        fread(&player[i].id, sizeof(int), 1, file);
        fread(&player[i].nome, sizeof(char), 64, file);
        fread(&player[i].spr1d_game_giocati, sizeof(int), 1, file);
        fread(&player[i].finali_giocate, sizeof(int), 1, file);
        fread(&player[i].spr1d_game_vinti, sizeof(int), 1, file);
        fread(&player[i].tot_giochi_giocati, sizeof(int), 1, file);
        fread(&player[i].tot_giochi_vinti, sizeof(int), 1, file);
    }
}


// scrive un numero num di profili in un file

void scrivi_profili(FILE *file, int num, ProfiloGiocatore *player) {

    for(int i = 0; i < num; i++) {
        fwrite(&player[i].id, sizeof(int), 1, file);
        fwrite(&player[i].nome, sizeof(char), 64, file);
        fwrite(&player[i].spr1d_game_giocati, sizeof(int), 1, file);
        fwrite(&player[i].finali_giocate, sizeof(int), 1, file);
        fwrite(&player[i].spr1d_game_vinti, sizeof(int), 1, file);
        fwrite(&player[i].tot_giochi_giocati, sizeof(int), 1, file);
        fwrite(&player[i].tot_giochi_vinti, sizeof(int), 1, file);
    }
}


// salva un file con una partita non in corso

void save_nogame(int numero_profili, ProfiloGiocatore *profili, FILE *file) {

    int num = numero_profili;
    bool game = false;

    // usa scrivi_profili() per scrivere i profili

    fwrite(&num, sizeof(int), 1, file);
    scrivi_profili(file, numero_profili, profili);
    fwrite(&game, sizeof(int), 1, file);
}


// salva una partita in corso
// il principio e' simile a quello della funzione precedente
// ma scrive nel file le informazioni sulla partita in corso

void save_game(FILE *file, int numero_giocatori, int numero_giocatori_veri, Elenco *giocatori) {

    int num = numero_giocatori;
    int veri = numero_giocatori_veri;

    fwrite(&num, sizeof(int), 1, file);
    fwrite(&veri, sizeof(int), 1, file);

    for(int i = 0, j = 0; j < numero_giocatori_veri; i++) {
        if(giocatori[i].id != -1) {
            fwrite(&giocatori[i].id, sizeof(int), 1, file);
            j++;
        }
    }

    for(int i = 0; i < numero_giocatori; i++) {
        fwrite(&giocatori[i].vivo, sizeof(int), 1, file);
    }
}




// aggiunge il file appena generato alla lista di file disponibili

void add_file(char *newname) {

    FILE *file = NULL;
    int many, n = 0;
    char **filenames = NULL;

    // apre il file dei file in lettura, legge il numero di file disponibili, i loro nomi, e chiude

    file = fopen_secure(make_path("savegame_files", ".bin"), "rb");
    fread(&many, sizeof(int), 1, file);
    filenames = trova_nomi(file, many);
    fclose(file);



    many++;

    // apre lo stesso file in scrittura, scrive il numero aggiornato, i nomi di prima, e il nuovo nome
    //poi chiude e libera l'array dei nomi
    file = fopen_secure(make_path("savegame_files", ".bin"), "wb");
    fwrite(&many, sizeof(int), 1, file);

    for(n = 0; n < many - 1; n++) {
        fwrite(filenames[n], sizeof(char), 32, file);
    }
    fwrite(newname, sizeof(char), 32, file);

    fclose(file);



    free(filenames);
}





// salva un file differenziando fra partita in corso o no

bool save_short(int args, ...) {

    va_list lista;
    va_start(lista, args);

    // prende dagli argomenti tutte le variabili richieste
    // il loro numero potrebbe variare

    int numero_profili = va_arg(lista, int);
    ProfiloGiocatore *profili = va_arg(lista, ProfiloGiocatore *);
    bool game = (bool) va_arg(lista, int);

    int numero_giocatori = 0;
    int numero_giocatori_veri = 0;
    Elenco *giocatori = NULL;

    if(game) {
        numero_giocatori = va_arg(lista, int);
        numero_giocatori_veri = va_arg(lista, int);
        giocatori = va_arg(lista, Elenco *);
    }

    // chiede il nome del nuovo file
    // salva il file e lo aggiunge alla lista

    printf("\n\nCome vuoi chiamare il file di salvataggio?");
    printf("\nAttento, se scegli un nome gia' usato, il file verra' sovrascritto!\n\nScelta: ");
    char nome_file[32];
    scanf(" %s", nome_file);

    FILE *file = fopen_secure(make_path(nome_file, ".bin"), "wb");
    save_nogame(numero_profili, profili, file);
    if(game) {
        save_game(file, numero_giocatori, numero_giocatori_veri, giocatori);
    }
    add_file(nome_file);
    fclose(file);

    // poi chiede all'utente se vuole uscire dal gioco e ritorna la risposta

    char fine[2][DIM_OPZIONE] = {"continua", "esci"};
    printf("\n\nContinui a giocare o esci dal gioco? (continua / esci)");
    bool fin = (bool)choice_string("\nRisposta: ", 2, fine);

    va_end(lista);

    return fin;
}





// funzione mia per resettare la lista dei file

void restore() {

    char names[4][32] = {
            "savegame_Nplayers_game",
            "savegame_Nplayers_noGame",
            "savegame_twoPlayers_game",
            "savegame_twoPlayers_noGame"
    };

    FILE *file = NULL;
    int i, num = 4;

    file = fopen_secure(make_path("savegame_files", ".bin"), "wb");

    fwrite(&num, sizeof(int), 1, file);
    for(i = 0; i < num; i++) {
        fwrite(&names[i], sizeof(char), 32, file);
    }

    fclose(file);
}




