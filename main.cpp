#include <iostream>
#include "Lexer.h"
#include "Automate.h"

using namespace std;

int main() {
    string chaine;

    cout << "=== Analyseur Lexical & Automate Syntaxique ===" << endl;
    cout << "Entrez une expression à analyser (ou tapez 'exit' pour quitter) :" << endl;

    while (true) {
        cout << "> ";
        getline(cin, chaine);

        if (chaine == "exit") {
            cout << "Fermeture du programme." << endl;
            break;
        }


        // === TEST DU LEXER ===
        /*
        Lexer l(chaine);
        Symbole* s;

        cout << "Tokens détectés :" << endl;
        while (*(s = l.Consulter()) != FIN) {
            s->Affiche();
            cout << endl;
            l.Avancer();
        }

        cout << "FIN" << endl; // Indique la fin du flux
        */

        
        // === TEST DE L'AUTOMATE ===
        Automate automate(chaine);
        automate.run();
    }

    return 0;
}
