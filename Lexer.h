#pragma once

#include <string>
#include "Symbole.h"

using namespace std;

class Lexer {
public:
    Lexer(string s) : flux(s), tete(0), tampon(nullptr) { }
    ~Lexer() { if (tampon && *tampon != FIN) delete tampon; }

    Symbole* Consulter();  // Récupère le prochain token sans avancer
    void Avancer();        // Passe au token suivant

protected:
    string flux;   // La chaîne d’entrée
    int tete;      // Position actuelle dans la chaîne
    Symbole* tampon;  // Stocke le dernier symbole analysé
};
