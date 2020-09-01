// @ Davide Andreolli, 2020

#ifndef TERM_H_INCLUDED
#define TERM_H_INCLUDED

// Stampa il logo del programma
void term_printlogo();

// Stampa la lista delle funzioni disponibili
void term_help();

// Stampa le informazioni del programma
void term_info();

// Trova l'ID dell'utente dato in input
int term_find_id(char username[]);

// Trova il numero degli utenti
int term_check_id(char username[]);

// Stampa il contenuto della chat
void term_load_chat(int id, char user[]);

// Registra un nuovo utente al programma
void term_register(char * user);

// Effettua il login al programma
void term_login(char * user);

// Programma principale che si occupa di interagir econ l'utente e stampare la funzione desiderata
void term();

#endif // term_H_INCLUDED
