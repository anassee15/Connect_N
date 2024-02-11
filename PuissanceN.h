//
// Created by anasse on 02/06/2021.
//

#ifndef PUISSANCEN_IFB_PUISSANCEN_H
#define PUISSANCEN_IFB_PUISSANCEN_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#define TAILLE 100

typedef struct {
    /**
     * tableau contenant la grille
     */
    char tab[TAILLE][TAILLE];
    /**
     * ligne de la grille (sert à stocker la ligne du dernier jeton posé)
     */
    int ligne;
    /**
     * colonne de la grille (sert à stocker la colonne du dernier jeton posé)
     */
    int colonne;
    /**
     * taille de la grille
     */
    int taille;
    /**
     * mode de jeu de la partie en cours (1 = IA, 2 = 1v1)
     * 3 = charger_une_partie (pour save)
     */
    int mode_de_jeu;
} Grid;

// grid.c //

/**
 * permet d'initialiser une grille (tableau à 2 dimensions) à ' '
 * @param taille taille de la grille à initialiser
 * @param grille grille à initialiser
 */
void initialize_grid(Grid *grille);

/**
 * permet d'afficher la grille
 * @param taille taille de la grille
 * @param grille grille à afficher
 */
void show_grid(Grid *grille);

/**
 * vérifie si la grille est pleine ou vide
 * @param grille grille de jeu
 * @return 0 si la grille est vide, 1 si la grille est rempli, -1 sinon
 */
int check_grid(Grid *grille);

/**
 * permet d'ajouter un jeton
 * @param grille grille du jeu
 * @param symbole 'X' ou 'O' représente le jeton du joueur
 * @param nb_joueur permet de savoir si c'est L'IA ou un joueur qui utilise la fonction
 * @return 1 si l'ajout de jeton est possible, 0 si l'ajout est impossible
 */
int add_token(Grid *grille, char symbole, int nb_joueur);

/**
 * permet de retirer un jeton
 * @param grille grille du jeu
 * @param nb_joueur permet de savoir si c'est L'IA ou un joueur qui utilise la fonction
 * @return 1 si la suppression de jeton est possible, 0 si elle est impossible
 */
int remove_token(Grid *grille, int nb_joueur);


// check.c //

/**
 * controle si la colonne saisie est valide
 * @param grille grille du jeu
 * @return 'Y' s'il n'y a pas de problème, 'I' si la colonne saisie est incorrect,
 * 'R' si la colonne est remplie et 'V' si la colonne est vide
 */
char check_colonne(Grid *grille);

/**
  * vérifie si N jetons sont alignés horizontalement
  * @param grille grille de jeu
  * @return 0 si le joueur rouge 'X' gagne, 1 si le joueur jaune 'O' gagne, -1 si personne n'a gagné pour l'instant
  */
int check_horizontal(Grid *grille);

/**
 * vérifie si N jetons sont alignés verticalement
 * @param grille grille de jeu
 * @return 0 si le joueur rouge 'X' gagne, 1 si le joueur jaune 'O' gagne, -1 si personne n'a gagné pour l'instant
 */
int check_vertical(Grid *grille);

/**
 * vérifie que N jetons sont alignés en diagonale en partant à gauche
 * @param grille grille de jeu
 * @return 0 si le joueur rouge 'X' gagne, 1 si le joueur jaune 'O' gagne, -1 si personne n'a gagné pour l'instant
 */
int check_diagonal_left(Grid *grille);

/**
 * vérifie que N jetons sont alignés en diagonale en partant à droite
 * @param grille grille de jeu
 * @return 0 si le joueur rouge 'X' gagne, 1 si le joueur jaune 'O' gagne, -1 si personne n'a gagné pour l'instant
 */
int check_diagonal_right(Grid *grille);

/**
 * vérifie s'il y a bien N jetons alignés et détermine quel joueur à N jetons alignés
 * @param grille grille de jeu
 * @param compteur le nombre de jetons alignés
 * @param jeton 'O' ou 'X'
 * @return -1 si pas N jetons alignés, 'O' si N jetons 'X' alignés, 1 si N jetons 'O' alignés
 */
int check_jeton(Grid *grille, int compteur, char jeton);

/**
 * vérifie si le jeu est gagné par un des joueurs
 * @param grille grille du jeu
 * @return 0 si le joueur rouge 'X' gagne, 1 si le joueur jaune 'O' gagne,
 * 2 si la grille est pleine donc match nul et -1 si personne n'a gagné pour l'instant
 */
int check_winner(Grid *grille);


// game.c //

/**
 * menu affiché au lancement du jeu
 * @param rep action choisi par le joueur
 */
void menu_demarrage(int *rep);

/**
 * menu affichant les différents mode de jeu
 * @param rep action choisi par le joueur
 */
void menu_modejeu(int *rep);

/**
 * permet de choisir qui commence au début de la partie
 * @return 'X' si le joueur rouge est tiré au sort, sinon 'O' pour le joueur jaune / IA
 */
char tirage();

/**
 * permet de changer de joueur entre chaque tour
 * @param symbole stocke le jeton du joueur qui vient de jouer
 * @return 'X' si le jeton est 'O', 'O' si le jeton est 'X'
 */
char changement_tour(char symbole);

/**
 * décide de l'action que va réaliser le joueur / L'IA
 * @param grille
 * @param nb_joueur 1 pour version 'IA', 2 pour 'joueur'
 * @return 1 pour add_token, 2 pour remove_token, 3 pour save
 */
int choix_action(Grid *grille, int nb_joueur);

/**
 * déroulement classique d'une manche du joueur
 * @param grille grille de jeu
 * @param symbole 'O' ou 'X'
 * @param colonne_remove la colonne où a eu lieu le remove_token le tour d'avant
 * @return 1 pour un add_token, 2 pour un remove_token, 3 pour save
 */
int deroulement_tour_joueur(Grid *grille, char symbole, int colonne_remove);

/**
 * déroulement de la partie joueur contre joueur
 * @param grille grille de jeu
 * @param jeton stocke le jeton du joueur qui commence (uniquement pour charger une partie)
 * @return 3 si le joueur souhaite quitter et sauvegarder
 */
int deroulement_1v1(Grid *grille, char symbole);

/**
 * déroulement classique d'une manche faite par l'IA
 * @param grille
 * @param symbole 'X' ou 'O'
 * @param colonne_remove la colonne où a eu lieu le remove_token le tour d'avant
 * @return 1 pour add_token, 2 pour remove_token, 3 pour save
 */
int deroulement_tour_IA(Grid *grille, char symbole, int colonne_remove);

/**
 * deroulement de la partie contre l'IA
 * @param grille grille de jeu
 * @param jeton stocke le jeton du joueur qui commence (uniquement pour charger une partie)
 * @return 3 si le joueur souhaite quitter et sauvegarder
 */
int deroulement_vs_IA(Grid *grille, char jeton);

/**
 * lance une nouvelle partie
 * @param grille grille de jeu
 */
void nouvelle_partie(Grid *grille);

/**
 * charge la partie sauvegardé
 * @param grille grille de jeu
 */
void charger_partie(Grid *grille);


// IA.c //

/**
 * Intelligence Artificiel permet de retourner une valeur de colonne sans intervention de l'utilisateur
 * @param grille grille de jeu
 * @param mode 1 pour add_token, 2 pour remove_token
 * @param colonne_remove la colonne ou a eu lieu un remove_token le tour d'avant
 * @return la valeur de colonne choisi
 */
int IA(Grid *grille, int mode, int colonne_remove);

/**
 * renvoie la colonne où l'IA va poser son jeton (pour add_token)
 * @param grille grille de jeu
 * @param symbole 'O' ou 'X'
 * @return la colonne gagnant/blocante ou -1 s'il n'y en a pas
 */
int IA_add(Grid *grille, char symbole);


// files.c //

/**
 * permet de sauvegarder en cours de partie
 * @param grille  grille de jeu
 * @param symbole joueur dont c'est le tour
 */
void save(Grid *grille, char symbole);

/**
 * permet de charger une partie
 * @param grille grille de jeu
 * @return 0 si c'est au tour de 'X', 1 si c'est au tour de 'O', -1 s'il y a eu un problème
 */
int load(Grid *grille);

/**
 * permet de récuperer les valeurs stockées dans un fichier, et de les attribuées à des variables
 * @param grille grille de jeu
 * @param sauvegarde fichier de sauvegarde
 * @return 0 si c'est au tour de 'X', 1 si c'est au tour de 'O', -1 s'il y a eu un problème
 */
int incrementation_load(Grid *grille, FILE *sauvegarde);

/**
 * permet de mettre du texte en couleur (ATTENTION NE FONCTIONNE QUE SOUS WINDOWS)
 * @param couleurDuTexte
 * @param couleurDeFond
 */
void Color(int couleurDuTexte,int couleurDeFond);

#endif //PUISSANCEN_IFB_PUISSANCEN_H
