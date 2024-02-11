#include "PuissanceN.h"

int main() {

    Grid grille;
    int rep;

    menu_demarrage(&rep);

    switch (rep) {
        // démarrer une nouvelle partie
        case 1 :
            nouvelle_partie(&grille);
            break;

        // charger une nouvelle partie
        case 2 :
            charger_partie(&grille);
            break;

        // Quitter
        default :
            Color(12,0);    // texte en rouge
            printf("Vous avez choisi de quitter le programme !\n");
            break;
    }
    return 0;
}