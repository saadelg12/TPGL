#include "Etat.h"
#include "Automate.h"
#include <iostream>

// État 0 : État initial
bool Etat0::transition(Automate &automate, Symbole *s)
{
    //cout << "Transition en Etat0 avec symbole : " << Etiquettes[*s] << endl;

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
    cerr << "Erreur syntaxique : [En Etat 0] caractère '" << getSymbolCharacter(*s) << "' inattendu." << endl;
    cerr << "Assurez-vous de bien entrer 'val' ou '(' en début d'expression." << endl;
        return false;
    }
    return true;
}

// État 1 : Expression acceptée
bool Etat1::transition(Automate &automate, Symbole *s)
{
    //cout << "Transition en Etat1 avec symbole : " << Etiquettes[*s] << endl;

    // Récupération du dernier symbole empilé pour affichage
    Symbole* lastSymbol = automate.getLastSymbol();
    string lastSymbolStr = lastSymbol ? getSymbolCharacter((int)*lastSymbol) : "début de l'expression";

    switch (*s)
    {
    case PLUS:
        automate.decalage(s, new Etat4());
        break;
    case MULT:
        automate.decalage(s, new Etat5());
        break;
    case FIN:
        return false;  // Fin de l'expression acceptée
    default:
        cerr << "Erreur syntaxique : [En Etat 1] caractère '" << getSymbolCharacter((int)*s) << "' inattendu." << endl;
        cerr << "Rappel : Les symboles possibles après '"<< lastSymbolStr << "' sont" ;
        cerr << " '+' ; '*' ; 'fin d'expression' .";
        cerr << endl;
        return false;
    }
    return true;
}



// État 2 : '('
bool Etat2::transition(Automate &automate, Symbole *s)
{
    //cout << "Transition en Etat2 avec symbole : " << Etiquettes[*s] << endl;

    // Récupération du dernier symbole empilé pour affichage
    Symbole* lastSymbol = automate.getLastSymbol();
    string lastSymbolStr = lastSymbol ? getSymbolCharacter((int)*lastSymbol) : "début de l'expression";

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
        cerr << "Erreur syntaxique : [En Etat 2] caractère '" << getSymbolCharacter((int)*s) << "' inattendu." << endl;
        cerr << "Rappel : Les symboles possibles après '"<< lastSymbolStr << "' sont" ;
        cerr << " 'val' ; '(' .";
        cerr << endl;
        return false;
    }
    return true;
}

// État 3 : Entier
bool Etat3::transition(Automate &automate, Symbole *s)
{
    //cout << "Transition en Etat3 avec symbole : " << Etiquettes[*s] << endl;

    // Récupération du dernier symbole empilé pour affichage
    Symbole* lastSymbol = automate.getLastSymbol();
    string lastSymbolStr = lastSymbol ? getSymbolCharacter((int)*lastSymbol) : "début de l'expression";


    switch (*s)
    {
    case PLUS:
    case MULT:
    case CLOSEPAR:
    case FIN:
        // Réduction de 1 élément : E → valeur entière
        automate.reduction(1);
        return true;
    default:
        cerr << "Erreur syntaxique : [En Etat 3] caractère '" << getSymbolCharacter((int)*s) << "' inattendu." << endl;
        cerr << "Rappel : Les symboles possibles après '"<< lastSymbolStr << "' sont" ;
        cerr << " '+' ; '*' ; ')' ; 'fin d'expression' .";
        cerr << endl;
        return false;
    }
    return true;
}

// État 4 : après un '+' on attend une autre EXPR
bool Etat4::transition(Automate &automate, Symbole *s)
{
    //cout << "Transition en Etat4 avec symbole : " << Etiquettes[*s] << endl;

    // Récupération du dernier symbole empilé pour affichage
    Symbole* lastSymbol = automate.getLastSymbol();
    string lastSymbolStr = lastSymbol ? getSymbolCharacter((int)*lastSymbol) : "début de l'expression";


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
        cerr << "Erreur syntaxique : [En Etat 4] caractère '" << getSymbolCharacter((int)*s) << "' inattendu." << endl;
        cerr << "Rappel : Les symboles possibles après '"<< lastSymbolStr << "' sont" ;
        cerr << " 'val' ; '(' .";
        cerr << endl;
        return false;
    }
    return true;
}

// État 5 : après un '*' on attend une autre EXPR
bool Etat5::transition(Automate &automate, Symbole *s)
{
    //cout << "Transition en Etat5 avec symbole : " << Etiquettes[*s] << endl;

    // Récupération du dernier symbole empilé pour affichage
    Symbole* lastSymbol = automate.getLastSymbol();
    string lastSymbolStr = lastSymbol ? getSymbolCharacter((int)*lastSymbol) : "début de l'expression";


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
        cerr << "Erreur syntaxique : [En Etat 5] caractère '" << getSymbolCharacter((int)*s) << "' inattendu." << endl;
        cerr << "Rappel : Les symboles possibles après '"<< lastSymbolStr << "' sont" ;
        cerr << " 'val' ; '(' .";
        cerr << endl;
        return false;
    }
    return true;
}

// État 6 : après '(' on a obtenu un EXPR
bool Etat6::transition(Automate &automate, Symbole *s)
{
    //cout << "Transition en Etat6 avec symbole : " << Etiquettes[*s] << endl;

    // Récupération du dernier symbole empilé pour affichage
    Symbole* lastSymbol = automate.getLastSymbol();
    string lastSymbolStr = lastSymbol ? getSymbolCharacter((int)*lastSymbol) : "début de l'expression";


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
        cerr << "Erreur syntaxique : [En Etat 6] caractère '" << getSymbolCharacter((int)*s) << "' inattendu." << endl;
        cerr << "Rappel : Les symboles possibles après '"<< lastSymbolStr << "' sont" ;
        cerr << " '+' ; '*' ; ')' .";
        cerr << endl;
        return false;
    }
    return true;
}

// État 7 : après avoir décodé EXPR suite à un '+'
bool Etat7::transition(Automate &automate, Symbole *s)
{
    //cout << "Transition en Etat7 avec symbole : " << Etiquettes[*s] << endl;

    // Récupération du dernier symbole empilé pour affichage
    Symbole* lastSymbol = automate.getLastSymbol();
    string lastSymbolStr = lastSymbol ? getSymbolCharacter((int)*lastSymbol) : "début de l'expression";


    switch (*s)
    {
    case PLUS:
    case CLOSEPAR:
    case FIN:
        // Réduction de 3 éléments : E → E + E
        automate.reduction(3);
        //cout << "Réduction faite par la règle 2 en Etat7" << endl;
        break;
    case MULT:
        automate.decalage(s, new Etat5());
        break;
    default:
        cerr << "Erreur syntaxique : [En Etat 7] caractère '" << getSymbolCharacter((int)*s) << "' inattendu." << endl;
        cerr << "Rappel : Les symboles possibles après '"<< lastSymbolStr << "' sont" ;
        cerr << " '+' ; '*' ; ')' ; 'fin d'expression' .";
        cerr << endl;
        return false;
    }
    return true;
}

// État 8 : après avoir décodé EXPR suite à un '*'
bool Etat8::transition(Automate &automate, Symbole *s)
{
    //cout << "Transition en Etat8 avec symbole : " << Etiquettes[*s] << endl;

    // Récupération du dernier symbole empilé pour affichage
    Symbole* lastSymbol = automate.getLastSymbol();
    string lastSymbolStr = lastSymbol ? getSymbolCharacter((int)*lastSymbol) : "début de l'expression";


    switch (*s)
    {
    case PLUS:
    case MULT:
    case CLOSEPAR:
    case FIN:
        // Réduction de 3 éléments : E → E * E
        automate.reduction(3);
        //cout << "Réduction faite par la règle 3 en Etat8" << endl;
        break;
    default:
        cerr << "Erreur syntaxique : [En Etat 8] caractère '" << getSymbolCharacter((int)*s) << "' inattendu." << endl;
        cerr << "Rappel : Les symboles possibles après '"<< lastSymbolStr << "' sont" ;
        cerr << " '+' ; '*' ; ')' ; 'fin d'expression' .";
        cerr << endl;
        return false;
    }
    return true;
}

bool Etat9::transition(Automate &automate, Symbole *s) {
    //cout << "Transition en Etat9 avec symbole : " << Etiquettes[*s] << endl;

    // Récupération du dernier symbole empilé pour affichage
    Symbole* lastSymbol = automate.getLastSymbol();
    string lastSymbolStr = lastSymbol ? getSymbolCharacter((int)*lastSymbol) : "début de l'expression";


    switch (*s)
    {
    case PLUS:
    case MULT:
    case CLOSEPAR:
    case FIN:  // <-- On autorise la réduction si la fin survient juste après ')'
        //cout << "[DEBUG] Réduction dans Etat9 (E → ( E ))" << endl;
        automate.reduction(3);
        break;
    default:
        cerr << "Erreur syntaxique : [En Etat 9] caractère '" << getSymbolCharacter((int)*s) << "' inattendu." << endl;
        cerr << "Rappel : Les symboles possibles après '"<< lastSymbolStr << "' sont" ;
        cerr << " '+' ; '*' ; ')' ; 'fin d'expression' .";
        cerr << endl;
        return false;
    }
    return true;
}


