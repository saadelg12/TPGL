#pragma once

#include "Lexer.h"
#include "Etat.h"
#include <stack>

class Automate {
public:
    Automate(string flux);
    ~Automate();
    void run();

    void decalage(Symbole *s, Etat *e);
    void reduction(int n);
    void transitionSimple(Symbole *s, Etat *e);

    Expression* getResult();

    Symbole* getLastSymbol() {
        if (!pileSymboles.empty()) {
            return pileSymboles.top();  // Retourne le dernier symbole empilé
        }
        return nullptr;  // Retourne nullptr si la pile est vide
    }
    Etat* getLastState() {
        if (!pileEtats.empty()) {
            return pileEtats.top();  // Retourne le dernier symbole empilé
        }
        return nullptr;  // Retourne nullptr si la pile est vide
    }

private:
    stack<Symbole *> pileSymboles;
    stack<Etat *>    pileEtats;
    Lexer            lexer;
};
