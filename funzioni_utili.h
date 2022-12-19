//
// Created by davyf on 30/11/2022.
//

#ifndef DAVIDE_FLORE_66174_FUNZIONI_UTILI_H
#define DAVIDE_FLORE_66174_FUNZIONI_UTILI_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>

#define DIM_NOME 64
#define DIM_OPZIONE 10


// code goes here
typedef struct {
    int id;
    char nome[DIM_NOME];
    int spr1d_game_giocati;
    int finali_giocate;
    int spr1d_game_vinti;
    int tot_giochi_giocati;
    int tot_giochi_vinti;
} ProfiloGiocatore;


typedef struct {
    int id;
    ProfiloGiocatore *p;
    bool vivo;
} Elenco;



int choice_string(char *, int, char[][DIM_OPZIONE]);
int get_int(char *, int, int);
int string_to_int(char *);
char *int_to_string(int);
bool is_numeric(char *);
Elenco *componi_elenco(int);
bool is_player(Elenco);
char *print_player(Elenco);
int si_no(char *);
int rand_int(int, int);
int rand_int_between(int, int);



#endif //DAVIDE_FLORE_66174_FUNZIONI_UTILI_H
