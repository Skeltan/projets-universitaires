/**
* @file code-final-sudoku_ALEXIS_LE_GUERN.c
* @brief Programme permettant de jouer au Sudoku sur des grilles préremplies
* @author LE GUERN Alexis
* @version 1.0
* @date 25/11/23 (version finale) - 12/11/23 (1ère version)
*
* Ce programme permet de charger une grille préremplie de Sudoku. Le joueur peut indiquer un numéro de ligne puis de colonne pour cibler une case puis indiquer une valeur comprise entre 1 et 9 à insérer dans celle-çi.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Constantes du tableau
/**
*
* @def N
*
* @brief Taille d'un bloc (carrés de 3x3)
*
*/
#define N 3

/**
*
*@def TAILLE
*
* @brief Taille du tableau (carré de 9x9)
*
*/
#define TAILLE N*N

/**
*
* @typedef tab2D
*
* @brief type tableau à 2 dimensions de taille TAILLE*TAILLE
*
* Le type typTab sert de stockage pour les valeurs de la grille de Sudoku.
*
*/
typedef int tab2D[TAILLE][TAILLE];

// Déclaration des fonctions et procédures
void chargerGrille(tab2D grille);
void afficherGrille(tab2D grille); 
void saisir(int *valeur);
int possible(tab2D grille, int numLigne, int numColonne, int valeur);
int verifGrille(tab2D grille);


/*****************************************************
             * PROGRAMME PRINCIPAL *
*****************************************************/

/**
 * @fn int main()
 * @brief Programme Principal.
 * @return EXIT_SUCCESS, fin normale du programme
*/
int main() {
    //Déclaration des variables
    tab2D grille;
    int numLigne = 0;
    int numColonne = 0;
    int valeur;
    //Traitement des données
    chargerGrille(grille);
    while (verifGrille(grille) == false) { // Tant que la grille n'est pas remplie
        printf("\n");
        afficherGrille(grille);
        printf("Indices de la case:\n");
        printf("Ligne: ");
        saisir(&numLigne);
        printf("Colonne: ");
        saisir(&numColonne);
        numLigne = numLigne -1; 
        numColonne = numColonne -1; // Les -1 permettent de s'adapter à l'indexage à 0 du tableau
        if (grille[numLigne][numColonne] != 0) {  // Vérification de si la case est vide
            printf("IMPOSSIBLE, la case n'est pas libre.\n");
        }
        else {
            printf("Valeur à insérer: ");
            saisir(&valeur);
            if (possible(grille, numLigne, numColonne, valeur) == true) { // Si la valeur respecte toutes les règles du sudoku à la case saisie
                grille[numLigne][numColonne] = valeur;                   // On ajoute la valeur
            }
        }
    }
    // Fin de partie
    printf("Grille pleine, fin de partie\n");
    return EXIT_SUCCESS;
}


/**
* @fn void chargerGrille(tab2D grille)
* @brief Cette procédure permet de charger en mémoire une grille de sudoku existante à partir d’un fichier dont le nom est lu au clavier.
* @param grille de type tab2D, Entrée/Sortie: la grille a charger
*/
void chargerGrille(tab2D grille){
    char nomFichier[30];
    FILE * f;
    do {
        printf("Nom du fichier ? ");
        scanf("%s", nomFichier);
        f = fopen(nomFichier, "rb");
        if (f == NULL) {
            printf("\nERREUR sur le fichier %s. Veuillez recommencer.\n", nomFichier);
        } else {
            fread(grille, sizeof(int), TAILLE * TAILLE, f);
            fclose(f);
        }
    } while (f == NULL);
}


/**
* @fn void afficherGrille(tab2D grille)
* @brief Cette procédure réalise l’affichage à l’écran de la grille et de son contenu
* @param grille de type tab2D, Entrée/Sortie: la grille a afficher
*/
void afficherGrille(tab2D grille){
    int i,j;
    printf("   1 2 3   4 5 6   7 8 9 \n"); // Indices des cases
    printf(" +-------+-------+-------+"); // Délimitation des carrés
    for (i=0;i<TAILLE;i++){
        printf("\n%d| ",i+1);
        for (j=0;j<TAILLE;j++){
            if (grille[i][j]==0){ // Si la valeur vaut 0 (case vide) on affiche un point
                printf(". "); 
            }
            else{                  //Sinon on affiche la valeur
                printf("%d ",grille[i][j]);
            }
            if (j%3 == 2){printf("| ");}
        }
        if (i%3 == 2){printf("\n +-------+-------+-------+");}
    }
    printf("\n");
}


/**
* @fn void saisir(int *valeur)
* @brief Cette procédure est chargée de lire au clavier une valeur. La saisie se répète tant que la valeur n’est pas valide. La valeur lue doit être un entier, et cet entier doit être compris entre 1 et n2.
* Cette procédure sert aussi bien à saisir une numéro de ligne ou un numéro de colonne qu’à saisir une valeur à insérer dans la grille.
* @param valeur de type entier, Entrée/Sortie: la valeur à lire
*/
void saisir(int *valeur) {
    char ch[2];
    int varTemp;
    int conditionArret;
    conditionArret = 0;
    while (conditionArret == 0) {
        scanf("%s", ch);
        if (sscanf(ch, "%d", &varTemp) !=0){  // On cherche un entier dans la chaîne de caractère
            if (varTemp < 1 || varTemp > N*N) {
                // si la valeur n'est pas comprise entre 1 et 9 (n²)
                printf("Erreur: La valeur n'est pas comprise entre 1 et 9 inclus, veuillez réessayer.\n");
                conditionArret = 0;
            }
            else {
                // la conversion a réussi, x contient la valeur entière lue au clavier
                *valeur = varTemp;
                conditionArret = 1;
            }
        }
        else 
        {
            //la conversion en entier a échoué
            printf("Erreur: La valeur saisie n'est pas un entier, veuillez réessayer.\n");
            conditionArret = 0;
        }
    }
}


/**
* \fn int possible(tab2D grille, int numLigne, int numColonne, int valeur)
* @brief Cette fonction vérifie si une valeur peut être ajoutée dans une case particulière de la grille, c’est-à-dire si cela respecte les règles du sudoku :
        - la valeur n’est pas déjà présente sur la même ligne que la case
        - la valeur n’est pas déjà présente sur la même colonne que la case
        - la valeur n’est pas déjà présente dans le même bloc que la case
* @param grille de type tab2D, Entrée/Sortie: la grille à vérifier
* @param numLigne de type entier, Entrée: la ligne où la valeur souhaite être placée
* @param numColonne de type entier, Entrée: la colonne où la valeur souhaite être placée
* @param valeur de type entier, Entrée: la valeur qui souhaite être insérée
* @return valide = true si la valeur peut être placée dans la case spécifiée, valide = false si non
*/
int possible(tab2D grille, int numLigne, int numColonne, int valeur) {
    //Déclaration des variables
    int l, c; // ligne et colonne
    int ligBloc, colBloc; //départ pour traverser un bloc
    bool ligValid, colValid, blocValid, valide;
    ligValid = true;
    colValid = true;
    blocValid = true;
    valide = false;
    l=0; // ligne
    c=0; // colonne
    ligBloc = numLigne; //départ pour parcourir un bloc de 3x3 (verif bloc)
    colBloc = numColonne; //départ pour parcourir un bloc de 3x3 (verif bloc)

    // Check de la ligne
    while ((c < TAILLE) && (ligValid == true)) {
        if (grille[numLigne][c] == valeur) {
            ligValid = false;
            printf("Erreur: La valeur saisie est déjà présente dans la ligne\n");
        }
        else {
            c = c + 1;
        }
    }

    //Check de la colonne
    while ((l < TAILLE) && (colValid == true)) {
        if (grille[l][numColonne] == valeur) {
            colValid = false;
            printf("Erreur: La valeur saisie est déjà présente dans la colonne\n");
        }
        else {
            l = l + 1;
        }
    }

    //Check du bloc
    while (ligBloc%N != 0) {
        ligBloc = ligBloc - 1;
    }
    while (colBloc%N != 0) {
        colBloc = colBloc - 1;
    }
    for (int i=ligBloc; i%N<2; i = i + 1) {
        for (int j=colBloc; j%N<2; j = j + 1) {
            if (valeur == grille[i][j]){
                blocValid = false;
                printf("Erreur: La valeur saisie est déjà présente dans le bloc\n");
            }
        }
    }
    
    //Si les 3 conditions sont remplies, le booléen valide devient vrai
    if ((ligValid == true) && (colValid == true) && (blocValid == true)) {
        valide = true;
    }
    return valide;
}


/**
* @fn int verifGrille(tab2D grille)
* @brief Cette fonction parcours le tableau pour vérifier qu'il n'y a plus de cas vide (de 0) dans le tableau
* @param grille de type tab2D, Entrée/Sortie: la grille à vérifier
* @return grillePleine = false si la grille n'est pas pleine; grillePeine = true si elle est pleine
*/
int verifGrille(tab2D grille) {
    int i, j;
    bool grillePleine;
    for (i = 0 ; i<TAILLE ; i = i+1) {
        for (j = 0 ; j<TAILLE ; j = j+1) {
            if (grille[i][j] == 0) { // dès qu'on trouve un 0, on retourne false et la partie continue
                grillePleine = false;
                return grillePleine;
            }
            else { // Si la grille est parcourue entièrement et qu'aucun 0 n'a été trouvé: c'est fin de la partie
                grillePleine = true;
            }
        }
    }
    return grillePleine;
}