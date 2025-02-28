#include "Lexer.h"
#include <iostream>

Symbole* Lexer::Consulter() {
    if (!tampon) {
        // Ignorer les espaces
        while (tete < flux.length() && flux[tete] == ' ') {
           tete++;
        }

        if (tete == flux.length()) {  // Fin du flux
            tampon = new Symbole(FIN);
        } else {
            char c = flux[tete];  // Assurer que l'accès à flux[tete] est valide
            switch (c) {
                case '(':
                    tampon = new Symbole(OPENPAR);
                    tete++;
                    break;
                case ')':
                    tampon = new Symbole(CLOSEPAR);
                    tete++;
                    break;
                case '*':
                    tampon = new Symbole(MULT);
                    tete++;
                    break;
                case '+':
                    tampon = new Symbole(PLUS);
                    tete++;
                    break;
                default:
                    if (isdigit(c)) {  // Vérifier si c'est un chiffre
                        int resultat = c - '0';
                        int i = 1;
                        while (tete + i < flux.length() && isdigit(flux[tete + i])) {
                            resultat = resultat * 10 + (flux[tete + i] - '0');
                            i++;
                        }
                        tete += i;
                        tampon = new Entier(resultat);
                    } else {
                        cerr << "Erreur lexicale : caractère invalide '" << c << "'\n";
                        tampon = new Symbole(ERREUR);
                        tete++;
                    }
            }
        }
    }
    return tampon;
}

void Lexer::Avancer() {
    if (tampon) {
        delete tampon;
        tampon = nullptr;
    }
}
