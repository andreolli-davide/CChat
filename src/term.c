// @ Davide Andreolli, 2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "chat.h"
#include "text.h"
#include "terminal.h"

#define MAX_LENGHT_TEXT 200
#define MAX_LENGHT 30

void term_printlogo()
/*
 * void term_printlogo()
 *
 * Descrizione -> Stampa il logo del programma
 */
{
    colored_centred_text(" .o88b.       .o88b. db   db  .d8b.  d888888b", "cyan");
    colored_centred_text("d8P  Y8      d8P  Y8 88   88 d8' `8b `~~88~~'", "cyan");
    colored_centred_text("8P           8P      88ooo88 88ooo88    88   ", "cyan");
    colored_centred_text("8b           8b      88~~~88 88~~~88    88   ", "cyan");
    colored_centred_text("Y8b  d8      Y8b  d8 88   88 88   88    88   ", "cyan");
    colored_centred_text(" `Y88P'       `Y88P' YP   YP YP   YP    YP   ", "cyan");
    printf("\n\n");
}

void term_help()
/*
 * void term_help()
 *
 * Descrizione -> Stampa l'output del comando help
 */
{
    clear();
    term_printlogo();
    printf("Lista di comandi:\n");
    printf("help            Mostra questa schermata di aiuto\n");
    printf("load            Leggi o ricarica il contenuto della chat\n");
    printf("send            Invia un messaggio alla chat\n");
    printf("logout          Effettua il logout\n");
    printf("info            Informazioni sul programma\n");
    printf("quit            Effettua l'uscita dal programma\n\n");
}

void term_info()
/*
 * void term_info()
 *
 * Descrizione -> Stampa l'output del comando info
 */
{
    clear();
    term_printlogo();
    center_text("Creato da Davide Andreolli");
    center_text("Chat di messaggistica su terminale");
    center_text("Interamente scritto in linguaggio C");
    center_text("Leggi README.md per maggiori dettagli");
    printf("\n\n");
}

void term_load_chat(int id, char user[])
/*
 * void term_load_chat()
 *
 * Descrizione -> Carica la chat dai file di salvataggio e la stampa
 * Parametri -> id -> id dell'utente
 *              user -> nome utente
 */
{
    clear();
    term_printlogo();
    FILE * fp;
    char NomeFile[20] = "resources/chatbk.txt";
    char stringa[MAX_LENGHT_TEXT];
    char username[MAX_LENGHT];
    char text[MAX_LENGHT_TEXT] = "";
    int counter = 0, user_id = 0;

    fp = fopen(NomeFile, "r");

    while(!feof(fp))
    {
        fscanf(fp, "%s", stringa);
        if(!strcmp(stringa, "^/^"))
        {
            counter++;
            if(counter == 3)
            {
                if(strcmp(username, user))
                    chat_other_user_message(user_id, username, text);
                else
                    chat_logged_user_message(user_id, username, text);
                counter = 0;
                memset(text, 0, strlen(text));
            }

            printf("\n");
        }
        if(counter == 0) // ID
            user_id = stringtoint(stringa);
        else if (counter == 1 && strcmp(stringa, "^/^")) // Mittente
            strcpy(username, stringa);
        else if (counter == 2 && strcmp(stringa, "^/^"))
        {
            strcat(text, " ");
            strcat(text, stringa);
        }

    }

    fclose(fp);
}

int term_find_id(char user[])
/*
 * int term_find_id()
 *
 * Descrizione -> Trova l'id dell'utente nei file di salvataggio
 * Parametri -> user -> username dell'utente
 * Ritorna -> id dell'utente
 */
{
    FILE * fp;
    char NomeFile[20] = "resources/users.txt";
    char stringa[MAX_LENGHT];

    fp = fopen(NomeFile, "r");

    int id = 0, counter = 0;

    while(!feof(fp))
    {
        fscanf(fp, "%s", stringa);
        if(!strcmp(stringa, "^/^"))
        {
            counter++;
            if(counter == 2)
                counter = 0;
        }
        else if(counter == 0) // ID
            id++;
        else if(counter == 1) // Username
            if(!strcmp(user, stringa))
                return id;
    }

    fclose(fp);
    return id;
}

int term_check_id()
/*
 * int term_check_id()
 *
 * Descrizione -> Trova il numero di id (utenti) registrati
 * Ritorna -> numero di id registrati
 */
{
    FILE * fp;
    char NomeFile[20] = "resources/users.txt";
    char stringa[MAX_LENGHT];

    fp = fopen(NomeFile, "r");

    int id = 0, counter = 0;

    while(!feof(fp))
    {
        fscanf(fp, "%s", stringa);
        if(!strcmp(stringa, "^/^"))
        {
            counter++;
            if(counter == 2)
                counter = 0;
        }
        else if(counter == 0) // ID
            id++;
    }

    fclose(fp);
    return id;
}

void term_register(char * user)
/*
 * void term_register()
 *
 * Descrizione -> Stampa il messaggio di un utente diverso da quello loggato
 * Parametri -> *user -> puntatore alla variabile del nome utente
 */
{
    FILE * fp;
    char NomeFile[] = "resources/users.txt";
    char stringcopy[MAX_LENGHT];

    strcpy(stringcopy, user);
    fp = fopen(NomeFile, "a");
    fprintf(fp, "%d ^/^ %s ^/^ ", term_check_id() + 1, user);
    fclose(fp);
    tutto_minuscolo(stringcopy);
    clear();
    center_text("Benvenuto/a\n");
    print_Effetto_Figo(stringcopy, term_check_id() + 1);
    printf("\n\n");
}

void term_login(char * user)
/*
 * void term_login()
 *
 * Descrizione -> Carica la chat dai file di salvataggio e la stampa
 * Parametri -> *user -> puntatore alla variabile del nome utente
 */
{
    char NomeFile[] = "resources/users.txt";
    char stringa[MAX_LENGHT];
    char stringcopy[MAX_LENGHT];
    int id, counter = 0, scelta = 0;

    while(!scelta)
    {
        clear();
        term_printlogo();
        printf("LOGIN\nDigita il tuo username: ");
        scanf("%s", user);
        printf("\n");

        FILE * fp;
        fp = fopen(NomeFile, "r");

        while(!feof(fp))
        {
            fscanf(fp, "%s", stringa);
            if(!strcmp(stringa, "^/^"))
            {
                counter++;
                if(counter == 2)
                    counter = 0;
            }
            else if(counter == 0) // ID
            {
                id = stringtoint(stringa);
            }
            else if (counter == 1) // Username
            {
                if(!strcmp(user, stringa))
                {
                    strcpy(stringcopy, stringa);
                    tutto_minuscolo(stringcopy);
                    center_text("Benvenuto/a\n");
                    print_Effetto_Figo(stringcopy, id);
                    printf("\n\n");
                    clear();
                    return;
                }
            }
        }
        fclose(fp);
        printf("Mhhh... Sembra che nel database non ci sia questo nome.\nRiprovare(0) o aggiungerlo come nuovo utente(1)?\nScelta: ");
        scanf("%d", &scelta);
        if(scelta)
            term_register(user);

    }

}

void term()
/*
 * void term()
 *
 * Descrizione -> Main del programma
 */
{
    char input[MAX_LENGHT];
    char messaggio[MAX_LENGHT_TEXT];
    char temp;
    char username[MAX_LENGHT];

    term_login(username);
    term_printlogo();
    printf("Digita 'help' per la lista dei comandi\nConsiglio: Per una migliore esperienza metti a schermo intero la finestra\n\n");
    while(1)
    {
        printf("%s > ", username);
        memset(input,0,strlen(input));
        scanf("%s", input);

        if(!strcmp(input, "help"))
            term_help();
        else if(!strcmp(input, "logout"))
            term_login(username);
        else if(!strcmp(input, "quit"))
            return;
        else if(!strcmp(input, "send"))
        {
            printf("%s > Messaggio > ", username);
            scanf("%c",&temp);
            fgets(messaggio, 200, stdin);
            chat_write_message(term_find_id(username), username, messaggio);
        }
        else if(!strcmp(input, "load"))
            term_load_chat(term_find_id(username), username);
        else if(!strcmp(input, "info"))
            term_info();
        else
            printf("Sintassi errata, digita -h per la lista dei comandi\n");
    }
    return;
}
