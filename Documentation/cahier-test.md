#Manuel utilisateur

##Remarques générales

Les fichiers réunis dans le dossier "1-Parametres" sont indispensables pour le fonctionnement de l'application.
Une partie d'entre eux peuvent être mis à jour, de manière automatique ou avec l'intervention de l'utilisateur. La compromission de leur intégrité peut toutefois sérieusement compromettre le bon fonctionnement de l'application.
Seule exception, le fichier programme.txt, créé de manière automatique par l'application.

L'application a une approche résiliente et conservative: les modifications sont sauvegardées dès leur effectuation afin de garantir la persistence de l'information même en cas de dysfonctionnement.
En cas d'invite de saisie montrant deux alternatives en casse différente, une minuscule, l'autre majuscule (e.g. "o/N"), l'alternative en majuscule est le choix par défaut.

Les fichiers réunis dans les dossiers "note" et "resa" contiennent les informations sur les notes ouvertes et les réservations enregistrées. Les fichiers sont supprimés automatiquement par l'application quand le client part et solde son compte. En cas d'échec, l'application invite l'utilisateur à rémédier directement à l'erreur.

##Lancement du programme

1. On demande à l'utilisateur si la date correspond bien à la date du jour. Si ce n'est pas le cas, l'utilisateur répond 'n' et on lui propose le jour d'après jusqu'à ce que la réponse soit positive ('o').

2. Ensuite, on lui demande de saisir la date du jour suivant le dernier jour au format jj/mm/aaaa.

3. Enfin, l'utilisateur doit renseigner la saison: haute (h) ou basse (b).

##Réservation
###Effectuer une réservation

1. Saisir la période.

2. Saisir le type de chambre (on peut choisir de saisir tous les paramètres ou bien de uniquement le tipe de lits et la catégorie de la chambre).

3. Affichage des chambres disponibles.

4. L'utilisateur peut choisir une chambre correspondant aux critères renseignés.
    * Choix "0" → L'utilisateur ne souhaite pas choisir une chambre parmi la sélection proposée. Retour au menu principal.
    * Autrement si l'utilisateur souhaite réserver une chambre dans la liste. Il saisit le numéro de la chambre choisie.

5. Saisir des données du client: nom, prénom, numéro de téléphone.

6. Paiement de la réservation: l'utilisateur renseigne le mode de paiement et effectue le paiement. Un message lui confirme que le paiement a bien été effectué.

7. La réservation est sauvegardée dans le dossier "resa", le nom du fichier est le numéro de réservation.

8. Modification du planning.

###Recherche d'une réservation

1. Saisir le numéro de réservation.

2. Affichage du résultat.

3. On demande à l'utilisateur s'il souhaite modifier la réservation, l'annuler ou retourner au menu principal:
 * Choix "1" → pour modifier la réservation. L'utilisateur sera guidé ensuite dans la modification selon les étapes déjà abordées pour la réservation.
 * Choix "2" → pour annuler la réservation. L'utilisateur sera ensuite guidées pour déterminer les droits au remboursement éventuel et l'effectuer.
 * Choix "3" → pour retourner au menu principal.

####Modification d'une réservation
L'utilisateur a choisi 1 dans le menu précédent.

 1. L'utilisateur peut modifier la date et la chambre de la réservation.
 On recherche si la chambre actuelle ou si une autre chambre est disponible durant la période renseignée en fonction de la modification (changement de période et/ou de chambre).

2. On affiche les résultats.

   * Choix "1" → abandon
   * Choix "2" → sélection d'une chambre parmi la liste proposée

3. L'utilisateur peut modifier les données du client, son nom, son prénom, son numéro de téléphone.

4. Modification du planning.

5. Retour au menu principal.

####Annulation d'une réservation

#####Demandée par l'hôtel

 1. L'hôtel doit entièrement rembourser le client: remboursement du montant payé à la réservation.

 2. Mise à jour du planning.

 3. Retour au menu principal.

#####Demandée par le client

 1. Comparer la date de début du séjour (déterminée grâce à la   recherche de réservation) et la date du jour.

 2.
    * Cas 1 (Différence > 14 jours) → L'annulation a bien été prise en compte. Remboursement de 70%.
    * Cas 2 (Différence > 7 jours) → L'annulation a bien été prise en compte. Remboursement de 30%.
    * Cas 3 (Différence <= 7 jours) → L'annulation a bien été prise en compte. Pas de remboursement.

 3. Mise à jour du planning.

 4. Retour au menu principal.


###Note de la chambre
 1. On demande à l'utilisateur s'il souhaite accéder à une note en saisissant son numéro de réservation ou de chambre (seulement pour les réservations en cours).
   * Choix "1" → Saisir le numéro de réservation.
   * Choix "2" → Saisir le numéro de chambre.

 2.
    * Choix "1" → Afficher la note.
    * Choix "2" → Recherche une autre note.
    * Choix "3" → Ajout d'une note.
    * Choix "4" → Régler la note (dans le cas où la note recherchée a bien été trouvée).
    * Choix "9" → Retour au menu principal.

##Chambres

###Recherche chambres

1. On demande la saisie du numéro de chambre à rechercher. En cas de recherche sans résultats, un message d'erreur est affiché. En cas de recherche avec résultat, les caractéristiques de la chambre sont affichées.

2. Suite à l'affichage, on propose à l'utilisateur de modifier les caractéristiques de la chambre avec, comme invite de saisie "(o/N)". Le choix en majuscule est le choix par défaut.
Tout autre choix que "o" ne permet pas de modification de la chambre, et l'utilisateur est redirigé vers le menu principal. En choisissant "o", l'utilisateur pourra modifier toutes les valeurs de la chambre. La valeur actuelle est affichée, on demande de saisir la nouvelle valeur. À la fin de la saisie, les nouvelles valeurs sont enregistrées et l'utilisateur est redirigé vers le menu principal.

###Déclaration de travaux

1. Saisie de la chambre.

2. Saisie de la période.
   Si la chambre est réservée alors un message d'erreur est affiché et l'utilisateur est renvoyé vers le menu principal.

3. Modification du statut de la chambre.

4. Modification du planning.

5. Confirmation et retour au menu principal.

##Paramètres

###Services

1. Accéder au menu des services → Les choix possibles sont affichés, une invite de saisie est affichée, on attend la saisie de l'utilisateur.

2. Choix "1" ("Lire le catalogue des services"). Si le fichier catalogue-services.txt existe, alors il est affiché à l'écran. Si le fichier est vide, un message d'erreur est affiché et l'utilisateur est redirgé vers le menu des services.

3. Choix "2" → Si des services n'existent pas, un message d'avertissement est montré, sinon ils peuvent être modifiés (titre et prix). En donnant "fin" comme titre de service, on sort et on revient au menu services.

4. Choix "3" → On propose d'ajouter un nouveau service en saissiant d'abord son titre et puis son prix. En donnant "fin" comme titre, on sort et on revient au menu services. Les services saisis sont automatiquement sauvegardés dans le fichier catalogue avant le retour au menu.

5. Choix "9" → On sort du menu services pour revenir au menu principal.

6. Choix d'un chiffre non prévu →  Message d'erreur affiché.

###Programme du jour

L'application affiche, s'il a été créé, le programme du jour pour l'hôtel et revient au menu principal. Le programme est créé de manière automatique au démarrage en confrontant lors de la mise à jour de la date.

###Modifier le prix des chambres

En choisissant 8, le programme offre la possibilité de changer les prix de toutes les catégories des chambres.

##Quitter le programme

1. Choix "0" dans le menu principal → "Au revoir".
