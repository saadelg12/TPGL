#include "Automate.h"
#include <iostream>

Automate::Automate(string flux) : lexer(flux) {
    pileEtats.push(new Etat0());
}

void Automate::run() {
    bool running = true;
    
    while (running) {
        Symbole *s = lexer.Consulter();
        lexer.Avancer();
        
        running = pileEtats.top()->transition(*this, s);
    }
}

void Automate::decalage(Symbole *s, Etat *e) {
    pileSymboles.push(s);
    pileEtats.push(e);
}

void Automate::reduction(int n, Symbole *s) {
    for (int i = 0; i < n; i++) {
        delete pileEtats.top();
        pileEtats.pop();
        delete pileSymboles.top();
        pileSymboles.pop();
    }

    pileEtats.top()->transition(*this, s);
}
