#include "Lexer.h"
#include <iostream>

Symbole* Lexer::Consulter() {
    if (!tampon) {
        // Ignorer les espaces
        while (tete < (int)flux.length() && flux[tete] == ' ') {
           tete++;
        }

        if (tete >= (int)flux.length()) {
            // Fin du flux
            tampon = new Symbole(FIN);
        } else {
            char c = flux[tete];
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
                if (isdigit(c)) {
                    int resultat = c - '0';
                    int i = 1;
                    while (tete + i < (int) flux.length() && isdigit(flux[tete + i])) {
                        resultat = resultat * 10 + (flux[tete + i] - '0');
                        i++;
                    }
                    tete += i;
                    tampon = new Entier(resultat);
                    //cout << "[LEXER] Créé Entier(" << resultat << ")" << endl;
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
        tampon = nullptr;
    }
}
