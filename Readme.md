# ARCADE
___
## Compilation et exécution

Pour compiler le projet, vous devez exécuter le script `build.sh` à la racine du projet. Ce script se charge de créer le répertoire de build si nécessaire, d'exécuter CMake pour générer les fichiers de build, et enfin de lancer la commande `make` pour compiler le projet.

```bash
./build.sh
```

Une fois la compilation terminée, vous pouvez lancer le jeu en utilisant l'exécutable `arcade` généré. Vous devez fournir le chemin vers une des bibliothèques graphiques disponibles en argument. Par exemple, pour lancer le jeu avec la bibliothèque SFML, vous pouvez utiliser la commande suivante :

```bash
./arcade lib/lib_arcade_sfml.so
```

Remplacez `lib/lib_arcade_sfml.so` par le chemin vers la bibliothèque graphique que vous souhaitez utiliser. Les bibliothèques graphiques disponibles sont `lib_arcade_sfml.so`, `lib_arcade_ncurses.so` et `lib_arcade_sdl2.so` (ou tout autre librairies implentant l'interface IDisplay).

Veuillez noter que le chemin vers la bibliothèque graphique peut varier en fonction de l'endroit où vous exécutez la commande.
___
## Commandes de jeu

Voici un tableau qui résume les commandes du jeu et l'action associée à chaque touche :

| Touche | Action |
| --- | --- |
| `Escape` | Quitter le jeu |
| `Up` | Déplacer vers le haut dans le jeu |
| `Down` | Déplacer vers le bas dans le jeu |
| `Left` | Déplacer vers la gauche dans le jeu |
| `Right` | Déplacer vers la droite dans le jeu |
| `Space` | Tirer dans le jeu |
| `F1` | Passer au jeu précédent |
| `F2` | Passer au jeu suivant |
| `F3` | Passer à la bibliothèque précédente |
| `F4` | Passer à la bibliothèque suivante |
| `F5` | Redémarrer le jeu |
| `F8` | Ouvrir le menu |
| `F10` | Rafraîchir |
| `Enter` | Entrer |
| `BackSpace` | Effacer |

Veuillez noter que ces commandes peuvent varier en fonction de la configuration de la librairie utilisée.
Les commande ici présente sont valable uniquement pour les librairies fournie avec le projet.
___
## Jeux disponibles

- Snake
- Nibbler
___
## Bibliothèques graphiques disponibles

- SFML
- NCurses
- SDL2
___
## Contributeurs
| Nom du contributeur   | Rôle du contributeur | github du contributeur                             |
|-----------------------| --- |----------------------------------------------------|
| Justine **Loizel**    | Developpeur | [@justineloizel](https://github.com/justineloizel) |
| Ewen **Emeraud**      | Developpeur | [@ ewen1507](https://github.com/ewen1507)          |
| Tom **Lefoix**        | Developpeur | [@tlm25](https://github.com/tlmx25)                |
