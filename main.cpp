#include <iostream>
#include "Lexer.h"

using namespace std;

int main() {
    string chaine;

    cout << "=== Analyseur Lexical (Lexer) ===" << endl;
    cout << "Entrez une expression à analyser (ou tapez 'exit' pour quitter) :" << endl;

    while (true) {
        cout << "> ";
        getline(cin, chaine);

        if (chaine == "exit") {
            cout << "Fermeture du lexer." << endl;
            break;
        }

        Lexer l(chaine);
        Symbole* s;

        cout << "Tokens détectés :" << endl;
        while (*(s = l.Consulter()) != FIN) {
            s->Affiche();
            cout << endl;
            l.Avancer();
        }

        cout << "FIN" << endl; // Indique la fin du flux
    }

    return 0;
}
