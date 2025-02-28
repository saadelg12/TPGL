#pragma once

#include "Lexer.h"
#include "Etat.h"
#include <stack>

class Automate {
public:
    Automate(string flux);
    void run();
    void decalage(Symbole *s, Etat *e);
    void reduction(int n, Symbole *s);
    void transitionSimple(Symbole * s, Etat * e);
    Symbole *getTopSymbole() { 
        if (!pileSymboles.empty()) return pileSymboles.top(); 
        return nullptr; 
    }
    void popSymbole() { pileSymboles.pop(); }
    


private:
    stack<Symbole *> pileSymboles;
    stack<Etat *> pileEtats;
    Lexer lexer;
};
