// @ Davide Andreolli, 2020

#ifndef SHELL_H_INCLUDED
#define SHELL_H_INCLUDED

// Stampa il logo del programma
void shell_printlogo();

// Stampa la lista delle funzioni disponibili
void shell_help();

// Stampa le informazioni del programma
void shell_info();

// Trova l'ID dell'utente dato in input
int shell_find_id(char username[]);

// Trova il numero degli utenti
int shell_check_id(char username[]);

// Stampa il contenuto della chat
void shell_load_chat(char loginusername[], int loginid);

// Registra un nuovo utente al programma
void shell_register(char username[]);

// Effettua il login al programma
void shell_login();

// Programma principale che si occupa di interagir econ l'utente e stampare la funzione desiderata
void shell();

#endif // SHELL_H_INCLUDED
