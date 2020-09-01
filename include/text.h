// @ Davide Andreolli, 2020

#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

// Sovrascrive la stringa data in input rendendola interamente minuscola
void tutto_minuscolo(char* text);

// Centra il testo a seconda della dimensione del terminale
void center_text(char text[]);

// Colora e stampa la stringa che viene data in input con il colore scelto
void print_colored_text(char text[], char color[]);

// Colora e centra la stringa data in input
void colored_centred_text(char text[], char color[]);

// Crea un effetto sul terminale della stringa data in input
void print_Effetto_Figo(char text[], int color);

// Trasforma un numero contenuto in un carattere o in una stringa in una variabile intera
int stringtoint(char stringa[]);

#endif // TEXT_H_INCLUDED
