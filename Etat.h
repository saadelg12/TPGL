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
class Etat0 : public Etat {
public:
    Etat0() : Etat("E0") {}
    bool transition(Automate &automate, Symbole *s) override;
};

class Etat1 : public Etat {
public:
    Etat1() : Etat("E1") {}
    bool transition(Automate &automate, Symbole *s) override;
};

class Etat2 : public Etat {
public:
    Etat2() : Etat("E2") {}
    bool transition(Automate &automate, Symbole *s) override;
};

class Etat3 : public Etat {
public:
    Etat3() : Etat("E3") {}
    bool transition(Automate &automate, Symbole *s) override;
};

class Etat4 : public Etat {
public:
    Etat4() : Etat("E4") {}
    bool transition(Automate &automate, Symbole *s) override;
};

class Etat5 : public Etat {
public:
    Etat5() : Etat("E5") {}
    bool transition(Automate &automate, Symbole *s) override;
};

class Etat6 : public Etat {
public:
    Etat6() : Etat("E6") {}
    bool transition(Automate &automate, Symbole *s) override;
};

class Etat7 : public Etat {
public:
    Etat7() : Etat("E7") {}
    bool transition(Automate &automate, Symbole *s) override;
};

class Etat8 : public Etat {
public:
    Etat8() : Etat("E8") {}
    bool transition(Automate &automate, Symbole *s) override;
};

class Etat9 : public Etat {
public:
    Etat9() : Etat("E9") {}
    bool transition(Automate &automate, Symbole *s) override;
};
