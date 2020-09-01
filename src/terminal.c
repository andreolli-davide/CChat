// @ Davide Andreolli, 2020

#include <stdlib.h>

// Per esecuzione in CMD
#ifdef _WIN32
    #include <windows.h>

    int get_size_x_of_terminal()
    /*
    * int get_size_x_of_terminal()
    *
    * Descrizione -> Trova il numero di colonne nel terminale in uso
    * Ritorna -> numero di colonne del terminale
    */
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    int get_size_y_of_terminal()
    /*
    * int get_size_y_of_terminal()
    *
    * Descrizione -> Trova il numero di righe nel terminale in uso
    * Ritorna -> numero di righe del terminale
    */
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }

    void clear()
    {
        system("cls");
    }

#else
    #include <sys/ioctl.h>
    #include <unistd.h>
    #include <stdio.h>

    struct winsize w;

    int get_size_x_of_terminal()
    /*
    * int get_size_x_of_terminal()
    *
    * Descrizione -> Trova il numero di colonne nel terminale in uso
    * Ritorna -> numero di colonne del terminale
    */
    {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_col;
    }

    int get_size_y_of_terminal()
    /*
    * int get_size_y_of_terminal()
    *
    * Descrizione -> Trova il numero di righe nel terminale in uso
    * Ritorna -> numero di righe del terminale
    */
    {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_row;
    }

    void clear()
    {
        system("clear");
    }

#endif

