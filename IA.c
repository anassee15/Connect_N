//
// Created by anasse on 02/06/2021.
//
#include "PuissanceN.h"

int IA(Grid *grille, int mode, int colonne_remove) {

    srand(time(NULL));

    int colonne_jouer;

    if (mode == 1) {
        // pour gagner en priorité
        colonne_jouer = IA_add(grille, 'O');

        // ensuite si on ne peut pas gagner on essaye de bloquer, la condition évite de faire planter le programme à cause de la colonne bloqué
        if(colonne_jouer == -1 || colonne_jouer == colonne_remove) {
            colonne_jouer = IA_add(grille, 'X');
        }

    } else {

        colonne_jouer = IA_add(grille, 'X');
        // si on a un remove_token, l'IA joue aléatoirement
        colonne_jouer = rand() % grille->taille + 1;
    }

    // si la colonne n'a pas changé de valeur (c'est à dire aucun coup gagnant ni bloquant) ou bien si la colonne gagnante
    // est bloquée à cause d'un remove_token alors le coup joué sera aléatoire

    if(colonne_jouer == -1 || colonne_jouer == colonne_remove) {
        colonne_jouer = rand() % grille->taille + 1;
    }

    return colonne_jouer + 1; // +1 afin de faire comme si la colonne était donnée par un utilisateur pour que cela marche dans les autres fonctions
}

int IA_add(Grid *grille, char symbole) {

    // Même principe que les fonctions check, on réutilise le même code, sauf que l'on ne part pas du dernier jeton posé mais
    // on parcourt chaque colonne de la grille depuis la case vide la - 'haute' de la colonne, le principe :
    // on remplace cette case vide temporairement par 'X' ou 'O'. Si lorsque la case est remplacée et que 'symbole' peut gagner
    // alors la fonction renvoie la valeur cette colonne

    int colonne_jouer = -1;     // initialisé à -1 pour référence
    int compteur;
    int i, j = 0, k, l;

    // dès que la valeur de colonne est changée on sort de la boucle, afin de ne pas vérifier les autres colonnes pour rien
    while (j < grille->taille && colonne_jouer == -1) {

        i = grille->taille - 1;     // on se place à la premiere ligne de la grille de jeu

        // on cherche la ligne vide la plus haute
        while(grille->tab[i][j] != ' ' && i >= 0) {
            i--;
        }

        // on remplace temporairement la case vide par 'O' ou 'X'
        grille->tab[i][j] = symbole;
        compteur = 1;

        // vérif verticale
        k = i + 1;

        while (grille->tab[k][j] == grille->tab[i][j] && k != grille->taille) {
            compteur++;
            k++;
        }

        // si c'est un coup gagnant stocker la colonne
        if(compteur >= grille->taille - 2) {
            colonne_jouer = j;
        }

        // si la valeur de la colonne n'a pas changé
        if (colonne_jouer == -1) {

            // vérif horizontale
            compteur = 1;

            // vérif à gauche
            k = j - 1;
            while (grille->tab[i][k] == grille->tab[i][j] && k != -1) {
                compteur++;
                k--;
            }

            // verif à droite
            k = j + 1;
            while(grille->tab[i][k] == grille->tab[i][j] && k != grille->taille){
                compteur++;
                k++;
            }

            if(compteur >= grille->taille - 2) {
                colonne_jouer = j;
            }

            if (colonne_jouer == -1) {

                // vérif diagonale gauche
                compteur = 1;

                // vérif en haut
                k = i + 1;
                l = j + 1;
                while (grille->tab[k][l] == grille->tab[i][j] && k != grille->taille && l != grille->taille) {
                    compteur++;
                    k++;
                    l++;
                }

                // vérif en bas
                k = i - 1;
                l = j - 1;
                while (grille->tab[k][l] == grille->tab[i][j] && k != -1 && l != -1) {
                    compteur++;
                    k--;
                    l--;
                }

                if (compteur >= grille->taille - 2) {
                    colonne_jouer = j;
                }

                if (colonne_jouer == -1) {

                    // vérif diagonale droite
                    compteur = 1;

                    // vérif en bas
                    k = i + 1;
                    l = j - 1;
                    while (grille->tab[k][l] == grille->tab[i][j] && k != grille->taille && l != grille->taille) {
                        compteur++;
                        k++;
                        l--;
                    }

                    // vérif en haut
                    k = i - 1;
                    l = j + 1;
                    while (grille->tab[k][l] == grille->tab[i][j] && k != -1 && l != -1) {
                        compteur++;
                        k--;
                        l++;
                    }

                    if (compteur >= grille->taille - 2) {
                        colonne_jouer = j;
                    }
                }
            }
        }
        grille->tab[i][j] = ' ';    // on remet la case à ' '

        j++;
    }

    return colonne_jouer;
}
