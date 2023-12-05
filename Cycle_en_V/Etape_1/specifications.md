On doit implémenter un programme qui va permettre à un maximum de 4 joueurs/IA de jouer au jeu du Labyrinthe.
Pour ce faire, nous devons résoudre plusieurs sous-problèmes:

- ### Identifier les joueurs  
    - Qui sont-ils?
        - Donner la possibilité aux joueurs de choisir leur pseudo
        - Donner la possibilité aux joueurs de choisir leur couleur
            - Changer la couleur d'une écriture.
            #
    - Combien d'humains / Combien d'IA ?
        - Programmer une IA
            - Faire en sorte qu'elle puisse jouer comme un joueur humain, qu'elle ne soit ni stupide ni infallible
                - Regarder si de là où elle est, l'IA peut atteindre son trésor
                - Elle ne bougera une case que si ça lui ouvre un chemin pour déplacer son pion d'au moins une case, et si ce n'est pas possible, chercher à embêter les autres joueurs
                    - Regarder si, quand on bouge une ligne à proximité de l'IA, ça lui libère un chemin
                    - Boucher le chemin, si c'est possible d'un autre joueur
                        - Regarder, si en bougeant une  ligne, le chemin du joueur sera bouché
                    - Un autre joueur a-t-il un chemin ouvert pour son trésor?(qui est connu on le rappelle)
                    #
    - Assigner un pion à chaque joueur(pseudo, couleur...)
    - Répartir équitablement et aléatoirement la liste des trésors entre chaque joueurs
        - Trier un tableau de façon aléatoire
        #

- ### Créer le plateau
    - Placer aléatoirement les cases (chemin, trésor)
        - Définir tous les différents types de cases
            - Définir une case
            - Créer les trésors
    - Permettre à 12 lignes uniquement de se déplacer
#
- ### Jouer un tour
    - Afficher le plateau
        - Afficher le plateau avec ses cases fixes
        - Afficher les flèches autour du plateau avec leur numéro
        - Afficher une ligne de cases mouvantes
            - Afficher une case
                - Afficher un trésor sur une case
                - Afficher une case de sorte à ce qu'on reconnaisse quel type de case c'est, où sont les murs
                - Afficher un pion sur une case
        - Afficher la case temporaire à coté du plateau
        - Si on peut, décaler la ligne d'un cran
            - Regarder si la ligne qu'on veut décaler est une des 12 lignes décalable
            - Regarder si la ligne qu'on veut décaler à été décalée juste avant dans le sens inverse
                - Garder en mémoire la dernière ligne décalée et dans quel sens elle l'a été
            - Insérer la case temporaire dans le plateau pour remplir la ligne
            - La case à la fin de la ligne devient la nouvelle case temporaire
            - Si un ou plusieurs pions sont sur la case qui sort, alors ils sont placés sur la case qui vient de rentrer
    - Permettre ou non au pion de se déplacer
        - Le pion peut-il se déplacer à l'endroit voulu par le joueur?
            - Existe-il un chemin?
                - Lier toutes les cases compatibles pour créer un chemin
    - Afficher la manipulation effectuée par le joueur({nom du joueur} a déplacé son pion en...)
    - Regarder si on est sur une case trésor
    - Passer au trésor suivant quand on atteind
        - Arrivé au dernier trésor, le nouvel objectif est le point de spawn(un des 4 coins de l'écran)
#
- ### Stopper la partie lorsqu'un joueur a gagné
    - Regarder si un joueur a gagné à la fin du tour
        - Regarder si la pile de trésors d'un joueur est vide et si il est placé sur sa case de départ
    - Afficher un message en conséquense
        - Regarder quel joueur a gagné
