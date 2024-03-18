#!/usr/bin/bash

#Récupération de l'image clock (pas nécessaire à l'IUT, c'est à faire avant de lancer le script bash)

#docker image pull clock

#Création du volume sae103

echo -e "\e[93mCréation du volume sae103\e[0m"
docker volume create sae103

#On lance le conteneur clock en l'appelant sae103-forever, on fait aussi en sorte que quand on l'éteint il s'auto-détruit et se détache et on le monte sur le 		volume sae103

echo -e "\e[93mLancement de clock avec comme nom sae103-forever\e[0m"

docker container run -d -ti --name sae103-forever --rm -v sae103:/work/ clock

#On copie tous les codes sources, le fichier md, les codes php et le fichier config dans le volume sae103
	
echo -e "\e[93mCopie du fichier config vers le conteneur\e[0m"
docker container cp ./config sae103-forever:/work/
echo -e "\e[93mCopie du fichier doc.md vers le conteneur\e[0m"
docker container cp ./doc.md sae103-forever:/work/
echo -e "\e[93mCopie du fichier gendoc-user.php vers le conteneur\e[0m"
docker container cp ./gendoc-user.php sae103-forever:/work/
echo -e "\e[93mCopie du fichier src1.c vers le conteneur\e[0m"
docker container cp ./src1.c sae103-forever:/work/
echo -e "\e[93mCopie du fichier src2.c vers le conteneur\e[0m"
docker container cp ./src2.c sae103-forever:/work/
echo -e "\e[93mCopie du fichier src3.c vers le conteneur\e[0m"
docker container cp ./src3.c sae103-forever:/work/
echo -e "\e[93mCopie du fichier gendoc-tech.php vers le conteneur\e[0m"
docker container cp ./gendoc-tech.php sae103-forever:/work/

#On transforme les fichiers sources .c et .md en HTML

echo -e "\e[93mConvertion des fichiers .c et .md en html\e[0m"
docker container run -v sae103:/work/ sae103-php php gendoc-user.php
docker container run -v sae103:/work/ sae103-php sh -c "php gendoc-tech.php >> /work/doc-tech-version.html"

#On transforme les fichiers HTML en PDF
	
echo -e "\e[93mConvertion des fichiers .html en pdf\e[0m"
docker container run -v sae103:/work/ sae103-html2pdf "html2pdf gendoc-user.html gendoc-user.pdf"
docker container run -v sae103:/work/ sae103-html2pdf "html2pdf gendoc-tech.html gendoc-tech.pdf"

#On copie les pdf vers l'ordinateur hôte dans un dossier output
echo -e "\e[93mEnvoi des PDF vers l'hôte dans un dossier output\e[0m"
docker container cp sae103-forever:/work/ ./output

#On crée l'archive finale
	
echo -e "\e[93mCréation de l'archive finale\e[0m"
rm ./output/*.c
rm ./output/*.md
rm ./output/*.php
rm ./output/*.html
rm ./output/config
tar czvf archive-finale.tgz output/
rm -r ./output


#Arrêt du conteneur
echo -e "\e[93mArrêt du conteneur\e[0m"
docker container stop sae103-forever

