#pragma once

#include <string>
#include <iostream>

using namespace std;

// Enumération des types de symboles
enum Identificateurs { OPENPAR, CLOSEPAR, PLUS, MULT, INT, FIN, EXPR, ERREUR };

// Noms des symboles pour affichage
const string Etiquettes[] = { "OPENPAR", "CLOSEPAR", "PLUS", "MULT", "INT", "FIN", "EXPR", "ERREUR" };

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

// Classe pour les expressions
class Expression : public Symbole {
    public:
        // Constructeur pour une expression simple (ex: E → val)
        Expression(int v) : Symbole(EXPR), valeur(v) {}

        // Constructeur pour une expression composée (ex: E → E + E ou E * E)
        Expression(Expression* gauche, Expression* droite, char op) : Symbole(EXPR) {
            if (op == '+') {
                valeur = gauche->getValue() + droite->getValue();
            } else if (op == '*') {
                valeur = gauche->getValue() * droite->getValue();
            }

            // Libération de la mémoire des sous-expressions après calcul
            delete gauche;
            delete droite;
        }
        ~Expression() {}
        virtual void Affiche() { Symbole::Affiche(); cout << "(" << valeur << ")"; }
        int getValue() { return valeur; }
    
    protected:
        int valeur;
        Expression* gauche = nullptr;
        Expression* droite = nullptr;
        char operateur;  // '+' pour addition, '*' pour multiplication
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
