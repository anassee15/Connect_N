//
// Created by anasse on 02/06/2021.
//
#include "PuissanceN.h"

void initialize_grid(Grid *grille) {

    int i, j;
    // initialisation de toute la grille à ' '
    for (i = 0; i < grille->taille; i++) {
        for (j = 0; j < grille->taille; j++) {
            grille->tab[i][j] = ' ';
        }
    }
}

void show_grid(Grid *grille) {

    int compteur = 0;
    int ligne;      // ligne de la grille
    int colonne;    // colonne de la grille

    printf("+");

    for (colonne = 0; colonne < grille->taille; colonne++) {
        printf("---+");
    }

    printf("\n");

    // permet l'affichage de la grille et ajoute un contour au tableau pour plus d'esthétique
    do {

        for (ligne = 0; ligne < grille->taille; ligne++) {
            printf("| ");

            // POUR LES COULEURS
            switch (grille->tab[compteur][ligne]) {
                case 'X' :
                    Color(12,0);    // Met le jeton 'X' en rouge
                    printf("%c ", grille->tab[compteur][ligne]);
                    break;

                case 'O' :
                    Color(14,0);    // Met le jeton 'O' en jaune
                    printf("%c ", grille->tab[compteur][ligne]);
                    break;
                default :
                    printf("%c ", grille->tab[compteur][ligne]);
                    break;
            }

            Color(15, 0);   // remet le texte en blanc
        }

        printf("|\n");
        printf("+");

        for (ligne = 0; ligne < grille->taille; ligne++) {
            printf("---+");
        }

        printf("\n");
        compteur += 1;

    } while (compteur < grille->taille);

    printf("\n");
}

int check_grid(Grid *grille) {

    int i, j;
    int complet = 0;
    int remplissage = -1;

    for(i = 0; i < grille->taille; i++) {
        for(j = 0; j < grille->taille; j++) {
            if (grille->tab[i][j] == 'X' || grille->tab[i][j] == 'O') {
                complet++;
            }
        }
    }

    if (complet == 0) {
        remplissage = 0;      // tableau vide
    } else if (complet == (grille->taille * grille->taille) ){
        remplissage = 1;      // tableau plein
    }

    return remplissage;
}

int add_token(Grid *grille, char symbole, int nb_joueur) {

    int i;
    int possibilite = 0;        // 0 si l'ajout du jeton est impossible
    char controle;              // variable contenant le resultat du controle colonne
    grille->colonne -= 1;       // afin d'adapter le numéro de colonne donné par l'utilisateur au tableau de caractère représentant la grille

    i = grille->taille - 1;     // on se place à la première ligne de la grille de jeu

    // on cherche dans quel ligne placer le jeton, permet de placer les jetons les uns sur les autres
    while (grille->tab[i][grille->colonne] != ' ' && i >= 0) {
        i--;
    }

    // vérifie si la colonne saisie est valide
    controle = check_colonne(grille);

    // Cette condition est présente afin de pouvoir placer un message d'erreur en fonction du problème
    switch (controle) {

        case 'R' :
            // condition pour ne pas afficher le message si c'est au tour de l'IA
            if (nb_joueur == 2) {
                printf("La colonne choisie est pleine !\n");
            }
            break;

        case 'I' :
            if (nb_joueur == 2) {
                printf("La colonne n'existe pas !\n");
            }
            break;

        default :
            grille->tab[i][grille->colonne] = symbole;
            grille->ligne = i;      // stocke la ligne du dernier jeton posé
            possibilite = 1;
            break;
    }

    return possibilite;     // 1 si l'ajout est possible, 0 sinon
}

int remove_token(Grid *grille, int nb_joueur) {

    int i = 0;
    int possibilite = 0;        // 0 si l'ajout du jeton est impossible
    char controle;              // variable contenant le résultat du controle colonne
    grille->colonne -= 1;       // afin d'adapter le numéro de colonne donné par l'utilisateur au tableau de caractère représentant la grille

    // on cherche dans quel ligne supprimer le jeton, permet de supprimer uniquement le jeton le plus haut dans la colonne
    while (grille->tab[i][grille->colonne] == ' ' && i < grille->taille) {
        i++;
    }

    // vérifie si la colonne saisie est valide
    controle = check_colonne(grille);

    // Cette condition est présente afin de pouvoir placer un message d'erreur en fonction du problème
    switch (controle) {

        case 'V' :
            // condition pour ne pas afficher le message si c'est au tour de l'IA
            if(nb_joueur == 2) {
                printf("La colonne choisie est vide !\n");
            }
            break;

        case 'I' :
            if (nb_joueur == 2) {
                printf("La colonne n'existe pas !\n");
            }
            break;

        default :
            grille->tab[i][grille->colonne] = ' ';
            possibilite = 1;
            break;

    }

    return possibilite;
}
