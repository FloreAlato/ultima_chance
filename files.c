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




void save_nogame(int numero_profili, ProfiloGiocatore *profili, FILE *file) {

    int num = numero_profili;
    bool game = false;

    fwrite(&num, sizeof(int), 1, file);
    scrivi_profili(file, numero_profili, profili);
    fwrite(&game, sizeof(int), 1, file);
}





// DEBUGGARE! CONTROLLARE SE IL FILE ESISTE E NEL CASO NON AGGIUNGERLO


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




