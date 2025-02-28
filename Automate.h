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

private:
    stack<Symbole *> pileSymboles;
    stack<Etat *> pileEtats;
    Lexer lexer;
};
