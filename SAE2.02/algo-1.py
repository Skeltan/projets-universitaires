"""
Version du programme qui permet d'afficher un echiquier rempli de dames
"""

"""
Valeur des cases:

1: Case Occupée par une dame
0/-x: Nombre de menaces
"""

def initialiser():
    """
    Initialiser:
    Paramètres: rien
    Objectif: Crée un échiquier remplie de case vide (tableau à 2 dimensions rempli de 0)
    """
    echiquier = [] #Contient une valeur pour chaque case: 1 s'il y a une dame et 0 s'il n'y a rien
    colonne = []
    for i in range(TAILLE):
        for j in range(TAILLE):
            colonne.append(0) 
        echiquier.append(colonne)
        colonne = []
    return echiquier



def afficherEchiquier(echiquier):
    """
    Afficher Echiquier:
    Paramètres: échiquier(tableau à 2 dimensions)
    Objectif: Affiche un échiquier visuel sur le terminal on l'on peut voir les dames en '*' et les cases menacées en 'X'
    """
    print("  ",end='')
    for i in range(TAILLE):
        print(" ",chr(ord("A")+i),"",end='')#mettre un convertisseur ascii pour mettre les lettres en foncion de N
    print("")
    for i in range(TAILLE*2+1):
        if(i%2 == 1):
            print(int(i//2)+1,end='')
            print(" ",end='')
            for j in range(TAILLE):
                if(echiquier[int(i//2)][j] == 1): #si une dame se trouve ici afficher une "*"
                    print('| * ', end='')
                elif (echiquier[int(i//2)][j] < 0): #DEBUG elim candidats
                    print('| X ', end='')
                else:
                    print('|   ', end='')
            print("|")
        else:
            print("  ",end='')
            for j in range(TAILLE):
                print("+---", end='')
            print("+")

def poserDame(echiquier):
    """
    Poser Dame:
    Paramètres: échiquier(tableau à 2 dimensions)
    Objectif: On demande les coordonées du placement de la 1ère dame pour ensuite trouver une solution.
              La ligne se choisi en chiffres et la colonne en lettres.
              On ne peut pas entrer de mauvaises valeurs.
    """
    entreeL = -1
    entreeC = -1
    valideL = False
    valideC = False
    while(not valideL):
        entreeL = int(input("Choisissez la ligne de la première dame:  "))
        entreeL -= 1
        if (entreeL < 0 or entreeL > 7):
            print("Erreur, recommencez")
        else:
            valideL = True
    while(not valideC):
        entreeCstr = str(input("Choisissez la colonne de la première dame avec une lettre majuscule:  "))
        entreeC = ord(entreeCstr)-64
        entreeC -= 1
        if (entreeC < 0 or entreeC > 7):
            print("Erreur, recommencez et n'oubliez pas d'entrer une majuscule")
        else:
            valideC = True
    echiquier[entreeL][entreeC] = 1
    eliminerCases(entreeL, entreeC)



def eliminerCases(ligne, colonne):
    """
    Eliminer Cases:
    Paramètres: ligne, colonne (coordonnées d'une dame)
    Objectif: Permet de rajouter des menaces après qu'une dame est été placée, 
              en enlevant 1 à la valeur de la case (une case dans le négatif est menacée)
    """
    # Ligne
    for i in range(TAILLE):
        if (echiquier[ligne][i]<= 0):
            echiquier[ligne][i] -= 1
    
    # Colonne
    for i in range(TAILLE):
        if (echiquier[i][colonne]<= 0):
            echiquier[i][colonne] -= 1

    # Diagonale de haut gauche à bas droite [\]
    # Placement
    i = ligne
    j = colonne
    while ((i != 0) and (j != 0)):
        i -= 1
        j -= 1

    # Elimination
    while ((i != TAILLE) and (j != TAILLE)):
        if (echiquier[i][j]<= 0):
            echiquier[i][j] -= 1
        i += 1
        j += 1

    # Diagonale de haut droite à bas gauche [/]
    # Placement
    i = ligne
    j = colonne
    while ((i != 0) and (j != TAILLE - 1)):
        i -= 1
        j += 1

    # Elimination
    while ((i != TAILLE) and (j != -1)):
        if (echiquier[i][j]<= 0):
            echiquier[i][j] -=1
        i += 1
        j -= 1



def ajouterCases(ligne, colonne):
    """
    Ajouter Cases:
    Paramètres: ligne, colonne (coordonnées d'une dame ayant été enlevée)
    Objectif: Permet d'enlever des menaces après qu'une dame est été enlevée, 
              en ajoutant 1 à la valeur de la case (une case dans le négatif est menacée et une case égale à zero est vide et non menacée)
    """
    # Ligne
    for i in range(TAILLE):
        if (echiquier[ligne][i] < 0):
            echiquier[ligne][i] += 1
    
    # Colonne
    for i in range(TAILLE):
        if (echiquier[i][colonne] < 0):
            echiquier[i][colonne] += 1

    # Diagonale de haut gauche à bas droite
    # Placement
    i = ligne
    j = colonne
    while ((i != 0) and (j != 0)):
        i -= 1
        j -= 1

    # Elimination
    while ((i < TAILLE) and (j < TAILLE)):
        if (echiquier[i][j] < 0):
            echiquier[i][j] += 1
        i += 1
        j += 1

    # Diagonale de bas gauche à haut droite 
    # Placement
    i = ligne
    j = colonne
    while ((i != 0) and (j != TAILLE-1)):
        i -= 1
        j += 1

    # Elimination
    while ((i < TAILLE) and (j >= 0)):
        if (echiquier[i][j] < 0):
            echiquier[i][j] += 1
        i += 1
        j -= 1    


def backtracking(echiquier,caseActuelle,cptDame):
    """
    Backtracking:
    Paramètres: échiquier(tableau à 2 dimensions), caseActuelle, cptDame 
    Objectif: Algorithme permettant de placer des dames dans des cases neutres 
              ou de les enlever en cas d'échec en atteignant la fin de l'échiquier.
              La fonction s'arrête une fois huit dames placées.
    """
    resultat = False
    if caseActuelle == 64: #condition d'échecs: retour en arrière
        return False
   
    ligne = caseActuelle // TAILLE
    colonne = caseActuelle % TAILLE

    if echiquier[ligne][colonne] != 0:
        resultat = backtracking(echiquier,caseActuelle+1,cptDame)
    else:
        echiquier[ligne][colonne] = 1
        cptDame+=1
        eliminerCases(ligne, colonne)
        if cptDame == TAILLE:#condition d'arrêt
            return True
        
        if(backtracking(echiquier,caseActuelle+1,cptDame)):
            resultat = True
        else:
            if echiquier[ligne][colonne] == 1:
                cptDame -=1
                ajouterCases(ligne, colonne)
                echiquier[ligne][colonne] = 0
                resultat = backtracking(echiquier,caseActuelle+1,cptDame)
    
    return resultat

# Main
TAILLE = 8
cptDame = 1
echiquier = initialiser()
afficherEchiquier(echiquier)
poserDame(echiquier)
backtracking(echiquier, 0, cptDame)
afficherEchiquier(echiquier)