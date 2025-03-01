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
    cout << "Transition en Etat1 avec symbole : " << Etiquettes[*s] << endl;
    switch (*s)
    {
    case PLUS:
        automate.decalage(s, new Etat4());
        break;
    case MULT:
        automate.decalage(s, new Etat5());
        break;
    case FIN:
        cout << "Expression reconnue !" << endl;
        return false;
        break;
    default:
        cerr << "Erreur syntaxique : caractère inattendu en Etat1." << endl;
        return false;
    }
    return true;
}

// État 2 : Parenthèse ouvrante
bool Etat2::transition(Automate &automate, Symbole *s)
{
    cout << "Transition en Etat2 avec symbole : " << Etiquettes[*s] << endl;
    switch (*s)
    {
    case INT:
        automate.decalage(s, new Etat3());
        break;
    case OPENPAR:
        automate.decalage(s, new Etat2());
        break;
    case EXPR:
        automate.transitionSimple(s, new Etat6());
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
            automate.reduction(1, nullptr);
            return true;
        }
        default:
            cerr << "Erreur syntaxique après un entier." << endl;
            return false;
    }
}
// État 4 :
bool Etat4::transition(Automate &automate, Symbole *s)
{
    cout << "Transition en Etat4 avec symbole : " << Etiquettes[*s] << endl;
    switch (*s)
    {
    case INT:
        automate.decalage(s, new Etat3());
        break;
    case OPENPAR:
        automate.decalage(s, new Etat2());
        break;
    case EXPR:
        automate.transitionSimple(s, new Etat7());
        break;
    default:
        cerr << "Erreur syntaxique : caractère inattendu en Etat4." << endl;
        return false;
    }
    return true;
}
// État 5 :
bool Etat5::transition(Automate &automate, Symbole *s)
{
    cout << "Transition en Etat5 avec symbole : " << Etiquettes[*s] << endl;
    switch (*s)
    {
    case INT:
        automate.decalage(s, new Etat3());
        break;
    case OPENPAR:
        automate.decalage(s, new Etat2());
        break;
    case EXPR:
        automate.transitionSimple(s, new Etat8());
        break;
    default:
        cerr << "Erreur syntaxique : caractère inattendu en Etat5." << endl;
        return false;
    }
    return true;
}
// État 6 :
bool Etat6::transition(Automate &automate, Symbole *s)
{
    cout << "Transition en Etat6 avec symbole : " << Etiquettes[*s] << endl;
    switch (*s)
    {
    case PLUS:
        automate.decalage(s, new Etat4());
        break;
    case MULT:
        automate.decalage(s, new Etat5());
        break;
    case CLOSEPAR:
        automate.decalage(s, new Etat9());
        break;
    default:
        cerr << "Erreur syntaxique : caractère inattendu en Etat6." << endl;
        return false;
    }
    return true;
}
// État 7 :
bool Etat7::transition(Automate &automate, Symbole *s)
{
    cout << "Transition en Etat7 avec symbole : " << Etiquettes[*s] << endl;
    switch (*s)
    {
    case PLUS:
    case CLOSEPAR:
    case FIN:
    {
        automate.reduction(3, nullptr);
        cout << "Réduction faite par la règle 2 en Etat7 "<< endl;
        break;
    }
    case MULT:
        automate.decalage(s, new Etat5());
        break;
    default:
        cerr << "Erreur syntaxique : caractère inattendu en Etat7." << endl;
        return false;
    }
    return true;
}
// État 8 :
bool Etat8::transition(Automate &automate, Symbole *s)
{
    cout << "Transition en Etat8 avec symbole : " << Etiquettes[*s] << endl;
    switch (*s)
    {
    case PLUS:
    case MULT:
    case CLOSEPAR:
    case FIN:
    {
        automate.reduction(3, nullptr);
        cout << "Réduction faite par la règle 3 en Etat8 "<< endl;
        break;
    }
    default:
        cerr << "Erreur syntaxique : caractère inattendu en Etat8." << endl;
        return false;
    }
    return true;
}
// État 9 :
bool Etat9::transition(Automate &automate, Symbole *s)
{
    cout << "Transition en Etat9 avec symbole : " << Etiquettes[*s] << endl;
    switch (*s)
    {
    case PLUS:
    case MULT:
    case CLOSEPAR:
    case FIN:
    {
        // automate.popAndDestroySymbol();  // )
        // Expression* e = (Expression*) automate.popSymbol();  // E
        // automate.popAndDestroySymbol();  // (
        automate.reduction(3, nullptr);
        cout << "Réduction faite par la règle 4 en Etat9 "<< endl;
        break;
    }
    default:
        cerr << "Erreur syntaxique : caractère inattendu en Etat8." << endl;
        return false;
    }
    return true;
}

