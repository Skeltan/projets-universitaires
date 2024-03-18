<?php
#!/usr/bin/php
$fichiers = glob('*.c');

$nomConfig = "config";
$contenuConfig = file_get_contents($nomConfig);
$lignesConfig = explode("\n", $contenuConfig);
$sortie = "doc-tech-version.html";
$num = 1;
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

?>


<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="fr" lang="fr">
<head>
    <meta charset="utf-8">
    <title>Documentation d'utilisation</title>
    <meta name="description" content="Document technique de ...">
    <meta name="author" content="GANDEMER Alexis">
</head>

<?php
file_put_contents("$sortie", ""); // Reset le fichier
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
foreach ($fichiers as $fichier) {
    $lignes = file($fichier);
    $entete = "";
    $defines = [];
    $structures = array();
    $variablesGlobales = array();
    $fonctions = array();
    $descriptionCourte = "";
    $descriptionDetaillee = "";
    $parametres = [];
    $retour = "";
    $nomFonction = "";
    $indexDefine = 0;
    $indexStructure = 0;
    $indexVariable = 0;
    $indexFonction = 0;
    $indexParametre = 0;
    $indexVarStruct = 0;
    $tableauVarStruct = [];
    $dansStructure = false;
    $dansFonction = false;
    $separateurLigne = [];

    foreach ($lignes as $numeroLigne => $ligne) {
        $ligne = ltrim($ligne);

        if (strpos($ligne, 'struct') !== false) {
            $dansStructure = true;
        } elseif ($dansStructure && strpos($lignes[$numeroLigne - 1], '}') !== false) {
            $tableauVarStruct[$indexStructure] = $indexVarStruct;
            $indexVarStruct = 0;
            $indexStructure++;
            $dansStructure = false;
        }

        if (strpos($ligne, '#define') !== false) {
            $defines[$indexDefine] = ltrim($ligne, '#define');
            $indexDefine++;
        } elseif (strpos($ligne, '/**') !== false && strpos($ligne, '*/') !== false) {
            if ($dansStructure) {
                if (strpos($ligne, '}') !== false) {
                    $structures[$indexStructure][0] = ltrim($ligne, '}');
                } else {
                    $structures[$indexStructure][1][$indexVarStruct] = ltrim($ligne);
                    $indexVarStruct++;
                }
            } else {
                $variablesGlobales[$indexVariable] = ltrim($ligne, ' * \var');
                $indexVariable++;
            }
        }

        //------------FONCTION-----------
        elseif (!$dansFonction && strpos($ligne, '\\') !== false) {
            $dansFonction = true;
        } elseif ($dansFonction && strpos($ligne, '*/') !== false) {
            $nomFonction = rtrim($lignes[$numeroLigne + 1], '{');
            $fonctions[$indexFonction] = [$nomFonction, $parametres, $retour, $descriptionCourte, $descriptionDetaillee];
            $separateurLigne[$indexFonction] = $indexParametre;
            $indexFonction++;
            $indexParametre = 0;
            $dansFonction = false;
        }

        if ($dansFonction) {
            if (strpos($ligne, '*') !== false) {
                if (strpos($ligne, ' \brief ') !== false) {
                    $descriptionCourte = ltrim($ligne, ' * \brief ');
                } elseif (strpos($ligne, ' \detail ') !== false) {
                    $descriptionDetaillee = ltrim($ligne, '* \detail ');
                } elseif (strpos($ligne, '\param ') !== false) {
                    $parametres[$indexParametre] = ltrim($ligne, ' * \param ');
                    $indexParametre++;
                } elseif (strpos($ligne, '\return ') !== false) {
                    $retour = ltrim($ligne, '* \return ');
                }
            }
        }
        //-----------------------
        elseif (strpos($ligne, '*') !== false) {
            if (str_word_count($ligne, 0) > 1 && strpos($ligne, '\\') === false && strpos($ligne, '/') === false && strpos($ligne, ';') === false) {
                $entete = $entete . ltrim($ligne, "* ");
            }
        }
    }

?>
<body>
<h1><?php echo "Documentation technique du code src$num.C"?></h1>
<hr>

<h2>En-tête</h2>
<hr>
<p><?php echo $entete ?></p>

<h2>Define</h2>
<hr>
<?php if (!empty($defines)) {
    for ($i = 0; $i < $indexDefine; $i++) {
        $defSeparateur = explode('/**', $defines[$i]);
        ?>
        <ul>
            <li>
                <h4><?php echo rtrim($defSeparateur[0], ";") ?></h4>
                <ul>
                    <li><em><?php echo rtrim(rtrim($defSeparateur[1]), "*/") ?></em></li>
                </ul>
            </li>
        </ul>
    <?php }
} else {
    echo "Pas de #define";
} ?>

<h2>Structures</h2>
<hr>
<?php if (!empty($structures)) {
    for ($i = 0; $i < $indexStructure; $i++) {
        $defSeparateur = isset($structures[$i][0]) ? explode('/**', $structures[$i][0]) : ["", ""];
        ?>
        <h4><?php echo rtrim($defSeparateur[0], ";") ?></h4>
        <ul>
            <?php for ($j = 0; $j < $tableauVarStruct[$i]; $j++) {
                $defSeparateur = explode('/**', $structures[$i][1][$j]);
                ?>
                <li><strong><?php echo rtrim($defSeparateur[0], ";") ?></strong><em><?php echo rtrim(rtrim($defSeparateur[1]), "*/") ?></em>
                </li>
            </ul>
        <?php }
    }
} else {
    echo "Pas de structure";
} ?>

<h2>Variables globales</h2>
<hr>
<?php if (!empty($variablesGlobales)) {
    for ($i = 0; $i < $indexVariable; $i++) {
        $defSeparateur = explode('/**', $variablesGlobales[$i]);
        ?>
        <ul>
            <h4><?php echo rtrim($defSeparateur[0], ";") ?></h4>
            <li><?php echo rtrim(rtrim($defSeparateur[1]), "/*") ?></li>
        </ul>
    <?php }
} else {
    echo "Pas de variable globale";
} ?>
<h2>Fonctions</h2>
<hr>
<?php if (!empty($fonctions)) {
    for ($i = 0; $i < $indexFonction; $i++) {
        $defSeparateur = explode('(', $fonctions[$i][0]);
        ?>
        <h3><?php echo $defSeparateur[0] ?></h3>
        <table>
            <tr>
                <th>Paramètres</th>
                <th>Commentaire</th>
            </tr>
            <?php
            for ($j = 0; $j < count($fonctions[$i][1]); $j++) {
                $defSeparateur = explode(" ", $fonctions[$i][1][$j]);
                ?>
                <tr>
                    <td><?php echo $defSeparateur[0] ?></td>
                    <td><?php 
                        $phrase = '';
                        for ($k = 1; $k < count($defSeparateur); $k++) {
                            $phrase = $phrase . " " . $defSeparateur[$k];
                        } 
                        echo $phrase 
                    ?></td>

                </tr>
                <?php $phrase = "";
            } ?>
        </table>
    <?php }
} else {
    echo "Pas de fonction";
} ?>

</body>
</html>
<?php $num++; } ?>