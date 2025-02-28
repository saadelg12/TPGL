#pragma once

#include <string>
#include <iostream>

using namespace std;

// Enumération des types de symboles
enum Identificateurs { OPENPAR, CLOSEPAR, PLUS, MULT, INT, FIN, ERREUR };

// Noms des symboles pour affichage
const string Etiquettes[] = { "OPENPAR", "CLOSEPAR", "PLUS", "MULT", "INT", "FIN", "ERREUR" };

// Classe de base pour un symbole
class Symbole {
public:
    Symbole(int i) : ident(i) { }
    virtual ~Symbole() { }
    operator int() const { return ident; }
    virtual void Affiche() { cout << Etiquettes[ident]; }
    
protected:
    int ident;
};

// Classe pour les nombres entiers
class Entier : public Symbole {
public:
    Entier(int v) : Symbole(INT), valeur(v) { }
    ~Entier() { }
    virtual void Affiche() { Symbole::Affiche(); cout << "(" << valeur << ")"; }
    int getValue() { return valeur; }

protected:
    int valeur;
};
