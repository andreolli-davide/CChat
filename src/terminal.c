// @ Davide Andreolli, 2020

#include <stdlib.h>

// Per esecuzione in CMD
#ifdef _WIN32
    #include <windows.h>

    int get_size_x_of_terminal()
    /*
     *  Funzione get
     *
     *
     *
     */
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    int get_size_y_of_terminal()
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
    {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_col;
    }

    int get_size_y_of_terminal()
    {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_row;
    }

    void clear()
    {
        system("clear");
    }

#endif

