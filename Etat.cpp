#include "Etat.h"
#include "Automate.h"
#include <iostream>

// État 0 : État initial
bool Etat0::transition(Automate &automate, Symbole *s) {
    switch (*s) {
        case INT:  // Un entier doit être décalé vers Etat3
            automate.decalage(s, new Etat3());
            break;
        case OPENPAR:  // Une parenthèse ouvrante doit être décalée vers Etat2
            automate.decalage(s, new Etat2());
            break;
        case EXPR:  // Une expression complète doit passer à Etat1
            automate.decalage(s, new Etat1());
            break;
        default:
            cerr << "Erreur syntaxique : caractère inattendu en Etat0." << endl;
            return false;
    }
    return true;
}


// État 1 : Expression acceptée
bool Etat1::transition(Automate &automate, Symbole *s) {
    if (*s == FIN) {
        cout << "Expression reconnue !" << endl;
        return false;
    } else {
        cerr << "Erreur syntaxique en Etat1 : entrée non reconnue." << endl;
        return false;
    }
}

// État 2 : Parenthèse ouvrante
bool Etat2::transition(Automate &automate, Symbole *s) {
    switch (*s) {
        case INT:
            automate.decalage(s, new Etat3());
            break;
        case OPENPAR:
            automate.decalage(s, new Etat2());
            break;
        default:
            cerr << "Erreur syntaxique : caractère inattendu après '('." << endl;
            return false;
    }
    return true;
}

// État 3 : Lecture d'un entier
bool Etat3::transition(Automate &automate, Symbole *s) {
    switch (*s) {
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN:
            automate.reduction(1, new Symbole(EXPR)); // Réduction E → val
            break;
        default:
            cerr << "Erreur syntaxique après un entier." << endl;
            return false;
    }
    return true;
}
