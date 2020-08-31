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

void shell_printlogo()
{
    colored_centred_text(" .o88b.       .o88b. db   db  .d8b.  d888888b", "cyan");
    colored_centred_text("d8P  Y8      d8P  Y8 88   88 d8' `8b `~~88~~'", "cyan");
    colored_centred_text("8P           8P      88ooo88 88ooo88    88   ", "cyan");
    colored_centred_text("8b           8b      88~~~88 88~~~88    88   ", "cyan");
    colored_centred_text("Y8b  d8      Y8b  d8 88   88 88   88    88   ", "cyan");
    colored_centred_text(" `Y88P'       `Y88P' YP   YP YP   YP    YP   ", "cyan");
    printf("\n\n");
}

void shell_help()
{
    clear();
    shell_printlogo();
    printf("Lista di comandi:\n");
    printf("help            Mostra questa schermata di aiuto\n");
    printf("load            Leggi o ricarica il contenuto della chat\n");
    printf("send            Invia un messaggio alla chat\n");
    printf("logout          Effettua il logout\n");
    printf("info            Informazioni sul programma\n");
    printf("quit            Effettua l'uscita dal programma\n\n");
}

void shell_info()
{
    clear();
    shell_printlogo();
    center_text("Creato da Davide Andreolli");
    center_text("Chat di messaggistica su terminale");
    center_text("Interamente scritto in linguaggio C");
    center_text("Leggi README.md per maggiori dettagli");
    printf("\n\n");
}

void shell_load_chat(char loginusername[], int loginid)
{
    clear();
    shell_printlogo();
    FILE * fp;
    char NomeFile[20] = {"chatbk.txt"};
    char stringa[MAX_LENGHT_TEXT];
    char username[MAX_LENGHT];
    char text[MAX_LENGHT_TEXT] = "";
    int counter = 0, id = 0;

    fp = fopen(NomeFile, "r");

    while(!feof(fp))
    {
        fscanf(fp, "%s", stringa);
        if(!strcmp(stringa, "^/^"))
        {
            counter++;
            if(counter == 3)
            {
                if(strcmp(username, loginusername))
                    chat_other_user_message(id, username, text);
                else
                    chat_login_user_message(id, username, text);
                counter = 0;
                memset(text, 0, strlen(text));
            }

            printf("\n");
        }
        if(counter == 0) // ID
            id = stringtoint(stringa);
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

int shell_find_id(char username[])
{
    FILE * fp;
    char NomeFile[20] = {"users.txt"};
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
            if(!strcmp(username, stringa))
                return id;
    }

    fclose(fp);
    return id;
}

int shell_check_id()
{
    FILE * fp;
    char NomeFile[20] = {"users.txt"};
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

void shell_register(char username[], char loginusername[])
{
    FILE * fp;
    char NomeFile[] = "users.txt";
    char stringcopy[MAX_LENGHT];

    strcpy(stringcopy, username);
    fp = fopen(NomeFile, "a");
    fprintf(fp, "%d ^/^ %s ^/^ ", shell_check_id() + 1, username);
    fclose(fp);
    tutto_minuscolo(stringcopy);
    clear();
    center_text("Benvenuto/a\n");
    print_Effetto_Figo(stringcopy, shell_check_id() + 1);
    printf("\n\n");
    strcpy(loginusername, username);
}

void shell_login(char loginusername[])
{
    char NomeFile[] = "users.txt";
    char username[MAX_LENGHT], stringa[MAX_LENGHT];
    char stringcopy[MAX_LENGHT];
    int id, counter = 0, scelta = 0;

    while(!scelta)
    {
        clear();
        shell_printlogo();
        printf("LOGIN\nDigita il tuo username: ");
        scanf("%s", username);
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
                if(!strcmp(username, stringa))
                {
                    strcpy(stringcopy, stringa);
                    tutto_minuscolo(stringcopy);
                    center_text("Benvenuto/a\n");
                    print_Effetto_Figo(stringcopy, id);
                    strcpy(loginusername, stringa);
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
            shell_register(username, loginusername);

    }

}

void shell()
{
    char input[MAX_LENGHT];
    char messaggio[MAX_LENGHT_TEXT];
    char temp;
    char username[MAX_LENGHT];

    chdir("resources");

    shell_login(username);
    shell_printlogo();
    printf("Digita 'help' per la lista dei comandi\nConsiglio: Per una migliore esperienza metti a schermo intero la finestra\n\n");
    while(1)
    {
        printf("%s > ", username);
        memset(input,0,strlen(input));
        scanf("%s", input);

        if(!strcmp(input, "help"))
            shell_help();
        else if(!strcmp(input, "logout"))
            shell_login(username);
        else if(!strcmp(input, "quit"))
            return;
        else if(!strcmp(input, "send"))
        {
            printf("%s > Messaggio > ", username);
            scanf("%c",&temp);
            fgets(messaggio, 200, stdin);
            chat_write_message(username, shell_find_id(username), messaggio);
        }
        else if(!strcmp(input, "load"))
            shell_load_chat(username, shell_find_id(username));
        else if(!strcmp(input, "info"))
            shell_info();
        else
            printf("Sintassi errata, digita -h per la lista dei comandi\n");
    }
    return;
}
