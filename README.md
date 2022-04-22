# M1 Informatique - Synthèse Image 
Thomas DUMONT - Estelle GUYOT

## Compilation du projet 

Pour lancer le projet il suffit de taper la commande : `make`

Pour lancer une scène il faut taper la commande : `./<nomDeScene>`

Pour nettoyer le dossier (supprimer les *.o et les scènes) `make clean`

## Description du travail fourni

### 0. Modélisation des formes canoniques 

Nous avons réalisé les différentes canoniques demandé tels que : 
- le cube 
- la sphère 
- le cylindre 
- le tore
- le cone 

Etant parti sur des quads nous pourrions améliorer le code en utilisant des triangles, car cela réduirais la duplication de point au niveau des poles de la sphère et au centre des faces du cylindre et du cone.
