#Cahier de tests

##Lancement du programme

1. On demande à l'utilisateur si la date correspond bien à la date du jour. Si ce n'est pas le cas, l'utilisateur répond 'n' et on lui propose le jour d'après jusqu'à ce que la réponse soit positive ('o').

2. Ensuite, on lui demande de saisir la date des jours futurs au format jj/mm/aaaa.

3. Enfin, l'utilisateur doit renseigner la saison: haute (h) ou basse (b).

##Réservation
###Effectuer une réservation

(Lorsque l'utilisateur choisit d'effectuer une réservation, on charge automatiquement le fichier contenant le pris des nuitées dans un tableau.)

1. Saisir la période. Le calcul du nombre de nuitées est automatique.  

2. Saisir le type de chambre.

3. Affichage des chambres disponibles.

4. L'utilisateur peut choisir une chambre correspondant aux critères renseignés.
    * Choix "0": L'utilisateur ne souhaite pas choisir une chambre parmi la sélection proposée. Retour au menu principal.
    * Autrement si l'utilisateur souhaite réserver une chambre dans la liste. Il saisit le numéro de la chambre choisie.

5. Saisir des données du client: nom, prénom, numéro de téléphone.

6. Paiement de la réservation: l'utilisateur renseigne le mode de paiement et effectue le paiement. Un message lui confirme que le paiement a bien été effectué.

7. La réservation est sauvegardée dans le dossier "resa", le nom du fichier est le numéro de réservation.

8. Modification du planning.

###Recherche d'une réservation

1. Saisir le numéro de réservation.

2. Affichage du résultat.

3. On demande à l'utilisateur s'il souhaite modifier la réservation, l'annuler ou retourner au menu principal:
 * Choisir "1" pour modifier la réservation.
 * Choisir "2" pour annulerla réservation.
 * Choisir "3" pour retourner au menu principal.

####Modification d'une réservation

 1. Choisir "1" pour modifier la réservation. L'utilisateur peut modifier la date et la chambre de la réservation.
 On recherche si une autre chambre ou période est disponible en fonction de la modification et on affiche les résultats.
 Choix entre abandon, choix d'une chambre parmi la liste des chambres s'il y en a plusieurs, sinon possibilité de saisir directement la chambre.
 L'utilisateur peut modifier les données du client, son nom, son prénom, son numéro de téléphone.

 2. S'il y a différence négative entre le prix de la chambre initiale et celui de la nouvelle chambre, alors on demande le paiement du supplément.
 Si la modification entraine une augmentation du prix, alors le client doit payer un supplément.
 Si au contraire, la modification entraine une diminution du prix, dans le cas d'une réduction du nombre de jours, le client peut se voir rembourser une partie de la différence:
   * remboursement de 70% si l'écart entre la date du jour et la date de début de séjour est supérieur à 14 jours.
   * remboursement de 30% si l'écart entre la date du jour et la date de début de séjour est supérieur à 7 jours.
   * pas de remboursement.
 Sinon, on lui demande directement confirmation de la réservation avant le retour au menu principal.

 3. Modification du planning.

####Annulation d'une réservation

#####Demandée par le client

 1. Comparer la date de début du séjour (déterminée grâce à la   recherche de réservation) et la date du jour.

 2. * "1" (Différence > 14 jours): L'annulation a bien été prise en compte. Remboursement de 70%.
    * "2" (Différence > 7 jours): L'annulation a bien été prise en compte. Remboursement de 30%.
    * "3" (Différence <= 7 jours): L'annulation a bien été prise en compte. Pas de remboursement.

 3. Retour au menu principal.

#####Demandée par l'hôtel

 1. L'hôtel doit entièrement rembourser le client: remboursement du montant payé à la réservation.

 2. Confirmation et modification du planning.

 3. Retour au menu principal.

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

1. Accéder au menu des services → Les choix possibles sont affichés, une invite de saisie est affichée, on attend la saisie de l'utilisateur.

2. Choisir "1" ("Lire le catalogue des services"). S'il existe, le fichier catalogue-services.txt est affiché à l'écran. Si le fichier est vide, un message d'erreur est affiché et le menu des services est affiché à nouveau.

3. Choisir "2" → Si des services n'existent pas, un message d'avertissement est montré, sinon ils peuvent être modifiés (titre et prix). En donnant "fin" comme titre de service, on sort et on revient au menu services.

4. Choisir "3" → On propose d'ajouter un nouveau service en saissiant d'abord son titre et puis son prix. En donnant "fin" comme titre, on sort et on revient au menu services. Les services saisis sont automatiquement sauvegardés dans le fichier catalogue avant le retour au menu.

5. Choisir "9" → On sort du menu services pour revenir au menu principal.

6. Choisir un chiffre non prévu →  Message d'erreur affiché.

mise à jour prix
 services et chaege ds strsust elemenint et suuprimer ou meetrte ç jour ou laisser !

##Quitter le programme

1. Choix "9" dans le menu principal: "Au revoir".
