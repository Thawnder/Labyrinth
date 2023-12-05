+ Se placer à la racine du projet
+ > make  pour créer les deux exécutables.
+ > ./main  pour lancer le jeu
+ > ./test  pour lancer les tests
(remarque: erreur dans la compilation de l'exécutable test, pas corrigée à ce jour, il ne marche donc pas)
+ > make mrproper  pour effacer les fichiers objets et les exécutables à la fin de l'utilisation
+ Les fichiers .c se trouvent dans src/, les tests dans tests/, tous les headers dans include/, et les fichiers objets se génereront dans obj/. Le répertoire unity/ contient la librairie de tests utilisés pour les tests unitaires. Le fichiers tresors.txt contient le nom des 24 trésors du labyrinthe.
