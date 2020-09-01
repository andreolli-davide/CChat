// @ Davide Andreolli, 2020

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#include "text.h"
#include "term.h"
#include "terminal.h"

#define MAX_LENGHT_ID 2
#define MAX_N_MEX 100
#define MAX_LENGHT_TEXT 200
#define MAX_LENGHT 30

#define N 150

char text_colors_chat[6][7] = 
/*
    Colori che possono essere assegnati ad un utente
*/
{
    "red",
    "green",
    "yellow",
    "blue",
    "magenta",
    "cyan"
};

size_t strlen(const char *s);
/*
    Inizializzo strlen()
*/

void chat_other_user_message(int id, char user[], char text[])
/*
 * void chat_other_user_message()
 *
 * Descrizione -> Stampa il messaggio di un utente diverso da quello loggato,
                  cioè allineato a sinistra
 * Parametri -> id -> id dell'utente
 *              user -> nome utente
 *              text -> messaggio dell'utente
 */
{
    printf("    ------------------------------\n");
    printf("    ");
    print_colored_text(user, text_colors_chat[id%6]);
    printf("\n");
    printf("    %s\n", text);
    printf("    ------------------------------\n\n");
}

void chat_logged_user_message(int id, char user[], char text[])
/*
 * void chat_logged_user_message()
 *
 * Descrizione -> Stampa il messaggio dell'utente loggato, cioè allineato a destra
 * Parametri -> id -> id dell'utente
 *              user -> nome utente
 *              text -> messaggio dell'utente
 */
{
    int width = get_size_x_of_terminal(), len, i;
    len = strlen(user);
    for(i=1; i<width-29-4; i++)
        printf(" ");
    printf("------------------------------\n");
    for(i=1; i<width-len-3; i++)
        printf(" ");
    print_colored_text(user, text_colors_chat[id%6]);
    printf("\n");
    len = strlen(text);
    for(i=1; i<width-len-4; i++)
        printf(" ");
    printf("%s\n", text);
    for(i=1; i<width-33; i++)
        printf(" ");
    printf("------------------------------\n\n");
}

void chat_write_message(int id, char user[], char text[])
/*
 * void chat_write_message()
 *
 * Descrizione -> Scrive un messaggio nella chat e lo salva
 * Parametri -> id -> id dell'utente
 *              user -> nome utente
 *              text -> messaggio dell'utente
 */
{
    FILE * fp;
    char NomeFile[20] = "resources/chatbk.txt";

    fp = fopen(NomeFile, "a");

    fprintf(fp, "%d ^/^ %s ^/^ %s ^/^ ", id, user, text);
    fclose(fp);

    term_load_chat(id, user);
}
