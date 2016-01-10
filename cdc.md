#INTRODUCTION

##Objet 
Ce document a pour objet de définir les exigences liées à l’application concernant la gestion d’un hôtel. 
Il est destiné à la réservation de chambres dans un hôtel pour une période définie.

##Portée
L’application consiste en la gestion d’un hôtel : 
*réservation 
*consultation des réservations, des chambres 
*modification des prix, du statut des chambres

###RÉSERVATION 
La réservation d’une chambre s’effectue par le biais de l’application. Chaque réservation a un numéro unique, concerne un client, peu importe le nombre de personnes occupant la chambre. Elle peut concerner plusieurs chambres : par conséquent, chaque chambre (numéro) liée à la réservation figure dans cette dernière. Les réservations comportent les éléments suivants : 
La réservation peut s’effectuer jusqu’à un an à partir de la date du jour. 
Chaque réservation a une date de début et une date de fin, a un coût. 

Pour résumer, une réservation comprend les données suivantes : 
*numéro de réservation
*nom du client
*prénom du client
*numéro de téléphone
*date de début 
*date de fin
*numéro de chambre (une ou plusieurs)
*prix fixe
*coût supplémentaire

###ORGANISATION 
A chaque jour l’utilisateur a accès au statut de la chambre et au code correspondant au motif en cas d’indisponibilité de la chambre. 
Motifs d’indisponibilité : 
*réservé : A
*entretien habituel : B
*travaux exceptionnels : C

###CHAMBRE 
Chaque chambre a un numéro unique se décomposant ainsi : numéro de l’étage et de la position de la chambre (ex : 101 pour la première chambre du premier étage). 
Chaque chambre a un état à un moment t. 
Pour une chambre, on a :
*numéro de la chambre
*type (simple/double)
*chambre/suite
*type de la salle de bain
*présence d’un balcon ou non
*vue ou non
*fumeur ou non
*animaux autorisés ou non

###TARIF 

#####Prix fixe – prix variable
Le montant total se décompose en un prix fixe (montant payé à la réservation par le client avant son arrivée à l’hôtel) et en un prix variable (montants supplémentaires durant le séjour, du type minibar, internet, etc.). Le prix variable a un objet et une date précise. 

####Prix chambre
Le prix de la chambre est fixe à la réservation (payé à la réservation) mais varie en fonction de la chambre. Les variables à prendre en compte sont : 
*le type de chambre
*chambre/suite
*présence d’un balcon ou non
*vue ou non

Type 	Catégorie 	Balcon 	Vue 	Prix basse saison	Prix haute saison
Simple	Chambre 	Non 	Non 	80	100
Simple	Chambre 	Oui	Non 	85	110
Simple	Chambre 	Non	Oui	85	110
Simple	Chambre 	Oui	Oui 	90	130
Simple	Suite 	Non 	Non 	100	120
Simple	Suite 	Oui	Non 	105	130
Simple	Suite 	Non	Oui	105	130
Simple	Suite 	Oui	Oui 	110	150
Double	Chambre 	Non 	Non 	120	140
Double	Chambre 	Oui	Non 	125	150
Double	Chambre 	Non	Oui	125	150
Double	Chambre 	Oui	Oui 	130	160
Double	Suite 	Non 	Non 	140	170
Double	Suite 	Oui	Non 	150	185
Double	Suite 	Non	Oui	150	185
Double	Suite 	Oui	Oui 	160	200


####Prix à la réservation : 
Le prix de la réservation est celui que doit payer le client à la réservation. Il comprend : 
*le prix de la ou des chambres réservées
*la réservation du restaurant (pour x nombre de repas):
	*menu 1 : 15€
	*menu 2 : 28€
	*menu 3 : 36€

####Prix supplémentaires : 
Chaque coût supplémentaire comporte : 
*un objet
*une date
*un montant
Les coûts supplémentaires, à payer au moment de quitter l’hôtel, peuvent être engendrés par : 
*le minibar
*internet
*le room service

####Annulation : 
En cas d’annulation de la réservation, le montant total n’est pas remboursé au client. Ce dernier se voit rembourser 70% du montant de la réservation. Si l’annulation est effectuée entre une et deux semaines avant la date de début de séjour, un remboursement de 30% est effectué. Pour une annulation la dernière semaine, aucun remboursement n’est effectué. 



##Définitions, acronymes et abréviations


##Références



##Vue d’ensemble
Le document est organisé de la manière suivante : 
*description générale
*exigences 

#DESCRIPTION GÉNÉRALE

##Environnement


##Fonctions

Les fonctions disponibles sont : 
*Effectuer une réservation
*Consulter une réservation
*Modifier une réservation
*Supprimer une réservation
*Consulter une chambre 
*Consulter un jour
*Modifier le statut d’une chambre
*Modifier le prix d’une chambre
*Modifier le prix des offres supplémentaires : minibar, internet, room service
*Modifier le prix des menus du restaurant

##Caractéristiques des utilisateurs
Il existe deux types de profils : 
*Client
*Personnel de l’hôtel

###Client
Le client ne peut qu’effectuer une réservation, la modifier ou la supprimer. 

###Personnel de l’hôtel
Un membre du personnel de l’hôtel a accès à toutes les autres fonctions. Pour rappel, il s’agit de la: 
*Consultation d’une réservation, d’une chambre, d’un jour
*Modification du statut d’une chambre, du prix d’une chambre, du prix des offres supplémentaires, du prix des menus du restaurant

##Contraintes
Il faut prendre en compte la gestion du restaurant et les éventuels travaux de l’hôtel. 
Hypothèses et dépendances
On suppose que l’on fait confiance au client : lorsqu’on demande au client s’il est client ou membre du personnel, il répondra « client ». 

Si des prix sont modifiés après réservation des chambres, aucun frais supplémentaire ne peut être demandé au client. 

Lorsqu’une chambre est réservée à une date donnée, son statut n’est plus modifiable sauf pour cause de travaux exceptionnels (code C), par exemple s’il y a une fuite d’eau ou tout autre type d’incidents empêchant au client d’accéder à sa chambre. 

#EXIGENCES SPECIFIQUES

##Exigences fonctionnelles


##Exigences non fonctionnelles
L’application doit fonctionner avec Linux. 

