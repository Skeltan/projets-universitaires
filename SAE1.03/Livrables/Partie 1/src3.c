/**
 * Ce programme permet d'évaluer le risque d'orage selon des informations indiquées par l'utilisateur.
*/

#include <stdio.h>
#include <stdlib.h>


#define SEUIL_TEMPERATURE 25.0 /** Seuil de température pour le risque d'orage */
#define SEUIL_HUMIDITE 70.0 /** Seuil d'humidité pour le risque d'orage */



/**
 * \brief Structure représentant les données météorologiques.
 */
struct Meteo {
    float temperature; /** Température actuelle en Celsius */
    float humidite; /** Humidité actuelle en pourcentage */
};

/**
 * \brief Structure représentant les conditions météorologiques.
 */
struct ConditionsMeteo {
    struct Meteo actuelle; /** Données météorologiques actuelles */
    int risqueOrage; /** Indicateur de risque d'orage (1 si vrai, 0 sinon) */
};


void saisirMeteo(struct Meteo *meteo);
void afficherConditions(struct ConditionsMeteo conditions);
int evaluerRisqueOrage(struct Meteo meteo);
float calculerMoyenneSeuils();

int main() {
    struct ConditionsMeteo conditions;

    saisirMeteo(&conditions.actuelle);

    conditions.risqueOrage = evaluerRisqueOrage(conditions.actuelle);

    afficherConditions(conditions);

    printf("Moyenne des seuils : %.2f\n", calculerMoyenneSeuils());

    return 0;
}

/**
 * \brief Saisit les données météorologiques depuis l'utilisateur.
 * \detail Cette fonction invite l'utilisateur à entrer la température et l'humidité, puis les stocke dans la structure Meteo.
 * \param[out] meteo Pointeur vers la structure Meteo pour stocker les données.
 */
void saisirMeteo(struct Meteo *meteo) {
    printf("Entrez la température en Celsius : ");
    scanf("%f", &meteo->temperature);
    
    printf("Entrez l'humidité en pourcentage : ");
    scanf("%f", &meteo->humidite);
}


/**
 * \brief Affiche les conditions météorologiques actuelles.
 * \detail Cette fonction affiche les données météorologiques actuelles ainsi que l'indicateur de risque d'orage.
 * \param conditions Structure ConditionsMeteo contenant les données à afficher.
 */
void afficherConditions(struct ConditionsMeteo conditions) {
    printf("\nConditions météorologiques actuelles :\n");
    printf("Température : %.2f °C\n", conditions.actuelle.temperature);
    printf("Humidité : %.2f%%\n", conditions.actuelle.humidite);
    
    if (conditions.risqueOrage)
        printf("Risque d'orage : Oui\n");
    else
        printf("Risque d'orage : Non\n");
}


/**
 * \brief Évalue le risque d'orage en fonction des données météorologiques.
 * \detail Cette fonction détermine s'il y a un risque d'orage en comparant la température et l'humidité aux seuils définis.
 * \param meteo Structure Meteo contenant les données météorologiques.
 * \return int 1 si risque d'orage, 0 sinon.
 */
int evaluerRisqueOrage(struct Meteo meteo) {
    if (meteo.temperature > SEUIL_TEMPERATURE && meteo.humidite > SEUIL_HUMIDITE)
        return 1; // Il y a un risque d'orage
    else
        return 0; // Pas de risque d'orage
}


/**
 * \brief Calcule la moyenne du seuil de température et d'humidité.
 * \detail Cette fonction retourne la moyenne des seuils définis pour la température et l'humidité.
 * \return float Moyenne des seuils.
 */
float calculerMoyenneSeuils() {
    return (SEUIL_TEMPERATURE + SEUIL_HUMIDITE) / 2.0;
}

