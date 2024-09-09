BATISTE Quentin PROJET Traitement d'image
Le but de ce projet est de réalisé des opérations sur des images comme le redimensionnement intelligent (seam carving).

Pour ce qui est de l’exécution du programme, 
il faut donc posséder un environnement python ainsi que les différents modules suivants :
-	Numpy
-	Imageio
-	Scipy
-	Matplotlib

Pour installer ces modules, vous pouvez utiliser la commande pip install [module] (sur windows : la commande est py -m pip install [module]).


Une fois les modules installés, nous pouvons exécuter le programme via la commande :
-	py projet.py NomImage Scale BooleanAffichage

L’image doit être dans le répertoire data et il faut préciser l’extension de l’image (exemple : image.png) dans le premier paramètre.

Le paramètre scale permet de modifier le nombre de chemin à supprimer dans le seam carving (valeur entre 0 et 1). 
Une valeur de 0.5 permet d’obtenir une image réduite de moitié par rapport à l’image originale.
Le booléen d’affichage permet de voir l’avancement dans l’exécution du programme (0 pour inactif et 1 pour actif). 
Il est aussi possible de lancer le programme sans paramètres mais pour cette situation nous avons fixé des valeurs arbitraires.
