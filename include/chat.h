// @ Davide Andreolli, 2020

#ifndef CHAT_H_INCLUDED
#define CHAT_H_INCLUDED

// Stampa il messaggio di un utente diverso da quello con cui si � fatto il login
void chat_other_user_message(int id, char user[], char text[]);

// Stampa il messaggio dell'utente con con si � fatto il login
void chat_logged_user_message(int id, char user[], char text[]);

// Salva il messaggio che l'utente con coi si � fatto il login nella chat
void chat_write_message(int id, char user[], char text[]);

#endif // CHAT_H_INCLUDED
