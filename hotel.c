/*#########################################################################
#                                                                         #
#                                  hotel.c                                #
#                                                                         #
###########################################################################

* v 0.0   - 2016-01-31 squelette du main
* v 0.0.1 - 2016-02-02 ajout de l'option '6 - Modifier le catalogue des services.'
* v 0.0.2 - 2016-02-03 procédure mauvais_choix, procédure catalogue_services_menu
* v 0.0.2 - 2016-02-03 Saisie et enregistrement du catalogue des services
* v 0.1.0 - 2016-02-03 Sous-menu pour les services complet
* v 0.1.1 - 2016-02-04 On s'attaque aux chambres
* v 0.1.1 - 2016-02-04 Ebauches pour la réservation
* v 0.1.2 - 2016-02-05 Modification des chambres presque fonctionnelle
* v 0.1.3 - 2016-02-06 Modification et enregistrement fonctionnels. À optimiser
* v 0.1.4 - 2016-02-07 Chargement et mise à jour du calendrier

Reste à faire:
* optimiser enregistrement sur fichier et cycle de modification des chambres.
* Traiter des chaînes de caractères avec espaces.
* optimiser affichage et saisie des descripteurs des chambres.
* évaluer la possibilité de déclarer les variables de choix (vue/sans vue; fumeur/non fumeur; haute saison/basse saison) comme des short int;
* tests.
* void lecture_jours() à améliorer pour récomposer la date en format jj/mm/aaaa (cf numsecsoc de JM Léry)
* maj_calendrier() ajouter: tests sur les valeurs saisies et conversion aaaammjj en jj/mm/aaaa

*/

#include <stdio.h>
#include <string.h>

/*Constantes*/

#define MAX_CAT_SERV 20    /* Constante qui limite le catalogue des services -- ajouter un test concernant cette limite - Utilisé pour catalogue_services */
#define MAX_NOM_SERVICE 21 /* Taille maximale de la chaîne de caractères qui décrit les services complémentaires - Utilisé pour nom_service */
#define MAX_NB_CHAMBRES 50 /*Utilisée dans tab_chambres[]*/
#define NON_TROUVE -1 /*Pour tester si un résultat a été trouvé à la recherche*/
#define ANNEE 365 /* Utilisée pour dimensionner le planning et le calendrier*/

/*Fichiers*/

#define CALENDRIER "calendrier.txt" /*Nom du fichier contentant le calendrier (dates et saison)*/
#define CHAMBRES  "chambres.txt" /*Nom du fichier contentant les chambres*/
#define PLANNING "planning.txt" /*Nom du fichier contenant le planning*/


/*Déclarations préliminaires*/
/*D'utilité générale*/

void mauvais_choix(int par_choisi)   ; /* Mauvais choix à l'intérieur des menus*/
long int jjmmaaaa_vers_aaaammjj(int j, int m, int a); /*Prendre une date saisie et la traduire en lonf int date*/


/*Calendrier*/
void lecture_jours() ; /* Prend les jours présents dans le fichier qui tient conte des jours (et saison) et les charge dans le tableau correspondant.*/
void test_date()     ; /* Vérifie si la date du jour d'aujourd'hui correspond au premier jour dans le tableau et dans le calendrier. Si la date a changé, déclanche la mise à jour dans les deux.*/
void maj_calendrier(int i); /*mise à jour*/

/*Chambres*/
int rech_chambre(int chambre_rech);
void chargement_chambres()        ;
void modification_chambre(int res_chambre);
void enreg_chambre()              ;
void affichage_chambre()          ;

/*Planning*/
void chargement_planning();


/*Réservations*/
void creer_reservation()             ;
void cible_date()                    ;
void cible_chambre()                 ;

/*Gestion des services complémentaires*/
void catalogue_services_menu()       ; /* Menu qui montre les choix possibles pour le catalogue de services*/
void chargement_catalogue_services() ; /* Prend le fichier des services et le charge en mémoire (dans un tableau). Procédure transparente*/
void affichage_catalogue()           ; /* Montre le tableau de services*/
void saisie_services()               ; /* Pour saisir de nouveaux services, à la suite de ceux déjà listés*/
void enreg_catalogue_services()      ; /* Sauvegarde le tableau chargé en mémoire dans un fichier*/
void modif_services()                ; /* Pour modifier les services déjà listés*/

/*Variables globales*/

char poubelle           ; /*pour vider le buffer des \n*/

/*Calendrier*/
struct jour
{
  long unsigned int date ; /*date aaaammjj*/
  short int saison    ; /*0 basse saison, 1 haute saison*/
};

struct jour calendrier[ANNEE];

/*Planning*/

long unsigned int planning[MAX_NB_CHAMBRES][ANNEE]; /*Les valeurs dans ce tableau sont les codes de réservation. 0 est utilisé pour signaler que la chambre est libre; 1 pour déclarer des travaux.*/

/*Réservations*/

struct resa
{
  long unsigned int code_resa    ; /*long unsigned int, cela en garantit l'unicité sur une période assez longue.*/
  int datearrivee       ;
  int datedepart        ;
  char nomclient[50]    ;
  char prenomclient[50] ;
  char telclient[13]    ;  /*+33653332003 qui peut être affiché +33 6 53 33 20 03. Vérifier de quelle taille doit être le numéro: 12?*/
};

struct cha
{  /* structure pour les chambres*/
   /*l'idéntifiant unique de la chambre est son indice dans le tableau des chambres, qui correspond également à l'indice dans le planning, cela permet de relier les deux informations*/
  int num_chambre         ; /* Numéro selon la codification de l'hôtel */
  int type_chambre        ; /* 0 simple ; 1 double */
  int categorie_chambre   ; /* 0 chambre ; 1 suite */
  int type_lits           ; /* 0 simple ; 1 deux lits simples; 2 double */
  int balcon              ; /* 0 pas de balcon; 1 avec balcon */
  int vue                 ; /* 0 pas de vue; 1 avec vue */
  int bain                ; /* 0 baignoire; 1 douche */
  int fumeur              ; /* 0 non fumeur, 1 fumeur */
  int animaux             ; /* 0 pas d'animaux, 1 animaux acceptés */
  /*champ remarques en chaîne de caractères*/
};
  /* Variables globales concernant les chambres*/
struct cha tab_chambres[MAX_NB_CHAMBRES]; /*Tableau listant les chambres*/
struct cha chambre                      ;

int a_sauv_chambre = 0                  ; /*pour la modification des chambres*/

  /* Variables globales concernant les frais*/
struct frais
{
  int datefrais        ; /*autrement on en fera une string de 9, 'aaaammjj' (8) + '\0'*/
  float montantfrais   ;
  int codefrais[200]   ;
};


  /* Variables globales concernant le catalogue_services*/

int sauv_catalogue_services = 0 ; /* Test. 1 : tableau à sauvegarder; 0 non.*/
int nb_services = 0             ; /* Pour garder trace du nombre de services déjà saisis*/

struct entree_service /* Modèle du service additionnel*/
{
  char  nom_service[MAX_NOM_SERVICE]  ;
  float prix_service                  ;
};
struct entree_service catalogue_services[MAX_CAT_SERV] ;  /* Tableau listant les services*/


/*############################################
#                                            #
#                    main                    #
#       #############################        #
#                                            #
#                                            #
#                                            #
##############################################
*/

main()
{
  int choix = 0         ; /* Déclaration de la variable et initialisation à une valeur qui permet de rentrer dans le 'while'. */
  int res_chambre = 0   ; /*Résultat recherche chambres */
  int chambre_cible = 0 ; /*Chambre recherchée*/
  char choix_modif      ;

  lecture_jours()       ;
  test_date()           ;
  chargement_chambres() ;
  chargement_planning() ;
  printf("\n\nBienvenue dans le programme de gestion des réservations.\n\n") ;
  while(choix != 9) /* 9 est la valeur pour quitter. */
  {

    printf("Voici les actions possibles:\n")               ;
    printf("------------------------------------------\n") ;
    printf("   RÉSERVATIONS    \n\n")                      ;
    printf("1 - Effectuer une réservation\n")              ;
    printf("2 - Rechercher une réservation\n\n")           ;
    printf("------------------------------------------\n") ;
    printf("     CHAMBRES      \n\n")                      ;
    printf("3 - Déclarer des travaux dans une chambre.\n") ;
    printf("4 - Rechercher une chambre.\n\n")              ;
    printf("------------------------------------------\n") ;
    printf("     PARAMÈTRES    \n\n")                      ;
    printf("5 - Mettre à jour la date du planning.\n")     ;
    printf("6 - Catalogue des services.\n\n")              ;
    printf("------------------------------------------\n") ;
    printf("     QUITTER    \n\n")                         ;
    printf("9 - Quitter l'application.\n")                 ;
    /*printf("7 - Imprimer le programme d'aujourd'hui.\n") ; On ne l'a pas mis dans le planning, mais c'est une idée dont on avait parlé. On verra plus tard si et comment le faire.*/
    printf("-------------------\n")                        ;

    printf("Faire un choix : ")                            ;
    scanf("%d", &choix)                                    ; /* Attention, à partir de ce moment il y a un '\n' qui traîne dans le buffer. */

    switch(choix)
    {
      case 1: case 2: case 3:
        printf("C'est une fonction qui n'a pas encore été développée. Les auteurs sont des fainéants!\n") ;
        break                                                                                             ;
      case 4:
        printf("Entrez le numéro de la chambre à rechercher: ") ;
        scanf("%d", &chambre_cible)                             ;
        res_chambre=rech_chambre(chambre_cible)                 ;
        if(res_chambre == NON_TROUVE)
        {
          printf("%d n'a pas été trouvé.\n", chambre_cible)     ;
        }
        else
        {
          chambre=tab_chambres[res_chambre]                     ;
          affichage_chambre()                                   ;
          printf("Voulez-vous modifier la chambre (o/N) ? ")    ;
          while((poubelle=getchar()) != '\n')                   ;
          scanf("%c", &choix_modif)                             ;
          if (choix_modif == 'o')
          {
            modification_chambre(res_chambre);

          }
          printf("Retour au menu.\n");
          enreg_chambre()            ;

        }
        break                                                                                             ;
      case 5: /*case 7:*/
        printf("C'est une fonction qui n'a pas encore été développée. Les auteurs sont des fainéants!\n") ;
        break                                                                                             ;
      case 6:
        catalogue_services_menu()                                                                         ;
        break                                                                                             ;
      case 9:
        printf("Vous avez choisi de quitter l'application.\nMerci et au revoir.\n")                       ;
        break                                                                                             ;
      default:
        mauvais_choix(choix)                                                                              ;
        break                                                                                             ;
    }
  }
}

/*############################################
#                                            #
#             mauvais_choix                  #
#                                            #
##############################################

Fonction appelée par les menus de choix.
Elle signale à l'utilisateur que le choix fait n'est pas disponible.
Elle reçoit un paramètre pour signaler quel est le choix qui a été fait.

*/
void mauvais_choix(int par_choix)
{
  printf("Vous avez sélectionné %d : ce choix n'est pas disponible. Veuillez ressaisir.\n", par_choix);
}

/*############################################
#                                            #
#          jjmmaaaa_vers_aaaammjj            #
#                                            #
##############################################

Pour traduire ce qui est saisi dans le format convenable pour le stocker.
*/

long int jjmmaaaa_vers_aaaammjj(int j, int m, int a)
{
  return (a * 10000) + (m * 100) + j ;
}


/*############################################
#                                            #
#                PARTIE JOURS                #
#        #############################       #
#                                            #
#               lecture_jours                #
#                                            #
##############################################
Prend les jours présents dans le fichier qui tient conte des jours (et saison) et les charge dans le tableau correspondant.
*/

void lecture_jours()
{
  FILE *f1                    ;
  int i                       ;

  f1 = fopen(CALENDRIER, "r") ;
  for(i=0 ; i < ANNEE ; i++)
  {
    fscanf(f1, "%lu %hd", &calendrier[i].date, &calendrier[i].saison) ;
  }
}

/*############################################
#                                            #
#                test_date                   #
#                                            #
##############################################
Vérifie si la date du jour d'aujourd'hui correspond au premier jour dans le tableau et dans le calendrier. Si la date a changé, déclanche la mise à jour dans les deux.
*/

void test_date()
{
  char choix_date = 'f' ;
  int i = 0             ;

  while(choix_date != 'o')
  {
    printf("Test des paramètres\n") ;
    printf("Aujourd'hui nous sommes le %lu (o/n) ? ", calendrier[i].date) ;
    scanf("%c", &choix_date)        ;
    if(choix_date != 'o')
    {
      if(choix_date == 'n')
      {
        i++ ;
      }
      else
      {
        printf("Choix non accepté. Les choix possibles sont 'o' pour 'oui' ou 'n' pour 'non'.\n") ;
      }
    }
  }
  if (i != 0)
  {
    maj_calendrier(i) ;
  }
}

/*############################################
#                                            #
#             maj_calendrier                 #
#                                            #
##############################################

Mise à jour du calendrier déclenchée par le test sur la date courante.

*/
void maj_calendrier(int i)
{
  FILE *f1                         ;
  int j                            ;
  char choix_saison = 'a'          ;

  for(j = i; j < ANNEE; j++) /* déplacer les valeurs des jours dans le calendrier: LE FUTUR C'EST MAINTENANT!*/
  {
    calendrier[j-i] = calendrier[j] ;
  }
  for(j = ANNEE - i; j < ANNEE ; j++) /*créer les cases qui manquent: MORE FUTURE (slogan anti-punk)*/
  {
    printf("Quel jour vient après le %lu (format aaaammjj) ?", calendrier[j-1].date) ;
    scanf("%lu", &calendrier[j].date)       ;
    while((choix_saison != 'b') || (choix_saison != 'h'))
    printf("Quelle est sa saison (b/h) ?")  ;
    while((poubelle=getchar()) != '\n')     ;
    scanf("%c", &choix_saison)              ;
    if(choix_saison == 'b')
    {
      calendrier[j].saison = 0              ;
    }
    else
    if(choix_saison == 'h')
      {
        calendrier[j].saison = 1            ;
      }
      else
      {
        printf("Le choix n'est pas valide") ;
      }
  }
  f1 = fopen(CALENDRIER, "w")               ;
  for(j = 0 ; j < ANNEE ; j++) /*jsuqu'à la fin du tableau*/
  {
    fprintf(f1, "%lu %d\n", calendrier[j].date, calendrier[j].saison) ;
  }
  fclose(f1)                                ;
}


/*############################################
#                                            #
#               PARTIE PLANNING              #
#       #############################        #
#                                            #
#            chargement_planning             #
#                                            #
##############################################

*/

void chargement_planning()
{
  FILE *f1                              ;
  int i, j                              ;
  f1 = fopen(PLANNING, "r")             ;
  for(i = 0 ; i < MAX_NB_CHAMBRES ; i++)
  {
    for(j = 0 ; j < ANNEE ; j++)
    {
      fscanf(f1, "%lu", &planning[i][j]) ;
    }
  }
  fclose(f1)                            ;
}

/*############################################
#                                            #
#             PARTIE RESERVATIONS            #
#       #############################        #
#                                            #
#             creer_reservation              #
#                                            #
##############################################

Procédure pour créer une réservation.


*//*pour l'instant cela ne peut pas marcher
void creer_reservation()
{
  cible_date()    ;
  cible_chambre() ;
  rech_periode(date_debut, date_fin ) ;
  continue_resa = choix_chambre() ; /*À voir si choix chambre récupère des arguments ou bien si rech_periode affecte des variables globales*//*
  if(continue_resa)
  {
    saisie_client();
    paiement_resa();
    maj_planning   ;
  }
}

/*############################################
#                                            #
#                cible_date                  #
#                                            #
##############################################

Procédure pour saisir une date.


*//*ça ne peut pas marcher pour le moment
void /*à voir: affecte des variables globales? saisie_date()
{
  printf("Saisir la date de début (jj/mm/aaaa) : ")         ;
  scanf("%d/%d/%d\n", &jour_debut, &mois_debut, &annee_debut)  ;
  printf("Saisir la date de fin (jj/mm/aaaa) : ")           ;
  scanf("%d/%d/%d\n", &jour_fin, &mois_fin, &annee_fin)        ;
}*/

/*############################################
#                                            #
#              cible_chambre                 #
#                                            #
##############################################

Procédure pour déterminer quelle chambre recherche le client.

*//*
void cible_chambre()
{
  int cible_type_chambre; 1 simple, 2 double, 3 triple
  int cible_lits        ; 1 lit simple, 2 deux lits simples, 3 lit double, 4 trois lits simples, 5 lit simple et lit double
  int cible_cat_chambre ; 0 chambre, 1 suite
  int cible_balcon      ; 0 indifférent, 1 balcon, 2 pas de balcon
  int cible_vue         ; 0 indifférent, 1 vue, 2 pas de vue
  int cible_bain        ; 0 indifférent, 1 douche, 2 baignoire
  int cible_fumeur      ; 0 indifférent, 1 fumeur, 2 non fumeur
  int cible_animaux     ; 0 indifférent, 1 animaux acceptés, 2 pas d'animaux
  printf("Quel type de lits ?\n")               ;
  printf("1 - un lit simple\n")                 ;
  printf("2 - deux lits simples\n")             ;
  printf("3 - un lit double\n")                 ;
  printf("2 - trois lits simples\n")            ;
  printf("3 - un lit double et un lit simple\n");
  printf("Saisir le type de lits :")            ;
  scanf("%d", &cible_lits)                      ;
  printf("Quelle catégorie de chambre ? \n")    ;
  printf("0 - chambre\n")                       ;
  printf("1 - suite\n")                         ;
  printf("Saisir la catégorie :")               ;
  scanf("%d", &cible_cat_chambre)               ;
  printf("Chambre avec balcon ? ")              ;
  printf("0 - indifférent\n")                   ;
  printf("1 - balcon\n")                        ;
  printf("2 - pas de balcon\n")                 ;
  printf("Balcon :")                            ;
  scanf("%d", &cible_balcon)                    ;
  printf("Chambre avec vue ? ")                 ;
  scanf("%d", &cible_vue)                       ;
  printf("Quel type de salle de bain ?")        ;
  printf("0 - indifférent\n")                   ;
  printf("1 - douche\n")                        ;
  printf("2 - baignoire\n")                     ;
  printf("Saisir le type de salle de bain :")   ;
  scanf("%d", &cible_bain)                      ;
  printf("Chambre avec vue ? ")                 ;
  printf("0 - indifférent\n")                   ;
  printf("1 - vue\n")                           ;
  printf("2 - pas de vue\n")                    ;
  printf("Vue :")                               ;
  scanf("%d", &cible_vue)                       ;
  printf("Chambre "fumeur" ? ")                 ;
  printf("0 - indifférent\n")                   ;
  printf("1 - fumeur\n")                        ;
  printf("2 - non fumeur\n")                    ;
  printf("Fumeur :")                            ;
  scanf("%d", &cible_fumeur)                    ;
  printf("Chambre avec animaux autorisés? ")    ;
  printf("0 - indifférent\n")                   ;
  printf("1 - animaux autorisés\n")             ;
  printf("2 - animaux non autorisés\n")         ;
  printf("Animaux autorisés :")                 ;
  scanf("%d", &cible_animaux)                   ;
}


/*############################################
#                                            #
#             saisie_client                  #
#                                            #
##############################################

*/
/*
void saisie_client(){
  char nom_client[100], prenom_client[200], numero_telephone_client[20];
  printf("Nom du client ")           ;
  scan("%s", nom_client)             ;
  printf("Prénom du client ")        ;
  scan("%s", prenom_client)          ;
  printf("Numéro de téléphone ")     ;
  scan("%s", numero_telephone_client);
}

/*############################################
#                                            #
#             paiement_resa                  #
#                                            #
##############################################

*/
/*
float montant_resa = 0 ;
void paiement_resa(){
  printf("Montant à payer : %f", &montant_resa) ;
  printf("Choisir le mode de paiement: ") ;
  printf(": ) ;
  printf("Choisir le mode de paiement: ) ;
  printf("Tapez '1' pour payer ") ;
  scan("%s", &montant_paye)             ;
  printf("Le paiement a bien été effectué. ");

}

*/
/*############################################
#                                            #
#              PARTIE SERVICES               #
#       #############################        #
#                                            #
#           catalogue_services_menu          #
#                                            #
##############################################

Menu qui affiche les choix concernant les services de l'hôtel.


*/
void catalogue_services_menu()
{
  int choix_cat = 0                                        ;
  chargement_catalogue_services()                          ;
  while(choix_cat != 9){
    printf("\n")                                           ;
    printf("    CATALOGUE DES SERVICES\n\n")               ;
    printf("1 - Lire le catalogue des services\n")         ;
    printf("2 - Modifier le catalogue des services\n")     ;
    printf("3 - Ajouter un service\n")                     ;
    printf("9 - Quitter et revenir au menu principal\n\n") ;

    printf("Choisissez une action : ")                     ;
    scanf("%d", &choix_cat)                                ;
    switch(choix_cat)
    {
      case 1:
        affichage_catalogue()    ;
        break                    ;
      case 2:
        modif_services()         ;
/*        enreg_chambre()          ;*/
        break                    ;
      case 3:
        saisie_services()        ;
        break                    ;
      case 9:
        break                    ;
      default:
        mauvais_choix(choix_cat) ;
        break                    ;
    }
  }
}

/*############################################
#                                            #
#             modif_services                 #
#                                            #
##############################################

Modifie les services déjà saisis.


*/
void modif_services()
{
  char nom_serv[MAX_NOM_SERVICE] ;
  float prix_serv                ;
  struct entree_service service  ;
  int i = 0                      ;
  if (nb_services== 0)
  {
    printf("Il n'y a actuellement aucun service dans le catalogue pour la modification.\n");
  }
  else
  {
    strcpy(nom_serv, "début")                                           ;
    while(strcmp(nom_serv,"fin\0") != 0)
    {
      service = catalogue_services[i]                                   ;
      printf("Nom actuel du service : %s\n", service.nom_service)       ;
      printf("Nouveau nom ('fin' pour terminer) : ")                    ;
      scanf("%s", nom_serv)                                             ;
      printf("%s\n", nom_serv);
      if (strcmp(nom_serv, "fin")== 0)
      {
        printf("Fin de la modification. Retour au menu précédent. \n")  ;
      }
      else
      {
        strcpy(service.nom_service, nom_serv)                          ;
        printf("Prix actuel du service : %.2f\n", service.prix_service);
        printf("Nouveau prix : ")                                      ;
        scanf("%f", &service.prix_service)                             ;
        catalogue_services[i]=service                                  ;
        i++                                                            ;
      }
    }
    sauv_catalogue_services=1                                          ;
  }
}

/*############################################
#                                            #
#            saisie_services                 #
#                                            #
##############################################

Saisie par l'utilisateur de services.
Ils sont chargés dans un tableau après ceux déjà lus depuis le fichier.

*/
void saisie_services()
{
  struct entree_service service                                 ;
  int i = nb_services                                           ;

  strcpy(service.nom_service, "début")                          ;
  while(strcmp(service.nom_service,"fin") != 0)
  {
    printf("Saisir le nom du service ('fin' pour terminer) : ") ;
    scanf("%s", service.nom_service)                            ;
    if(strcmp(service.nom_service,"fin") == 0)
    {
      printf("Fin de la saisie. Retour au menu précédent.\n")   ;
    }
    else
    {
      printf("Saisir le prix : ")        ; /*test pour éviter des prix avec virgule au lieu du point*/
      scanf("%f", &service.prix_service) ;
      printf("\n")                       ;
      catalogue_services[i++] = service  ;
    }
  }
  if(i > 0)
  {
    nb_services = i                                                  ;
    printf("%d services présents dans le catalogue.\n", nb_services) ;
    sauv_catalogue_services = 1                                      ;
    enreg_catalogue_services()                                       ;
  }
}

/*############################################
#                                            #
#         enreg_catalogue_services           #
#                                            #
##############################################

Enregistre le tableau dans le fichier catalogue-services.txt.
Affiche un message de confirmation.

*/

void enreg_catalogue_services(){
  FILE *f1                                  ;
  f1 = fopen("catalogue-services.txt", "w") ;
  int i                                     ;
  struct entree_service service             ;


  for(i = 0; i < nb_services ; i++)
  {
    service = catalogue_services[i]                                     ;
    fprintf(f1, "%s %.2f\n", service.nom_service, service.prix_service) ;
  }
  fclose(f1)                                      ;
  sauv_catalogue_services = 0                     ;
  printf("Le catalogue a bien été sauvegardé.\n") ;
}

/*############################################
#                                            #
#       chargement_catalogue_services        #
#                                            #
##############################################

Lit le fichier catalogue-services.txt et charge son contenu dans le tableau de services.

*/
void chargement_catalogue_services()
{
  FILE *f1                      ;
  struct entree_service service ;
  char test_sauv                ;
  int i                         ;

/* Le chargement du catalogue a lieu de manière automatique lors de l'entrée dans le menu de services. Il n'est donc pas nécessaire de faire ce test. Bloc de code gardé ici pour d'éventuels futurs changements dans le processus qui pourraient se servir de cette fonction.

  if (sauv_catalogue_services == 1)
  {
    printf("Le catalogue chargé a été modifié.\n")                        ;
    printf("Voulez-vous sauvegarder les modifications effectuées? (O/n)") ;
    scanf("%c", &test_sauv)                                               ;
    if(test_sauv != 'n')
    {
      enreg_catalogue_services()            ;
    }
  }*/
  f1 = fopen("catalogue-services.txt", "r") ;
  while(!feof(f1))
  {
    fscanf(f1, "%s %f\n", service.nom_service, &service.prix_service) ;
    catalogue_services[i] = service                                   ;
    i++                                                               ;
  }
  fclose(f1)                                                          ;
  nb_services = i                                                     ;
}


/*############################################
#                                            #
#           affichage_catalogue              #
#                                            #
##############################################

Affiche les données déjà chargées dans le tableau de services.


*/
void affichage_catalogue()
{
  struct entree_service service                                        ;
  int i                                                                ;
  if(nb_services == 0)
  {
    printf("Le catalogue des services est vide.\n")                    ;
  }
  else
  {
    for(i=0; i < nb_services; i++)
    {
      service = catalogue_services[i]                                  ;
      printf("%s : %.2f € \n", service.nom_service, service.prix_service) ;
    }
  }
}

/*############################################
#                                            #
#              PARTIE CHAMBRES               #
#       #############################        #
#                                            #
#             chargement_chambres            #
#                                            #
##############################################

Lit le fichier CHAMBRES et charge son contenu dans le tableau de chambres.

*/
void chargement_chambres()
{
  FILE *f1                        ;
  int i = 0                       ;

  f1 = fopen("CHAMBRES", "r") ;
  while(!feof(f1))
  {
    fscanf(f1, "%d %d %d %d %d %d %d %d %d %d\n", &chambre.num_chambre, &chambre.type_chambre, &chambre.type_lits, &chambre.categorie_chambre, &chambre.type_lits, &chambre.balcon, &chambre.vue, &chambre.bain, &chambre.fumeur, &chambre.animaux) ;
    tab_chambres[i] = chambre ;
    i++                       ;
  }
  fclose(f1)                  ;
}


/*############################################
#                                            #
#           rech_chambre                     #
#                                            #
##############################################

Rechercher les chambres par leur numéro.


*/
int rech_chambre(int par_rech)
{
  int i =0, numcase_chambre=NON_TROUVE ;
  while((i<MAX_NB_CHAMBRES)&&(numcase_chambre==NON_TROUVE))
  {
    chambre=tab_chambres[i]            ;
    if(chambre.num_chambre==par_rech)
    {
      numcase_chambre=i                ;
    }
    else
    {
      i++                              ;
    }
  }
  return numcase_chambre               ;
}

/*############################################
#                                            #
#           modification_chambre             #
#                                            #
##############################################

Modifier les chambres par la recherche de leur numéro.


*/
void modification_chambre(int res_chambre)
{
  int chambre_rech = 0                                    ;
  /*Résultat recherche chambres */
  /*printf("Entrez le numéro de la chambre à modifier : ");
  scanf("%d",&chambre_rech )                            ;
  res_chambre=rech_chambre(chambre_rech)                ;
  if (res_chambre == NON_TROUVE)
  {
    printf("Aucune modification: %d n'a pas été trouvé\n", chambre_rech);
  }
  else
  {
    chambre=tab_chambres[res_chambre];*/
    printf("Numéro actuel de la chambre : %d\n", chambre.num_chambre) ;
    printf("Nouveau numéro de la chambre : ")                         ;
    scanf("%d", &chambre.num_chambre)                                 ;

    printf("Type actuel de la chambre : %d\n", chambre.type_chambre)  ;
    printf("Nouveau type de chambre : ")                              ;
    scanf("%d", &chambre.type_chambre)                                ;

    printf("Type actuel de lits : %d\n", chambre.type_lits)           ;
    printf("Nouveau type de lits : ")                                 ;
    scanf("%d", &chambre.type_lits)                                   ;

    printf("Catégorie actuelle de la chambre : %d\n", chambre.categorie_chambre);
    printf("Nouvelle catégorie de chambre : ")                        ;
    scanf("%d", &chambre.categorie_chambre)                           ;

    printf("Type actuel de lits : %d\n", chambre.type_lits)           ;
    printf("Nouveau type de lits : ")                                 ;
    scanf("%d", &chambre.type_lits)                                   ;

    printf("Chambre avec balcon : %d\n", chambre.balcon)              ;
    printf("Chambre avec vue : ")                                     ;
    scanf("%d", &chambre.balcon)                                      ;

    printf("Chambre avec vue : %d\n", chambre.vue)                    ;
    printf("Chambre avec vue : ")                                     ;
    scanf("%d", &chambre.vue)                                         ;

    printf("Douche ou baignoire : %d\n", chambre.bain)                ;
    printf("Douche ou baignoire : ")                                  ;
    scanf("%d", &chambre.bain)                                        ;

    printf("Fumeur ou non : %d\n", chambre.fumeur)                    ;
    printf("Fumeur ou non : ")                                        ;
    scanf("%d", &chambre.fumeur)                                      ;

    printf("Animaux acceptés ou non : %d\n", chambre.animaux)         ;
    printf("Animaux ou non : ")                                       ;
    scanf("%d", &chambre.animaux)                                     ;
    tab_chambres[res_chambre] = chambre                               ;
    /*a_sauv_chambre=1                                                ; ça après*/
  /*}*/
}

/*############################################
#                                            #
#           enreg_chambre                    #
#                                            #
##############################################

Enregistrer automatique lors de la modification des chambres.


*/
void enreg_chambre()
{
  FILE *f1                                  ;
  f1 = fopen("CHAMBRES", "w")           ;
  int i                                     ;

  for(i = 0; i < MAX_NB_CHAMBRES ; i++)
  {
    chambre = tab_chambres[i]               ;
    fprintf(f1, "%d %d %d %d %d %d %d %d %d %d\n", chambre.num_chambre, chambre.type_chambre, chambre.type_lits, chambre.categorie_chambre, chambre.type_lits, chambre.balcon, chambre.vue, chambre.bain, chambre.fumeur, chambre.animaux) ;
  }
  fclose(f1)                                                ;
  /*a_sauv_chambre = 0                                        ;*/
  printf("La liste des chambres a bien été sauvegardée.\n") ;
}

/*############################################
#                                            #
#           affichage_chambre                #
#                                            #
##############################################

Affiche les données déjà chargées dans la liste des chambres.


*/
void affichage_chambre()
{
    printf("Numéro de la chambre : %d\n", chambre.num_chambre)       ;
    printf("Type de chambre : %d\n", chambre.type_chambre)           ;
    printf("Type de lits : %d\n", chambre.type_lits)                 ;
    printf("Catégorie de chambre: %d\n", chambre.categorie_chambre)  ;
    printf("Balcon: %d\n", chambre.vue)                              ;
    printf("Vue: %d\n", chambre.balcon)                              ;
    printf("Douche ou baignoire : %d\n", chambre.bain)               ;
    printf("Fumeurs ou non : %d\n", chambre.fumeur)                  ;
    printf("Animaux autorisés : %d\n\n", chambre.animaux)            ;
}

/* tableau prix chambre

  int type_chambre        ; /* 0 simple ; 1 double ; 2 triple *//*
  int categorie_chambre   ; /* 0 chambre ; 1 suite *//*
  int prix_saison         ; /* 0 basse saison, 1 haute saison */
