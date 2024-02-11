//
// Created by anasse on 02/06/2021.
//
#include "PuissanceN.h"

void save(Grid *grille, char symbole) {

    // Principe de save : On enregistre tous les éléments qui nous intéresse dans un fichier .txt
    // tout ces éléments sont enregistrer en ligne dans un ordre précis afin de faciliter le travail de la fonction load

    char nom_utilisateur[256] = {0};        // stocke le nom de fichier souhaité par l'utilisateur
    char nom_fichier[256] = "../";          // stocke la syntaxe nécessaire + nom d'utilisateur pour le fopen

    printf("Quel nom souhaitez vous donner a votre sauvegarde : \n");
    gets(nom_utilisateur);

    strcat(nom_utilisateur, ".txt");    // on ajoute .txt, afin de créer un fichier texte
    strcat(nom_fichier, nom_utilisateur);       // on concatene '/..' et 'nom.txt' afin d'avoir la bonne syntaxe

    // mode 'w' afin de pouvoir créer un fichier s'il n'existe pas, et d'écrire dedans,
    // (utile également si le fichier existe deja permettant de supprimer le contenu).
    FILE* sauvegarde = fopen(nom_fichier, "w");

    // vérifie qu'il n'y a pas de problème avec le fichier
    if(sauvegarde == NULL) {

        // si il y a un problème
        printf("il y a eu un probleme lors de l'ouverture du programme! \n");

    } else {

        int i, j;

        // sauvegarde le mode de jeu : 1 pour VS IA, sinon 2 pour joueur contre joueur
        fprintf(sauvegarde,"%d ", grille->mode_de_jeu);
        // sauvegarde la taille de la grille de jeu
        fprintf(sauvegarde,"%d ", grille->taille);
        // sauvegarde le joueur dont c'est le tour
        fprintf(sauvegarde,"%c", symbole);

        // sauvegarde l'état de la grille de jeu au moment où l'utilisateur quitte
        for(i = 0; i < grille->taille; i++){
            for(j = 0; j < grille->taille; j++) {
                fprintf(sauvegarde, "%c", grille->tab[i][j]);
            }
        }
        // ferme le fichier car nous on en a plus besoin
        fclose(sauvegarde);
    }
}

int load(Grid *grille) {

    int valeur_retour;                          // valeur retourné
    char nom_utilisateur[256] = {0};            // stocke le nom de fichier souhaité par l'utilisateur
    char nom_fichier[256] = "../";              // stocke la syntaxe nécessaire + nom d'utilisateur pour le fopen
    int i;

    printf("Quel etait le nom de votre sauvegarde : \n");
    gets(nom_utilisateur);

    strcat(nom_utilisateur, ".txt");            // on ajoute .txt, afin de créer un fichier texte
    strcat(nom_fichier, nom_utilisateur);              // on concatene '/..' et 'nom.txt' afin d'avoir la bonne syntaxe

    // en lecture simple
    FILE* sauvegarde = fopen(nom_fichier, "r");

    // vérifie qu'il n'y a pas de problème avec le fichier
    if(sauvegarde == NULL) {

        // boucle en cas d'erreur, permet à l'utilisateur de recommencer sa recherche
        do {
            Color(4, 0);        // Met le texte en rouge
            printf("Votre sauvegarde n'existe pas ! \n");
            Color(15, 0);

            // initialise nom_utilisateur
            for(i = 0; i < 256; i++) {
                nom_utilisateur[i] = 0;
                nom_fichier[i] = 0;
            }

            strcat(nom_fichier, "../");

            // 'sauvegarde' est un fichier défini à l'avance, permettant d'avoir une sortie de secours pour l'utilisateur
            printf("Quel etait le nom de votre sauvegarde (mettre \"sauvegarde\" si vous ne retrouvez pas le nom de votre fichier): \n");
            gets(nom_utilisateur);

            strcat(nom_utilisateur, ".txt");
            strcat(nom_fichier, nom_utilisateur);

            sauvegarde = fopen(nom_fichier, "r");

        } while (sauvegarde == NULL);

    }

    valeur_retour = incrementation_load(grille, sauvegarde);

    // ferme le fichier
    fclose(sauvegarde);

    return valeur_retour;
}

int incrementation_load(Grid *grille, FILE *sauvegarde) {

    int i, j;
    int caractere;
    char symbole;
    int valeur_retour;

    // récupere le mode de jeu et la taille de la dernière partie sauvegardé
    fscanf(sauvegarde, "%d %d", &grille->mode_de_jeu, &grille->taille);
    fflush(stdin);

    // récupere le symbole du joueur dont c'est le tour
    fscanf(sauvegarde, " %c", &symbole);
    fflush(stdin);

    // initialise la grille
    initialize_grid(grille);

    // permet de recuperer la grille de jeu
    for(i = 0; i < grille->taille; i++) {
        for(j = 0; j < grille->taille; j++) {
            caractere = fgetc(sauvegarde);
            grille->tab[i][j] = caractere;
        }
    }

    if (symbole == 'X') {
        valeur_retour = 0;
    } else if (symbole == 'O') {
        valeur_retour = 1;
    } else {
        printf("Il y a eu un probleme");
        valeur_retour = -1;
    }

    return valeur_retour;
}

void Color(int couleurDuTexte,int couleurDeFond) { // fonction d'affichage de couleurs
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
