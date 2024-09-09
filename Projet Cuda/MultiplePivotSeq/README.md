# PROJET - CHPS0802
## Sujet de projet:
Implémentation en C d'un algorithme de résolution de système d'équations par un pivot de Gauss

## Travail à faire:
### Version séquentiel (branch seq)
- Choix structure de données ✅
- Ajout de l'utilisation des fichiers d'entrées et de sortie ✅
- Implémentation du choix de la ligne en fonction du coefficient avec le pivot de Gauss (Triangulation de la matrice) ✅
- Implémenté la remontée de Gauss pour obtenir les valeurs des variables et fichier de sortie ✅

- Améliorer l'algorithme via des échanges de lignes pour éviter les valeurs très proches de zero


## Utilisation:
- make
- ./main {nameFile}

{nameFile} = nom sans extension du fichier d'entrée (doit être dans ./data/)

Fichier de sortie:
Automatique dans ./data/{namefile}_resultat.txt

Que faire pour le projet CHPS0802:

V1 cuda:
Ecrire code pour version cuda pour diviser ligne et soustraction ligne
(possible de tout faire dans un gros kernel)

V2 cuda:
Multiplier le nombre de pivot pour dégager plus de parallélisme
/!\ moins de stabilité
Voir combien on peut prendre de pivot (si +100 dépasse la capacité GPU)
Attention lors de l'échange pour remettre en haut et eviter de choisir des lignes plusieurs fois (ecrire une ligne séquentielle avant pour être sûr)

Déroulement:
Choisir les lignes pivot
Remonter les lignes cuda en haut de la matrice
Normaliser les lignes de pivot puis propager sur les autres lignes du pivot
Propager sur toutes les autres lignes

Pour la soutenance : Notebook + code pour Roméo + analyse de performance (analyse critique) 