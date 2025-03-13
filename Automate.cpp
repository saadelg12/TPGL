#include "Automate.h"
#include <iostream>

Automate::Automate(string flux) : lexer(flux){
    // On empile l'état initial
    pileEtats.push(new Etat0());
}

Automate::~Automate() {
    // Vider la pile des états
    while (!pileEtats.empty()) {
        delete pileEtats.top();
        pileEtats.pop();
    }
    // Vider la pile des symboles
    while (!pileSymboles.empty()) {
        delete pileSymboles.top();
        pileSymboles.pop();
    }
}


void Automate::run() {
    bool running = true;
    
    while (running) {
        Symbole *s = lexer.Consulter();
        //cout << "\nEtat avant transition : " << pileEtats.top()->getNom() << endl;
        //cout << "Symbole : " << Etiquettes[*s] << endl;

        running = pileEtats.top()->transition(*this, s);

        //cout << "Etat après transition : " << pileEtats.top()->getNom() << endl;
    }
}

void Automate::transitionSimple(Symbole *s, Etat *e) {
    // Empile le symbole s et change d'état
    pileSymboles.push(s);
    pileEtats.push(e);
}

void Automate::decalage(Symbole *s, Etat *e) {
    //cout << "Décalage du symbole : " << Etiquettes[*s] << endl;
    pileSymboles.push(s);
    pileEtats.push(e);
    lexer.Avancer();

    //cout << "[DEBUG] Nouveau sommet de pileSymboles : ";
    //pileSymboles.top()->Affiche();
    //cout << endl;
}


void Automate::reduction(int n) {
    // On va dépiler n états et n symboles
    stack<Symbole *> aEnlever;

    for (int i = 0; i < n; i++) {
        delete pileEtats.top();
        pileEtats.pop();

        // Récupérer le symbole au sommet de la pile
        aEnlever.push(pileSymboles.top());
        pileSymboles.pop();
    }

    int val = 0; // par défaut

    if (n == 1) {
        Entier* entier = dynamic_cast<Entier*>(aEnlever.top());
        if (entier) {
            val = entier->getValue();
        } else {
            cerr << "[ERREUR] Échec du cast Entier* ! (Symbole incorrect)" << endl;
            aEnlever.top()->Affiche();
            cout << endl;
        }
    }
    
    else if (n == 3) {
        //cout << "[DEBUG] Réduction de 3 éléments : ";

        // Règles possibles :
        //   E → ( E )
        //   E → E + E
        //   E → E * E
        // Selon ce qu’on trouve dans aEnlever
        // L’ordre de dépilage est inversé par rapport à la lecture : 
        // le premier symbole dépilé est le dernier qu’on avait empilé.

        Symbole* s1 = aEnlever.top(); aEnlever.pop();
        Symbole* s2 = aEnlever.top(); aEnlever.pop();
        Symbole* s3 = aEnlever.top(); aEnlever.pop();

        //cout << "[DEBUG] Les 3 symboles dépilés : ";
        //s1->Affiche(); cout << " ";
        //s2->Affiche(); cout << " ";
        //s3->Affiche(); cout << endl;

        // 1) Cas : ( E )
        if (*s1 == OPENPAR && *s2 == EXPR && *s3 == CLOSEPAR) {
            Expression* expr = dynamic_cast<Expression*>(s2);
            if (expr) { val = expr->getValue(); }
        }
        // 2) Cas : E + E
        else if (*s1 == EXPR && *s2 == PLUS && *s3 == EXPR) {
            Expression* gauche = dynamic_cast<Expression*>(s3);
            Expression* droite = dynamic_cast<Expression*>(s1);
            if (gauche && droite) {
                val = gauche->getValue() + droite->getValue();
            }
        }
        // 3) Cas : E * E
        else if (*s1 == EXPR && *s2 == MULT && *s3 == EXPR) {
            Expression* gauche = dynamic_cast<Expression*>(s3);
            Expression* droite = dynamic_cast<Expression*>(s1);
            if (gauche && droite) {
                val = gauche->getValue() * droite->getValue();
            }
        }
        else {
            cerr << "Réduction impossible" << endl;
        }

        //cout << "[DEBUG] Valeur obtenue après réduction : " << val << endl;

        delete s1;
        delete s2;
        delete s3;
    }

    // Debug : on affiche la valeur qu’on a calculée
    //cout << "[Reduction] Valeur obtenue = " << val << endl;

    // Maintenant on crée un nouveau symbole EXPR(val) et on le «ré-injecte»
    Expression* newExpr = new Expression(val);

    // On ne ré-avance pas le lexer ici
    // On appelle la transition de l’état maintenant au sommet de la pile

    //cout << "[DEBUG] Transition après réduction : " << pileEtats.top()->getNom() << endl;

    pileEtats.top()->transition(*this, newExpr);

    // Libérer la mémoire des symboles «aEnlever» (ils ont servi pour l’analyse)
    // Sauf si on veut en garder un, mais ici on a déjà remonté la valeur 
    while (!aEnlever.empty()) {
        delete aEnlever.top();
        aEnlever.pop();
    }
}

Expression* Automate::getResult() {
    // On regarde le symbole au sommet de la pile
    if (!pileSymboles.empty()) {
        Symbole * s = dynamic_cast<Symbole*> (pileSymboles.top());
        if(*s == EXPR){
            Expression* expr = dynamic_cast<Expression*>(s);
            return expr;
        }
    }
    return nullptr;
}


