#Questions

##Définition de l'application

* S'agit-il d'une application pour la réservation dans un hôtel, une chaîne d'hôtels, une aire géographique comprenant plusieurs établissements? S'il ne s'agit pas d'un seul hôtel, une liste des établissements est nécessaire.

**Un seul hôtel**

* Le texte de l'application doit-il être en français?

**Oui**

* Est-il nécessaire d'envoyer une confirmation au client lorsque la réservation est effectuée ? De quel type.

**Non**

* Le logiciel doit-il gérer uniquement les réservations ou bien le paiement également? Est-ce qu'il y a une application consacrée au paiement qui prend la suite? Si c'est le cas est-ce qu'il y a des contraintes dans le format de données que l'application de facturation prend en input? Le logiciel doit-il fournir à l'application pour le paiement uniquement les données qui concernent la réservation ou bien également les autres services demandés par le client au cours de son séjour?

**Le paiement est simulé, et les données de paiement sont conservées dans un fichier. On suppose que le paiement sera toujours effectué.**

* Faut-il gérer le personnel, avec une liste du personnel par exemple ?

**Non**

* L'application prendra en compte la possible indisponibilité de certaines chambres à cause de travaux d'entretiens. Ces travaux pourront être indiqués de manière ponctuelle. En plus de cela, faut-il que l'application prenne en charge des travaux d'entretien extraordinaire (peinture, changement de mobilier, réaménagement) prévus selon un calendrier? Si oui, comment est-il structuré?

**Il faut prévoir la possibilité de rendre indisponible une chambre de telle à telle date. Le motif sera une information textuelle supplémentaire.**

##Définition de l'hôtel

* Quelle est la numérotation des chambres, comment l'hôtel est-il fait, un seul bâtiment ou plusieurs (cas dans lequel un même numéro de chambre pourrait exister dans plusieurs bâtiments)? Une liste des chambres est nécessaire.

**A VOUS DE VOIR. Définissez une numérotation type. Comme 1xx pour le premier étage, 2xx pour le deuxième étage, etc... Avec un seul bâtiment (mais plusieurs ne changerait pas le problème puisque c'est le numéro de la chambre qui est l'identifiant de la chambre)**

* Catégorie de l'hôtel?

**De 1 a 3 étoiles à fixer. Cela impacte les tarifs seulement.**

* Quelles catégories de chambres sont présentes (simple, double, triple...; chambre/suite; avec vue; avec balcon; avec salle de bain/salle de douche)?

**OUI avec tous ces critères. Il faut donc prévoir une structure de données permettant d'avoir ces informations. Ainsi le client pourrait demander une chambre avec bain, ou avec un balcon.**

* Y a-t-il des distinctions notables parmi les chambres (fumeur/non fumeur; animaux acceptés/non acceptés)?

**OUI.**

* L'hôtel offre-t-il des services supplémentaires? (Chauffeur/voiturier, , repassage, excursion, garderie, room service, minibar, fax, internet, d'autres...) Lesquels parmi ces services sont-ils payants?

**Le minimum. Minibar, internet, room service.**


##Tarif et cetera

* Comment est établi le prix des chambres, quelles sont les périodes (haute saison/mi-saison/basse saison)?

**A VOUS DE LE DEFINIR**

* Y a-t-il une distinction entre différents canaux par lesquels vient une réservation (client, agence, site)? Laquelle?

**A VOUS DE VOIR. Soit un seul tarif, soit un tarif avec un pourcentage de réduction si accès via agence ou internet.**

* Quelles sont les modalités de séjour prévues (petit déjeuner non inclus/inclus/demi-pension/pension complète)? Comment est calculé leur prix?

**Faisons simple. Pas de petit déjeuner, pas de demie-penseion. Mais il y a un restaurant. Donc le petit déjeuner est en plus (tarif forfaitaire), et le restaurant aussi (tarif a 3 menus par exemple).**

* Y a-t-il des réductions pour plusieurs nuits/chambres/personnes? Si oui, selon quel schéma?

**NON**

* Concernant les chambres doubles: faut-il prendre en compte usage individuel / double?

**NON**

* Quelles sont les règles pour l'annulation (sans retenue/avec, combien, en fonction de quels délais) ?

**Prenez une règle assez classique comme : Pas de remboursement pour annulation la dernière semaine. Remboursement de 30% entre 1 entre 2 semaines. Remboursement de 70% sinon.**

* Quelles règles pour le paiement (à l'avance, à l'arrivée, au départ, une caution doit-elle être versée)? Quels moyens de paiement sont acceptés?

**Paiement à la réservation.**

* Quand sont la haute et la basse saison? (Si l'hôtel se situe en France, se caler sur les vacances des trois zones? prendre en compte les weekends prolongés dus aux jours fériés?)

**Hotel en France. Saison haute : période de vacances . Saison basse sinon.**

* Si l'hôtel se situe à l'étranger, taxe de séjour (par personne)?

* Baisse des prix pour atteindre un taux maximum de remplissage?

**NON**

##Définition du restaurant

Lors de la présentation des sujets vous aviez dit que l'établissement inclut également un restaurant.

* L'accès au restaurant est-il possible même sans le forfait, et si c'est le cas, est-ce que la note est mise sur le compte de la chambre ou bien elle est réglée sur le moment?

**Uniquement aux clients de l'hôtel. 3 menus donc 3 prix. La note est mise sur le compte de la chambre. A régler au moment du départ avec minibar, etc.**

* Faut-il gérer le planning des tables?

**NON**

* Quelles options tarifaires (buffet, menu, à la carte)?

**3 menus donc 3 prix**

* En cas de tarifs tels que demi-pension ou pension complète, quel est le forfait du restaurant inclus, et quelles sont les options tarifaires à appliquer pour ce qui n'est pas inclus dans le forfait?

**Pas de demi-pension ni de pension complète.**

##Traitement des réservations

* Est-il nécessaire de mettre en attente les demandes qui ne peuvent être satisfaites?
**NON**
Ou bien les demandes sont prises et enregistrées tout de suite si elles peuvent être satisfaites, rejetées si elles ne peuvent pas être satisfaites?
**OUI**
Si mise en attente il y a, quels sont les détails des règles de la mise en attente (pour combien de jours les demandes restent en attente, passage en réservation automatique ou après confirmation du client, fréquence du contrôle)?

* Existe-t-il une base de clients?
**NON**
Quelles informations contient-elle? Faut-il permettre de sélectionner parmi les clients passés pour attribuer une réservation à une personne?
**Par contre il faut dans la réservation conserver les informations du client et son contact (N° téléphone).**

* Quelles informations sur le client sont nécessaires (
  **Nom, Prénom, contact (N° téléphone)**
-quel type-, date de naissance, pièce d'identité, carte de crédit), et à quel moment (
**réservation**
, arrivée) ?

* Est-il nécessaire de garder trace des réservations annulées?

**NON**

* Sur quelle période les réservations sont-elles ouvertes (un an, dix-huit mois, deux ans...)?

**Un an**

* Comment faut-il prendre en compte la modification de statut d’une chambre, par exemple pour cause de travaux exceptionnels alors que la réservation a déjà été effectuée? Cela impliquerait de demander au client s’il souhaite changer de chambre (dans le cas d’une chambre moins bien classée par exemple, ainsi qu’un remboursement partiel du prix qu’il a payé)

**Si la chambre ne peut plus être louée du fait de travaux, non prévue, ou fuite d’eau ou …
on propose soit une annulation et remboursement
soit un changement de chambre identique ou surclassée**
