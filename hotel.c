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
* v 0.1.5 - 2016-02-09 Affichage et saisie date jj/mm/aaaa
* v 0.1.6 - 2016-02-13 Début de création de réservation, cible_date marche
* v 0.1.7 - 2016-02-13 Début de création de réservation, cible_chambre marche
* v 0.1.8 - 2016-02-13 Correction de la mise à jour du calendrier dans la saisie des saisons
* v 0.1.9 - 2016-02-13 rech_periode fonctionnelle
* v 0.1.10 - 2016-02-14 tests sur cible_date, rech_periode problématique
* v 0.1.11 - 2016-02-14 cible_date OK, problèmes sur cible_chambre
* v 0.1.12 - 2016-02-15 cible_date OK avec tests. Problèmes sur cible_chambre
* v 0.1.13 - 2016-02-15 Réservation OK jusqu'au paiement
* v 0.1.14 - 2016-02-16 Séparation du code: utilitaires sortis dans fichier consacré. Makefile
* v 0.1.15 - 2016-02-16 fin paiement_cb
* v 1.0.0 - 2016-02-16 Réservation fonctionnelle
* v 1.0.1 - 2016-02-16 Création note
* v 2.1.5 - 2016-02-18 (almost) feature complete.
* v 2.1.5.1 - 2016-02-29 Préparation à la sortie des jours (rationalisation du code)
* v 2.1.6 - 2016-03-05 Sortie des jours.
* v 2.1.7 - 2016-03-09 Sortie des résa.
Reste à faire:
* Traiter des chaînes de caractères avec espaces.

#include <stdio.h>

main()
{
  char c          ;
  char phrase[50] ;
  int i           ;
  phrase[0] = '\0';
  i = 0 ;
  printf("Saisir une chaîne de caractères avec espaces : ") ;
  while((c = getchar())!='\n')
  {
    phrase[i] = c;
    i++ ;
  }
  printf("Voici la phrase : '%s'\n", phrase) ;

}

* Pour améliorer les préstations, transformer les boucles de recherche while en boucles for.
* optimiser enregistrement sur fichier et cycle de modification des chambres.
* optimiser affichage et saisie des descripteurs des chambres.
* évaluer la possibilité de déclarer les variables de choix (vue/sans vue; fumeur/non fumeur; haute saison/basse saison) comme des short int;
* Dans chaque sous-programme existent des test à ajouter, spécifiés dans l'en-tête du programme-même.

*/

#include "declarations.h" /*c'est ici que sont les #include et les #define*/

/*----------------------

Déclarations préliminaires

----------------------*/


/*----------------------

D'utilité générale

Programmes réunis dans utilitaires.c
----------------------*/

void mauvais_choix(int par_choisi)                            ; /* Mauvais choix à l'intérieur des menus */
long unsigned int jjmmaaaa_vers_aaaammjj(int j, int m, int a) ; /* Prendre une date saisie et la traduire en lonf int date */
char aaaammjj_vers_jjmmaaaa(long unsigned int date)           ; /* Retourne en chaine de caractères jj/mm/aaaa la date fournie en format aaaammjj */

/*----------------------

Calendrier
----------------------*/
void lecture_jours()       ; /* Prend les jours présents dans le fichier qui tient compte des jours (et saison) et les charge dans le tableau correspondant.*/
void test_date()           ; /* Vérifie si la date du jour d'aujourd'hui correspond au premier jour dans le tableau et dans le calendrier. Si la date a changé, déclanche la mise à jour dans les deux.*/
void maj_calendrier(int i) ; /* Mise à jour du calendrier à partir des déclarations de l'utilisateur */

/*----------------------

Chambres
----------------------*/
void chargement_chambres()                 ; /* Procédure lancée au démarrage: les chambres sont chargées dans un tableau à partir du fichier (défini dans les constantes)*/
int rech_chambre(int chambre_rech)         ; /* Trouver une chambre à partir d'un numéro de chambre */
void modification_chambre(int res_chambre) ; /* Modifier les caractéristiques d'une chambre */
void enreg_chambre()                       ; /* Enregistrer les changemens apportés aux chambres */
void affichage_chambre()                   ; /* Montre toutes les caractéristiques */
void modif_prix_chambre()                  ; /* Modification du prix des nuitées */

/*----------------------

Planning
----------------------*/
void chargement_planning()                 ; /* Procédure lancée au démarrage: le planning est chargé dans un tableau à partir du fichier (défini dans les constantes)*/
void enregistrement_planning()             ;
void maj_planning()                        ; /* La nouvelle réservation est intégrée dans le planning */
void maj_planning_travaux()                ; /* La nouvelle déclaration de travaux est intégrée dans le planning */
void annulation_resa_planning()            ; /* Met en acte l'annulation en changeant le planning */
void programme_crea(int p_hier)            ; /* Appellé par maj_calendrier, prépare le programme de la journée */
void programme_lis()                       ; /* Permet de consulter le programme de la journée */

/*----------------------

Réservations
----------------------*/
void dernier_code_resa()                   ; /* Chargement des paramètres, au démarrage */
void chargement_prix()                     ; /* Chargement des paramètres, au démarrage */

void creer_reservation()                   ; /* Création d'une réservation. Contient toutes les suivantes */
void cible_date()                          ; /* Saisie de la période demandée */
void cible_chambre()                       ; /* Saisie de tous les critères demandés pour la chambre */
void cible_chambre_simple()                ; /* Choix de la chambre simplifié */
void rech_periode(long unsigned int datearrivee, long unsigned int datedepart) ; /* Identification des cases correspondantes à la période demandée dans le tableau planning */
void calcul_nuitees()                      ; /* Calcul des nuitées selon saison pour la période demandée*/
int choix_chambre()                        ; /* Identification des chambres disponibles dans la période selon les critères demandés */
int choix_chambre_simple()                 ; /* Identification des chambres disponibles dans la période selon les critères simplifiés */
void saisie_client()                       ; /* Saisie des informations sur le client */
void nouveau_nb_resa()                     ; /* Un numéro de réservation est affecté à la demande de réservation en cours de traitement */
void paiement_resa()                       ; /* Paiement de la réservation */
void paiement_cb()                         ; /* Saisie des données de la carte bancaire en cas de paiement par cb */
void sauvegarde_resa()                     ; /* Les informations sur la réservation sont sauvegardées dans un fichier */
void depart()                              ; /* Vérification d'une éventuelle note à payer au moment du départ */
void supprime_resa(long unsigned int p_code_resa) ;/* Appelée par depart() ou bien suite à l'annulation */
void recherche_resa()                      ; /* Modification d'une réservation. Contient toutes les suivantes */
void chargement_resa(long unsigned int p_code_resa) ; /* Charge la réservation */
void affichage_resa()                      ; /* Affichage de la réservation chargée */
void choix_modif_resa()                    ; /* Choisir entre modification, annulation ou retour au menu principal */
void modif_resa()                          ; /* Modification des dates et des informations client. */
void modif_resa_cha()                      ;
void annul_origine()                       ; /* Menu de choix selon l'origine de la demande d'annulation */
void remboursement()                       ; /* En cas de remboursement integral */
void annul_client()                        ; /* Défini si il doit y avoir remboursement, à quel niveau, et puis met à jour le planning */
void remboursement_partiel(int p_poursan)  ; /* Rembourse le client en fonction du pourcentage indiqué par le paramètre p_poursan */

/*----------------------

Travaux
----------------------*/
void travaux()                            ;

/*----------------------

Note
----------------------*/
void creation_note()                       ; /* Création de la note, vide. Appellée dans creer_reservation */

void menu_recherche_note()                 ; /* Permet de choisir entre recherche_note_cha et recherche_note_num */
void recherche_note_cha()                  ; /* Prend un numéro de chambre et le passe à menu_choix_note */
void recherche_note_num()                  ; /* Prend un numéro de réservation et le passe à menu_choix_note */
void menu_choix_note(char p_entree_note[]) ; /* Offre le choix entre les trois suivantes */
void affichage_note(char p_entree_note[])  ; /* La note est affichée ensuite choix possibles (ajout, règlement)*/
void ajout_note(char p_entree_note[])      ; /* Ajout d'une entrée dans le fichier de la note */
void paiement_note(char p_entree_note[])   ; /* Paiement de la note*/
void recreation_note(char p_entree_note[]) ; /* Une fois la note payée elle est remise à zéro */
void supprime_note(long unsigned int p_code_resa) ; /* Suppression de la note */


/*----------------------

Gestion des services
complémentaires
----------------------*/
void catalogue_services_menu()                        ; /* Menu qui montre les choix possibles pour le catalogue de services */
void chargement_catalogue_services()                  ; /* Prend le fichier des services et le charge en mémoire (dans un tableau). Procédure transparente */
void affichage_catalogue()                            ; /* Montre le tableau de services */
void saisie_services()                                ; /* Pour saisir de nouveaux services, à la suite de ceux déjà listés */
void enreg_catalogue_services()                       ; /* Sauvegarde le tableau chargé en mémoire dans un fichier */
void modif_services()                                 ; /* Pour modifier les services déjà listés */
int rech_service(char nom_serv_rech[MAX_NOM_SERVICE]) ; /* Recherche pour la suppression d'un service*/
void suppression_service()                            ; /* Suppression d'un service */

/*----------------------

Nuitées
----------------------*/
void catalogue_services_menu()             ; /* Menu qui montre les choix possibles pour le catalogue de services */
void chargement_catalogue_services()       ; /* Prend le fichier des services et le charge en mémoire (dans un tableau). Procédure transparente */
void affichage_catalogue()                 ; /* Montre le tableau de services */
void saisie_services()                     ; /* Pour saisir de nouveaux services, à la suite de ceux déjà listés */
void enreg_catalogue_services()            ; /* Sauvegarde le tableau chargé en mémoire dans un fichier */
void modif_services()                      ; /* Pour modifier les services déjà listés */
void modification_catalogue()              ;
int rech_services(char nom_serv_rech[MAX_NOM_SERVICE]) ;
void sauvegarde_prix_chambres()            ; /* Sauvegarde le tableau des prix des nuitées dans le fichier PRIX_NUIT*/



/*----------------------

Structures et variables

----------------------*/

/*Utilitaires*/

char poubelle            ; /*pour vider le buffer des \n*/

/*Calendrier*/
struct jour
{
  long unsigned int date ; /*date aaaammjj*/
  short int saison       ; /*0 basse saison, 1 haute saison*/
}                        ;

struct jour calendrier[ANNEE] ;


/*Prix nuitée*/
struct prix_nuit
{
  int type_chambre        ; /* 0 simple ; 1 double ; 2 triple */
  int categorie_chambre   ; /* 0 chambre ; 1 suite */
  float prix_hs           ; /* prix haute saison */
  float prix_bs           ; /* prix basse saison */
}                         ;

struct prix_nuit tab_prix_chambres[NB_CHAMBRES_PRIX] ;
struct prix_nuit nuit                                ;


/*Réservations*/

struct resa
{
  long unsigned int code_resa    ; /* long unsigned int, cela en garantit l'unicité sur une période assez longue. */
  int chambre_resa               ; /* Le numéro de la chambre dans laquelle dormira le client */
  long unsigned int datearrivee  ; /* Date (aaaammjj) de la première nuitée */
  long unsigned int datedepart   ; /* Date (aaaammjj) de la dernière nuitée */
  int nuitees_resa[2]            ; /* Case 0 basse saison, case 1 haute saison */
  char nomclient[MAX_NOM_CLI]    ;
  char prenomclient[MAX_PNOM_CLI] ;
  char telclient[12]             ;  /* +33653332003 qui peut être affiché +33 6 53 33 20 03. Vérifier de quelle taille doit être le numéro: 12? */
  float total_resa               ; /* Montant total de la chambre en fonction des nuitées et de la saison */
  int mode_paiement              ; /* Comment est reglée la réservation: 1 espèces, 2 chèque, 3 CB, 4 virement */
}                                ;

struct resa demande              ;
long unsigned int nb_resa        ; /* Dernière réservation faite, la suivante devra prendre nb_resa+1 */
long unsigned int planning[MAX_NB_CHAMBRES][ANNEE] ; /* Les valeurs dans ce tableau sont les codes de réservation. 0 est utilisé pour signaler que la chambre est libre; 1 pour déclarer des travaux. */

int numcase_resa_chambre         ; /*Identifie la case dans le tableau planning ou dans tab_chambres qui correspond à la chambre demandée/reservée*/
int numcase_resa_date_debut, numcase_resa_date_fin ; /*identifient la position dans le planning/calendrier de la case où débute et finit la réservation*/
/* Variables globales concernant les chambres*/

struct cha
{  /* structure pour les chambres*/
   /*l'identifiant unique de la chambre est son indice dans le tableau des chambres, qui correspond également à l'indice dans le planning, cela permet de relier les deux informations*/
  int num_chambre         ; /* Numéro selon la codification de l'hôtel */
  int type_chambre        ; /* 1 simple, 2 double, 3 triple */
  int categorie_chambre   ; /* 0 chambre ; 1 suite */
  int type_lits           ; /* 1 lit simple, 2 deux lits simples, 3 lit double, 4 trois lits simples, 5 lit simple et lit double */
  int balcon              ; /* 0 pas de balcon; 1 avec balcon */
  int vue                 ; /* 0 pas de vue; 1 avec vue */
  int bain                ; /* 0 baignoire; 1 douche */
  int fumeur              ; /* 0 non fumeur, 1 fumeur */
  int animaux             ; /* 0 pas d'animaux, 1 animaux acceptés */
  /*champ remarques en chaîne de caractères*/
}                         ;

struct cha tab_chambres[MAX_NB_CHAMBRES] ; /*Tableau listant les chambres*/
struct cha chambre                       ;


int a_sauv_chambre = 0                   ; /*pour la modification des chambres*/



  /* Variables globales concernant les frais*/
struct frais
{
  long int datefrais                     ; /*autrement on en fera une string de 9, 'aaaammjj' (8) + '\0'*/
  float montantfrais                     ;
  char  nomfrais[MAX_NOM_SERVICE]        ;
}                                        ;


  /* Variables globales concernant le catalogue_services*/

int sauv_catalogue_services = 0          ; /* Test. 1 : tableau à sauvegarder; 0 non.*/
int nb_services = 0                      ; /* Pour garder trace du nombre de services déjà saisis*/

struct entree_service /* Modèle du service additionnel*/
{
  char  nom_service[MAX_NOM_SERVICE]     ;
  float prix_service                     ;
}                                        ;
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
  char choix_modif      ;
  int chambre_cible = 0 ; /*Chambre recherchée*/
  int choix = 3         ; /* Déclaration de la variable et initialisation à une valeur qui permet de rentrer dans le 'while'. */
  int res_chambre = 0   ; /*Résultat recherche chambres */
  int test, t1, t2      ;

  dernier_code_resa()   ;
  chargement_chambres() ;
  lecture_jours()       ;
  test_date()           ;
  chargement_planning() ;
  chargement_prix()     ;
  chargement_catalogue_services() ;

  printf("\n\nBienvenue dans le programme de gestion des réservations.\n\n") ;
  while(choix != 0) /* 0 est la valeur pour quitter. */
  {
    test = 0                                                   ;
    while(test == 0)
    {
      printf("__________________________________________\n\n") ;
      printf("              MENU PRINCIPAL\n\n")               ;
      printf("__________________________________________\n\n") ;
      printf("Voici les actions possibles\n\n")                ;
      printf("               RÉSERVATIONS      \n")            ;
      printf("__________________________________________\n\n") ;
      printf("-1- Effectuer une réservation\n")                ;
      printf("-2- Rechercher une réservation\n")               ;
      printf("-3- Rechercher une note\n")                      ;
      printf("-4- Exécuter un check-out\n\n\n")                ;
      printf("                CHAMBRES      \n")               ;
      printf("__________________________________________\n\n") ;
      printf("-5- Déclarer des travaux dans une chambre\n")    ;
      printf("-6- Rechercher une chambre\n\n\n")               ;
      printf("                PARAMÈTRES    \n")               ;
      printf("__________________________________________\n\n") ;
      printf("-7- Catalogue des services\n")                   ;
      printf("-8- Voir le programme du jour\n")                ;
      printf("-9- Modifier le prix des chambres\n\n\n")        ;
      printf("                 QUITTER    \n")                 ;
      printf("__________________________________________\n\n") ;
      printf("-0- Quitter l'application\n\n")                  ;
      /*printf("7 - Imprimer le programme d'aujourd'hui.\n") ; On ne l'a pas mis dans le planning, mais c'est une idée dont on avait parlé. On verra plus tard si et comment le faire.*/

      printf("Choix : ")                                       ;
      t1=scanf("%d", &choix)                                   ; /* Attention, à partir de ce moment il y a un '\n' qui traîne dans le buffer. */
      if(t1 == 0)
      {
        printf("Choix invalide.\n")                            ;
        while((poubelle=getchar()) != '\n')                    ;
      }
      else
      {
        test = 1                                               ;
      }
    }

    switch(choix)
    {
      case 0:
        printf("Vous avez choisi de quitter l'application.\nMerci et au revoir.\n") ;
        break                                                                       ;
      case 1:
        creer_reservation()                                                         ;
        break                                                                       ;
      case 2:
        recherche_resa()                                                            ;
        break                                                                       ;
      case 3:
        menu_recherche_note()                                                       ;
        break                                                                       ;
      case 4:
        depart()                                                                    ;
        break                                                                       ;
      case 5:
        travaux()                                                                   ;
        break                                                                       ;
      case 6:
        printf("Entrez le numéro de la chambre à rechercher: ") ;

        t2 = scanf("%d", &chambre_cible)                        ;
        if(t2 == 0)
        {
          printf("Erreur de saisie.\n")                         ;
          while((poubelle=getchar()) != '\n')                   ;
        }
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
            modification_chambre(res_chambre)                   ;
          }
          printf("Retour au menu.\n")                           ;
          enreg_chambre()                                       ;

        }
        break                                                                       ;
      case 7:
        catalogue_services_menu()                                                   ;
        break                                                                       ;
      case 8:
        programme_lis()                                                             ;
        break                                                                       ;
      case 9:
        modif_prix_chambre()                                                        ;
        break                                                                       ;
      default:
        mauvais_choix(choix)                                                        ;
        break                                                                       ;
    }
  }
}

/*############################################
#                                            #
#              PARTIE NOTES                  #
#       #############################        #
#                                            #
#              creation_note                 #
#                                            #
##############################################

Création de la note, vide. Appellée dans creer_reservation.

*/
void creation_note()
{
  char entree_note[20], temporaire[11]          ;
  FILE *f1                                      ;

  temporaire[0] = '\0'                          ;
  entree_note[0] = '\0'                         ;
  strcat(entree_note, DOSSIER_NOTES)            ;
  sprintf(temporaire, "%lu", demande.code_resa) ;
  strcat(entree_note, temporaire)               ;
  strcat(entree_note, ".txt")                   ;
  f1=fopen(entree_note, "w")                    ;
  fprintf(f1, "%s %s\n", demande.nomclient, demande.prenomclient) ; /*Pour avoir accès à toutes les informations rapidement et de manière indépendante de la réservation, on met dans la première ligne du fichier nom et prénom du client*/
  fclose(f1)                                    ;
}


/*############################################
#                                            #
#           menu_recherche_note              #
#                                            #
##############################################

Appelée dans le menu principal.

*/
void menu_recherche_note()
{
  int t1 = 0, t2 = 0, choix_recherche_note   ;
  printf("Menu de recherche d'une note\n")   ;
  while(t1 == 0)
  {
    printf("-1- Recherche de note par numéro de réservation\n") ;
    printf("-2- Recherche de note par numéro de chambre (uniquement pour les réservations en cours)\n") ;
    printf("-3- Retour au menu principal\n") ;
    printf("Choix : ")                       ;
    t2 = scanf("%d", &choix_recherche_note)  ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")           ;
      while((poubelle=getchar()) != '\n')    ;
    }
    switch (choix_recherche_note)
    {
      case 1:
        recherche_note_num()                 ;
        t1 = 1                               ;
        break                                ;
      case 2:
        recherche_note_cha()                 ;
        t1 = 1                               ;
        break                                ;
      case 3:
        printf("Retour au menu principal\n") ;
        t1 = 1                               ;
        break                                ;
      default:
        mauvais_choix(choix_recherche_note)  ;
        break                                ;
    }
  }
}

/*############################################
#                                            #
#           recherche_note_cha               #
#                                            #
##############################################

Appelée par menu_recherche_note().
Après son éxecution on revient au menu principal.

On demande la saisie du numéro de chambre, on récupère le numéro de réservation correspondante. Il sera passé à menu_choix_note.

*/

void recherche_note_cha()
{
  char temporaire[11], entree_note[20], client_nom[MAX_NOM_CLI], client_prenom[MAX_PNOM_CLI], confirmation;
  FILE *f1                                        ;
  int rech_note_chambre, t1 = 0, t2               ;
  long unsigned int id_resa                       ;

  while(t1 == 0)
  {
    printf("Saisir le numéro de la chambre : " )  ;
    t2 = scanf("%d", &rech_note_chambre)          ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                ;
      while((poubelle=getchar()) != '\n')         ;
    }
    else
    {
      t1 = 1                                      ;
    }
  }

  if ((planning[rech_note_chambre][0]==0) || (planning[rech_note_chambre][0]==1))
  {
    printf("Erreur: la chambre n'est pas réservée.\n");
    menu_recherche_note()                         ;
  }
  else
  {
   id_resa = planning[rech_note_chambre][0]       ;
   temporaire[0] = '\0'                           ;
   entree_note[0] = '\0'                          ;
   strcat(entree_note, DOSSIER_NOTES)             ;
   sprintf(temporaire, "%lu", id_resa) ;
   strcat(entree_note, temporaire)                ;
   strcat(entree_note, ".txt")                    ;
   f1=fopen(entree_note, "r")                     ;

   fscanf(f1, "%s %s", client_nom, client_prenom) ;
   fclose(f1)                                     ;

   printf("Réservation de %s %s\n", client_prenom, client_nom) ;
   t2 = 0                                         ;
   while(t2 == 0)
   {
     while((poubelle=getchar()) != '\n')          ;
     printf("Vous confirmez (o/n) ? ")            ;
     scanf("%c", &confirmation)                   ;
     if((confirmation != 'o') && (confirmation != 'n'))
     {
       printf("Erreur de saisie\n")               ;
     }
     else
     {
       t2 = 1                                     ;
     }
   }
   if(confirmation == 'n')
   {
     printf("Retour au menu principal\n")         ;
   }
   else
   {
     menu_choix_note(entree_note)                 ;
   }
  }
}

/*############################################
#                                            #
#           recherche_note_num               #
#                                            #
##############################################
On demande la saisie du numéro de réservation, on le passe à menu_choix_note.
*/

void recherche_note_num()
{
  char temporaire[11], entree_note[20], client_nom[MAX_NOM_CLI], client_prenom[MAX_PNOM_CLI], confirmation;
  FILE *f1                                        ;
  int t1 = 0, t2                                  ;
  long unsigned int id_resa                       ;

  while(t1 == 0)
  {
    printf("Saisir le numéro de réservation : " ) ;
    t2 = scanf("%lu", &id_resa)                   ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                ;
      while((poubelle=getchar()) != '\n')         ;
    }
    else
    {
      t1 = 1                                      ;
    }
  }

  temporaire[0] = '\0'                            ;
  entree_note[0] = '\0'                           ;
  strcat(entree_note, DOSSIER_NOTES)              ;
  sprintf(temporaire, "%lu", id_resa)             ;
  strcat(entree_note, temporaire)                 ;
  strcat(entree_note, ".txt")                     ;
  f1=fopen(entree_note, "r")                      ;

  fscanf(f1, "%s %s", client_nom, client_prenom)  ;
  fclose(f1)                                      ;

  printf("Réservation de %s %s\n", client_prenom, client_nom) ;
  t2 = 0                                          ;
  while(t2 == 0)
  {
    while((poubelle=getchar()) != '\n')           ;
    printf("Vous confirmez (o/n) ? ")             ;
    scanf("%c", &confirmation)                    ;
    if((confirmation != 'o') && (confirmation != 'n'))
    {
      printf("Erreur de saisie\n")                ;
    }
    else
    {
      t2 = 1                                      ;
    }
  }
  if(confirmation == 'n')
  {
    printf("Retour au menu de recherche d'une note\n");
    menu_recherche_note()                         ;
  }
  else
  {
    menu_choix_note(entree_note)                  ;
  }
}

/*############################################
#                                            #
#              menu_choix_note               #
#                                            #
##############################################
Récupère le numéro d'une réservation, trouve le fichier correspondant, et propose des actions à l'utilisateur.
*/

void menu_choix_note(char p_entree_note[])
{
  int t1, t2, choix_note                                 ;
  FILE *f1                                               ;

  while(t1 == 0)
  {
    printf("-1- Afficher la note\n")                     ;
    printf("-2- Ajouter une entrée sur la note\n")       ;
    printf("-3- Régler la note\n")                       ;
    printf("-4- Quitter et revenir au menu principal\n") ;
    printf("Choix : ")                                   ;
    t2 = scanf("%d", &choix_note)                        ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                       ;
    }
    else
    {
      switch(choix_note)  /* Passe p_entree_note au programme suivant, selon le choix. */
      {
        case 1:
          affichage_note(p_entree_note)        ;
          break                                ;
        case 2:
          ajout_note(p_entree_note)            ;
          break                                ;
        case 3:
          paiement_note(p_entree_note)         ;
          break                                ;
        case 4:
          printf("Retour précédent\n")         ;
          t1 = 1                               ;
          break                                ;
      }
    }
  }
}

/*############################################
#                                            #
#              affichage_note                #
#                                            #
##############################################

Appelée par recherche_note, prend en argument le nom du fichier de la note (num_note).
Sortie par un menu de choix.
*/

void affichage_note(char p_entree_note[])
{
  char note_nom_cli[MAX_NOM_CLI], note_pnom_cli[MAX_PNOM_CLI] ;
  char date_chaine[11], temporaire[5]                         ;
  FILE *f1                                                    ;
  float note_total = 0                                        ;
  int i = 0, k, a, m, j                                       ;
  struct frais note[MAX_ENTREES_FRAIS]                        ;

  f1=fopen(p_entree_note, "r")                                ;
  fscanf(f1, "%s %s\n", note_nom_cli, note_pnom_cli) ; /*Pour avoir accès à toutes les informations rapidement et de manière indépendante de la réservation, on met dans la première ligne du fichier nom et prénom du client*/
  while(!feof(f1))
  {
    fscanf(f1, "%lu %s %f", &note[i].datefrais, note[i].nomfrais, &note[i].montantfrais) ;
    note_total += note[i].montantfrais                 ;
    i++                                                ;
  }
  fclose(f1)                                           ;

  for(k = 0 ; i < k ; j++)
  {
    date_chaine[0] = '\0'                              ;
    temporaire[0] = '\0'                               ;
    a = note[i].datefrais/10000                        ;
    m = (note[i].datefrais - (a * 10000)) / 100        ;
    j = (note[i].datefrais - (a * 10000) - (m * 100))  ;
    sprintf(temporaire, "%d", j)                       ;
    strcat(date_chaine, temporaire)                    ;
    strcat(date_chaine, "/")                           ;
    sprintf(temporaire, "%d", m)                       ;
    strcat(date_chaine, temporaire)                    ;
    strcat(date_chaine, "/")                           ;
    sprintf(temporaire, "%d", a)                       ;
    strcat(date_chaine, temporaire)                    ;

    printf("%s %s %.2f", date_chaine, note[i].nomfrais, note[i].montantfrais) ;
  }
  printf("Le montant total de la note est : %.2f €.\n", note_total) ;
  if(i == 1000)
  {
    printf("La note est pleine et doit être réglée.") ;
    paiement_note(p_entree_note)                      ;
  }
  menu_choix_note(p_entree_note)                      ;
}

/*############################################
#                                            #
#                ajout_note                  #
#                                            #
##############################################
Ajoute une entrée depuis le catalogue des services.
Prend en paramètre l'identifiant d'une note.
*/

void ajout_note(char p_entree_note[])
{
  char date[11], note_nom_cli[MAX_NOM_CLI], note_pnom_cli[MAX_PNOM_CLI] ;
  int t1 = 0, t2, ajout_frais, j, i=0                              ;
  FILE *f1                                                         ;
  struct entree_service ajout                                      ;
  struct frais note[MAX_ENTREES_FRAIS]                             ;

  affichage_catalogue()                                            ;

  while(t1 == 0)
  {
    printf("Saisir le numéro du service à ajouter sur la note : ") ;
    t2 = scanf("%d", &ajout_frais)                                 ;
    if((t2 == 0) || (ajout_frais > nb_services))
    {
      printf("Erreur de saisie.\n")                                ;
      while((poubelle=getchar()) != '\n')                          ;
    }
    else
    {
      t1 = 1                                                       ;
    }
  }

  ajout = catalogue_services[ajout_frais]                          ;

  f1=fopen(p_entree_note, "r")                                     ;
  fscanf(f1, "%s %s\n", note_nom_cli, note_pnom_cli)               ; /*Pour avoir accès à toutes les informations rapidement et de manière indépendante de la réservation, on met dans la première ligne du fichier nom et prénom du client*/
  while(!feof(f1))
  {
    fscanf(f1, "%lu %s %f", &note[i].datefrais, note[i].nomfrais, &note[i].montantfrais) ;
    i++                                                            ;
  }
  fclose(f1)                                                       ;

  note[i].datefrais = calendrier[0].date                           ;
  strcpy(note[i].nomfrais, ajout.nom_service)                      ;
  note[i].montantfrais = ajout.prix_service                        ;

  i++                                                              ;
  j = 0                                                            ;

  f1=fopen(p_entree_note, "w")                                     ;
  fprintf(f1, "%s %s\n", note_nom_cli, note_pnom_cli) ;
  while(j < i)
  {
    fprintf(f1, "%lu %s %f", note[j].datefrais, note[j].nomfrais, note[j].montantfrais) ;
    j++                                                            ;
  }
  fclose(f1)                                                       ;
  printf("Le service a bien été ajouté à la note. \n")             ;
}

/*############################################
#                                            #
#              paiement_note                 #
#                                            #
##############################################
Prend en paramètre le nom d'une note.
Teste si la note existe. Si non, renvoie un message d'erreur.
Autrement elle récupère le total, demande les moyens de paiement et des informations.
Le paiement est simulé et sauvegardé.
*/
void paiement_note(char p_entree_note[])
{
  char note_nom_cli[MAX_NOM_CLI], note_pnom_cli[MAX_PNOM_CLI] ;
  char date_chaine[11], temporaire[5]                         ;
  FILE *f1                                                    ;
  float note_total = 0                                        ;
  int i = 0, k, a, m, j, test=0, t2                           ;
  struct frais note[MAX_ENTREES_FRAIS]                        ;


  f1=fopen(p_entree_note, "r")                                ;
  fscanf(f1, "%s %s\n", note_nom_cli, note_pnom_cli)          ; /*Pour avoir accès à toutes les informations rapidement et de manière indépendante de la réservation, on met dans la première ligne du fichier nom et prénom du client*/
  while(!feof(f1))
  {
    fscanf(f1, "%lu %s %f", &note[i].datefrais, note[i].nomfrais, &note[i].montantfrais) ;
    note_total += note[i].montantfrais                 ;
    i++                                                ;
  }
  fclose(f1)                                           ;

  for(k = 0 ; i < k ; j++)
  {
    date_chaine[0] = '\0'                              ;
    temporaire[0] = '\0'                               ;
    a = note[i].datefrais/10000                        ;
    m = (note[i].datefrais - (a * 10000)) / 100        ;
    j = (note[i].datefrais - (a * 10000) - (m * 100))  ;
    sprintf(temporaire, "%d", j)                       ;
    strcat(date_chaine, temporaire)                    ;
    strcat(date_chaine, "/")                           ;
    sprintf(temporaire, "%d", m)                       ;
    strcat(date_chaine, temporaire)                    ;
    strcat(date_chaine, "/")                           ;
    sprintf(temporaire, "%d", a)                       ;
    strcat(date_chaine, temporaire)                    ;

    printf("%s %s %.2f", date_chaine, note[i].nomfrais, note[i].montantfrais) ;
  }
  printf("Le montant total de la note est : %.2f €.\n", note_total)           ;

  while(test == 0)
  {

    printf("Choisir le mode de paiement: \n")              ;
    printf("-1- Espèces\n")                                ;
    printf("-2- Chèque\n")                                 ;
    printf("-3- Carte bancaire\n")                         ;
    printf("-4- Virement\n")                               ;
    printf("Choix : ")                                     ;
    t2 = scanf("%d", &demande.mode_paiement)               ;
    if(t2 == 0)
    {
      printf("Erreur de saisie.\n")                        ;
    }
    else
    {
      if((demande.mode_paiement < 0) || (demande.mode_paiement > 4))
      {
        mauvais_choix(demande.mode_paiement)               ;
      }
      else
      {
        if(demande.mode_paiement == 3)
        {
          paiement_cb()                                    ;
        }
        printf("Le paiement a bien été effectué.\n")       ;
        test = 1                                           ;
       }
     }
   }
   recreation_note(p_entree_note);
}


/*############################################
#                                            #
#              recreation_note               #
#                                            #
##############################################
Ecrase ancienne note.

*/
void recreation_note(char p_entree_note[])
{
  char note_nomclient[MAX_NOM_CLI], note_prenomclient[MAX_PNOM_CLI] ;
  FILE *f1                                                          ;

  f1=fopen(p_entree_note, "r")                                      ;
  fscanf(f1, "%s %s", note_nomclient, note_prenomclient)            ;
  fclose(f1)                                                        ;

  f1=fopen(p_entree_note, "w")                                      ;
  fprintf(f1, "%s %s\n", note_nomclient, note_prenomclient)         ;
  fclose(f1)                                                        ;
}

/*############################################
#                                            #
#               supprime_note                #
#                                            #
##############################################

Appelée par depart() ou annul_origine().
Supprime la note.

*/

void supprime_note(long unsigned int p_code_resa)
{
  char entree_note[20], temporaire[11]                             ;
  int test                                                         ;

  temporaire[0] = '\0'                                             ;
  entree_note[0] = '\0'                                            ;
  strcat(entree_note, DOSSIER_NOTES)                               ;
  sprintf(temporaire, "%lu", p_code_resa)                          ;
  strcat(entree_note, temporaire)                                  ;
  strcat(entree_note, ".txt")                                      ;

  test = unlink(entree_note)                                       ;
  if(test == -1)
  {
    printf("Erreur dans la suppression du fichier\n")              ;
    printf("Supprimez manuellemenet le fichier %s\n", entree_note) ;
  }
}

/*############################################
#                                            #
#              PARTIE SERVICES               #
#       #############################        #
#                                            #
#           catalogue_services_menu          #
#                                            #
##############################################

Appelé dans le main()
Menu qui affiche les choix concernant les services de l'hôtel.


*/
void catalogue_services_menu()
{
  int choix_cat = 0                                        ;
  while(choix_cat != 9)
  {
    printf("\n")                                           ;
    printf("    CATALOGUE DES SERVICES\n\n")               ;
    printf("-1- Lire le catalogue des services\n")         ;
    printf("-2- Modifier le catalogue des services\n")     ;
    printf("-3- Ajouter un service\n")                     ;
    printf("-9- Quitter et revenir au menu principal\n\n") ;

    printf("Choisissez une action : ")                     ;
    scanf("%d", &choix_cat)                                ;
    switch(choix_cat)
    {
      case 1:
        affichage_catalogue()                ;
        break                                ;
      case 2:
        modif_services()                     ;
        break                                ;
      case 3:
        saisie_services()                    ;
        break                                ;
      case 9:
        printf("Retour au menu principal\n") ;
        break                                ;
      default:
        mauvais_choix(choix_cat)             ;
        while((poubelle=getchar()) != '\n')  ;
        break                                ;
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
    printf("Il n'y a actuellement aucun service dans le catalogue pour la modification.\n") ;
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
      printf("%s\n", nom_serv)                                          ;
      if (strcmp(nom_serv, "fin")== 0)
      {
        printf("Fin de la modification. Retour au menu précédent. \n")  ;
      }
      else
      {
        strcpy(service.nom_service, nom_serv)                           ;
        printf("Prix actuel du service : %.2f\n", service.prix_service) ;
        printf("Nouveau prix : ")                                       ;
        scanf("%f", &service.prix_service)                              ;
        catalogue_services[i]=service                                   ;
        i++                                                             ;
      }
    }
    sauv_catalogue_services=1                                           ;
  }
}


/*############################################
#                                            #
#           rech_service                     #
#                                            #
##############################################

Recherche d'un service

*/

int rech_services(char nom_serv_rech[MAX_NOM_SERVICE])
{
  struct entree_service service     ;
  int i, numserv = -1               ;
  for (i=0; i<MAX_CAT_SERV; i++)
  {
    service = catalogue_services[i] ;
    if (strcmp(service.nom_service, nom_serv_rech) ==0)
    {
      numserv = i                   ;
    }
  }
  if(numserv == -1)
  {
    return(NON_TROUVE)              ;
  }
  else
  {
    return(numserv)                 ;
  }
}

/*############################################
#                                            #
#           suppression_service              #
#                                            #
##############################################

Supprime un service


*/
void suppression_service()
{
  char nom_rech[MAX_NOM_SERVICE]                      ;
  int i = 0, numero=NON_TROUVE                        ;
  if (nb_services== 0)
  {
    printf("Il n'y a actuellement aucun service dans le catalogue pour la suppression.\n") ;
  }
  else
  {
    printf("Nom du service à supprimer : ")           ;
    scanf("%s", nom_rech)                             ;
    numero = rech_services(nom_rech)                  ;
    if (numero == NON_TROUVE)
      {
        printf("%s non trouvé \n", nom_rech)          ;
      }
    else
    {
      for (i=numero ; i<nb_services-1 ; i++)
      {
        catalogue_services[i]=catalogue_services[i+1] ;
      }
      nb_services--                                   ;
      printf("%s supprimé \n", nom_rech)              ;
      sauv_catalogue_services=1                       ;
    }
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
      printf("Saisir le prix : ")                               ; /*test pour éviter des prix avec virgule au lieu du point*/
      scanf("%f", &service.prix_service)                        ;
      printf("\n")                                              ;
      catalogue_services[i++] = service                         ;
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

Enregistre le tableau dans le fichier CAT_SERVICES.
Affiche un message de confirmation.

*/

void enreg_catalogue_services(){
  FILE *f1                                                              ;
  f1 = fopen(CAT_SERVICES, "w")                                         ;
  int i                                                                 ;
  struct entree_service service                                         ;


  for(i = 0; i < nb_services ; i++)
  {
    service = catalogue_services[i]                                     ;
    fprintf(f1, "%s %.2f\n", service.nom_service, service.prix_service) ;
  }
  fclose(f1)                                                            ;
  sauv_catalogue_services = 0                                           ;
  printf("Le catalogue a bien été sauvegardé.\n")                       ;
}

/*############################################
#                                            #
#       chargement_catalogue_services        #
#                                            #
##############################################

Lit le fichier CAT_SERVICES et charge son contenu dans le tableau de services.

*/
void chargement_catalogue_services()
{
  FILE *f1                      ;
  struct entree_service service ;
  char test_sauv                ;
  int i                         ;

  f1 = fopen(CAT_SERVICES, "r") ;
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
  struct entree_service service                                                 ;
  int i                                                                         ;
  if(nb_services == 0)
  {
    printf("Le catalogue des services est vide.\n")                             ;
  }
  else
  {
    printf("\n")                                                                ;
    for(i=0; i < nb_services; i++)
    {
      service = catalogue_services[i]                                           ;
      printf("%d %s : %.2f € \n", i, service.nom_service, service.prix_service) ;
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
  FILE *f1                  ;
  int i                     ;

  f1 = fopen(CHAMBRES, "r") ;
  for(i = 0; i < 50 ; i++)
  {
    fscanf(f1, "%d %d %d %d %d %d %d %d %d", &tab_chambres[i].num_chambre, &tab_chambres[i].type_chambre, &tab_chambres[i].categorie_chambre, &tab_chambres[i].type_lits, &tab_chambres[i].balcon, &tab_chambres[i].vue, &tab_chambres[i].bain, &tab_chambres[i].fumeur, &tab_chambres[i].animaux) ;
  }
  fclose(f1)                ;
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
}

/*############################################
#                                            #
#           enreg_chambre                    #
#                                            #
##############################################

Appelée dans un choix du menu principal.
Sauvegarde automatique lors de la modification des chambres.


*/
void enreg_chambre()
{
  FILE *f1                                                  ;
  f1 = fopen("CHAMBRES", "w")                               ;
  int i                                                     ;

  for(i = 0; i < MAX_NB_CHAMBRES ; i++)
  {
    chambre = tab_chambres[i]                               ;
    fprintf(f1, "%d %d %d %d %d %d %d %d %d %d\n", chambre.num_chambre, chambre.type_chambre, chambre.type_lits, chambre.categorie_chambre, chambre.type_lits, chambre.balcon, chambre.vue, chambre.bain, chambre.fumeur, chambre.animaux) ;
  }
  fclose(f1)                                                ;
  printf("La liste des chambres a bien été sauvegardée.\n") ;
}

/*############################################
#                                            #
#           affichage_chambre                #
#                                            #
##############################################

Appelée dans un choix du menu principal.
Affiche les données déjà chargées dans la liste des chambres pour les modifier ensuite.

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

/*############################################
#                                            #
#                  travaux                   #
#                                            #
##############################################

Procédure pour déclarer des travaux

*/
void travaux()
{
  char temporaire[5], date_1[11]                                    ;
  int cible_num_chambre, t1=0, t2, i, libre, a, m, j, k             ;
  long unsigned int date_num                         ;

  printf("Déclaration de travaux.\n")                               ;
  cible_date()                                                      ;
  while (t1 == 0)
  {
    printf("Saisir le numéro de la chambre (0 pour quitter) : ")    ;
    t2 = scanf("%d", &cible_num_chambre)                            ;
    if(t2 == 0)  /* test de la saisie */
    {
      printf("Erreur de saisie.\n")                                 ;
      while((poubelle=getchar()) != '\n')                           ;
    }
    else
    {
      if(cible_num_chambre == 0) /* abandon */
      {
        printf("Abandon.\n")                                        ;
        printf("Retour au menu principal.\n")                       ;
        t1 = 1                                                      ;
      }
      else /* la saisie correspond-t-elle à une chambre?*/
      {
        i = 0                                                       ;
        t2 = 0                                                      ;
        while((t2 == 0) && (i < MAX_NB_CHAMBRES))
        {
          if(cible_num_chambre == tab_chambres[i].num_chambre)
          {
            t2 = 1                                                  ;
          }
          else
          {
            i++                                                     ;
          }
        }
        if(t2 == 0)
        {
          printf("Le choix fait ne correspond pas à une chambre existante.\n") ;
        }
        else
        {
          t1 = 2                                                    ; /* pour sortir de la boucle de saisie */
          demande.chambre_resa = cible_num_chambre                  ; /* Nous savons maintenant que la valeur saisie est celle d'une chambre, on la stocke dans la structure demande */
        }
      } /* sortie du test de chambre */
    }
  } /* sortie de la boucle de saisie */

  if(t1 == 2)
  {
  rech_periode(demande.datearrivee, demande.datedepart) ;
  k = numcase_resa_date_debut                           ;
  libre = 0                                             ;
  while(k < numcase_resa_date_fin + 1)
  {
    if(planning[i][k] != 0)
    {
      libre = 1                                         ;
      date_num = calendrier[k].date                     ;
      date_1[0] = '\0'                                  ;
      temporaire[0] = '\0'                              ;
      a = date_num/10000                                ;
      m = (date_num - (a * 10000)) / 100                ;
      j = (date_num - (a * 10000) - (m * 100))          ;
      sprintf(temporaire, "%d", j)                      ;
      strcat(date_1, temporaire)                        ;
      strcat(date_1, "/")                               ;
      sprintf(temporaire, "%d", m)                      ;
      strcat(date_1, temporaire)                        ;
      strcat(date_1, "/")                               ;
      sprintf(temporaire, "%d", a)                      ;
      strcat(date_1, temporaire)                        ;
      if(planning[i][k] == 1)
      {
        printf("Le %s la chambre est déjà en travaux\n", date_1);
      }
      else
      {
        printf("La chambre est occupée le %s par la réservation %lu\n", date_1, planning[i][k]) ;
      }
    }
    k++                                                                                         ;
  }
  if(libre != 0)
  {
    printf("Impossible de déclarer des travaux, veuillez modifier les réservations avant.\n")   ;
  }
  else
  {
    demande.code_resa = 1                                      ;
    maj_planning_travaux()                                     ;
    printf("La déclaration de travaux a bien été effectuée\n") ;
  }
}
}

/*############################################
#                                            #
#             modif_prix_chambre             #
#                                            #
##############################################

Procédure modifier le prix d'un chambre


*/
void modif_prix_chambre()
{

  int t2=0                                                                     ;
  float prix=0                                                                 ;

  while(t2 == 0)
  {
    printf("Modification du prix d'une chambre.\n")                            ;
    printf("Type de la chambre: chambre simple.\n")                            ;
    printf("Catégorie de la chambre: chambre.\n")                              ;
    printf("Prix actuel de la chambre en haute saison : %.2f\n", tab_prix_chambres[1].prix_hs) ;
    printf("Nouveau prix de la chambre en haute saison : ")                    ;
    t2 = scanf("%f", &prix)                                                    ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                                             ;
      while((poubelle=getchar()) != '\n')                                      ;
    }
    tab_prix_chambres[1].prix_hs = prix                                        ;
  }

  t2 = 0                                                                       ;
  while(t2 == 0)
  {
    printf("Prix actuel de la chambre en basse saison : %.2f\n", tab_prix_chambres[1].prix_bs) ;
    printf("Nouveau prix de la chambre en basse saison : ")                    ;
    t2 = scanf("%f", &prix)                                                    ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                                             ;
      while((poubelle=getchar()) != '\n')                                      ;
    }
    tab_prix_chambres[1].prix_bs = prix                                        ;
  }

  t2 = 0                                                                       ;
  while(t2 == 0)
  {
    printf("Type de la chambre: chambre simple.\n")                            ;
    printf("Catégorie de la chambre: suite.\n")                                ;
    printf("Prix actuel de la chambre en haute saison : %.2f\n", tab_prix_chambres[2].prix_hs) ;
    printf("Nouveau prix de la chambre en haute saison : ")                    ;
    scanf("%f", &prix)                                                         ;
    t2 = scanf("%f", &prix)                                                    ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                                             ;
      while((poubelle=getchar()) != '\n')                                      ;
    }
    tab_prix_chambres[2].prix_hs = prix                                        ;
  }

  t2 = 0                                                                       ;
  while(t2 == 0)
  {
    printf("Prix actuel de la chambre en basse saison : %.2f\n", tab_prix_chambres[2].prix_bs) ;
    printf("Nouveau prix de la chambre en basse saison : ")                    ;
    scanf("%f", &prix)                                                         ;
    t2 = scanf("%f", &prix)                                                    ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                                             ;
      while((poubelle=getchar()) != '\n')                                      ;
    }
    tab_prix_chambres[2].prix_bs = prix;
  }

  t2 = 0 ;
  while(t2 == 0)
  {
    printf("Type de la chambre: chambre double.\n")                            ;
    printf("Catégorie de la chambre: chambre.\n")                              ;
    printf("Prix actuel de la chambre en haute saison : %.2f\n", tab_prix_chambres[3].prix_hs) ;
    printf("Nouveau prix de la chambre en haute saison : ")                    ;
    scanf("%f", &prix)                                                         ;
    t2 = scanf("%f", &prix)                                                    ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                                             ;
      while((poubelle=getchar()) != '\n')                                      ;
    }
    tab_prix_chambres[3].prix_hs = prix                                        ;
  }

  t2 = 0                                                                       ;
  while(t2 == 0)
  {
    printf("Prix actuel de la chambre en basse saison : %.2f\n", tab_prix_chambres[3].prix_bs) ;
    printf("Nouveau prix de la chambre en basse saison : ")                    ;
    scanf("%f", &prix)                                                         ;
    t2 = scanf("%f", &prix)                                                    ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                                             ;
      while((poubelle=getchar()) != '\n')                                      ;
    }
    tab_prix_chambres[3].prix_bs = prix;
  }

  t2 = 0                                                                       ;
  while(t2 == 0)
  {
    printf("Type de la chambre: chambre double.\n")                            ;
    printf("Catégorie de la chambre: suite.\n")                                ;
    printf("Prix actuel de la chambre en haute saison : %.2f\n", tab_prix_chambres[4].prix_hs) ;
    printf("Nouveau prix de la chambre en haute saison : ")                    ;
    scanf("%f", &prix)                                                         ;
    t2 = scanf("%f", &prix)                                                    ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                                             ;
      while((poubelle=getchar()) != '\n')                                      ;
    }
    tab_prix_chambres[4].prix_hs = prix;
  }
  t2 = 0                                                                       ;
  while(t2 == 0)
  {
    printf("Prix actuel de la chambre en basse saison : %.2f\n", tab_prix_chambres[4].prix_bs) ;
    printf("Nouveau prix de la chambre en basse saison : ")                    ;
    scanf("%f", &prix)                                                         ;
    t2 = scanf("%f", &prix)                                                    ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                                             ;
      while((poubelle=getchar()) != '\n')                                      ;
    }
    tab_prix_chambres[4].prix_bs = prix                                        ;
  }


  t2 = 0                                                                       ;
  while(t2 == 0)
  {
    printf("Type de la chambre: chambre triple.\n")                            ;
    printf("Catégorie de la chambre: chambre.\n")                              ;
    printf("Prix actuel de la chambre en haute saison : %.2f\n", tab_prix_chambres[5].prix_hs) ;
    printf("Nouveau prix de la chambre en haute saison : ")                    ;
    scanf("%f", &prix)                                                         ;
    t2 = scanf("%f", &prix)                                                    ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                                             ;
      while((poubelle=getchar()) != '\n')                                      ;
    }
    tab_prix_chambres[5].prix_hs = prix                                        ;
  }

  t2 = 0                                                                       ;
  while(t2 == 0)
  {
    printf("Prix actuel de la chambre en basse saison : %.2f\n", tab_prix_chambres[5].prix_bs) ;
    printf("Nouveau prix de la chambre en basse saison : ")                    ;
    scanf("%f", &prix)                                                         ;
    t2 = scanf("%f", &prix)                                                    ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                                             ;
      while((poubelle=getchar()) != '\n')                                      ;
    }
    tab_prix_chambres[5].prix_bs = prix                                        ;
  }

  t2 = 0 ;
  while(t2 == 0)
  {
    printf("Type de la chambre: chambre triple.\n")                            ;
    printf("Catégorie de la chambre: suite.\n")                                ;
    printf("Prix actuel de la chambre en haute saison : %.2f\n", tab_prix_chambres[6].prix_hs) ;
    printf("Nouveau prix de la chambre en haute saison : ")                    ;
    scanf("%f", &prix)                                                         ;
    t2 = scanf("%f", &prix)                                                    ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                                             ;
      while((poubelle=getchar()) != '\n')                                      ;
    }
    tab_prix_chambres[6].prix_hs = prix                                        ;
  }

  t2 = 0 ;
  while(t2 == 0)
  {
    printf("Prix actuel de la chambre en basse saison : %.2f\n", tab_prix_chambres[6].prix_bs) ;
    printf("Nouveau prix de la chambre en basse saison : ")                    ;
    scanf("%f", &prix)                                                         ;
    t2 = scanf("%f", &prix)                                                    ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                                             ;
      while((poubelle=getchar()) != '\n')                                      ;
    }
    tab_prix_chambres[6].prix_bs = prix                                        ;
  }
    sauvegarde_prix_chambres()                                                 ;
}

/*############################################
#                                            #
#         sauvegarde_prix_chambres           #
#                                            #
##############################################

Enregistre le tableau dans le fichier PRIX_NUIT.
Appelée par modif_prix_chambre().
Affiche un message de confirmation.

*/

void sauvegarde_prix_chambres()
{
  FILE *f1                                                                     ;
  f1 = fopen(PRIX_NUIT, "w")                                                   ;
  int i                                                                        ;
  struct prix_nuit nuit                                                        ;


  for(i = 0; i < NB_CHAMBRES_PRIX ; i++)
  {
    nuit = tab_prix_chambres[i]                                                ;
    fprintf(f1, "%d %d %.2f %.2f\n", nuit.type_chambre, nuit.categorie_chambre, nuit.prix_hs, nuit.prix_bs) ;
  }
  fclose(f1)                                                                   ;
  printf("Le tableau des prix des nuitées a bien été sauvegardé.\n")           ;
}
