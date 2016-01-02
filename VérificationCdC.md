##Version corrigée

1. Le système doit permettre la réservation de chambres d'hôtel pour plusieurs stations chacune
ayant plusieurs hôtels.

2.h Le système doit utiliser la codification des hôtels déjà existante et référencer leurs chambres par leurs numéros.

3.  Le système ne doit accepter que des demandes qui portent sur une période unique.
3.1 Lorsque la demande est faite par une personne non présente dans la base de données cliens, le système doit demander les informations suivantes:

  * nom, prénom
  * adresse mél
  * numéro de téléphone
  * numéro de carte de crédit, type de carte, date d'expiration
  * période de réservation (entendue comme continue)
  * nombre de chambres
  * catégorie d'hôtel
  * station désirée

3.3 Si la personne est présente dans la base, le système doit proposer automatiquement les informations suivantes

  * nom, prénom
  * adresse
  * numéro de téléphone
  * numéro de carte de crédit, type de carte, date d'expiration

Permettre qu'elles soient modifiées et demander les informations suivantes:

  * période de réservation (entendue comme continue)
  * nombre de chambres
  * catégorie d'hôtel
  * station désirée

*Critères de vérification*:

  1. Impossibilité de faire une demande sans renseigner les informations obligatoires; possibilité de renseigner les informations complémentaires.
  2. Lorsque le nom et le prénom saisis correspondent à un client présent dans la base de données


4. Le système doit affecter un numéro d'ordre unique à chaque demande.

*Critère de vérification*: présence d'un numéro d'ordre pour chaque démande.

6. Le système doit contrôler que les chambres du type et nombre demandés sont disponibles pour la période indiquée. En cas de disponibilité, le système signale la possibilité d'effectuer la réservation.

*Critère de vérification*: une réservation doit être évaluée comme possible uniquement en cas de disponibilité des solutions requises (chambres -type et nombre-, catégorie d'hôtel et période).

7. Le système doit pouvoir mettre une demande en attente.

*Critère de vérification*: Il est possible de consulter une demande de réservation qui n'a pas été confirmée, mais qui a été mise en attente.

8. S'il est possible de satisfaire la demande, et si le client n'est pas déjà présent dans la base, le système doit introduire dans la base de données ces informations du nouveau client:

  * nom, prénom
  * adresse mél
  * numéro de téléphone

Le système doit marquer les chambres concernées par la demande comme occupées.

Le système doit envoyer automatiquement un courriel de confirmation au client contenant les dates de début et de fin du séjour, le montant total.

*Critères de vérification*:

  * Un nouveau client doit être présent dans la base de données après l'acceptation d'une demande.
  * Une chambre concernée par une réservation doit être marquée comme non disponibile.
  * Pour une réservation effectuée par un client déjà présent dans la base de données, les informations sont gardées inchangées. Elles sont mises à jour en cas de changements.

9. Le système ne doit pas effectuer de prélèvement en cas d'annulation de réservation ayant lieu au plus tard le matin, 7 jours calendaires avant le début du séjour.

*Critère de vérification*: Pour une réservation à partir du 7 du mois, en cas d'annulation le dernier jour du mois précédent à midi, aucun prélèvement n'aura lieu. Toute annulation avant ne donnera lieu à prélèvement non plus.

10. En cas d'annullation parvenant après le délai défini dans l'exigence n.9, le système doit débiter la carte bancaire du client de 75% du prix de la réservation.

*Critère de vérification*: Pour une réservation à partir du 7 du mois, en cas d'annulation le dernier jour du mois précédent l'après-midi, le 75% du prix de la réservation sera prélevé, ainsi qu'en cas de toute annulation postérieure.
