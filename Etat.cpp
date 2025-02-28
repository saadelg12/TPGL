#include "Etat.h"
#include "Automate.h"
#include <iostream>

// État 0 : État initial
bool Etat0::transition(Automate &automate, Symbole *s)
{
    cout << "Transition en Etat0 avec symbole : " << Etiquettes[*s] << endl;
    switch (*s)
    {
    case INT:
        automate.decalage(s, new Etat3());
        break;
    case OPENPAR:
        automate.decalage(s, new Etat2());
        break;
    case EXPR:
        automate.transitionSimple(s, new Etat1());
        break;
    default:
        cerr << "Erreur syntaxique : caractère inattendu en Etat0." << endl;
        return false;
    }
    return true;
}

// État 1 : Expression acceptée
bool Etat1::transition(Automate &automate, Symbole *s)
{
    if (*s == FIN)
    {
        cout << "Expression reconnue !" << endl;
        return false;
    }
    else
    {
        cerr << "Erreur syntaxique en Etat1 : entrée non reconnue." << endl;
        return false;
    }
}

// État 2 : Parenthèse ouvrante
bool Etat2::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
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

// État 3 : Entier
bool Etat3::transition(Automate &automate, Symbole *s) {
    switch (*s) {
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN:
        {
            // Vérification du symbole en haut de la pile
            if (automate.getTopSymbole() == nullptr) {
                cerr << "Erreur : Pile vide lors de la réduction." << endl;
                return false;
            }

            Symbole *topSymbole = automate.getTopSymbole();
            cout << "Symbole récupéré en haut de la pile : " << Etiquettes[*topSymbole] << endl;

            Entier *val = dynamic_cast<Entier *>(topSymbole);
            if (!val) {
                cerr << "Erreur : Symbole en haut de pile n'est pas un Entier." << endl;
                return false;
            }

            // On effectue la réduction
            int valeur = val->getValue();
            automate.reduction(1, new Expression(valeur));
            return true;
        }
        default:
            cerr << "Erreur syntaxique après un entier." << endl;
            return false;
    }
}

