#include <stdio.h>
#include "main.h"



int main() {


    /*srand(time(NULL));


    ProfiloGiocatore prova_profili[2] = {
            {0, "Andrea Sangaino\0", 0, 0, 0, 0, 0},
            {2, "Davide Flore\0", 0, 0, 0, 0, 0}
    };

    Elenco prova_giocatori[3] = {
            {0, &prova_profili[0], true},
            {1, NULL, true},
            {2, &prova_profili[1], true}
    };


    printf("\n\n\nHa vinto %s!!!", print_player(prova_giocatori[indovina_il_numero(3, prova_giocatori)]));



    return 0;*/



    // VARIABILI
    int numero_giocatori = 0;
    int numero_giocatori_veri = 0;
    int numero_profili = 0;
    FILE *file = NULL;
    ProfiloGiocatore *profili = NULL;
    Elenco *giocatori = NULL;
    bool game = false;

    srand(time(NULL));



    // OPERAZIONI PRE PARTITA (inserimento profili / caricamento salvataggi)

    char opzioni[2][DIM_OPZIONE] = {"carica", "inserisci"};

    printf("\nVuoi creare un nuovo profilo o caricare un file di salvataggio? (carica / inserisci)\n");
    bool scelta = choice_string("Risposta: ", 2, opzioni);


    if(!scelta) {       // se scegli di caricare la partita

        file = fopen_secure(scegli_file(), "rb");
        profili = leggi_file(&numero_profili, &game, file);

        if(game) {
            giocatori = aggiunte(&numero_giocatori, &numero_giocatori_veri, profili, file);
        }

        fclose(file);

    } else {       // se scegli di inserire i profili manualmente

        int separatore;
        bool fin;

        profili = crea_profili(&numero_profili, &separatore);

        // fai lo switch del separatore e agisci di conseguenza
        switch (separatore) {
            case SALVA:       // salva
                fin = save_short(numero_profili, profili);
                if(fin) {
                    printf("\n\nAddio allora! (invio)");
                    getchar();
                    free(profili);
                    exit(0);
                }
                break;
            case INIZIA:       // inizia
                printf("\n\nAllora cominciamo!\nSi parte dal riempimento della lista dei giocatori!\n\n");
                break;
            case ESCI:       // esci
                printf("\n\n\nBene, e' stato bello giocare con te! (invio)");
                getchar();
                free(profili);
                exit(0);
            default:
                break;
        }
    }



    // OPERAZIONI PRE PARTITA (generazione dell'elenco giocatori)

    if(!game) {       // vuol dire che il gioco non e' iniziato e bisogna inserire il numero totale

        // chiedi il numero di giocatori
        // riempi l'elenco
        // chiedi gli id e associa i profili
        printf("\n\nQuanti giocatori vuoi che partecipino alla partita? (minimo 16)\n");
        numero_giocatori = get_int("Risposta: ", 16, MAX_GIOCATORI);
        giocatori = componi_elenco(numero_giocatori);

        int risposta;

        if(numero_profili == 1) {
            printf("\nVuoi usare il profilo a disposizione? (si / no)\n");
            risposta = si_no("Risposta: ");

            if(risposta) {
                printf("\nBene, quale id vuoi assegnare a %s?\n", profili[0].nome);
                risposta = get_int("Risposta: ", 0, numero_giocatori - 1);
                giocatori[risposta].p = &profili[0];
                profili[0].id = risposta;
            }

        } else {
            printf("\nQuanti dei %d profili a disposizione vuoi usare?\n", numero_profili);

            if(numero_profili <= numero_giocatori) {
                risposta = get_int("Risposta: ", 0, numero_profili);
            } else {
                risposta = get_int("Risposta: ", 0, numero_giocatori);
            }

            // prcedi in base al numero di profili scelti
            int *prov = (int *) calloc(numero_profili, sizeof(int));
            for(int i = 0; i < numero_profili; i++) {
                prov[i] = i;
            }

            // processo di scelta degli id, debuggato
            scegli_id(risposta, numero_profili, numero_giocatori, profili, giocatori, prov);


            free(prov);
        }
    }




    // VISUALIZZAZIONE PROFILI E GIOCATORI PER IL DEBUG

    printf("\n\nCi sono %d profili:", numero_profili);
    for(int j = 0; j < numero_profili; j++) {
        printf("\nId: %d\nNome: %s\nGiochi vinti: %d\n", profili[j].id, profili[j].nome, profili[j].tot_giochi_vinti);
    }
    printf("\n\nGame: %d", game);

    getchar();

    printf("\n\nCi sono %d giocatori:", numero_giocatori);
    for(int i = 0; i < numero_giocatori; i++) {
        printf("\n[%s] - > %d", print_player(giocatori[i]), giocatori[i].vivo);
    }




    // CONTROLLO GIOCATORI IN VITA (nel caso venga caricato un file con scrematura incompleta)

    int numero_giocatori_vivi = 0;
    Elenco **giocatori_vivi = NULL;

    if(game) {
        int j = 0;
        giocatori_vivi = (Elenco **) calloc(1, sizeof(Elenco *));

        // controlla quanti giocatori sono in vita
        for(int i = 0; i < numero_giocatori; i++) {
            if(giocatori[i].vivo) {
                numero_giocatori_vivi += 1;

                if(numero_giocatori_vivi > 1) {
                    giocatori_vivi = (Elenco **) realloc(giocatori_vivi, sizeof(Elenco *) * numero_giocatori_vivi);
                }

                giocatori_vivi[j] = &giocatori[i];

                j++;
            }
        }

    } else {
        numero_giocatori_vivi = numero_giocatori;
        giocatori_vivi = (Elenco **) calloc(numero_giocatori_vivi, sizeof(Elenco *));
        for(int i = 0; i < numero_giocatori_vivi; i++) {
            giocatori_vivi[i] = &giocatori[i];
        }
    }

    // STAMPA GIOCATORI IN VITA PER IL DEBUG

    printf("\n\n\nCi sono %d giocatori in vita, e sono:", numero_giocatori_vivi);
    for(int i = 0; i < numero_giocatori_vivi; i++) {
        printf("\n%s", print_player(*giocatori_vivi[i]));
    }








    // SCREMATURA (se non gia' avvenuta completamente)

    if(numero_giocatori_vivi > 2) {
        int conto = 1;
        while(pow(2, conto) < numero_giocatori_vivi) {
            conto++;
        }
        int target = (int)pow(2, conto - 2);

        printf("\n\n\nAbbiamo un problema qui! %d giocatori sono troppi! %d sono piu' comodi...", numero_giocatori_vivi, target);

        // SCREMATURA

        giocatori_vivi = scrematura(numero_giocatori_vivi, target, giocatori_vivi, numero_profili, profili);
        numero_giocatori_vivi = target;

        printf("\n\n\nCi sono %d giocatori in vita, e sono:", numero_giocatori_vivi);
        for(int i = 0; i < numero_giocatori_vivi; i++) {
            printf("\n%s", print_player(*giocatori_vivi[i]));
        }
    }





    // SVOLGIMENTO (se non gia' avvenuto con successo)

    if(numero_giocatori_vivi > 2) {
        // svolgimento
        // sistema scalare per ridurre il numero
        // non dimenticare di far scegliere i giochi a Riccardo Scateni
    }





    // FINALE (controlla che almeno uno sia utente)

    if(numero_giocatori_vivi == 2) {
        // blackjack
    } else {
        printf("\n\nMANNAGGIA, DAVIDE! HAI FATTO UN CASINO!!");
    }




    // LIBERA LA MEMORIA ALLOCATA DINAMICAMENTE

    free(profili);
    free(giocatori);
    free(giocatori_vivi);

    return 0;
}










ProfiloGiocatore *crea_profili(int *numero_profili, int *fine) {

    int i, prosegui;
    bool doppione;
    char proposte[4][DIM_OPZIONE] = {"continua", "salva", "inizia", "esci"};

    *numero_profili = 1;
    ProfiloGiocatore *lista_profili = (ProfiloGiocatore *) malloc(sizeof(ProfiloGiocatore));
    do {
        do {
            doppione = false;

            printf("\nNome giocatore: ");
            scanf(" %[^\n]%*c", lista_profili[*numero_profili - 1].nome);

            i = *numero_profili - 1;
            while(i > 0) {
                if(strcmp(lista_profili[*numero_profili - 1].nome, lista_profili[i - 1].nome) == 0) {
                    doppione = true;
                    printf("\nIl nome deve essere unico!\n");
                }
                i--;
            }

        } while(doppione);

        printf("\nChe operazione vuoi svolgere? (continua / salva / inizia / esci)\n");
        prosegui = choice_string("Scelta: ", 4, proposte);
        getchar();

        if(prosegui == 0) {
            *numero_profili += 1;
            lista_profili = (ProfiloGiocatore *) realloc(lista_profili, sizeof(ProfiloGiocatore) * *numero_profili);
        }

    } while(prosegui == CONTINUA);

    for(i = 0; i < *numero_profili; i++) {
        lista_profili[i].id = -1;
        lista_profili[i].spr1d_game_giocati = 0;
        lista_profili[i].finali_giocate = 0;
        lista_profili[i].spr1d_game_vinti = 0;
        lista_profili[i].tot_giochi_giocati = 0;
        lista_profili[i].tot_giochi_vinti = 0;
    }

    *fine = prosegui;

    return lista_profili;
}



ProfiloGiocatore *leggi_file(int *numero_profili, bool *game, FILE *file) {

    ProfiloGiocatore *lista_profili = NULL;
    int segnaposto;

    fread(&segnaposto, sizeof(int), 1, file);
    lista_profili = (ProfiloGiocatore *) calloc(segnaposto,  sizeof(ProfiloGiocatore));

    leggi_profili(file, segnaposto, lista_profili);

    fread(game, sizeof(int), 1, file);
    *numero_profili = segnaposto;

    return lista_profili;
}



Elenco *aggiunte(int *numero_giocatori, int *numero_giocatori_veri, ProfiloGiocatore *profili, FILE *file) {

    Elenco *giocatori = NULL;
    int N, M, segnaposto, i;

    fread(&N, sizeof(int), 1, file);
    fread(&M, sizeof(int), 1, file);

    giocatori = componi_elenco(N);

    for(i = 0; i < M; i++) {
        fread(&segnaposto, sizeof(int), 1, file);
        printf("\nId: %d", segnaposto);
        giocatori[profili[segnaposto].id].p = &profili[segnaposto];
    }

    for(i = 0; i < N; i++) {
        fread(&segnaposto, sizeof(int), 1, file);
        if(segnaposto == 0) {
            giocatori[i].vivo = false;
        } else {
            giocatori[i].vivo = true;
        }
    }

    *numero_giocatori = N;
    *numero_giocatori_veri = M;

    return giocatori;
}



char *scegli_file() {

    int numero_files;
    char **files = NULL;

    printf("\nQuesti sono i file disponibili:\n");
    FILE *file = fopen_secure(make_path("savegame_files", ".bin"), "rb");
    fread(&numero_files, sizeof(int), 1, file);
    files = trova_nomi(file, numero_files);
    fclose(file);

    for(int k = 0; k < numero_files; k++) {
        printf("\n[%d] -> %s", k, files[k]);
    }

    int scelta = get_int("\n\nScelta: ", 0, numero_files - 1);

    char *nome = make_path(files[scelta], ".bin");
    free(files);

    return nome;
}



void scegli_id(int numero_scelto, int numero_profili, int numero_giocatori, ProfiloGiocatore *profili, Elenco *giocatori, int *prov) {

    int scelta, id;

    if(numero_scelto > 0) {
        printf("\nQuesti sono i profili a disposizione: (ancora %d da scegliere)", numero_scelto);
        for(int i = 0; i < numero_profili; i++) {
            printf("\n[%d] -> %s", i, profili[prov[i]].nome);
        }

        scelta = get_int("\n\nScelta: ", 0, numero_profili - 1);
        getchar();

        do {
            printf("\nId di %s: ", profili[prov[scelta]].nome);
            id = get_int("", 0, numero_giocatori - 1);
            getchar();

            if(is_player(giocatori[id])) {
                printf("\nHai gia' usato questo id, scegline un altro");
            }

        } while(is_player(giocatori[id]));

        profili[prov[scelta]].id = id;
        giocatori[id].p = &profili[prov[scelta]];

        prov[scelta] = prov[numero_profili - 1];

        scegli_id(numero_scelto - 1, numero_profili - 1, numero_giocatori, profili, giocatori, prov);
    }
}




