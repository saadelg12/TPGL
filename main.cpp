#include <iostream>
#include "Lexer.h"
#include "Automate.h"

using namespace std;

int main() {
    string chaine;

    cout << "Entrez une expression à analyser (ou tapez 'exit' pour quitter) :" << endl;

    while (true) {
        cout << "> ";
        if (!getline(cin, chaine)) {
            // Si on arrive en fin de stdin
            break;
        }

        if (chaine == "exit") {
            cout << "Fermeture du programme." << endl;
            break;
        }
        
        Automate automate(chaine);
        automate.run();

        // Récupérer l’éventuel résultat :
        Expression* resultat = automate.getResult();
        if (resultat) {
            cout << "Résultat de l'expression : " << resultat->getValue() << endl;
        } else {
            cout << "Aucun résultat disponible (expression invalide)" << endl;
        }
    }

    return 0;
}
