#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define N 4
#define TAILLE (N*N)

typedef int tGrille[TAILLE][TAILLE];

bool backtracking(tGrille grille, int numeroCase);
bool possible(tGrille g, int numLigne, int numColonne, int valeur);
int chargerGrille(tGrille g);
void afficherGrille(tGrille g);
bool backtracking(tGrille grille, int numeroCase);
bool possible(tGrille g, int numLigne, int numColonne, int valeur);

int main() {
    tGrille g;
    int nbCasesVides;
    nbCasesVides = chargerGrille(g);
    printf("Il y a %d cases vides\n", nbCasesVides);
    printf("Grille Initiale\n");
    afficherGrille(g);
    clock_t begin = clock();
    backtracking(g, 0);
    clock_t end = clock();
    printf("Grille Finale\n");
    afficherGrille(g);
    double tmpsCPU = (end - begin)*1.0 / CLOCKS_PER_SEC;
    printf( "Temps CPU = %.6f secondes\n",tmpsCPU);
}

bool backtracking(tGrille grille, int numeroCase)
{
    int ligne;
    int colonne;
    bool resultat;
    resultat = false;
    if (numeroCase == TAILLE * TAILLE)
    {
        resultat = true;
    }
    else
    {
        ligne = numeroCase / TAILLE;
        colonne = numeroCase % TAILLE;
        if(grille[ligne][colonne] != 0)
        {
            resultat = backtracking(grille, numeroCase+1);
        }
        else
        {
            for(int valeur = 1 ; valeur <= TAILLE ; valeur++)
            {
                if(possible(grille,ligne,colonne,valeur))
                {
                    grille[ligne][colonne] = valeur;
                    
                    if(backtracking(grille,numeroCase+1))
                    {
                        resultat = true;
                    }
                    else
                    {
                        grille[ligne][colonne] = 0;
                    }
                }
            }
        }
    }
    return resultat;
}

bool possible(tGrille g, int numLigne, int numColonne, int valeur)
/**
 * @brief  fonction qui vérifie que la valeur donnée peut être placée dans cette case
 * @param  g de type tGrille, Entrée/Sortie : les données de la grille de sudoku sous forme de tableau 2D
 * @param  numLigne de type int, Entrée : le numéro de ligne de la valeur évaluée
 * @param  numColonne de type int, Entrée : le numéro de colonne de la valeur évaluée
 * @param  valeur de type int, Entrée : la valeur entrée par le joueur
 * @return true si la valeur peut être placé, false si elle ne le peut pas
*/
{
    int cpt;
    int cptl;
    int cptc;
    int debutcareel;
    int debutcareec;
    bool resultat;
    bool valide;
    valide = true;
    cpt = 0;
    while (cpt < TAILLE && valide == true) // sert à parcourir la colonne de notre valeur
    {
        if(g[cpt][numColonne] == valeur)
        {
            valide = false;
        }
        cpt = cpt +1;
    }
    cpt = 0;
    while (cpt < TAILLE && valide == true) //sert à parcourir la ligne de notre valeur
    {
        if(g[numLigne][cpt] == valeur)
        {
            valide = false;
        }
        cpt = cpt +1;
    }
    cptl = 0; 
    cptc = 0;
    debutcareel = numLigne - numLigne%N; // repère de la coordonée de ligne de la première case du carré
    debutcareec = numColonne - numColonne%N; // repère de la coordonée de colonne de la première case du carré
    while((cptl < N || cptc < N) && valide == true)
    {
        for(cptl=0;cptl < N;cptl = cptl + 1)// sert à parcourir le carrée de notre valeur
        {
            if(g[debutcareel+cptl][debutcareec+cptc] == valeur)
                {
                    valide = false;
                }
        }  
        cptc = cptc + 1;
    }
    return valide;
}

int chargerGrille(tGrille g){
    int nbCasesVides;
    int val;
    char nomFichier[30];
    int i, j;
    nbCasesVides = 0;
    FILE * f;
    do {
        printf("Nom du fichier ? ");
        scanf("%s", nomFichier);
        f = fopen(nomFichier, "rb");
        if (f == NULL) {
            printf("\nERREUR sur le fichier %s. Veuillez recommencer.\n", nomFichier);
        } 
        else {
            for (i=0; i < TAILLE; i++){
                for (j=0; j < TAILLE; j++){
                    fread(&val, sizeof(int), 1, f);
                    g[i][j] = val;
                    if (g[i][j] == 0) {
                        nbCasesVides++;
                    }

                }
            }
            fclose(f);
        }
    } while (f == NULL);
    return nbCasesVides;
}

void afficherGrille(tGrille g){
    int i,j;
    printf("     1  2  3  4    5  6  7  8     9 10 11 12   13 14 15 16\n");
    printf("   +-------------+-------------+-------------+-------------+");
    for (i=0;i<TAILLE;i++){
        if (i<9) {
            printf("\n%2d | ",i+1);
        }
        else {
            printf("\n%3d| ",i+1);
        }
        for (j=0;j<TAILLE;j++){
            if (g[i][j] == 0){
                printf(" . "); 
            }
            else{
                printf("%2d ",g[i][j]);
            }
            if (j%N == 3){printf("| ");}
        }
        if (i%N == 3){printf("\n   +-------------+-------------+-------------+-------------+");}
    }
    printf("\n");
}