#include "Automate.h"
#include <iostream>

Automate::Automate(string flux) : lexer(flux) {
    pileEtats.push(new Etat0());
}

void Automate::run() {
    bool running = true;
    
    while (running) {
        Symbole *s = lexer.Consulter();
        //lexer.Avancer();
        cout << "Etat avant transition :" << pileEtats.top()->getNom() << endl;
        cout << "Symbole :" << Etiquettes[*s] << endl;

        running = pileEtats.top()->transition(*this, s);

        cout << "Etat après transition :" << pileEtats.top()->getNom() << endl;
    }
}

void Automate::transitionSimple(Symbole *s, Etat *e) {
    pileSymboles.push(s);
    pileEtats.push(e);

}

void Automate::decalage(Symbole *s, Etat *e) {
    cout << "Décalage du symbole : " << Etiquettes[*s] << endl;
    pileSymboles.push(s);
    pileEtats.push(e);
    lexer.Avancer();
}


void Automate::reduction(int n, Symbole *s) {
    // for (int i = 0; i < n; i++) {
    //     delete pileEtats.top();
    //     pileEtats.pop();
    // }
    // // Ajouter le nouveau symbole après la réduction
    // pileSymboles.push(s);
    // pileEtats.top()->transition(*this, s);
    stack<Symbole *> aEnlever;
    for (int i = 0; i < n; i++) {
        delete (pileEtats.top());
        pileEtats.pop();
        aEnlever.push(pileSymboles.top());
        pileSymboles.pop();
      }
    
      int val;
    
      if (n == 1) {
        val = ((Entier *)aEnlever.top())->getValue();
      } else if (n == 3) {
        if (*aEnlever.top() == OPENPAR) {
          aEnlever.pop();
          val = ((Expression *)aEnlever.top())->getValue();
        } else {
          val = ((Expression *)aEnlever.top())->getValue();
          aEnlever.pop();
          if (*aEnlever.top() == MULT) {
            aEnlever.pop();
            val = val * ((Expression *)aEnlever.top())->getValue();
          } else {
            aEnlever.pop();
            val = val + ((Expression *)aEnlever.top())->getValue();
          }
        }
      }
    
      pileEtats.top()->transition(*this, new Expression(val));
}



