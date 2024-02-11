//
// Created by anasse on 02/06/2021.
//
#include "PuissanceN.h"

char check_colonne(Grid * grille) {

    char validite = 'Y'; // Y comme 'YES' pour pas de problème avec la saisie de la colonne

    // vérifie que la colonne saisie soit compatible avec la taille de la grille
    if (grille->colonne >= grille->taille || grille->colonne < 0) {
        validite = 'I'; // 'I' comme invalide
    }

    // vérifie que la colonne saisie par l'utilisateur ne soit pas pleine pour la fonction add_token
    if (grille->tab[0][grille->colonne] == 'X' || grille->tab[0][grille->colonne] == 'O') {
        validite = 'R'; // 'R' comme remplie
    }

    // vérifie que la colonne saisie ne soit pas vide pour la fonction remove_token
    if (grille->tab[grille->taille - 1][grille->colonne] == ' ') {
        validite = 'V'; // 'V' comme colonne vide
    }

    return validite;
}

// DANS TOUTES LES FONCTIONS CHECK ON PART DU DERNIER JETON POSÉ

int check_horizontal(Grid *grille) {

    int gagnant;
    int k;
    int j = grille->colonne;    // colonne du dernier jeton posé
    int i = grille->ligne;      // ligne du dernier jeton posé (récupérée au moment du add_token)
    int compteur = 1;           // stocke le nombre de jetons alignés

    // pour vérifier à gauche du jeton
    k = grille->colonne - 1;

    while (grille->tab[i][k] == grille->tab[i][j] && k != -1) {
        compteur++;
        k--;
    }

    // pour vérifier à droite du jeton
    k = grille->colonne + 1;

    while(grille->tab[i][j] == grille->tab[i][k] && k != grille->taille){
        compteur++;
        k++;
    }

    gagnant = check_jeton(grille, compteur, grille->tab[i][j]);

    return gagnant;     // -1 si pas N jeton alignés, 0 pour 'X', 1 pour 'O'
}

int check_vertical(Grid *grille) {

    int gagnant;
    int k;
    int j = grille->colonne;    // colonne du dernier jeton posé
    int i = grille->ligne;      // ligne du dernier jeton posé (récupérée au moment du add_token)
    int compteur = 1;           // stocke le nombre de jetons alignés

    // pour vérifier en bas
    k = grille->ligne + 1;

    while (grille->tab[k][j] == grille->tab[i][j] && k != grille->taille) {
        compteur++;
        k++;
    }

    gagnant = check_jeton(grille, compteur, grille->tab[i][j]);

    return gagnant;     // -1 si pas N jeton alignés, 0 pour 'X', 1 pour 'O'
}

int check_diagonal_left(Grid *grille) {

    int gagnant;
    int j = grille->colonne;    // colonne du dernier jeton posé
    int i = grille->ligne;      // ligne du dernier jeton posé (récupérée au moment du add_token)
    int compteur = 1;           // stocke le nombre de jetons alignés
    int k, l;

    // pour vérifier en bas à droite
    k = grille->ligne + 1;
    l = grille->colonne + 1;

    while (grille->tab[k][l] == grille->tab[i][j] && k != grille->taille && l != grille->taille) {
        compteur++;
        k++;
        l++;
    }

    // pour vérifier en haut à gauche
    k = grille->ligne - 1;
    l = grille->colonne - 1;

    while (grille->tab[k][l] == grille->tab[i][j] && k != -1 && l != -1) {
        compteur++;
        k--;
        l--;
    }

    gagnant = check_jeton(grille, compteur, grille->tab[i][j]);

    return gagnant;     // -1 si pas N jeton alignés, 0 pour 'X', 1 pour 'O'
}

int check_diagonal_right(Grid * grille) {

    int gagnant;
    int j = grille->colonne;    // colonne du dernier jeton posé
    int i = grille->ligne;      // ligne du dernier jeton posé (récupérée au moment du add_token)
    int compteur = 1;           // stocke le nombre de jetons alignés
    int k, l;

    // pour vérifier en bas à gauche
    k = grille->ligne + 1;
    l = grille->colonne - 1;

    while (grille->tab[k][l] == grille->tab[i][j] && k != grille->taille && l != -1) {
        compteur++;
        k++;
        l--;
    }

    // pour vérifier en haut à droite
    k = grille->ligne - 1;
    l = grille->colonne + 1;

    while (grille->tab[k][l] == grille->tab[i][j] && k != -1 && j != grille->taille) {
        compteur++;
        k--;
        l++;
    }

    gagnant = check_jeton(grille, compteur, grille->tab[i][j]);

    return gagnant;     // -1 si pas N jeton alignés, 0 pour 'X', 1 pour 'O'
}

int check_jeton(Grid *grille, int compteur, char jeton){

    int gagnant = -1;       // - 1 si personne ne gagne lors de ce tour

    if(compteur >= grille->taille -2) {
        switch (jeton) {
            case 'X' :
                gagnant = 0;    // O si N jetons 'X' sont alignés
                break;
            case 'O' :
                gagnant = 1;    // 1 si N jetons 'O' sont alignés
                break;
        }
    }

    return gagnant;
}

int check_winner(Grid *grille) {

    int gagnant = -1;

    // 0 pour 'X'
    if (check_horizontal(grille) == 0   || check_vertical(grille) == 0 ||
        check_diagonal_left(grille) == 0 || check_diagonal_right(grille) == 0) {

        if(grille->mode_de_jeu == 1) {
            Color(0, 4);       // Met le fond en rouge
            printf("Vous 'X' avez gagne la partie !\n");
        } else {
            printf("le vainqueur est le ");
            Color(0, 4);        // Met le fond en rouge
            printf("joueur rouge 'X' !\n");
        }

        gagnant = 0;
    }

    // 1 pour 'O'
    if (check_horizontal(grille) == 1 || check_vertical(grille) == 1 ||
        check_diagonal_left(grille) == 1 || check_diagonal_right(grille) == 1) {

        if (grille->mode_de_jeu == 1) {
            Color(0, 14);       // Met le fond en jaune
            printf("L'IA 'O' a gagnee la partie !\n");
        } else {
            printf("le vainqueur est le ");
            Color(0, 14);       // Met le fond en jaune
            printf("joueur jaune 'O' !\n");
        }

        gagnant = 1;
    }

    // 2 pour nul
    if (check_grid(grille) == 1) {
        Color(5, 0);
        printf("La grille est pleine, il y a match nul !\n");
        gagnant = 2;
    }

    return gagnant;
}
