# CHPS0805 - BATISTE Quentin - Projet Optimisation et Recherche Opérationnelle
Le but de se projet est de résoudre des problèmes d'optimisation et de recherche opérationnelle comme le problème de voyageur 
de commerce (TSP) ou encore le problème du sac à dos en valeur entière (Knapsack problem)


## 1. Partie C
### Compilation:
make
### Execution:
./main <type> <type_file> <nom_fichier> <boolAffichage>

### Avec :
- type : 0 pour un problème de sac à dos, 1 pour un problème de TSP
- type_file : 0 pour un fichier de données, 1 pour gros fichier (à partir de 20 pour le sac à dos ou fichier venant de TSPLib pour le TSP)
- nom_fichier : nom du fichier contenant le problème (dans data et sans extension) 
- boolAffichage : 0 pour ne pas afficher toute l'exécution, 1 pour afficher

### Exemple:
Lancement du problème de sac à dos 1 avec affichage : <br> ./main 0 0 prob_sac_1 1 <br> ./main 0 1 prob_sac_20 0<br>
Lancement d'un problème de TSP avec affichage : <br> ./main 1 0 graphe12 1

### Nettoyage:
make clean

## 2. Partie Ortools

### Exécution:
python Solver.py <type> <type_file> <nom_fichier>

### Avec :
- type : 0 pour un problème de sac à dos, 1 pour un problème de TSP
- type_file : 0 pour un fichier de données, 1 pour gros fichier (à partir de 20 pour le sac à dos ou fichier venant de TSPLib pour le TSP)
- nom_fichier : nom du fichier contenant le problème (dans data et sans extension)

### Exemple:
Lancement du problème de sac à dos 1 : 
<br> python Solver.py 0 0 prob_sac_1
<br> python Solver.py 0 1 prob_sac_20

Lancement d'un problème de TSP :
<br> python Solver.py 1 0 graphe12
<br> python Solver.py 1 1 berlin52