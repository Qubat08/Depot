# CHPS0801 - Kokkos Branch
# Auteurs
    - COGNE Romain
    - BATISTE Quentin
    - CORTINHAL Simão
## Version : Kokkos
---
## Prérequis:
- Vérifier que le package Python Pillow soit installé (sur le noeud de calcul aussi) sinon:
    - python3 -m venv \<nom>
    - source \<nom>/bin/activate
    - pip install Pillow
    - Mettre à jour les source dans les différents fichiers de soumission de jobs.

- Les images doivent être au format .jpg ou .jpeg dans le dossier img/ de chaque version

- Pour la version kokkos, il faut avoir une installation de Kokkos fonctionnelle et mettre à jour les différents liens vers Kokkos

## Utilisation soumission.job

Pour exécuter et compiler le code, il suffit d'exécuter le fichier de soumission de job.
Pour ce faire :

    - sbatch soumission.job \<arg1> \<arg2>

\<arg1>: représente l'image d'origine (mettre juste le nom et l'extention, exemple: img.jpg) <br>
\<arg2>: Deux choix possibles: <br>
    - noised_res pour travailler sur l'image en couleur <br>
    - grey_res pour travailler sur l'image en gris

