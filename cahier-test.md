#Cahier de tests

##Recherche chambres

1. On demande la saisie du numéro de chambre à rechercher
 → En cas de recherche sans résultats, un message d'erreur est affiché.

2.

##Menu services

1. Accéder au menu des services → Les choix possibles sont affiché, une invite de saisie est affichée, on attend la saisie de l'utilisateur.

2. Choisir "1" ("Lire le catalogue des services") → Si existe, le fichier catalogue-services.txt est chargé en mémoire et affiché à l'écran. Si le fichier n'existe pas, un message d'erreur est affiché et le menu des services est affiché à nouveau.

3. Choisir "2" → Si des services n'existent pas, un message d'avertissement est montré, sinon ils peuvent être modifiés (titre et prix). En donnant "fin" comme titre de service, on sort et on revient au menu services.

4. Choisir "3" → On propose d'ajouter un nouveau service en saissiant d'abord son titre et puis son prix. En donnant "fin" comme titre, on sort et on revient au menu services. Les services saisis sont automatiquement sauvegardés dans le fichier catalogue avant le retour au menu.

5. Choisir "9" → On sort du menu services pour revenir au menu principal.

6. Choisir un chiffre non prévu →  Message d'erreur affiché.
