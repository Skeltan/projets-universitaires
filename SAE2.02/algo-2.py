import random

"""
Algo 2:

Algorithme se basant sur une génération aléatoire du placement d'une dame par ligne
"""


# (Ré)Initialise toutes les valeurs de l'échiquier à 0
def initialiser(): 
    echiquier = []
    colonne = []
    for i in range(TAILLE):
        for j in range(TAILLE):
            colonne.append(0) 
        echiquier.append(colonne)
        colonne = []
    return echiquier


"""
Cette  fonction affiche l'échiquier
"""
def afficherEchiquier(echiquier):
    print("  ",end='')
    for i in range(TAILLE):
        print(" ",chr(ord("A")+i),"",end='')# convertisseur ascii pour remplacer les chiffres en lettres
    print("")
    for i in range(TAILLE*2+1):
        if(i%2 == 1):
            print(int(i//2)+1,end='')
            print(" ",end='')
            for j in range(TAILLE):
                if(echiquier[int(i//2)][j] == 1): # si une dame se trouve ici afficher une "*"
                    print('| * ', end='')
                else:
                    print('|   ', end='')
            print("|")
        else:
            print("  ",end='')
            for j in range(TAILLE):
                print("+---", end='')
            print("+")


"""
Cette fonction place une dame dans une colonne aléatoire pour chaque ligne
"""
def randomPlacement(echiquier):
    echiquier = initialiser()  # Réinitialisation de l'échiquier à chaque tentative
    for i in range(TAILLE):
        j = random.randint(0, TAILLE-1) # Génère un nombre aléatoire entre 0 et TAILLE-1 (équivalant à la coloone)
        echiquier[i][j] = 1
    return echiquier


"""
Cette fonction vérifie qu'une dame n'en menace pas une autre, elle vérifie que la combinaison est valide
"""
def verifEchiquier(echiquier):
    valide = True
    for ligne in range(TAILLE):
        for colonne in range(TAILLE):
            if echiquier[ligne][colonne] == 1:
                # Vérification colonne
                for i in range(ligne + 1, TAILLE):
                    if echiquier[i][colonne] == 1:
                        valide = False
                
                # Vérification diagonale \
                i, j = ligne + 1, colonne + 1
                while i < TAILLE and j < TAILLE:
                    if echiquier[i][j] == 1:
                        valide = False
                    i += 1
                    j += 1
                
                # Vérification diagonale /
                i, j = ligne + 1, colonne - 1
                while i < TAILLE and j >= 0:
                    if echiquier[i][j] == 1:
                        valide = False
                    i += 1
                    j -= 1
    return valide




# Main
TAILLE = 8
echiquier = initialiser()
valide = False
print("Recherche d'une solution... Veuillez patienter...")

while not valide:
    echiquier = randomPlacement(echiquier)
    valide = verifEchiquier(echiquier)
    
afficherEchiquier(echiquier)

