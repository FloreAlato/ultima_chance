//
// Created by davyf on 30/11/2022.
//

#include "files.h"





FILE *fopen_secure(char *filename, char *mode) {

    FILE *file = NULL;
    file = fopen(filename, mode);
    if(file == NULL) {
        printf("\nERRORE! Impossibile aprire il file!\n");
        exit(1);
    }

    return file;
}






char *make_path(char filename[], char extention[]) {

    char *path = NULL;

    path = (char *) calloc(63, sizeof(char));
    if(path == NULL) {
        printf("\n\nERRORE! Allocazione fallita!");
        exit(-1);
    }

    strcpy(path, "../cmake-build-debug/Save_Files/");
    strcat(path, filename);
    strcat(path, extention);

    return path;
}






char **trova_nomi(FILE *file, int numero) {

    char **nomi = NULL;

    // alloca la matrice
    nomi = (char **) calloc(numero, sizeof(char *));
    if(nomi == NULL) {
        printf("\n\nERRORE! Allocazione fallita!\n\n");
        exit(-1);
    }
    // alloca le singole stringhe
    for(int k = 0; k < numero; k++) {
        nomi[k] = (char *) calloc(sizeof(char), 32);
        if(nomi[k] == NULL) {
            printf("\n\nERRORE! Allocazione fallita!\n\n");
            exit(-1);
        }

        // legge le stringhe dal file
        fread(nomi[k], sizeof(char), 32, file);
    }

    // infine ritorna la matrice
    return nomi;
}





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
