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

Reste à faire:
* Traiter des chaînes de caractères avec espaces.
* optimiser enregistrement sur fichier et cycle de modification des chambres.
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
#define NB_CHAMBRES_PRIX 6 /* nb de chambres différentes dans les prix*/

/*Fichiers*/

#define CALENDRIER "calendrier.txt" /*Nom du fichier contentant le calendrier (dates et saison)*/
#define CAT_SERVICES "catalogue-services.txt" /* Nom du fichier qui contient le catalogue des services*/
#define CHAMBRES  "chambres.txt" /*Nom du fichier contentant les chambres*/
#define PLANNING "planning.txt" /*Nom du fichier contenant le planning*/
#define PRIX_NUIT "prix_nuits.txt" /*Nom du fichier contenant le prix d'une nuitée*/


/*----------------------

Déclarations préliminaires

----------------------*/


/*D'utilité générale*/

void mauvais_choix(int par_choisi)                   ; /* Mauvais choix à l'intérieur des menus*/
long unsigned int jjmmaaaa_vers_aaaammjj(int j, int m, int a) ; /*Prendre une date saisie et la traduire en lonf int date*/


/*Calendrier*/
void lecture_jours()       ; /* Prend les jours présents dans le fichier qui tient compte des jours (et saison) et les charge dans le tableau correspondant.*/
void test_date()           ; /* Vérifie si la date du jour d'aujourd'hui correspond au premier jour dans le tableau et dans le calendrier. Si la date a changé, déclanche la mise à jour dans les deux.*/
void maj_calendrier(int i) ; /*mise à jour*/

/*Chambres*/
int rech_chambre(int chambre_rech)         ;
void chargement_chambres()                 ;
void modification_chambre(int res_chambre) ;
void enreg_chambre()                       ;
void affichage_chambre()                   ;

/*Planning*/
void chargement_planning()                 ;


/*Réservations*/
void creer_reservation()                   ;
void cible_date()                          ;
void cible_chambre()                       ;
void rech_periode(int datearrivee, int datedepart);
void calcul_nuitees()                      ;
int choix_chambre()                        ;
void saisie_client()                       ;
void paiement_resa()                       ;
int rech_resa(int p_num_resa)              ;
void modif_resa_dates_client()             ;
void modif_resa_cha()                      ;
void annulation_resa()                     ;
void annul_dates_client()                  ;
// void annul_chambre()                       ;


/*Gestion des services complémentaires*/
void catalogue_services_menu()             ; /* Menu qui montre les choix possibles pour le catalogue de services*/
void chargement_catalogue_services()       ; /* Prend le fichier des services et le charge en mémoire (dans un tableau). Procédure transparente*/
void affichage_catalogue()                 ; /* Montre le tableau de services*/
void saisie_services()                     ; /* Pour saisir de nouveaux services, à la suite de ceux déjà listés*/
void enreg_catalogue_services()            ; /* Sauvegarde le tableau chargé en mémoire dans un fichier*/
void modif_services()                      ; /* Pour modifier les services déjà listés*/


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
};

struct jour calendrier[ANNEE] ;


/*Prix nuitée*/
struct prix_nuit
{
  int type_chambre        ; /* 0 simple ; 1 double ; 2 triple */
  int categorie_chambre   ; /* 0 chambre ; 1 suite */
  float prix_hs           ; /* prix haute saison */
  float prix_bs           ; /* prix basse saison */
};

struct prix_nuit tab_prix_chambres[NB_CHAMBRES_PRIX] ;


/*Réservations*/

struct resa
{
  long unsigned int code_resa    ; /*long unsigned int, cela en garantit l'unicité sur une période assez longue.*/
  int chambre_resa               ;
  int datearrivee                ;
  int datedepart                 ;
  int nuitees_resa[1]            ; /*case 0 basse saison, case 1 haute saison*/
  char nomclient[50]             ;
  char prenomclient[50]          ;
  char telclient[12]             ;  /*+33653332003 qui peut être affiché +33 6 53 33 20 03. Vérifier de quelle taille doit être le numéro: 12?*/
};

struct resa demande ;
long int nb_resa    ; /*dernière réservation*/
long unsigned int planning[MAX_NB_CHAMBRES][ANNEE] ; /*Les valeurs dans ce tableau sont les codes de réservation. 0 est utilisé pour signaler que la chambre est libre; 1 pour déclarer des travaux.*/

struct resa tab_modif_resa[ANNEE];


int  numcase_resa_chambre; /*Identifie la case dans le tableau planning ou dans tab_chambres qui correspond à la chambre demandée/reservée*/
int numcase_resa_date_debut, numcase_resa_date_fin ; /*identifient la position dans le planning/calendrier de la case où débute et finit la réservation*/
/* Variables globales concernant les chambres*/

struct cha
{  /* structure pour les chambres*/
   /*l'idéntifiant unique de la chambre est son indice dans le tableau des chambres, qui correspond également à l'indice dans le planning, cela permet de relier les deux informations*/
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
};

struct cha tab_chambres[MAX_NB_CHAMBRES] ; /*Tableau listant les chambres*/
struct cha chambre                       ;


int a_sauv_chambre = 0                   ; /*pour la modification des chambres*/



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
      case 1:
        creer_reservation();
        break ;

      case 2: case 3:
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

long unsigned int jjmmaaaa_vers_aaaammjj(int j, int m, int a)
{
  return (a * 10000) + (m * 100) + j ;
}


/*############################################
#                                            #
#          aaaammjj_vers_jjmmaaaa            #
#                                            #
##############################################

Retourne en chaine de caractères jj/mm/aaaa la date fournie en format aaaammjj

*/

char aaaammjj_vers_jjmmaaaa(long unsigned int date)
{
  int annee, mois, jour                         ;
  char temporaire[5];
  char date_chaine[11]                          ;
  annee = date/10000                            ;
  mois = (date - (annee * 10000)) /100          ;
  jour = (date - (annee *10000) - (mois * 100)) ;
  sprintf(temporaire, "%d", annee);
  strcat(date_chaine, temporaire);
  strcat(date_chaine, "/");
  sprintf(temporaire, "%d", mois);
  strcat(date_chaine, temporaire);
  strcat(date_chaine, "/");
  sprintf(temporaire, "%d", jour);
  strcat(date_chaine, temporaire);
  return *date_chaine;
}


/*############################################
#                                            #
#                PARTIE JOURS                #
#        #############################       #
#                                            #
#               lecture_jours                #
#                                            #
##############################################

Prend les jours présents dans le fichier qui tient compte des jours (et saison) et les charge dans le tableau correspondant.

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
  char choix_date = 'f'               ;
  char date_chaine[11], temporaire[5] ;
  int i = 0, a, m, j                  ;

  printf("Test des paramètres\n")     ;
  while(choix_date != 'o')
  {
    date_chaine[0] = '\0'; /*cette ligne et les onze suivantes étaient dans une fonction à part entière, mais retourner une chaîne de caractères et l'affecter à une variable, je ne sais pas faire*/
    a = calendrier[i].date/10000                       ;
    m = (calendrier[i].date - (a * 10000)) / 100       ;
    j = (calendrier[i].date - (a * 10000) - (m * 100)) ;
    sprintf(temporaire, "%d", j)                       ;
    strcat(date_chaine, temporaire)                    ;
    strcat(date_chaine, "/")                           ;
    sprintf(temporaire, "%d", m)                       ;
    strcat(date_chaine, temporaire)                    ;
    strcat(date_chaine, "/")                           ;
    sprintf(temporaire, "%d", a)                       ;
    strcat(date_chaine, temporaire)                    ;
    printf("Aujourd'hui nous sommes le %s (o/n) ? ", date_chaine) ;
    scanf("%c", &choix_date)                           ;
    if(choix_date != 'o')
    {
      if(choix_date == 'n')
      {
        while((poubelle=getchar()) != '\n')            ;
        i++                                            ;
      }
      else
      {
        printf("Choix non accepté. Les choix possibles sont 'o' pour 'oui' ou 'n' pour 'non'.\n") ;
      }
    }
  }
  if(i != 0)
  {
    maj_calendrier(i)                        ;
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
  FILE *f1                            ;
  int j, a, m, d                      ;
  char date_chaine[11], temporaire[5] ;
  char choix_saison = 'z'             ;

  for(j = i; j < ANNEE; j++) /* déplacer les valeurs des jours dans le calendrier: LE FUTUR C'EST MAINTENANT!*/
  {
    calendrier[j-i] = calendrier[j]   ;
  }
  for(j = ANNEE - i; j < ANNEE ; j++) /*créer les cases qui manquent: MORE FUTURE (slogan anti-punk)*/
  {
    date_chaine[0] = '\0'; /*cette ligne et les onze suivantes étaient dans une fonction à part entière, mais retournaient une chaîne de caractères et l'affectaient à une variable, je ne sais pas faire*/
    a = calendrier[j-1].date/10000                       ;
    m = (calendrier[j-1].date - (a * 10000)) / 100       ;
    d = (calendrier[j-1].date - (a * 10000) - (m * 100)) ;
    sprintf(temporaire, "%d", d)                         ;
    strcat(date_chaine, temporaire)                      ;
    strcat(date_chaine, "/")                             ;
    sprintf(temporaire, "%d", m)                         ;
    strcat(date_chaine, temporaire)                      ;
    strcat(date_chaine, "/")                             ;
    sprintf(temporaire, "%d", a)                         ;
    strcat(date_chaine, temporaire)                      ;

    printf("Quel jour vient après le %s (format jj/mm/aaaa) ? ", date_chaine) ;
    scanf("%d/%d/%d", &d, &m, &a)                        ;
    calendrier[j].date = jjmmaaaa_vers_aaaammjj(d, m, a) ;
    while((choix_saison != 'b') && (choix_saison != 'h'))
    {
      printf("Quelle est sa saison (b/h) ? ") ;
      while((poubelle=getchar()) != '\n')     ;
      scanf("%c", &choix_saison)              ;
      if((choix_saison != 'b') && (choix_saison != 'h'))
      {
        printf("Le choix n'est pas valide")   ;
      }
    }
    if(choix_saison == 'b')
    {
      calendrier[j].saison = 0                ;
    }
    else
    {
      calendrier[j].saison = 1                ;
    }
    choix_saison = 'z'                        ; /*réinitialisation de la variable*/
  }
  f1 = fopen(CALENDRIER, "w")                 ;
  for(j = 0 ; j < ANNEE ; j++) /*jusqu'à la fin du tableau*/
  {
    fprintf(f1, "%lu %d\n", calendrier[j].date, calendrier[j].saison) ;
  }
  fclose(f1)                                  ;
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
  FILE *f1                               ;
  int i, j                               ;
  f1 = fopen(PLANNING, "r")              ;
  for(i = 0 ; i < MAX_NB_CHAMBRES ; i++)
  {
    for(j = 0 ; j < ANNEE ; j++)
    {
      fscanf(f1, "%lu", &planning[i][j]) ;
    }
  }
  fclose(f1)                             ;
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


*/
void creer_reservation()
{
  int continue_resa ; /* continue resa permet de savoir si on poursuit ou bien on abandonne le processus. 0 pour abandonner, 1 pour continuer */
  cible_date()       ;
  cible_chambre()    ;

  rech_periode(demande.datearrivee, demande.datedepart) ;
  calcul_nuitees()   ;
  continue_resa = choix_chambre() ;
  if(continue_resa == 1)
  {
    saisie_client();
    paiement_resa() ;
    /*
    maj_planning   ;
    */
  }
}

/*############################################
#                                            #
#                cible_date                  #
#                                            #
##############################################

Procédure pour saisir une date.


*/
void cible_date()
{
  int jour_debut, mois_debut, annee_debut ;
  int jour_fin, mois_fin, annee_fin       ;
  printf("Saisir la date de début (jj/mm/aaaa) : ")                                ;
  scanf("%d/%d/%d", &jour_debut, &mois_debut, &annee_debut)                        ;
  demande.datearrivee = jjmmaaaa_vers_aaaammjj(jour_debut, mois_debut, annee_debut);
  printf("Saisir la date de la dernière nuitée (jj/mm/aaaa) : ")                   ;
  scanf("%d/%d/%d", &jour_fin, &mois_fin, &annee_fin)                              ;
  demande.datedepart = jjmmaaaa_vers_aaaammjj(jour_fin, mois_fin, annee_fin)       ;
}

/*############################################
#                                            #
#              cible_chambre                 #
#                                            #
##############################################

Procédure pour déterminer quelle chambre recherche le client.
Les données sont chargées dans la struct cha chambre.
Dans un premier temps on contraint à spécifier tout choix, on ne permet pas de déclarer un critère comme indifférent (ceci est une évolution envisageable).
*/
void cible_chambre()
{
  /*ce n'est pas nécessaire, on le déduit d cible_type_lits int cible_type_chambre ; /* 1 lit simple, 2 double, 3 triple*/
  int cible_cat_chambre  ; /* 0 chambre, 1 suite*/
  int cible_type_lits    ; /* 1 lit simple, 2 deux lits simples, 3 lit double, 4 trois lits simples, 5 lit simple et lit double */
  int cible_balcon       ; /* 0 pas, 1 balcon, 2 indifférent*/
  int cible_vue          ; /* 0 pas, 1 vue, 2 indifférent*/
  int cible_bain         ; /* 0 pas, 1 douche, 2 indifférent*/
  int cible_fumeur       ; /* 0 pas, 1 fumeur, 2 indifférent*/
  int cible_animaux      ; /* 0 pas, 1 animaux acceptés, 2 indifférent*/
  printf("Quel type de lits ?\n")                ;
  printf("1 - un lit simple\n")                  ;
  printf("2 - deux lits simples\n")              ;
  printf("3 - un lit double\n")                  ;
  printf("4 - trois lits simples\n")             ;
  printf("5 - un lit double et un lit simple\n") ;
  printf("Saisir le type de lits :")             ;
  scanf("%d", &cible_type_lits)                  ;
  chambre.type_lits = cible_type_lits            ;

  switch(cible_type_lits)
  {
    case 1 :
      chambre.type_chambre = 1                   ;
      break                                      ;
    case 2 :
    case 3 :
      chambre.type_chambre = 2                   ;
      break                                      ;
    case 4 :
    case 5 :
      chambre.type_chambre = 3                   ;
      break                                      ;
  }
  printf("Quelle catégorie de chambre ?\n")     ;
  printf("0 - chambre\n")                        ;
  printf("1 - suite\n")                          ;
  printf("Saisir la catégorie :")                ;
  scanf("%d", &cible_cat_chambre)                ;
  chambre.categorie_chambre = cible_cat_chambre  ;
  printf("Chambre avec balcon ? ")               ;
  printf("0 - pas de balcon\n")                  ;
  printf("1 - balcon\n")                         ;
/*  printf("2 -indifférent\n")                    ;*/
  printf("Balcon :")                             ;
  scanf("%d", &cible_balcon)                     ;
  chambre.balcon = cible_balcon                  ;
  printf("Quel type de salle de bain ?")         ;
  printf("0 - baignoire\n")                      ;
  printf("1 - douche\n")                         ;
/*  printf("2 - indifférent\n")                   ;*/
  printf("Saisir le type de salle de bain :")    ;
  scanf("%d", &cible_bain)                       ;
  chambre.bain = cible_bain                      ;
  printf("Chambre avec vue ? ")                  ;
  printf("0 - pas de vue\n")                     ;
  printf("1 - vue\n")                            ;
/*  printf("2 - indifférent\n")                   ;*/
  printf("Vue :")                                ;
  scanf("%d", &cible_vue)                        ;
  chambre.vue = cible_vue                        ;
  printf("Chambre pour fumeur ? ")               ;
  printf("0 - non fumeur\n")                     ;
  printf("1 - fumeur\n")                         ;
/*  printf("2 - indifférent\n")                   ;*/
  printf("Fumeur :")                             ;
  scanf("%d", &cible_fumeur)                     ;
  chambre.fumeur = cible_fumeur                  ;
  printf("Chambre avec animaux autorisés? ")     ;
  printf("0 - animaux non autorisés\n")          ;
  printf("1 - animaux autorisés\n")              ;
/*  printf("2 - indifférent\n")                   ;*/
  printf("Animaux autorisés :")                  ;
  scanf("%d", &cible_animaux)                    ;
  chambre.animaux = cible_animaux                ;
}




/*############################################
#                                            #
#             rech_periode                   #
#                                            #
##############################################

*/

void rech_periode(int datearrivee, int datedepart)
{

/*demande.date arrivee parcourir le tableau pour trouver la même valeur: indice
de la case de la date et boucler à partir de la date vers la suivante pour avoir les deux indices*/

  int i                        ;

  for(i = 0 ; i < 2 ; i++)
  {
    nuitees_demande[i] = 0 ;
  }
  i = 0                    ;

  numcase_resa_date_debut=NON_TROUVE   ;
  numcase_resa_date_fin=NON_TROUVE   ;

  while((i<ANNEE)&&(numcase_resa_date_debut==NON_TROUVE))
  {
    if(datearrivee==calendrier[i].date)
    {
      numcase_resa_date_debut=i ;
      if(calendrier[i].saison == 0)
      {
        nuitees_demande[0]++  ;
      }
      else
      {
        nuitees_demande[1]++ ;
      }
    }
    else
    {
      i++               ;
    }
  }
  if (numcase_resa_date_debut!=NON_TROUVE)
  {
    while ((i<ANNEE)&&(numcase_resa_date_fin==NON_TROUVE))
    {
      if(datedepart==calendrier[i].date)
      {
        numcase_resa_date_fin=i ;
      }
      else
      {
        i++               ;
      }
    }
  }
  else
  {
      printf("Date d'arrivée non trouvée\n") ;
  }
  if (numcase_resa_date_fin!=NON_TROUVE)
  {
    return nuitees_demande                           ;
  }
  else
  {
      printf("Date de départ non trouvée\n") ;
  }
}

/*############################################
#                                            #
#             calcul_nuitees                 #
#                                            #
##############################################

Renseigne les deux cases du tableau demande.nuitees_resa en regardant dans le calendrier[].saison
saison = 0 : basse saison
saison = 1 : haute saison

[0] = basse saison
[1] = haute saison

*/

void calcul_nuitees()
{
  d
}

/*############################################
#                                            #
#             choix_chambre                  #
#                                            #
##############################################
Dans les bornes du planning données par rech_periode, recherche de chambres avec code de réservation qui indique qu'elles sont libres.
On désigne une liste des chambres possibles.
On demande d'en choisir une ou bien de renoncer.
*/
int choix_chambre()
{
  int chambres_ok[MAX_NB_CHAMBRES]    ;
  int chambres_dispo[MAX_NB_CHAMBRES] ;
  int i, j, k, l, m, test, chambre_choisie ;
  j = 0                               ;


  /* On trouve les chambres qui correspondent à la chambre souhaitée */

  for(i=0 ; i < MAX_NB_CHAMBRES ; i++)
  {
    if
    (
      (chambre.type_chambre == tab_chambres[i].type_chambre) &&
      (chambre.type_lits == tab_chambres[i].type_lits) &&
      (chambre.categorie_chambre == tab_chambres[i].categorie_chambre) &&
      (chambre.balcon == tab_chambres[i].balcon) &&
      (chambre.bain == tab_chambres[i].bain) &&
      (chambre.vue == tab_chambres[i].vue) &&
      (chambre.fumeur == tab_chambres[i].fumeur) &&
      (chambre.animaux == tab_chambres[i].animaux)
    )
    {
    chambres_ok[j] = i ;
    j++                ;
    }
  }

  printf("Chambres correspondant à la demande : %d\n", j) ;

  /*On teste leur disponibilité sur la période demandée*/
  l = 0 ; /*décompte des chambres disponibles*/
  if(j > 0)
  {
    for(i = 0 ; i < j ; i++)
    {
      k = chambres_ok[i]  ;
      m = demande_ind_deb ;
      while((test==1)&&(m <= demande_ind_fin))
       /*disponibilité sur le premier jour*/
      {
        test = 1 ;
          if(planning[k][m] != 0)
          {
            test = 0 ;
          }
          else
          {
            m++ ;
          }
      }
      if(test == 1)
      {
        chambres_dispo[l] = chambres_ok[i] ;
        l++                                ;
      }
    }
  }
  else
  {
    printf("Pas de réservation possible.\n") ;
    return(0)                               ;
    /*Offrir la possibilité de modifier les critères de chambre*/
  }
  /*Si l == 0, pas de choix disponibles dans la période, avec les critères donnés*/
  if(l==0)
  {
    printf("Il n'y a pas de chambres disponibles dans la période définie selon les critères donnés\n") ;
    return(0) ;
    /*Offir la possibilité de modifier les critères de date*/
  }
  else
  {
    printf("Chambres disponibles : %d\n", l) ;
    for(i=0; i < l; i++)
    {
      j = chambres_dispo[i] ;
      printf("Chambre n.%d\n", tab_chambres[j].num_chambre);
    }
  }
  test = NON_TROUVE ;
  while(test == NON_TROUVE)
  {
    printf("Choisir la chambre à réserver (0 pour quitter) : ") ;
    scanf("%d", &chambre_choisie)              ;
    if(chambre_choisie = 0)
    {
      return(0) ;
    }
    else
    {

      i = 0 ;
      while((test == NON_TROUVE) || (i < l)) /*test pour vérifier que le choix fait est parmi les choix possibles*/
      {
        j = chambres_dispo[i] ;
        if(chambre_choisie == tab_chambres[j].num_chambre)
        {
          test = 1 ;
        }
        else
        {
          i++ ;
        }
      }
      if(test == NON_TROUVE)
      {
        printf("Le choix n'est pas valide. Choisir une des chambres disponibles affichées.\n");
      }
      return(1) ;
    }
  }
}

/*############################################
#                                            #
#             saisie_client                  #
#                                            #
##############################################

*/
void saisie_client()
{
  char nom_client[100], prenom_client[200], numero_telephone_client[20];
  printf("Nom du client ")          ;
  scanf("%s", demande.nomclient)    ;
  printf("Prénom du client ")       ;
  scanf("%s", demande.prenomclient) ;
  printf("Numéro de téléphone ")    ;
  scanf("%s", demande.telclient)    ;
}

/*############################################
#                                            #
#             paiement_resa                  #
#                                            #
##############################################

*/
void paiement_resa()
{/*
  float total_resa ;
  int mode_paiment = 0, nb_nuitee, i, test = 0 ;
  struct prix_nuit nuit ;
  FILE *f1;

  nuit.type_chambre=type_chambre;
  nuit.categorie_chambre=categorie_chambre;
  f1=fopen(FICHIER_PRIX_CHAMBRES, "w");
  for (i=0; i<NB_CHAMBRES_PRIX; i++)
  {
  fscanf(f1, "%d %d %f %f", &tab_prix_chambres[i].type_chambre, &tab_prix_chambres[i].categorie_chambre, &tab_prix_chambres[i].prix_hs, &tab_prix_chambres[i].prix_bs);
  }
    i= -1;
    while (test == 0)
    {
      i++ ;
      if (tab_prix_chambres[i].type_chambre==nuit.type_chambre)
      {
        if (tab_prix_chambres[i].categorie_chambre==nuit.categorie_chambre)
        {
          nuit=tab_prix_chambres[i];
          test = 1 ;
        }
      }
    }
  total_resa=(nb_nuitee_hs*nuit.prix_hs)+(nb_nuitee_bs*nuit.prix_bs);

  printf("Montant à payer : %f", &total_resa);
  printf("Choisir le mode de paiement: ")      ;
  printf("1- Espèces : )                       ;
  printf("2- Chèque : )                        ;
  printf("3- Carte bancaire : )                ;
  printf("4- Virement : )                      ;
  scanf("%d", &mode_paiment)                   ;
  printf("Le paiement a bien été effectué. ")  ;
  /*à ce moment on imprime toutes les données de la réservation et du moyen de paiement dans un fichier numero_reservation_paiement_resa.txt
  */
}


/*############################################
#                                            #
#             rech_resa                      #
#                                            #
##############################################

Rechercher une réservation par son numéro dans planning[MAX_NB_CHAMBRES][ANNEE]
pour chaque jour, je parcours toutes les chambres et on s'arrete quand on trouve un num égal à

*/

int rech_resa(int p_num_resa)
{
  int i=0, j=0, k, numcase_resa_date_debut=NON_TROUVE,
  numcase_resa_date_fin=NON_TROUVE, numcase_resa_chambre=NON_TROUVE;
  while (j<ANNEE)
  {
    while ((i<MAX_NB_CHAMBRES)&&(numcase_resa_date_debut==NON_TROUVE))
    {
     if(p_num_resa==planning[i][j])
     {
      numcase_resa_date_debut = j;
      numcase_resa_chambre = i   ;
     }
     else
     {
      i++;
     }
    }
    j++;
    if(numcase_resa_date_debut!=NON_TROUVE)
    {
      k = numcase_resa_date_debut+1;
      while (k<ANNEE)
      {
        if (planning[numcase_resa_chambre][k]==p_num_resa)
        {
          numcase_resa_date_fin = k ;
        }
        else
        {
          k++;
        }
      }
    }
  }
  return numcase_resa ;
}


/*############################################
#                                            #
#             modif_resa_dates_client        #
#                                            #
##############################################

Modification d'une réservation : partie dates et client

*/
void modif_resa_dates_client()
{
  char nom_client[100], prenom_client[200], numero_telephone_client[20];
  int jour_debut, mois_debut, annee_debut ;
  int jour_fin, mois_fin, annee_fin       ;
  int numero, numresa                     ;
  struct resa modif                       ;
  numero=rech_resa(numresa)               ;
  if (numero==NON_TROUVE)
  {
    printf("Modification impossible: le numéro de réservation %d n'a pas été trouvé. \n", numresa) ;
  }
  else
  {
    modif=tab_modif_resa[numero]                                                        ;
    printf("Date actuelle de début  : %d/%d/%d \n", jour_debut, mois_debut, annee_debut);
    printf("Saisir la nouvelle date de début (jj/mm/aaaa) : ")                          ;
    scanf("%d/%d/%d", &jour_debut, &mois_debut, &annee_debut)                           ;
    demande.datearrivee = jjmmaaaa_vers_aaaammjj(jour_debut, mois_debut, annee_debut)   ;
    printf("Date actuelle de fin  : %d/%d/%d \n", jour_fin, mois_fin, annee_fin)        ;
    printf("Saisir la date de la dernière nuitée (jj/mm/aaaa) : ")                      ;
    scanf("%d/%d/%d", &jour_fin, &mois_fin, &annee_fin)                                 ;
    demande.datedepart = jjmmaaaa_vers_aaaammjj(jour_fin, mois_fin, annee_fin)          ;
    modif_resa_cha()                                                                    ;
    if (modif_chambre_OK)  //SI DES CHAMBRES SONT DISPO DURANT LA PÉRIODE
    {
      printf("Nom actuel du client : \n", nom_client)                                     ;
      printf("Nouveau nom du client : ")                                                  ;
      scanf("%s", nom_client)                                                             ;
      printf("Prénom actuel du client : \n", prenom_client)                               ;
      printf("Nouveau prénom du client : ")                                               ;
      scanf("%s", prenom_client)                                                          ;
      printf("Numéro de téléphone actuel : \n", numero_telephone_client)                  ;
      printf("Nouveau numéro de téléphone : ")                                            ;
      scanf("%s", numero_telephone_client)                                                ;
      tab_modif_resa[numero]=modif                                                        ;
    }
  }
}

/*############################################
#                                            #
#              modif_cha_origine             #
#                                            #
##############################################

Origine de la modification d'une chambre
*//*
void modif_cha_origine()
{
  printf("Quelle est la raison de la modification ? ");
  printf("1 - Travaux \n")                            ;
  printf("2 - Décision du client \n")                 ;
  printf("3 - Décision de l'hôtel \n")                ;
  scanf("%d", &raison_modif)                          ;
  switch (raison_modif)
{
    case 1:
      travaux();
    break;
    case 2:
      modif_resa_cha();
    break;
    case 3:
      annulation_resa();
    break;
    default:
      printf("Erreur de saisie. \n");
    break;
 }
}
*/

/*############################################
#                                            #
#              modif_resa_cha                #
#                                            #
##############################################

Modification de la réservation : partie chambres
Saisie d'une nouvelles chambre
Cherche si dispo durant période
*/
void modif_resa_cha()
{
  int cible_cat_chambre             ; /* 0 chambre, 1 suite*/
  int cible_type_lits               ; /* 1 lit simple, 2 deux lits simples, 3 lit double, 4 trois lits simples, 5 lit simple et lit double */
  int cible_balcon                  ; /* 0 pas, 1 balcon, 2 indifférent*/
  int cible_vue                     ; /* 0 pas, 1 vue, 2 indifférent*/
  int cible_bain                    ; /* 0 pas, 1 douche, 2 indifférent*/
  int cible_fumeur                  ; /* 0 pas, 1 fumeur, 2 indifférent*/
  int cible_animaux                 ; /* 0 pas, 1 animaux acceptés, 2 indifférent*/
  int numero, numresa, raison_modif ;
  struct cha modif                  ;
  printf("Saisir les critères de la chambre souhaitée :   ");
  modif=rech_resa(numresa)  ;
  printf("Type actuel de chambre : %d \n", chambre.type_lits);
  printf("Nouveau type de chambre : ")           ;
  printf("1 - un lit simple\n")                  ;
  printf("2 - deux lits simples\n")              ;
  printf("3 - un lit double\n")                  ;
  printf("4 - trois lits simples\n")             ;
  printf("5 - un lit double et un lit simple\n") ;
  scanf("%d", &cible_type_lits)                  ;
  chambre.type_lits = cible_type_lits            ;
  switch(cible_type_lits)
  {
    case 1 :
      chambre.type_chambre = 1                   ;
      break                                      ;
    case 2 :
    case 3 :
      chambre.type_chambre = 2                   ;
      break                                      ;
    case 4 :
    case 5 :
      chambre.type_chambre = 3                   ;
      break                                      ;
  }
  printf("Catégorie actuelle de la chambre : %d \n", chambre.categorie_chambre);
  printf("Nouvelle catégorie :")                 ;
  printf("0 - chambre\n")                        ;
  printf("1 - suite\n")                          ;
  scanf("%d", &cible_cat_chambre)                ;
  chambre.categorie_chambre = cible_cat_chambre  ;
  printf("Présence d'un balcon ou non actuellement : %d \n", chambre.balcon);
  printf("Balcon :")                             ;
  printf("0 - pas de balcon\n")                  ;
  printf("1 - balcon\n")                         ;
  scanf("%d", &cible_balcon)                     ;
  chambre.balcon = cible_balcon                  ;
  printf("Type actuel de salle de bain : %d \n", chambre.bain);
  printf("Saisir le type de salle de bain : ")   ;
  printf("0 - baignoire\n")                      ;
  printf("1 - douche\n")                         ;
  scanf("%d", &cible_bain)                       ;
  chambre.bain = cible_bain                      ;
  printf("Chambre avec vue actuellement : %d\n", chambre.vue);
  printf("Vue :")                                ;
  printf("0 - pas de vue\n")                     ;
  printf("1 - vue\n")                            ;
  scanf("%d", &cible_vue)                        ;
  chambre.vue = cible_vue                        ;
  printf("Fumeurs autorisés actuellement \n", chambre.fumeur);
  printf("Fumeur : %d ", chambre.fumeur)         ;
  printf("0 - non fumeur\n")                     ;
  printf("1 - fumeur\n")                         ;
  scanf("%d", &cible_fumeur)                     ;
  chambre.fumeur = cible_fumeur                  ;
  printf("Chambre avec animaux autorisés actuellement : %d \n", chambre.animaux);
  printf("Animaux autorisés :")                  ;
  printf("0 - animaux non autorisés\n")          ;
  printf("1 - animaux autorisés\n")              ;
  scanf("%d", &cible_animaux)                    ;
  chambre.animaux = cible_animaux                ;
  tab_modif_resa[numero]=modif                   ;
}

/*############################################
#                                            #
#             annulation_resa                #
#                                            #
##############################################

*/
/*
void annulation_resa()
{
  int ecart_jour, j, m, a, datedujour                  ;
  float total_resa                                     ;
  calendrier[0].date = jjmmaaaa_vers_aaaammjj(j, m, a) ;
  datedujour=calendrier[0].date                        ;
  void annul_dates_client()                            ;
  void annul_chambre()                                 ;
  printf("L'annulation a bien été effectuée. \n")      ;
  ecart_jour=jour_debut-datedujour                    ;
  if (ecart_jour>14)
  {
    printf("Remboursement de 70%, soit %f \n", 0.7*total_resa);
  }
  else
  {
   if (ecart_jour>7)
   {
    printf("Remboursement de 30%, soit %f \n", 0.3*total_resa);
   }
   else
   {
    printf("Pas de remboursement.");
   }
  }
}

/*############################################
#                                            #
#             annul_dates_client             #
#                                            #
##############################################

*/
/*
void annul_dates_client()
{
  int numero, numresa, i                    ;
  struct resa modif                         ;
  numero=rech_resa(numresa)                 ;
  if (numero==NON_TROUVE)
  {
    printf("Annulation impossible: le numéro de réservation %d n'a pas été trouvé. \n", numresa);
  }
  else
  {
    tab_modif_resa[numero]=modif              ;
    modif=tab_modif_resa[numero]              ;
    for (i=numero; i<ANNEE; i++)
    {
      tab_modif_resa[i]=tab_modif_resa[i+1]   ;
    }
  }
}


/*############################################
#                                            #
#             annul_chambre                  #
#                                            #
##############################################

*/
/*
void annul_chambre()
{

}

/*############################################
#                                            #
#              PARTIE NOTES                  #
#       #############################        #
#                                            #
#             recherche_note                 #
#                                            #
##############################################

On demande la saisie du numéro de réservation, on récupère la note correspondante. Elle sera passée au programme d'affichage, de paiement ou bien d'ajout.

void recherche_note()
{
  char num_note[15] ;
  int choix_note ;
  long unsigned int num_resa ;

  printf("Saisir le numéro de réservation : ") ;
  scanf("%lu", num_resa) ;
  sprintf(num_note, "%lu", num_resa) ;
  strcat(num_note, "_note.txt") ;
  printf(" 1 - Afficher la note\n"); /*menu de choix
  printf(" 2 - Ajouter une entrée sur la note\n");
  printf(" 3 - Régler la note\n");
  printf(" 9 - Quitter et revenir au menu principal\n");
  printf("Faire un choix : ");
  scanf("%d", &choix_note);
  switch(choix_note)  /* passe num_note au programme suivant, selon le choix
  {
    case 1:
      affichage_note(num_note);
      break;
    case 2:
      ajout_note(num_note);
      break;
    case 3:
      paiement_note(num_note);
      break;
    case 9:
      printf("Retour au menu principal\n");
      break;
  }
}

/*############################################
#                                            #
#              affichage_note                #
#                                            #
##############################################

Appelée par recherche_note, prend en argument le nom du fichier de la note (num_note). Elle vérifie si le fichier existe. Si oui, l'affiche, sinon elle previent l'utilisateur.
Sortie par un menu de choix.


void affichage_note(char num_note[])
{
  FILE *f1;
  float total_commande = 0, prix_commande ;
  int choix_note ;
  /*il faut utiliser stat, apparemment, qui a besoin d'une structure


  /*vérification de l'existence du fichier
  if()/* si le fichier n'existe pas
  {
    printf("Il n'existe pas de note pour cette réservation. Pour en créer une, ajouter une entrée.\n\n") ;
    printf("Choix possibles :\n\n");
    printf("1 - Rechercher une autre note\n");
    printf("2 - Ajouter une entrée à cette note\n");
    printf("9 - Revenir au menu principal\n");
    printf("Faire un choix : ");
    scanf("%d", choix_note) ;
    switch(choix_note)
    {
      case 1:
        recherche_note();
        break;
      case 2:
        ajout_note(num_note);
        break;
      case 3:
        paiement_note(num_note);
        break;
      case 9:
        printf("Retour au menu principal\n");
        break;
     }
/*toute la suite va dans un else: si le fichier existe
     else
     {
       f1 = fopen(num_note);

       while(!feof(f1))
       {
         fscanf(f1, ""); /*déterminer la structure de la note: jj/mm/aaaa commande prix?
         printf(""); affichage de chaque entrée de la note
         total_note += prix_commande ;
       }
       printf("___________________________________________\n");
       printf("Total de la note : %f euros\n\n", total_note) ; /* et €, ça passerait? -> ça fonctionne dans affichage_catalogue()
       printf("Choix possibles :\n\n")
       printf("1 - Rechercher une autre note\n");
       printf("2 - Ajouter une entrée à cette note\n");
       printf("3 - Régler cette note\n");
       printf("9 - Revenir au menu principal\n");
       printf("Faire un choix : ");
       scanf("%d", choix_note) ;
       switch(choix_note)
       {
         case 1:
           recherche_note();
           break;
         case 2:
           ajout_note(num_note);
           break;
         case 3:
           paiement_note(num_note);
           break;
         case 9:
           printf("Retour au menu principal\n");
           break;
       }
     }
}

/*############################################
#                                            #
#                ajout_note                  #
#                                            #
##############################################
Ajoute une entrée depuis le catalogue des services.
Prend en paramètre l'identifiant d'une note.
Si la note n'existe pas, elle sera créée.


void ajout_note(char num_note[])
{
  char date[11];
  FILE *f1;


  /* ici une recherche dans le tableau des services
  printf("");
  f1 = fopen(num_note, ""); /* il n'y aurait pas de 'append'?
  fclose(f1);
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

void paiement_note(char num_note[])
{
  FILE *f1;

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
      printf("%s\n", nom_serv);
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

Enregistre le tableau dans le fichier CAT_SERVICES.
Affiche un message de confirmation.

*/

void enreg_catalogue_services(){
  FILE *f1                                  ;
  f1 = fopen(CAT_SERVICES, "w") ;
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

Lit le fichier CAT_SERVICES et charge son contenu dans le tableau de services.

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
  struct entree_service service                                           ;
  int i                                                                   ;
  if(nb_services == 0)
  {
    printf("Le catalogue des services est vide.\n")                       ;
  }
  else
  {
    for(i=0; i < nb_services; i++)
    {
      service = catalogue_services[i]                                     ;
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
  FILE *f1                                                  ;
  f1 = fopen("CHAMBRES", "w")                               ;
  int i                                                     ;

  for(i = 0; i < MAX_NB_CHAMBRES ; i++)
  {
    chambre = tab_chambres[i]                               ;
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
