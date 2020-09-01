// @ Davide Andreolli, 2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "terminal.h"

char text_colors[6][7] = {
    "red",
    "green",
    "yellow",
    "blue",
    "magenta",
    "cyan"
};

#ifdef _WIN32
    #include <windows.h>

    void print_colored_text(char text[], char color[])
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD saved_attributes;

        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        saved_attributes = consoleInfo.wAttributes;

        int i;

        for(i=0; i<16; i++)
            if(strcmp(color, text_colors[i]) == 0)
                SetConsoleTextAttribute(hConsole, i);

        printf("%s", text);

        SetConsoleTextAttribute(hConsole, saved_attributes);
    }

#else

    #define COLOR_RESET "\e[0;0m"

    char ansi_colors[6][8] = {
        "\e[0;31m",
        "\e[0;32m",
        "\e[0;33m",
        "\e[0;34m",
        "\e[0;35m",
        "\e[0;36m"
    };

    void print_colored_text(char text[], char color[])
    {
        int i;

        for(i=0; i<6; i++)
            if(strcmp(color, text_colors[i]) == 0)
                printf("%s%s%s", ansi_colors[i], text, COLOR_RESET);
    }

#endif

size_t strlen(const char *s);

void tutto_minuscolo(char* text)
/*
 * void tutto_minuscolo()
 *
 * Descrizione -> Converte una stringa con delle possibili lettere minuscole in minuscolo
 * Parametri -> text -> stringa da convertire
 */
{
    int i;
    for(i=0; i<strlen(text); i++)
        if(text[i] > 64 && text[i] < 91)
            text[i] += 32;
}

void center_text(char text[])
/*
 * void center_text()
 *
 * Descrizione -> Stampa una scritta allineata al centro dell'interfaccia del terminale
 * Parametri -> text -> stringa da allineare
 */
{
    int width = get_size_x_of_terminal();
    int i;

    for(i=0; i < (width/2 - strlen(text)/2); i++)
        printf(" ");
    printf("%s\n", text);
}

void colored_centred_text(char text[], char color[])
/*
 * void colored_center_text()
 *
 * Descrizione -> Converte una stringa con delle possibili lettere minuscole in minuscolo
 * Parametri -> text -> stringa da allineare e colorare
 *              color -> colore della stringa
 */
{
    int width = get_size_x_of_terminal();
    int i;

    for(i=0; i < (width/2 - strlen(text)/2); i++)
        printf(" ");
    print_colored_text(text, color);
    printf("\n");
}

void print_Effetto_Figo(char text[], int color)
/*
 * void print_Effetto_Figo()
 *
 * Descrizione -> Stampa un effetto del testo
 * Parametri -> text -> stringa da allineare e colorare
 *              color -> colore della stringa
 */
{
    int width = get_size_x_of_terminal();
    int i, j;

    printf("%s", text);

    for(i=0; i<strlen(text); i++)
    {
        if(text[i] != ' ')
        {
            text[i] -= 32;
            printf("\r");
            for(j=0; j < (width/2 - strlen(text)/2); j++)
            printf(" ");
            print_colored_text(text, text_colors[color]);
            text[i] += 32;
            usleep(100000);
        }
    }

    i--;

    for(; i>=0; i--)
    {
        if(text[i] != ' ')
        {
            text[i] -= 32;
            printf("\r");
            for(j=0; j < (width/2 - strlen(text)/2); j++)
            printf(" ");
            print_colored_text(text, text_colors[color]);
            usleep(100000);
        }
    }
}

int stringtoint(char string[])
/*
 * int stringtoint()
 *
 * Descrizione -> Converte una stringa in un intero
 * Parametri -> text -> stringa da convertire
 */
{
    int i, tot = 0;
    for(i=0; i<strlen(string); i++)
        tot = tot * 10 + string[i] - 48;
    return tot;
}