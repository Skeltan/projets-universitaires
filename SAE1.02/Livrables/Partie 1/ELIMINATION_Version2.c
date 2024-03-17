#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 3
#define TAILLE (N * N)

typedef struct {
    int valeur;
    bool candidats[TAILLE + 1];
    int nbCandidats;
} tCase2;

typedef tCase2 tGrille[TAILLE][TAILLE];

float initialiser_candidats(tGrille g);
void ajouterCandidat(tCase2 *laCase, int val);
bool retirerCandidat(tCase2 *laCase, int val, int i, int j);
bool estCandidat(tCase2 laCase, int val);
int nbCandidat(tCase2 laCase);
int chargerGrille(tGrille g);
void afficherGrille(tGrille g);
void afficherStats(tGrille g, int nbCasesVidesInit, int nbCasesVides, float candidatsElimTotal);

int main()
{
    tGrille g;
    bool progression;
    int nbCasesVides;
    int nbCasesVidesInit;
    bool verif;
    float candidatsElimTotal;
    nbCasesVides = chargerGrille(g);
    nbCasesVidesInit = nbCasesVides;
    candidatsElimTotal = initialiser_candidats(g);
    progression = true;
    while (nbCasesVides != 0 && progression)
    {
        printf("\nIl y a %d cases vides\n", nbCasesVides);
        afficherGrille(g);
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
                    candidatsElimTotal++;
                    nbCasesVides = nbCasesVides - 1;
                    for (int ligne = 0; ligne < TAILLE; ligne++)
                    {
                        verif = retirerCandidat(&g[ligne][j], val, i, j);
                        if (verif == true){
                            candidatsElimTotal++;
                        }
                    }
                    for (int colonne = 0; colonne < TAILLE; colonne++)
                    {
                        verif = retirerCandidat(&g[i][colonne], val, i, j);
                        if (verif == true){
                            candidatsElimTotal++;
                        }
                    }
                    int carrel;
                    int carrec;
                    carrel = i - (i % 3);
                    carrec = j - (j % 3);
                    for (int cptc = 0; cptc < N; cptc++)
                    {
                        for (int cptl = 0; cptl < N; cptl++)
                        { 
                            verif = retirerCandidat(&g[carrel + cptl][carrec + cptc], val, i, j);
                            if (verif == true){
                                candidatsElimTotal++;
                            } 
                        }
                    }
                    progression = true;
                }
            }
        }
    }
    printf("\nIl y a %d cases vides\n", nbCasesVides);
    afficherGrille(g);
    afficherStats(g,nbCasesVidesInit,nbCasesVides,candidatsElimTotal);
}

float initialiser_candidats(tGrille g)
{
    int i;
    int j;
    int k;
    int val;
    bool verif;
    float candidatsElimTotal;

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
                        verif = retirerCandidat(&g[i][j], val, i, j);
                        if (verif == true){
                                candidatsElimTotal++;
                            } 
                    }
                }
                for (int colonne = 0; colonne < TAILLE; colonne++)
                {
                    if (g[i][colonne].valeur != 0)
                    {   
                        val = g[i][colonne].valeur;
                        verif = retirerCandidat(&g[i][j], val, i, j);
                        if (verif == true){
                            candidatsElimTotal++;
                        } 
                    }
                }
                int carrel;
                int carrec;
                carrel = i - (i % 3);
                carrec = j - (j % 3);
                for (int cptl = 0; cptl < N; cptl++)
                {
                    for (int cptc = 0; cptc < N; cptc++)
                    {
                        if (g[carrel + cptl][carrec + cptc].valeur != 0)
                        {
                            val = g[carrel + cptl][carrec + cptc].valeur;
                            verif = retirerCandidat(&g[i][j], val, i, j);
                            if (verif == true){
                                candidatsElimTotal++;
                            } 
                        }
                    }
                }
            }
        }
    }
    return candidatsElimTotal;
}

void ajouterCandidat(tCase2 *laCase, int val)
{
    laCase->candidats[val] = true;
    laCase->nbCandidats = laCase->nbCandidats + 1;
}

bool retirerCandidat(tCase2 *laCase, int val, int i, int j) {
    bool verif = false;
    if (laCase->candidats[val] == true) {
        laCase->candidats[val] = false;
        laCase->nbCandidats = laCase->nbCandidats - 1;
        verif = true;
        //printf("%d %d - Suppression de %d\n", i + 1, j + 1, val);
    }
    return verif;
}

bool estCandidat(tCase2 laCase, int val)
{
    int cpt;
    int limiteLaCase;
    bool resultat;
    bool valEstCand;
    cpt = 0;
    limiteLaCase = nbCandidat(laCase);
    resultat = false;
    valEstCand = false;
    while (cpt <= limiteLaCase && valEstCand != true)
    {
        if (laCase.candidats[cpt] == true)
        {
            resultat = true;
            valEstCand = true;
        }
        else
        {
            cpt = cpt + 1;
        }
    }
    return resultat;
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

void afficherGrille(tGrille g)
{
    int i, j;
    printf("   1 2 3   4 5 6   7 8 9 \n");
    printf(" +-------+-------+-------+");
    for (i = 0; i < TAILLE; i++)
    {
        printf("\n%d| ", i + 1);
        for (j = 0; j < TAILLE; j++)
        {
            if (g[i][j].valeur == 0)
            {
                printf(". ");
            }
            else
            {
                printf("%d ", g[i][j].valeur);
            }
            if (j % N == 2)
            {
                printf("| ");
            }
        }
        if (i % N == 2)
        {
            printf("\n +-------+-------+-------+");
        }
    }
    printf("\n");
}

void afficherStats(tGrille g, int nbCasesVidesInit, int nbCasesVides, float candidatsElimTotal)
{
    float nbCasesRemplie;
    float tauxRemplissage;
    float tauxCandidatElim;
    nbCasesRemplie = (nbCasesVidesInit - nbCasesVides);
    tauxRemplissage = (nbCasesRemplie/nbCasesVidesInit*1.0) * 100.0;
    tauxCandidatElim = (candidatsElimTotal / (nbCasesVidesInit * 9.0)) * 100.0;
    printf("\n****** RESULTATS POUR Grille99.sud ******\n");
    printf("Nombre de cases remplies = %.0f sur %d     Taux de remplissage = %.3f%%\n", nbCasesRemplie, nbCasesVidesInit, tauxRemplissage);
    printf("Nombre de candidats elimines = %.0f      Pourcentage d'elimination = %.3f%%\n", candidatsElimTotal, tauxCandidatElim);
}