#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 3
#define TAILLE (N * N)

typedef struct
{
    int valeur;
    int candidats[TAILLE];
    int nbCandidats;
} tCase1;

typedef tCase1 tGrille[TAILLE][TAILLE];

float initialiser_candidats(tGrille g);
void ajouterCandidat(tCase1 laCase, int val);
bool retirerCandidat(tCase1 *laCase, int i, int j, int val);
bool estCandidat(tCase1 laCase, int val);
int nbCandidat(tCase1 laCase);
int chargerGrille(tGrille g);
void afficherGrille(tGrille g);
void affiche_candidat(tGrille g);
void afficherStats(tGrille g, int nbCasesVidesInit, int nbCasesVides, float candidatsElimTotal);

int main()
{
    tGrille g;
    bool verif;
    bool progression;
    int nbCasesVides;
    int nbCasesVidesInit;
    float candidatsElimTotal;
    nbCasesVides = chargerGrille(g);
    nbCasesVidesInit = nbCasesVides;
    candidatsElimTotal = initialiser_candidats(g);
    progression = true;
    while (nbCasesVides != 0 && progression)
    {
        printf("Il y a %d cases vides\n", nbCasesVides);
        // affiche_candidat(g);
        afficherGrille(g);
        progression = false;

        for (int i = 0; i < TAILLE; i++)
        {
            for (int j = 0; j < TAILLE; j++)
            {
                if (nbCandidat(g[i][j]) == 1)
                {
                    int val = 0;
                    while (g[i][j].candidats[val] == 0)
                    {
                        val = val + 1;
                    }
                    g[i][j].valeur = g[i][j].candidats[val];
                    g[i][j].nbCandidats = 0;
                    candidatsElimTotal++;
                    nbCasesVides = nbCasesVides - 1;
                    for (int ligne = 0; ligne < TAILLE; ligne++)
                    {
                        for (int cand = 0; cand < TAILLE; cand++)
                        {
                            if (g[ligne][j].candidats[cand] == g[i][j].valeur)
                            {
                                verif = retirerCandidat(&g[ligne][j], i, j, g[i][j].valeur);
                                if(verif)
                                {
                                    candidatsElimTotal++;
                                }
                            }
                        }
                    }
                    for (int colonne = 0; colonne < TAILLE; colonne++)
                    {
                        for (int cand = 0; cand < TAILLE; cand++)
                        {
                            if (g[i][colonne].candidats[cand] == g[i][j].valeur)
                            {
                                verif = retirerCandidat(&g[i][colonne], i, j, g[i][j].valeur);
                                if(verif)
                                {
                                    candidatsElimTotal++;
                                }
                            }
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
                            for (int cand = 0; cand < TAILLE; cand++)
                            {
                                if (g[carrel + cptl][carrec + cptc].candidats[cand] == g[i][j].valeur)
                                {
                                    verif = retirerCandidat(&g[carrel + cptl][carrec + cptc], i, j, g[i][j].valeur);
                                    if(verif)
                                    {
                                        candidatsElimTotal++;
                                    }
                                }
                            }
                        }
                    }
                    progression = true;
                }
            }
        }
    }
    afficherGrille(g);
    afficherStats(g,nbCasesVidesInit,nbCasesVides,candidatsElimTotal);
}

float initialiser_candidats(tGrille g)
{
    int i;
    int j;
    int k;
    bool verif;
    float candidatsElimTotal;
    for (i = 0; i < TAILLE; i++)
    {
        for (j = 0; j < TAILLE; j++)
        {
            if (g[i][j].valeur == 0)
            {
                for (k = 0; k < TAILLE; k++)
                {
                    g[i][j].candidats[k] = k + 1;
                }
                g[i][j].nbCandidats = TAILLE;
            }
            else
            {
                for (k = 0; k < TAILLE; k++)
                {
                    g[i][j].candidats[k] = 0;
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
                        verif = retirerCandidat(&g[i][j], i, j, g[ligne][j].valeur);
                        if(verif)
                        {
                            candidatsElimTotal++;
                        }
                    }
                }
                for (int colonne = 0; colonne < TAILLE; colonne++)
                {
                    if (g[i][colonne].valeur != 0)
                    {
                        verif = retirerCandidat(&g[i][j], i, j, g[i][colonne].valeur);
                        if(verif)
                        {
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
                            verif = retirerCandidat(&g[i][j], i, j, g[carrel + cptl][carrec + cptc].valeur);
                            if (verif)
                            {
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

void ajouterCandidat(tCase1 laCase, int val)
{
    int limiteLaCase;
    limiteLaCase = nbCandidat(laCase);
    laCase.candidats[limiteLaCase + 1] = val;
    laCase.nbCandidats = laCase.nbCandidats + 1;
}

bool retirerCandidat(tCase1 *laCase, int i, int j, int val)
{
    int cpt;
    int limiteLaCase;
    bool valide;
    cpt = 0;
    limiteLaCase = TAILLE;
    valide = false;
    while (cpt < limiteLaCase)
    {
        if (laCase->candidats[cpt] == val)
        {
            laCase->candidats[cpt] = 0;
            laCase->nbCandidats--;
            valide = true;
            break;
        }
        cpt++;
    }
    return valide;
}

bool estCandidat(tCase1 laCase, int val)
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
        if (val == laCase.candidats[cpt])
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

int nbCandidat(tCase1 laCase)
{
    return laCase.nbCandidats;
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
    nbCasesRemplie = nbCasesVidesInit - nbCasesVides;
    tauxRemplissage = (nbCasesRemplie/(nbCasesVidesInit*1.0)) * 100.0;
    tauxCandidatElim = (candidatsElimTotal / (nbCasesVidesInit * 9.0)) * 100.0; // 9.0 est TAILLE mais en float     Ce calcul marche mais à un problème.
    printf("****** RESULTATS POUR Grille99.sud ******\n");
    printf("Nombre de cases remplies = %.0f sur %d     Taux de remplissage = %.3f%%\n", nbCasesRemplie, nbCasesVidesInit, tauxRemplissage);
    printf("Nombre de candidats elimines = %.0f        Pourcentage d'elimination = %.3f%%\n", candidatsElimTotal, tauxCandidatElim);
}