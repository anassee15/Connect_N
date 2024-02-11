//
// Created by anasse on 02/06/2021.
//
#include "PuissanceN.h"

void menu_demarrage(int *rep) {

    do {
        printf("========= PUISSANCE N =========\n");
        printf("1 Demarrer une nouvelle partie\n");
        printf("2 Charger une partie existante\n");
        printf("3 Quitter\n");

        scanf("%d", rep);
        fflush(stdin);

    } while (*rep < 1 || *rep > 3);

}

void menu_modejeu(int *rep) {

    do {
        printf("========= MODE DE JEU =========\n");
        printf("1 - Joueur vs IA\n");
        printf("2 - Joueur 1 vs Joueur 2\n");

        scanf("%d", rep);
        fflush(stdin);
    } while (*rep < 1 || *rep > 2);

}

char tirage() {

    srand(time(NULL)); // Initialise le générateur de nombre aléatoire

    int joueur_rouge, joueur_jaune;
    char jeton;

    // permet de tirer aléatoirement le joueur jaune ou rouge, la boucle évite le cas les deux nombres sont égaux
    do {

        joueur_rouge = rand() % 50 + 1; // tire un nombre aléatoire entre 1 et 50
        joueur_jaune = rand() % 50 + 1;

    } while (joueur_rouge == joueur_jaune);

    if (joueur_rouge > joueur_jaune) {
        printf("le joueur rouge commence \n");
        jeton = 'X';
    } else {
        printf("le joueur jaune commence \n");
        jeton = 'O';
    }

    return jeton;
}

char changement_tour(char symbole) {

    char jeton = ' ';

    if (symbole == 'X') {
        jeton = 'O';
    } else if (symbole == 'O') {
        jeton = 'X';
    }
    return jeton;
}

int choix_action(Grid *grille, int nb_joueur) {

    int choix = 0;

    // si la grille est vide on ajoute forcement un jeton
    if(check_grid(grille) == 0) {

        choix = 1; // pour add_token -> ajouter un jeton

    } else {
        // si on est en joueur contre joueur
        if (nb_joueur == 2) {

            do {
                printf("Ajouter (1), retirer (2) un jeton ? (3) sauvegarder et quitter la partie\n");
                scanf("%d", &choix);
                fflush(stdin);
            } while (choix < 1 || choix > 3);

            // pour l'IA
        } else if (nb_joueur == 1) {

            choix = rand() % 100 + 1;

            // (90 % de chance que ce soit un add_token, 10 % pour un remove_token)
            if (choix > 10) {
                choix = 1;
            } else {
                choix = 2;
            }
        }
    }

    return choix;   // 1 pour add_token, 2 pour remove_token, 3 pour save
}

int deroulement_tour_joueur(Grid *grille, char symbole, int colonne_remove) {

    int action;         // stock si c'est add_token ou remove_token qui a lieu
    int validite;       // permet de stocker les valeurs de retour des fonctions add et remove

    action = choix_action(grille, 2);

    switch (action) {

        // ajouter un jeton
        case 1 :

            // on recommence tant que la colonne saisie n'est pas valide
            do {

                grille->colonne = 0;

                printf("Dans quelle colonne souhaitez-vous poser votre jeton ?\n");
                scanf("%d", &grille->colonne);
                fflush(stdin);

                // si la colonne saisie est égale à la colonne supprimer le tour d'avant, on redemande une colonne
                while (colonne_remove + 1 == grille->colonne) {
                    printf("Vous ne pouvez pas poser de jeton dans cette colonne, un jeton a ete supprime dans celle-ci le tour d'avant\n");
                    printf("Dans quelle colonne souhaitez-vous poser votre jeton ?\n");
                    scanf("%d", &grille->colonne);
                    fflush(stdin);      // pour ne pas avoir de problème lors de la saisie
                }
                validite = add_token(grille, symbole, 2);

            } while (validite != 1);
            break;

            // retirer un jeton
        case 2 :

            // on recommence tant que la colonne saisie n'est pas valide
            do {

                grille->colonne = 0;

                printf("Dans quelle colonne souhaitez-vous retirer un jeton ?\n");
                scanf("%d", &grille->colonne);
                fflush(stdin);
                validite = remove_token(grille, 2);

            } while (validite != 1);
            break;

            // sauvegarder et quitter
        case 3 :
            save(grille, symbole);
            printf("Vous avez quitte, votre partie a ete sauvegarde !\n");
            break;
    }

    return action;  // 1 si add, 2 si remove, 3 si save
}

int deroulement_1v1(Grid *grille, char jeton) {

    char symbole = ' ';     // 'O' ou 'X'

    // La condition ne concerne que la fonction load, pour récupérer le joueur dont c'est le tour, sinon tirage au sort pour celui qui commence
    if (jeton == 'X' || jeton == 'O') {
        symbole = jeton;
    } else {
        symbole = tirage();
    }

    int colonne_remove = -3;        // pour bloquer une colonne suite à un remove_token
    int vainqueur;                  // permet de déterminer le gagnant, en stockant 'check_winner'
    int action;                     // stocke la valeur de retour des fonction 'deroulement'

    // La partie continue tant qu'un gagnant n'est pas annoncé
    do {

        action = deroulement_tour_joueur(grille, symbole, colonne_remove);

        // si l'utilisateur a choisi de quitter on sort de la boucle
        if (action == 3) {
            vainqueur = 3;
        } else {

            show_grid(grille);
            vainqueur = check_winner(grille);
            symbole = changement_tour(symbole);

            // si un remove a eu lieu, on stocke la colonne du dernier jeton posé
            if (action == 2) {
                colonne_remove = grille->colonne;
            } else {
                colonne_remove = -3;
            }
        }

    } while (vainqueur == -1);

    // retourne 3 si le joueur sauvegarde, pour les autres valeurs elles n'ont pas d'intérêts
    return vainqueur;
}

int deroulement_tour_IA(Grid *grille, char symbole, int colonne_remove) {

    int action;         // stock si c'est add_token ou remove_token qui a lieu
    int validite;       // permet de stocker les valeurs de retour des fonctions add et remove

    // recommence tant que la colonne donné par l'IA n'est pas valide
    do {
        action = choix_action(grille, 1);    // inclus dans la boucle, si jamais la valeur retourné est non valide on en trouve une autre

        switch (action) {

            // ajouter un jeton
            case 1 :

                do {
                    grille->colonne = IA(grille, 1, colonne_remove);
                } while (colonne_remove + 1 == grille->colonne);

                validite = add_token(grille, symbole, 1);
                break;

                // retirer un jeton
            case 2 :

                grille->colonne = IA(grille, 2, colonne_remove);
                validite = remove_token(grille, 1);
                break;
        }

    } while (validite != 1);

    return action;
}

int deroulement_vs_IA(Grid *grille, char jeton) {

    char symbole = ' ';     // 'O' ou 'X'

    // La condition ne concerne que la fonction load, pour récupérer le joueur dont c'est le tour, sinon tirage au sort pour celui qui commence
    if (jeton == 'X' || jeton == 'O') {
        symbole = jeton;
    } else {
        symbole = tirage();
    }

    int colonne_remove = -3;        // pour bloquer une colonne suite à un remove_token
    int vainqueur;                  // permet de déterminer le gagnant, en stockant 'check_winner'
    int action;                     // stocke la valeur de retour des fonction 'deroulement'

    // La partie continue tant qu'un gagnant n'est pas annoncé
    do {

        // on attribue arbitrairement le jeton 'O' à l'IA
        switch(symbole) {
            case 'X' :
                action = deroulement_tour_joueur(grille, symbole, colonne_remove);
                show_grid(grille);
                break;
            case 'O' :
                action = deroulement_tour_IA(grille, symbole, colonne_remove);
                show_grid(grille);

                // permet d'afficher quel action a réalisée l'IA
                switch (action) {
                    case 1 :
                        printf("L'IA a pose un jeton dans la colonne %d\n", grille->colonne + 1);
                        break;
                    case 2 :
                        printf("L'IA a retire un jeton dans la colonne %d\n", grille->colonne + 1);
                        break;
                }
                break;
        }

        // si l'utilisateur a choisi de quitter on sort de la boucle
        if (action == 3) {
            vainqueur = 3;
        } else {

            vainqueur = check_winner(grille);
            symbole = changement_tour(symbole);
            // si un remove a eu lieu, on stocke la colonne du dernier jeton posé
            if (action == 2) {
                colonne_remove = grille->colonne;
            } else {
                colonne_remove = -3;
            }
        }

    } while (vainqueur == -1);

    // retourne 3 si le joueur sauvegarde, pour les autres valeurs elles n'ont pas d'intérêts
    return vainqueur;
}

void nouvelle_partie(Grid *grille) {

    int rep;
    char restart;
    int leave;      // stock la valeur de retour des fonctions déroulement, notamment si le joueur souhaite quitter

    // Permet de recommencer une partie si le joueur le souhaite
    do {

        // on initialise dans la boucle dans le cas ou le joueur refait une partie afin de ne pas avoir de problèmes
        restart = ' ';
        rep = 0;
        grille->taille = 0;

        menu_modejeu(&rep);

        printf("Combien de jetons devrons-etre alignes pour gagner ?\n");
        scanf("%d", &grille->taille);
        fflush(stdin);

        // On limite la taille maximum à 25 pour éviter les bugs d'affichage, et au moins à 5 car cela n'aurait aucun sens sinon
        while (grille->taille + 2 > 25 || grille->taille < 3) {

            Color(4, 0);    // met le texte en rouge
            printf("La valeur demande est invalide !\n");
            Color(15, 0);   // remet le texte en blanc

            printf("Combien de jetons devrons-etre alignes pour gagner ?\n");
            scanf("%d", &grille->taille);
            fflush(stdin);
        }

        grille->taille += 2;            // permet de définir la taille de la grille à ( N jetons à alignés ) + 2
        initialize_grid(grille);       // on initialise la grille
        show_grid(grille);              // on montre la grille

        switch (rep) {

            // VS IA
            case 1 :
                grille->mode_de_jeu = 1;
                leave = deroulement_vs_IA(grille, ' '); // jeton = ' ' car on commence une nouvelle partie
                break;

                // VS JOUEUR
            case 2 :
                grille->mode_de_jeu = 2;
                leave = deroulement_1v1(grille, ' ');   // jeton = ' ' car on commence une nouvelle partie
                break;
        }

        Color(15, 0);
        // si le joueur n'a pas souhaité quitter la partie, et qu'un gagnant a été annoncé
        if (leave != 3 ) {

            // controle d'acquisition
            do {
                printf("\nSouhaitez-vous refaire une partie ? ('O' pour oui ou 'N' pour non)\n");
                scanf(" %c", &restart);
                fflush(stdin);

                // met le caractère en majuscule pour éviter des problèmes inutile de casse
                restart = toupper(restart);
            } while (restart != 'O' && restart != 'N');
        }

    } while (restart == 'O');

    // condition afin de ne pas mettre un message inutile si le joueur sauvegarde
    if (leave != 3) {
        printf("La partie est terminee\n");
    }
}

void charger_partie(Grid *grille){

    int joueur;
    char symbole;
    char restart = ' ';
    int leave;

    joueur = load(grille);

    if(joueur != -1) {

        show_grid(grille);

        printf("Vous devez aligner %d jetons pour gagner\n", grille->taille - 2);

        if (joueur == 0) {
            symbole = 'X';
            printf("C'est au tour du joueur rouge 'X' !\n");
        } else {
            symbole = 'O';
            printf("C'est au tour du joueur jaune 'O' !\n");
        }

        switch (grille->mode_de_jeu) {
            case 1 :
                printf("Vous etes en mode Joueur contre IA\n");
                leave = deroulement_vs_IA(grille, symbole);
                break;
            case 2 :
                printf("Vous etes en mode Joueur contre Joueur\n");
                leave = deroulement_1v1(grille, symbole);
                break;
        }

        Color(15, 0);

        // si l'utilisateur ne choisi pas de sauvegarder
        if (leave != 3) {

            // controle d'acquisition
            do {
                printf("\nSouhaitez-vous refaire une partie ? ('O' pour oui ou 'N' pour non)\n");
                scanf(" %c", &restart);
                fflush(stdin);
                // met le caractère en majuscule pour éviter des problèmes inutile de casse
                restart = toupper(restart);
            } while (restart != 'O' && restart != 'N');

            // pour pouvoir recommencer si l'utilisateur le souhaite
            if(restart == 'O') {
                nouvelle_partie(grille);
            } else {
                printf("La partie est terminee\n");
            }
        }
    }
}
