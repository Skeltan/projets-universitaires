/**
 * Optimisations: 
 *      - Ajout de la technique du singleton nu avant le backtracking.
 *      - Implémentation de la structure tCase2 + backtracking prend désormais en compte les candidats.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define N 4
#define TAILLE (N * N)

typedef struct {
    int valeur;
    bool candidats[TAILLE + 1];
    int nbCandidats;
} tCase2;

typedef tCase2 tGrille[TAILLE][TAILLE];

void initialiser_candidats(tGrille g);
void retirerCandidat(tCase2 *laCase, int val, int i, int j);
int nbCandidat(tCase2 laCase);
void singletonNue(tGrille g, int nbCasesVides);
bool backtracking(tGrille grille, int numeroCase);
bool possible(tGrille grille, int numLigne, int numColonne, int valeur);
int chargerGrille(tGrille g);
void afficherGrille(tGrille g);

int main()
{
    tGrille g;
    int nbCasesVides;
    nbCasesVides = chargerGrille(g);
    initialiser_candidats(g);
    printf("Grille Initiale:\n");
    afficherGrille(g);
    clock_t begin = clock();
    singletonNue(g,nbCasesVides);
    backtracking(g,0);
    clock_t end = clock();
    double tmpsCPU = (end - begin)*1.0 / CLOCKS_PER_SEC;
    printf("\nGrille Finale:\n");
    afficherGrille(g);
    printf( "Temps de resolution de la grille: %.6f secondes\n",tmpsCPU);
    
}

void initialiser_candidats(tGrille g)
{
    int i;
    int j;
    int k;
    int val;
    for (i = 0; i < TAILLE; i++)
    {
        for (j = 0; j < TAILLE; j++)
        {
            if (g[i][j].valeur == 0)
            {
                for (k = 1; k < TAILLE+1; k++)
                {
                    g[i][j].candidats[k] = true;
                }
                g[i][j].nbCandidats = TAILLE;
            }
            else
            {
                for (k = 1; k < TAILLE+1; k++)
                {
                    g[i][j].candidats[k] = false;
                }
                g[i][j].nbCandidats = 0;
            }
        }
    }
    
    for (i = 0; i < TAILLE; i++)
    {
        for (j = 0; j < TAILLE; j++)
        {
            if (g[i][j].valeur == 0)
            {
                for (int ligne = 0; ligne < TAILLE; ligne++)
                {
                    if (g[ligne][j].valeur != 0)
                    {
                        val = g[ligne][j].valeur;
                        retirerCandidat(&g[i][j], val, i, j);
                    }
                }
                for (int colonne = 0; colonne < TAILLE; colonne++)
                {
                    if (g[i][colonne].valeur != 0)
                    {   
                        val = g[i][colonne].valeur;
                        retirerCandidat(&g[i][j], val, i, j);
                    }
                }
                int carrel;
                int carrec;
                carrel = i - (i % N);
                carrec = j - (j % N);
                for (int cptl = 0; cptl < N; cptl++)
                {
                    for (int cptc = 0; cptc < N; cptc++)
                    {
                        if (g[carrel + cptl][carrec + cptc].valeur != 0)
                        {
                            val = g[carrel + cptl][carrec + cptc].valeur;
                            retirerCandidat(&g[i][j], val, i, j);
                        }
                    }
                }
            }
        }
    }
}

void retirerCandidat(tCase2 *laCase, int val, int i, int j) {
    if (laCase->candidats[val] == true) {
        laCase->candidats[val] = false;
        laCase->nbCandidats = laCase->nbCandidats - 1;
    }
}

int nbCandidat(tCase2 laCase)
{
    int cpt = 0;
    for (int i=1; i<TAILLE+1; i++) {
        if (laCase.candidats[i] == true) {
            cpt++;
        }
    }
    return cpt;
}

void singletonNue(tGrille g, int nbCasesVides)
{
    bool progression;
    progression = true;
    while (nbCasesVides != 0 && progression)
    {
        progression = false;
        for (int i = 0; i < TAILLE; i++)
        {
            for (int j = 0; j < TAILLE; j++)
            {
                if (nbCandidat(g[i][j]) == 1)
                {
                    int val = 1;
                    while (g[i][j].candidats[val] == false)
                    {
                        val = val + 1;
                    }
                    g[i][j].valeur = val;
                    g[i][j].nbCandidats = 0;
                    nbCasesVides = nbCasesVides - 1;
                    for (int ligne = 0; ligne < TAILLE; ligne++)
                    {
                        retirerCandidat(&g[ligne][j], val, i, j);
                    }
                    for (int colonne = 0; colonne < TAILLE; colonne++)
                    {
                        retirerCandidat(&g[i][colonne], val, i, j);
                    }
                    int carrel;
                    int carrec;
                    carrel = i - (i % N);
                    carrec = j - (j % N);
                    for (int cptc = 0; cptc < N; cptc++)
                    {
                        for (int cptl = 0; cptl < N; cptl++)
                        { 
                            retirerCandidat(&g[carrel + cptl][carrec + cptc], val, i, j);
                        }
                    }
                    progression = true;
                }
            }
        }
    }
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
        if(grille[ligne][colonne].valeur != 0)
        {
            resultat = backtracking(grille, numeroCase+1);
        }
        else
        {
            for(int valeur = 1 ; valeur <= TAILLE ; valeur++)
            {
                if(grille[ligne][colonne].candidats[valeur] == true){
                    if(possible(grille,ligne,colonne,valeur))
                    {
                        grille[ligne][colonne].valeur = valeur;
                        
                        if(backtracking(grille,numeroCase+1))
                        {
                            resultat = true;
                        }
                        else
                        {
                            grille[ligne][colonne].valeur = 0;
                        }
                    }
                }
            }
        }
    }
    return resultat;
}

bool possible(tGrille g, int numLigne, int numColonne, int valeur)
{
    int cpt;
    int cptl;
    int cptc;
    int debutcareel;
    int debutcareec;
    bool valide;
    valide = true;
    cpt = 0;
    while (cpt < TAILLE && valide == true) // sert à parcourir la colonne de notre valeur
    {
        if(g[cpt][numColonne].valeur == valeur)
        {
            valide = false;
        }
        cpt = cpt +1;
    }
    cpt = 0;
    while (cpt < TAILLE && valide == true) //sert à parcourir la ligne de notre valeur
    {
        if(g[numLigne][cpt].valeur == valeur)
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
            if(g[debutcareel+cptl][debutcareec+cptc].valeur == valeur)
                {
                    valide = false;
                }
        }  
        cptc = cptc + 1;
    }
    if(valide)
    {
        // tout est validé
        return true;
    }
    else
    {
        // une ou plusieurs conditions ne sont pas validées
        return false;
    }
}

int chargerGrille(tGrille g)
{
    int nbCasesVides;
    int val;
    char nomFichier[30];
    int i, j;
    nbCasesVides = 0;
    FILE *f;
    do
    {
        printf("Nom du fichier ? ");
        scanf("%s", nomFichier);
        f = fopen(nomFichier, "rb");
        if (f == NULL)
        {
            printf("\nERREUR sur le fichier %s. Veuillez recommencer.\n", nomFichier);
        }
        else
        {
            for (i = 0; i < TAILLE; i++)
            {
                for (j = 0; j < TAILLE; j++)
                {
                    fread(&val, sizeof(int), 1, f);
                    g[i][j].valeur = val;
                    if (g[i][j].valeur == 0)
                    {
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
            if (g[i][j].valeur == 0){
                printf(" . "); 
            }
            else{
                printf("%2d ",g[i][j].valeur);
            }
            if (j%N == 3){printf("| ");}
        }
        if (i%N == 3){printf("\n   +-------------+-------------+-------------+-------------+");}
    }
    printf("\n");
}