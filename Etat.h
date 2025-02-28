#pragma once

#include "Symbole.h"
#include <string>

class Automate;  // Déclaration anticipée

using namespace std;

class Etat {
public:
    Etat(string nom) : etatNom(nom) {}
    virtual ~Etat() {}

    virtual bool transition(Automate &automate, Symbole *s) = 0;
    string getNom() const { return etatNom; }

protected:
    string etatNom;
};

// Définition des États spécifiques
class Etat0 : public Etat{
public:
    Etat0() : Etat("E0") {}
    bool transition(Automate &automate, Symbole *s);
};

class Etat1 : public Etat{
public:
    Etat1() : Etat("E1") {}
    bool transition(Automate &automate, Symbole *s);
};

class Etat2 : public Etat{
public:
    Etat2() : Etat("E2") {}
    bool transition(Automate &automate, Symbole *s);
};

class Etat3 : public Etat{
public:
    Etat3() : Etat("E3") {}
    bool transition(Automate &automate, Symbole *s);
};
