
/*
 *       .o88b.       .o88b. db   db  .d8b.  d888888b
 *      d8P  Y8      d8P  Y8 88   88 d8' `8b `~~88~~'
 *      8P           8P      88ooo88 88ooo88    88
 *      8b           8b      88~~~88 88~~~88    88
 *      Y8b  d8      Y8b  d8 88   88 88   88    88
 *       `Y88P'       `Y88P' YP   YP YP   YP    YP
 *
 *      PROGETTO DI FINE ANNO, C CHAT
 *      di Davide Andreolli
 *
 *      Questo programma che ho scritto permette di scambiare messaggi in un gruppo di lavoro,
 *      come ad esempio una classe, un team ma può anche essere usato per scambiare tra amici
 *      brevi messaggi.
 *
 *      Come esempio di utilizzo del programma ho già preimpostato nei salvataggi una chat copiata
 *      da un nostro gruppo di classe su Whatsapp, per far vedere che effettivamente ha le stesse
 *      funzionalità della famosa chat di messaggistica.
 *
 *      Mettendo la cartella con il file eseguibile e il file di salvataggio su un server accessibile
 *      da più dispositivi è possibile scambiare messaggi in remoto, facendola diventare funzionale
 *      e facilmente accessibile.
 *
 *      Il programma è stato scritto esclusivamente da me con l'aiuto di forum per determinate
 *      funzionalità che ho aggiunto, come poter scrivere una stringa con all'interno spaziature,
 *      non possibile con il comune scanf.
 *
 *      File essenziali per il funzionamento del programma:
 *      resources/chatbk.txt  -->  Sul file di testo vengono salvati i dati e i messaggi degli utenti e
 *                       della chat.
 *      resources/users.txt   -->  Sul file salva gli utenti che hanno creato un profilo sul programma.
 *
 *      Librerie:
 *      include/shell.h        -->  Contiene le funzioni che si occupano della stampa a terminale dell'interfaccia
 *                                  e dell'interazione con l'utente.
 *      include/chat.h         -->  Contiene alcune funzioni che vengono utilizzate dalle funzioni contenute
 *                                  in shell.h.
 *      include/text.h         -->  Contiene alcune funzione di formattazione del testo nel terminale e alcuni
 *                                  effetti per rendere l'interfaccia meno "noiosa".
 *      include/terminal.h     -->  Contiene le funzioni per poter conoscele le dimensioni del terminale nel
 *                                  momento in cui vengono invocate.
 *
 *      AGGIORNAMENTO AGOSTO 2020:
 *      - Aggiunta la compatibilità con terminale bash (MacOS e Linux), quindi eseguibile su qualsiasi
 *        sistema operativo desktop
 *
 *	- Sistemati alcuni problemi riguardanti i colori assegnati agli utenti
 *
 *      @ Davide Andreolli, 2020
 */



#include "shell.h"

int main()
{
    shell();

    return 0;
}
