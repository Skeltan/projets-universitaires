#!/usr/bin/php
<?php
$nomMd = "doc.md";
$sortie = "doc-user-version.html";
$contenu = file_get_contents($nomMd);
$lignes = explode("\n", $contenu);
$listeOuverte = false;
$codeOuvert = false;
$tableauOuvert = false;
$patternHyperlien = '/\[([^\]]+)\]\(([^)]+)\)/'; // Expression régulière pour extraire le texte du lien et l'URL
$patternItaliqueGras = '/\*{1,3}(.*?)\*{1,3}/'; // Expression régulière pour extraire le texte encadré par des étoiles
$patternCode = '/`([^`]+)`/';

$nomConfig = "config";
$contenuConfig = file_get_contents($nomConfig);
$lignesConfig = explode("\n", $contenuConfig);

/*
Le fichier config suit ce format:
    CLIENT=Les Génies du Ponant
    PRODUIT=Machine à courber les bananes
    VERSION=2.7.4
*/

foreach ($lignesConfig as $ligneConfig) {
    if (strpos($ligneConfig, "CLIENT=") === 0) {
        $nomClient = ltrim($ligneConfig, "CLIENT=");
    }
    if (strpos($ligneConfig, "PRODUIT=") === 0) {
        $produit = ltrim($ligneConfig, "PRODUIT=");
    }
    if (strpos($ligneConfig, "VERSION=") === 0) {
        $version = ltrim($ligneConfig, "VERSION=");
    }
    $date = date("j F Y, H:i:s");
}

file_put_contents("$sortie", 
"<!DOCTYPE html>
<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"fr\" lang=\"fr\">
	<head>
	    <meta charset=\"utf-8\" >
	    <title>Document Utilisateur</title>
	    <meta name=\"description\" content=\"Manuel d\'utilisation de ...\" >
		<meta name=\"author\" content=\"GANDEMER Alexis et LE GUERN Alexis et $nomClient\">
	</head>
    <body>"
);

file_put_contents("$sortie",
"<header>
    <hr>
        <h2>$produit</h2>
        <p>Nom: $nomClient</p>
        <p>Version: $version</p>
        <p>Date: $date</p>
    <hr>
</header>", FILE_APPEND
);

foreach ($lignes as $ligne) {
    // Détecter et remplacer les * pour italique et gras
    if (preg_match_all($patternItaliqueGras, $ligne, $matches)) {
        // $matches[1] contient le texte entre les étoiles
        foreach ($matches[1] as $texteEntreEtoiles) {
            $texteGrasItalique = '<strong><em>' . $texteEntreEtoiles . '</em></strong>';
            $texteGras = '<strong>' . $texteEntreEtoiles . '</strong>';
            $texteItalique = '<em>' . $texteEntreEtoiles . '</em>';
            
            $ligne = str_replace('***' . $texteEntreEtoiles . '***', $texteGrasItalique, $ligne);
            $ligne = str_replace('**' . $texteEntreEtoiles . '**', $texteGras, $ligne);
            $ligne = str_replace('*' . $texteEntreEtoiles . '*', $texteItalique, $ligne);  
        }
    }
    // Détecter et remplacer les ` pour les bouts de code
    if (preg_match_all($patternCode, $ligne, $matches)) {
        // $matches[1] contient le texte entre les backticks
        foreach ($matches[1] as $texteEntreBackticks) {
            $code = '<code>' . $texteEntreBackticks . '</code>';

            $ligne = str_replace('`' . $texteEntreBackticks . '`', $code, $ligne);
        }
    }

    // Fin de liste si elle a été ouverte mais que la prochaine ligne n'est pas une donnée de liste
    if ((strpos($ligne, "- ") !== 0) && ($listeOuverte)) { 
        file_put_contents("$sortie", "</ul>\n", FILE_APPEND);
        $listeOuverte = false;
    }
    // Fin de tableau si il a été ouvert mais que la prochaine ligne n'est pas une donnée de tableau
    if ((strpos($ligne, "|") !== 0) && ($tableauOuvert)) {
        file_put_contents("$sortie", "</table>\n", FILE_APPEND);
        $tableauOuvert = false;
    }

    // Titre de tous niveaux
    if (strpos($ligne, "#### ") === 0) {
        $ligne = ltrim($ligne, $characters = "#### ");
        file_put_contents("$sortie", "<h4>$ligne</h4>\n", FILE_APPEND);
    }
    else if (strpos($ligne, "### ") === 0) {
        $ligne = ltrim($ligne, $characters = "### ");
        file_put_contents("$sortie", "<h3>$ligne</h3>\n", FILE_APPEND);
    }
    else if (strpos($ligne, "## ") === 0) {
        $ligne = ltrim($ligne, $characters = "## ");
        file_put_contents("$sortie", "<h2>$ligne</h2>\n", FILE_APPEND);
    }
    else if (strpos($ligne, "# ") === 0) {
        $ligne = ltrim($ligne, $characters = "# ");
        file_put_contents("$sortie", "<h1>$ligne</h1>\n", FILE_APPEND);
    }
    // Liste
    else if (strpos($ligne, "- ") === 0) {
        $ligne = ltrim($ligne, $characters = "- ");
        if (!$listeOuverte){
            file_put_contents("$sortie", "<ul>\n", FILE_APPEND);
            $listeOuverte = true;
            file_put_contents("$sortie", "<li>$ligne</li>\n", FILE_APPEND);
        }
        else {
            file_put_contents("$sortie", "<li>$ligne</li>\n", FILE_APPEND);
        }
    }
    // Bloc de codes
    else if ((strpos($ligne, "```") === 0) && (!$codeOuvert)) {
        $codeOuvert = true;
        file_put_contents("$sortie", "<pre><code><p>\n", FILE_APPEND);
    }
    elseif ((strpos($ligne, "```") !== 0) && $codeOuvert) {
        file_put_contents($sortie, "$ligne\n", FILE_APPEND);
    }
    elseif ((strpos($ligne, "```") === 0) && $codeOuvert) {
        $codeOuvert = false;
        file_put_contents("$sortie", "</p></code></pre>\n", FILE_APPEND);
    }
    // Ligne unique de code
    else if (strpos($ligne, "`") !== false && strpos($ligne, "```") === false) {
        $ligne = trim($ligne, '`');
        $ligne = str_replace('`', '', $ligne);
        file_put_contents("$sortie", "<code>$ligne</code>\n", FILE_APPEND);
    }
    // Lien hypertexte
    else if (preg_match($patternHyperlien, $ligne, $matches)) {
        $texteDuLien = $matches[1]; // Texte du lien
        $urlDuLien = $matches[2]; // URL du lien
        $ligne = '<a href="' . htmlspecialchars($urlDuLien, ENT_QUOTES, 'UTF-8') . '">' . htmlspecialchars($texteDuLien, ENT_QUOTES, 'UTF-8') . '</a>';
        file_put_contents($sortie, "$ligne\n", FILE_APPEND);
    }
    // Tableau
    else if (strpos($ligne, "|") === 0) {
        if (!strpos($ligne, "|-")) {
            $cellules = explode('|', $ligne);
            array_shift($cellules); // Suppr la première cellule (vide)
            array_pop($cellules); // Suppr la dernière cellule (vide)
            if (!$tableauOuvert){ 
                file_put_contents("$sortie", "<table>\n", FILE_APPEND);
                $tableauOuvert = true;
                file_put_contents("$sortie", "<tr>", FILE_APPEND);
                foreach ($cellules as $cellule) {
                    file_put_contents("$sortie", "<th>$cellule</th>", FILE_APPEND);
                }
                file_put_contents("$sortie", "</tr>", FILE_APPEND);
            }
            else {
                file_put_contents("$sortie", "<tr>", FILE_APPEND);
                foreach ($cellules as $cellule) {
                    file_put_contents("$sortie", "<td>$cellule</td>", FILE_APPEND);
                }
                file_put_contents("$sortie", "</tr>", FILE_APPEND);
            }   
        }
    }
    // Paragraphes
    else if (!((strpos($ligne, "# ") === 0) || (strpos($ligne, "- ") === 0) || (strpos($ligne, "`") === 0) || (preg_match($patternHyperlien, $ligne, $matches)) || (strpos($ligne, "|") === 0) || (!str_word_count($ligne)))) {
        file_put_contents("$sortie", "<p>$ligne</p>\n", FILE_APPEND);
    }
}
file_put_contents("$sortie", '</body></html>', FILE_APPEND);
?>
