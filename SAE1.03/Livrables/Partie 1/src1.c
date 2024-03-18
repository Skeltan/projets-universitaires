/**
 *  Programme de gestion des salaires des employés. qui calcule la moyenne et les salaire des employés.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define N 5 /**Valeurs maximal du tableau*/
#define CASE 6 /** Nombre de cases présent dans le tableau */
typedef char chaine20[21] ;
typedef chaine20 tabnoms[N] ;

typedef struct {
int min;/**valeur minimum*/
int max;/**valeur maximum*/

} min_max; /** Structure du minimum et du maximum */

typedef struct {
char nom[50]; /** nom de l'utilisateur */
char prenom[50]; /** prenom de l'utilisateur */
} nom_prenom; /** Structure des projets d'un·e étudiant·e */

typedef struct  
{
    int choixNombre; /**choix du nombre.*/
    char choixLettre;/**choix de la lettre*/
}choix;/**structure contenant tout les choix*/

int gertrude[4];/**Nombre de Gertrude*/
int tableau[4];/**tableau à trier*/

int verifie(char question);


bool fonctionne(int valeur, char reponse);




struct  valeurs/**structure contenant toutes les valeurs*/
{
    int max; /**Valeur à insérer*/
    int val;/**Valeur maximal*/
    int min;/**Valeur minimal*/
};



void maintientTrie (tabnoms t , int i);


void triParInsertion ( tabnoms t, int n);



int main(){
    int n;
    n=0;
    tabnoms tNoms = {"toto","zozo","loto","momo","mimi"};
    affiche(tNoms);
    triParInsertion(tNoms, n);
    affiche(tNoms);
}






void affiche(tabnoms t){
    for (int i = 0; i < N; i++)
    {    
        printf("%s ", t[i]);       
    }
    printf("\n");

}


/**
* \brief Permet de maintenir le trie effectuer.
* \details Permet de maintenir le tri qui a été effectuer
* \param int i est un indice qui va s'incrémenter
* \param tabnoms t c'est le tableau
*/
void maintientTrie (tabnoms t , int i){
    chaine20 temp;
    while(i>0 && strcmp(t[i-1], t[i])>0){
        strcpy(temp, t[i-1]);
        strcpy(t[i-1],t[i]);
        strcpy(t[i],temp);
        i--;
    }
}


/**
* \brief tri le tableau par insertion
* \details tri le tableau par un système d'insertion, une valeur est insérer dans une variable différente puis placer au bon endroit.
* 
* 
* \param tabnoms t tableau insérer à trier
* \param int n valeur à incrémenter
*/
void triParInsertion ( tabnoms t, int n){
    int i;
    for ( i=1; i<N; i++){
        maintientTrie(t, i);
    }
}
/**
 * \brief fonction qui vérifie si la question est bonne
 * \details fonction qui verifie si la question possède un point d'interrogation
 * 
 * \param question question choisis par l'utilisateur
 * \return retourne 1 si la question est bonne 0 sinon.
*/
int verifie(char question){}

/**
 * \brief fonction qui vérifie si la valeur est bonne 
 * \details fonction qui va vérifier si la valeur est la même que la réponse 
 * 
 * \param valeur valeur indiquer par l'utilisateur
 * \param reponse la valeur attendu pas l'utilisateur
 * \return retourne vrai si la valeur est bonne 
*/
bool fonctionne(int valeur, char reponse){}





/**
* \brief affiche le tableau
* \details Affiche le tableau complet en affichant chaque case une par une
* \param tabnoms t est le tableau.
*/
void affiche(tabnoms t){}
