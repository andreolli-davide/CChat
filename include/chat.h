// @ Davide Andreolli, 2020

#ifndef CHAT_H_INCLUDED
#define CHAT_H_INCLUDED

// Stampa il messaggio di un utente diverso da quello con cui si è fatto il login
void chat_other_user_message(int id, char user[], char text[]);

// Stampa il messaggio dell'utente con con si è fatto il login
void chat_login_user_message(int id, char user[], char text[]);

// Salva il messaggio che l'utente con coi si è fatto il login nella chat
void chat_write_message(char loginusername[], int loginid, char messaggio[]);

#endif // CHAT_H_INCLUDED
