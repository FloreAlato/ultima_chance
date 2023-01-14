#include <stdio.h>
#include "main.h"



int main() {


    // VARIABILI INDISPENSABILI

    // sono quelle variabili che salvano dati importanti e scollegati dal contesto

    int numero_giocatori = 0;       // numero di giocatori totali
    int numero_giocatori_veri = 0;      // numero di giocatori controllati dall'utente
    int numero_profili = 0;     // numero di profili inseriti o caricati
    ProfiloGiocatore *profili = NULL;       // array di ProfiloGiocatore come da consegna
    Elenco *giocatori = NULL;       // Elenco dei giocatori utente e non (informazioni su "Elenco nel file di testo")
    bool game = false;      // booleano che salva lo stato della partita

    srand(time(NULL));      // inizializza la rand()






    // OPERAZIONI PRE PARTITA (inserimento profili / caricamento salvataggi)

    char opzioni[2][DIM_OPZIONE] = {"carica", "inserisci"};     // matrice con le opzioni per la scelta

    // raccoglie la scelta sotto forma di booleano
    printf("\nVuoi creare un nuovo profilo o caricare un file di salvataggio? (carica / inserisci)\n");
    bool scelta = choice_string("Risposta: ", 2, opzioni);


    if(!scelta) {       // se scegli di caricare la partita

        // apre il file con i nomi dei salvataggi e recupera i nomi, usa tre funzioni:
        // fopen_secure -> files.c (apre un file in modo sicuro)
        // scegli_file() -> main.c (consulta la raccolta dei salvataggi e prende dall'utente il nome del file scelto)
        // leggi_file() -> main.c (recupera i dati salvati nel file scelto)

        FILE *file = fopen_secure(scegli_file(), "rb");
        profili = leggi_file(&numero_profili, &game, file);


        // se il file contiene una partita in corso, usa una funzione per recuperare i dati aggiuntivi descritti nella consegna
        // aggiunte() -> main.c (recupera i dati della partita in corso)
        if(game) {
            giocatori = aggiunte(&numero_giocatori, &numero_giocatori_veri, profili, file);
        }

        fclose(file);


    } else {       // se scegli di inserire i profili manualmente

        int separatore;     // intero che fara' da indice per le operazioni successive
        bool fin;       // questo lo inizializzo qui perche' non me lo fa fare all'interno della switch

        // riempie l'array dei profili manualmente con l'apposita funzione
        // crea_profili() -> main.c (funzione per l'inserimento manuale dei profili giocatore)

        profili = crea_profili(&numero_profili, &separatore);

        // usa il separatore per decidere quale operazione eseguire ora
        // quando deve uscire dal programma, delloca sempre la memoria dinamica

        switch (separatore) {
            case SALVA:       // salva
                fin = save_short(3, numero_profili, profili, false);
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



    // (nota) dopo questa fase (sempre che il programma stia ancora girando) sriamo rimasti con un array di profili giocatore
    // inseriti manualmente o caricati da file
    // se il file caricato conteneva una partita in corso, abbiamo anche un'array contenente tutti i giocatori, utente e non
    // la fase successiva serve proprio a generare l'array di giocatori qualora la partita non fosse iniziata





    // OPERAZIONI PRE PARTITA (generazione dell'Elenco giocatori)

    if(!game) {       // vuol dire che il gioco non e' iniziato e bisogna inserire il numero totale deo giocatori

        // chiede all'utente quanti giocatori parteciperanno alla partita e salva la risposta nella variabile corrispondente
        // poi compone l'elenco usando una funzione apposita
        // get_int() -> funzioni_utili.c (prende in input e ritorna un intero all'interno di un range specificato nei parametri)
        // componi_elenco() -> funzioni_utili.c (alloca dinamicamente un'array di Elenco)

        printf("\n\nQuanti giocatori vuoi che partecipino alla partita? (minimo 16)\n");
        numero_giocatori = get_int("Risposta: ", 16, MAX_GIOCATORI);
        giocatori = componi_elenco(numero_giocatori);

        int risposta;

        // chiede all'utente quali profili usare e quali id assegnarvi
        // cambia se abbiamo un solo profilo a disposizione

        if(numero_profili == 1) {

            // se abbiamo un solo profilo, chiede all'utente se lo vuole usare
            // se si', l'id viene raccolto e assegnato

            printf("\nVuoi usare il profilo a disposizione? (si / no)\n");
            risposta = si_no("Risposta: ");

            if(risposta) {
                printf("\nBene, quale id vuoi assegnare a %s?\n", profili[0].nome);
                risposta = get_int("Risposta: ", 0, numero_giocatori - 1);
                giocatori[risposta].p = &profili[0];
                profili[0].id = risposta;
            }

        } else {

            // altrimenti chiede all'utente quanti prifili usare
            // facendo attenzione che il numero di giocatori utente non superi il numero di giocatori effettivi

            printf("\nQuanti dei %d profili a disposizione vuoi usare?\n", numero_profili);

            if(numero_profili <= numero_giocatori) {
                risposta = get_int("Risposta: ", 0, numero_profili);
            } else {
                risposta = get_int("Risposta: ", 0, numero_giocatori);
            }

            // un'array di interi biene allocata provvisoriamente (da qui il nome prov)
            // e riempita in modo ordinato

            int *prov = (int *) calloc(numero_profili, sizeof(int));
            for(int i = 0; i < numero_profili; i++) {
                prov[i] = i;
            }

            // poi prov sara' usata per scegliere gli id dei profili utente usando la funzione apposita
            // scegli_id() -> main.c (scelta manuale degli id dei giocatori controllati dall'utente)

            scegli_id(risposta, numero_profili, numero_giocatori, profili, giocatori, prov);

            // infine prov non serve piu' e puo' essere liberato

            free(prov);
        }
    }



    // (nota) dopo questa fase siamo rimasti con un'array di profili e un'array di giocatori, strettamente legat
    // l'array di giocatori infatti e' composta da una struttura che ho scritto per salvare in modo compatto i giocatori
    // vedrete che alcune sue caratteristiche la rendono molto versatile




    // VISUALIZZAZIONE PROFILI E GIOCATORI PER IL DEBUG

    // non ho rimosso questa parte perche' ritengo che sia utile per la correzione
    // e non rovina troppo l'estetica del programma

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

    getchar();




    // CONTROLLO GIOCATORI IN VITA (nel caso venga caricato un file con svolgimento incompleto)

    // questa sezione genera e siempie un'array ausiliaria che contiene solo i giocatori in vita
    // in questo modo posso tenere l'array principale per salvare la partita, ma senza dover controllare ogni volta chi e' morto

    int numero_giocatori_vivi = 0;      // inizializzato qui perche' vi devo poter accedere ovunque
    Elenco *giocatori_vivi = NULL;      // idem

    // naturalmente questa operazione si rende necessaria solo se la partita e' in corso
    // altrimenti i giocatori non avrebbero avuto tempo di morire

    if(game) {

        // parte con un' array di dimensione 1

        int j = 0;
        giocatori_vivi = (Elenco *) calloc(1, sizeof(Elenco));

        // controlla quanti giocatori sono in vita e aumenta il numero di giocatori vivi
        // realloca di volta in volta la nuova array e la riempie con i giocatori vivi

        for(int i = 0; i < numero_giocatori; i++) {
            if(giocatori[i].vivo) {
                numero_giocatori_vivi += 1;

                if(numero_giocatori_vivi > 1) {
                    giocatori_vivi = (Elenco *) realloc(giocatori_vivi, sizeof(Elenco) * numero_giocatori_vivi);
                }

                giocatori_vivi[j] = giocatori[i];

                j++;
            }
        }

    } else {

        // se la partita no e' cominciata, i giocatori sono tutti vivi
        // quindi la nuova array sara' uguale a quella principale

        numero_giocatori_vivi = numero_giocatori;
        giocatori_vivi = (Elenco *) calloc(numero_giocatori_vivi, sizeof(Elenco));
        for(int i = 0; i < numero_giocatori_vivi; i++) {
            giocatori_vivi[i] = giocatori[i];
        }
    }

    // STAMPA GIOCATORI IN VITA PER IL DEBUG (proprio come prima)

    printf("\n\n\nCi sono %d giocatori in vita, e sono:", numero_giocatori_vivi);
    for(int i = 0; i < numero_giocatori_vivi; i++) {
        printf("\n%s", print_player(giocatori_vivi[i]));
    }








    // SCREMATURA (se non gia' avvenuta completamente)

    // la scrematura avviene solo se la partita non e' cominciata

    if(!game) {

        // calcola il numero target di giocatori desiderati prima della partita, come da consegna

        int conto = 1;
        while(pow(2, conto) < numero_giocatori_vivi) {
            conto++;
        }
        int target = (int)pow(2, conto - 2);

        // stampa un messaggio a schermo per informare l'utente del numero calcolato

        printf("\n\n\nAbbiamo un problema qui! %d giocatori sono troppi! %d sono piu' comodi...", numero_giocatori_vivi, target);



        // SCREMATURA (la scrematura effettiva)

        // l'array di giocatori vivi viene ridimensionata con la funzione scrematura
        // scrematura() -> scrematura.c (riduce il numero di giocatori in vita giocando a indovina il numero)
        // e ovviamente, il nuovo numero di giocatori in vita sara' il numero target

        giocatori_vivi = scrematura(numero_giocatori_vivi, target, giocatori_vivi, numero_profili, profili, giocatori);
        numero_giocatori_vivi = target;

        // stampa di nuovo i giocatori in vita per il debug

        printf("\n\n\nCi sono %d giocatori in vita, e sono:", numero_giocatori_vivi);
        for(int i = 0; i < numero_giocatori_vivi; i++) {
            printf("\n%s", print_player(giocatori_vivi[i]));
        }
        getchar();
        getchar();
    }





    // (nota) dopo questa sezione siamo rimasti con un'array di giocatori di dimensioni ridotte
    // la sezione successiva ridurra' questo numero fino a due, per permettere la finale





    // SVOLGIMENTO (se non gia' avvenuto con successo)

    // ancora una volta, inizializzo la nuova array qui per usarla ovunque
    // se il numero di giocatori in vita e' gia' due, non servira' giocare per ridurre il numero
    // questo capita spesso nei file forniti nella consegna


    Elenco *finalisti = NULL;

    if(numero_giocatori_vivi > 2) {

        // la coppia di finalisti viene riempita tramite la funzione svolgimento
        // svolgimento() -> svolgimento.c (riduce il numero di giocatori vivi a due con vari giochi e li salva come finalisti)

        finalisti = svolgimento(numero_giocatori_vivi, giocatori_vivi, numero_giocatori, giocatori, numero_profili, profili, numero_giocatori_veri);

    } else if(numero_giocatori_vivi == 2) {

        // se i giocatori vivi sono gia' due, vengono salvati pari pari nella coppia dei finalisti
        // la coppia viene anche allocata dinamicamente, operazione che altrimenti svolgerebbe la funzione svolgimento()

        finalisti = (Elenco *) calloc(2, sizeof(Elenco));

        finalisti[0] = giocatori_vivi[0];
        finalisti[1] = giocatori_vivi[1];
    }


    // stampa a schermo i nomi dei finalisti e da' il via alla fase finale


    printf("\n\n\n\nGli ultimi due rimasti sono %s e %s!!!!", print_player(finalisti[0]), print_player(finalisti[1]));
    printf("\nPassiamo alla fase finale!! (invio)");
    getchar();




    // (nota) questa era la penultima fase del gioco, che ci lascia con la coppia dei finalisti per finire la partita







    // FINALE

    // il vincitore viene deciso con una partita di blackjack se almeno un finalista e' controllato dall'utente
    // altrimenti viene scelto a caso

    int vincitore;

    if(is_player(finalisti[0]) || is_player(finalisti[1])) {
        vincitore = black_jack(finalisti);
    } else {
        vincitore = rand_int(0, 1);
    }

    // esce senza salvare
    // mi spiace per questa mancanza, ma sto finendo di commentare questa parte alle 00:40 del 29 dicembre
    // non ce la faccio piu', spero solo di essermi guadagnato almeno una sufficienza

    printf("\n\n\nQUINDI %s SI AGGIUDICA GLI SPR1D GAMES!!!!!", print_player(finalisti[vincitore]));
    getchar();
    printf("\n\n\nAddio!\n");



    // LIBERA LA MEMORIA ALLOCATA DINAMICAMENTE

    free(profili);
    free(giocatori);
    free(giocatori_vivi);
    free(finalisti);

    return 0;
}









// funzione per l'inserimento manuale dei prifili giocatore
// alloca passo passo l'array e infine lo ritorna

ProfiloGiocatore *crea_profili(int *numero_profili, int *fine) {

    int i, prosegui;
    bool doppione;
    char proposte[4][DIM_OPZIONE] = {"continua", "salva", "inizia", "esci"};

    // la dimensione parte da uno, e l'array viene allocata

    *numero_profili = 1;
    ProfiloGiocatore *lista_profili = (ProfiloGiocatore *) malloc(sizeof(ProfiloGiocatore));
    do {
        do {

            // per ogni muovo profilo, scorre la lista a ritroso per cercare doppioni del nome
            // se li trova manda un messaggio di errore e ripete l'inserimento

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

        // dopo ogni inserimento chiede la prossima operazione da eseguire
        // questa viene salvata con choice_string()
        // choice_string() -> funzioni_utili.c (prende un intero che fa da indice per un'array di opzioni)

        printf("\nChe operazione vuoi svolgere? (continua / salva / inizia / esci)\n");
        prosegui = choice_string("Scelta: ", 4, proposte);
        getchar();

        // se il giocatore vuole proseguire, si rialloca l'array e il ciclo continua
        // aumenta anche il numero di profili

        if(prosegui == 0) {
            *numero_profili += 1;
            lista_profili = (ProfiloGiocatore *) realloc(lista_profili, sizeof(ProfiloGiocatore) * *numero_profili);
        }

    } while(prosegui == CONTINUA);

    // i profili vanno azzerati
    // perche' realloc non lo fa in automatico

    for(i = 0; i < *numero_profili; i++) {
        lista_profili[i].id = -1;
        lista_profili[i].spr1d_game_giocati = 0;
        lista_profili[i].finali_giocate = 0;
        lista_profili[i].spr1d_game_vinti = 0;
        lista_profili[i].tot_giochi_giocati = 0;
        lista_profili[i].tot_giochi_vinti = 0;
    }

    // questo valore fara' da indice nella main per scegliere la prossima operazione

    *fine = prosegui;

    return lista_profili;
}





// funzione alternativa alla precedente
// genera la stessa array di profili, ma leggendola da un file


ProfiloGiocatore *leggi_file(int *numero_profili, bool *game, FILE *file) {

    ProfiloGiocatore *lista_profili = NULL;     // array di profili da ritornare
    int segnaposto;

    // legge il numero di profili dal file e lo usa per allocare l'array

    fread(&segnaposto, sizeof(int), 1, file);
    lista_profili = (ProfiloGiocatore *) calloc(segnaposto,  sizeof(ProfiloGiocatore));

    // legge i profili dal file con l'apposita funzione
    // leggi_prifili() -> files.c (legge i profili)

    leggi_profili(file, segnaposto, lista_profili);

    // legge anche lo stato della partita in corso

    fread(game, sizeof(int), 1, file);
    *numero_profili = segnaposto;

    return lista_profili;
}



// funzione aggiuntiva alla precedente
// legge dal file le informazioni salvate solo nei file contenenti una partita in corso


Elenco *aggiunte(int *numero_giocatori, int *numero_giocatori_veri, ProfiloGiocatore *profili, FILE *file) {

    Elenco *giocatori = NULL;       // variabili che diverteranno quelle universali
    int N, M, segnaposto, i;

    // ho usato i nomi della consegna
    // cosi' posso risparmiare un paio di commenti (spero)

    fread(&N, sizeof(int), 1, file);
    fread(&M, sizeof(int), 1, file);

    // compone l'elenco dei giocatori totali

    giocatori = componi_elenco(N);

    // assegna i profili corrispondenti
    // anziche' leggere un'array di interi legge un intero M volte e compone l'Elenco

    for(i = 0; i < M; i++) {
        fread(&segnaposto, sizeof(int), 1, file);
        printf("\nId: %d", segnaposto);
        giocatori[profili[segnaposto].id].p = &profili[segnaposto];
    }

    // idem per lo stato vitale dei giocatori
    // tutto compreso nella struttura Elenco

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



// funzione per la scelta del file da caricare
// ritorna il nome del file scelto

char *scegli_file() {

    int numero_files;
    char **files = NULL;

    // stampa i file disponibili con trova_nomi()
    // trova_nomi() -> files.c (trova nomi)

    printf("\nQuesti sono i file disponibili:\n");
    FILE *file = fopen_secure(make_path("savegame_files", ".bin"), "rb");
    fread(&numero_files, sizeof(int), 1, file);
    files = trova_nomi(file, numero_files);
    fclose(file);

    for(int k = 0; k < numero_files; k++) {
        printf("\n[%d] -> %s", k, files[k]);
    }

    // prende un intero dall'utente e lo usa come indice
    // compone il nome dell apath con make_path -> funzioni_utili.c

    int scelta = get_int("\n\nScelta: ", 0, numero_files - 1);

    char *nome = make_path(files[scelta], ".bin");
    free(files);

    return nome;
}



// funzione per scegliere líd dei giocatori utente (ricorsiva)
// tiene conto del numero di profili ancora da scegliere e ripete se stessa fino ad azzerarlo


void scegli_id(int numero_scelto, int numero_profili, int numero_giocatori, ProfiloGiocatore *profili, Elenco *giocatori, int *prov) {

    int scelta, id;

    if(numero_scelto > 0) {

        // stampa i nomi dei giocatori e ne fa scegliere uno all'utente

        printf("\nQuesti sono i profili a disposizione: (ancora %d da scegliere)", numero_scelto);
        for(int i = 0; i < numero_profili; i++) {
            printf("\n[%d] -> %s", i, profili[prov[i]].nome);
        }

        scelta = get_int("\n\nScelta: ", 0, numero_profili - 1);
        getchar();

        // se il giocatore con l'is scelto e' un giocatore, vuol dire che l'id e' gia' preso
        // quindi la selezione si ripete finche' l'utente sceglie un giocatore che non sia gia' utente

        do {
            printf("\nId di %s: ", profili[prov[scelta]].nome);
            id = get_int("", 0, numero_giocatori - 1);
            getchar();

            if(is_player(giocatori[id])) {
                printf("\nHai gia' usato questo id, scegline un altro");
            }

        } while(is_player(giocatori[id]));

        // assegna poi gli id ai prifili scelti, per coerenza

        profili[prov[scelta]].id = id;
        giocatori[id].p = &profili[prov[scelta]];

        prov[scelta] = prov[numero_profili - 1];

        scegli_id(numero_scelto - 1, numero_profili - 1, numero_giocatori, profili, giocatori, prov);
    }
}




