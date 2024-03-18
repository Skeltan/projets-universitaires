/**
 * Ce programme permet d'indiquer la valeur minimal et la valeur maximal sur une suite de chiffres indiquer par l'utilisateur.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
const int ERREUR = -1;  
const int STOP = 0; 
#define BONJOUR 45; /**Nombre de bonjour*/
#define ENREVOIR 50; /**Nombre d'enrevoir*/

typedef struct {
    char nom[50]; /** Nom de l'étudiant·e */
    char groupe_td[3]; /** Lettre indiquant son groupe TD */
int num_tp; /** Numéro de son groupe TP (1 ou 2) */
} str_etu; /** Structure d'un·e étudiant·e */

typedef struct {
char objectif_vie[50]; /** Objectif dans la vie */
char passion[50]; /** Passion dans la vie */
} projet; /** Structure des projets d'un·e étudiant·e */


int bonjour[6]; /** Liste des bonjour */
int enrevoir[8]; /** Liste des enrevoir */

int verifier(int valeur);


bool temps(int heure, char jours);


void projet(char passion, char objectif_vie);


void suite(int val, int *max, int *min);



int main(){
    
    int val, max, min;
    val = 0;            
    max = 0;            
    min = 0;            
    suite(val, &max, &min);
    if ((max == ERREUR) && (min == ERREUR)){
        printf("Erreur.");
    }
    else{
        printf("Le max est : %d\n", max);
        printf("Le min est : %d\n", min);
    }

}

/**
 * \brief fonction qui vérifie si la valeur est bonne
 * \details fonction qui vérifie si la valeur est un entier naturelle
 * 
 * \param valeur valeur choisis par l'utilisateur
 * \return retourne 1 si la valeur est bonne 0 sinon.
*/
int verifier(int valeur){}

/**
 * \brief procédure qui vérifie si l'horaire est possible 
 * \details procédure qui va vérifier si l'horaires est disponible le jour indiquer 
 * 
 * \param heure heure indiquer par l'utilisateur
 * \param jours jours indiquer par l'utilisateur
 * \return retourne vrai si l'horaire est disponible
*/
bool temps(int heure, char jours){}

/**
 * \brief procédure qui affiche les objectifs et la passion de l'utilisateur
 * \details procédure qui va afficher les objectifs et la passion de l'utilisateur
 * 
 * \param objectif_vie objectif indiquer par l'utilisateur
 * \param passion passion indiquer par l'utilisateur
*/
void projet(char passion, char objectif_vie){}




/**
 * \brief procédure qui initialise la valeur max et min
 * \details procédure qui va initialiser la valeur maximal et la valeur minimale.
 * 
 * \param val valeur indiquer par l'utilisateur
 * \param *max valeur max
 * \param *min valeur min 
*/
void suite(int val, int *max, int *min ){
    printf("Quelle est la valeur ");
    scanf("%d",&val);
    if (val!=STOP){
        *min = val;
        *max = val;
        while (val != STOP){
            if (val > *max){
                *max = val;
            }
            if (val < *min){
                *min = val;
            }

            printf("Quelle est la valeur ");
            scanf("%d",&val);
        }
    }
    else{
        *min = ERREUR;
        *max = ERREUR;
    }
}