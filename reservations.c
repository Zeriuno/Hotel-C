#include "declarations.h" /*c'est ici que sont les #include et les #define*/



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


/* Variables globales concernant les frais*/
struct frais
{
long int datefrais                     ; /*autrement on en fera une string de 9, 'aaaammjj' (8) + '\0'*/
float montantfrais                     ;
char  nomfrais[MAX_NOM_SERVICE]        ;
}                                        ;


/*############################################
#                                            #
#             PARTIE RESERVATIONS            #
#       #############################        #
#                                            #
#             dernier_code_resa              #
#                                            #
##############################################

Cherche dans le fichier qui contient le numéro de la dernière réservation faite.
Lancée au démarrage.
Le code 0 indique que la chambre est libre, le code 1 est réservé pour la déclaration de travaux.

*/

void dernier_code_resa()
{
  FILE *f1                    ;
  f1 = fopen(RESA_CODE, "r")  ;
  fscanf(f1, "%lu", &nb_resa) ;
  fclose(f1)                  ;
}

/*############################################
#                                            #
#              chargement_prix               #
#                                            #
##############################################

Au démarrage, récupère les prix des nuitées et les charge dans un tableau, variable globale.

*/

void chargement_prix()
{
  FILE *f1                 ;
  int i                    ;

  f1=fopen(PRIX_NUIT, "r") ;
  for (i=0; i<NB_CHAMBRES_PRIX; i++)
  {
    fscanf(f1, "%d %d %f %f", &tab_prix_chambres[i].type_chambre, &tab_prix_chambres[i].categorie_chambre, &tab_prix_chambres[i].prix_hs, &tab_prix_chambres[i].prix_bs) ;
  }
}

/*############################################
#                                            #
#             creer_reservation              #
#                                            #
##############################################

Procédure pour créer une réservation.


*/
void creer_reservation()
{
  int continue_resa, kell_resa, t1 = 0, t2                  ; /* continue resa permet de savoir si on poursuit ou bien on abandonne le processus. 0 pour abandonner, 1 pour continuer */

  printf("Création de réservation.\n")                      ;
  cible_date()                                              ;
  while(t1 == 0)
  {
    printf("Sélection de la chambre :\n")                   ;
    printf("-1- Spécification de tous les critères\n")      ;
    printf("-2- Par type de lits et catégorie seulement\n") ;
    printf("-3- Retour au menu principal\n")                ;
    printf("Choix : ")                                      ;
    t2 = scanf("%d", &kell_resa)                            ;
    if(t2 == 0)
    {
      printf("Erreur de saisie.\n")                         ;
      while((poubelle=getchar()) != '\n')                   ;
    }
    else
    {
      if(kell_resa > 3)
      {
        mauvais_choix(kell_resa)                            ;
      }
      else
      {
        t1 = 1                                              ;
      }
    }
  }
  if(kell_resa == 1)
  {
    cible_chambre()                                         ;
    rech_periode(demande.datearrivee, demande.datedepart)   ;
    calcul_nuitees()                                        ;
    continue_resa = choix_chambre()                         ;
    if(continue_resa == 1)
    {
      saisie_client()                                       ;
      nouveau_nb_resa()                                     ;
      paiement_resa()                                       ; /* Comme le paiement est supposé être toujours effectué avec succès, pas de test pour décider si poursuivre ou pas. */
      sauvegarde_resa()                                     ;
      creation_note()                                       ; /* On crée la note, vide. À partir de ce moment le client peut faire des commandes qui seront enregistrées.*/
      maj_planning()                                        ;
    }
  }
  else
  {
    if(kell_resa == 2)
    {
      cible_chambre_simple();
      rech_periode(demande.datearrivee, demande.datedepart) ;
      calcul_nuitees()                                      ;
      continue_resa = choix_chambre_simple()                ;
      if(continue_resa == 1)
      {
        saisie_client()                                     ;
        nouveau_nb_resa()                                   ;
        paiement_resa()                                     ; /* Comme le paiement est supposé être toujours effectué avec succès, pas de test pour décider si poursuivre ou pas. */
        sauvegarde_resa()                                   ;
        creation_note()                                     ; /* On crée la note, vide. À partir de ce moment le client peut faire des commandes qui seront enregistrées.*/
        maj_planning()                                      ;
      }
    }
    else
    {
      printf("Abandon.\nRetour au menu principal\n")        ;
    }
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
  int jour_debut, mois_debut, annee_debut                                             ;
  int jour_fin, mois_fin, annee_fin                                                   ;
  short int  test                                                                     ; /*test 0: FAUX; test 1: VRAI*/

  test = 0                                                                            ;
  while(test == 0)
  {
    printf("Saisir la date de début (jj/mm/aaaa) : ")                                 ;
    scanf("%d/%d/%d", &jour_debut, &mois_debut, &annee_debut)                         ;
    demande.datearrivee = jjmmaaaa_vers_aaaammjj(jour_debut, mois_debut, annee_debut) ;
    if((demande.datearrivee < calendrier[0].date)|| (demande.datearrivee > calendrier[ANNEE-1].date))
    {
      printf("Date fausse.\n")                                                        ;
      while((poubelle=getchar()) != '\n')                                             ;
    }
    else
    {
      test = 1                                                                        ;
    }
  }

  test = 0                                                                            ;
  while(test == 0)
  {
    printf("Saisir la date de la dernière nuitée (jj/mm/aaaa) : ")                    ;
    scanf("%d/%d/%d", &jour_fin, &mois_fin, &annee_fin)                               ;
    demande.datedepart = jjmmaaaa_vers_aaaammjj(jour_fin, mois_fin, annee_fin)        ;
    if((demande.datedepart < demande.datearrivee)||(demande.datedepart > calendrier[ANNEE-1].date))
    {
      printf("Date fausse.\n")                                                        ;
      while((poubelle=getchar()) != '\n')                                             ;

    }
    else
    {
      test = 1                                                                        ;
    }
  }
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
  /*ce n'est pas nécessaire, on le déduit d cible_type_lits int cible_type_chambre dont les valeurs possibles sont 1 lit simple, 2 double, 3 triple*/
  int cible_cat_chambre  ; /* 0 chambre, 1 suite*/
  int cible_type_lits    ; /* 1 lit simple, 2 deux lits simples, 3 lit double, 4 trois lits simples, 5 lit simple et lit double */
  int cible_balcon       ; /* 0 pas, 1 balcon, 2 indifférent*/
  int cible_vue          ; /* 0 pas, 1 vue, 2 indifférent*/
  int cible_bain         ; /* 0 pas, 1 douche, 2 indifférent*/
  int cible_fumeur       ; /* 0 pas, 1 fumeur, 2 indifférent*/
  int cible_animaux      ; /* 0 pas, 1 animaux acceptés, 2 indifférent*/
  int test = 0           ;

  cible_type_lits = 999  ;
  while((cible_type_lits < 1) || (cible_type_lits > 5))
  {
    printf("Quel type de lits ?\n")                ;
    printf("-1- un lit simple\n")                  ;
    printf("-2- deux lits simples\n")              ;
    printf("-3- un lit double\n")                  ;
    printf("-4- trois lits simples\n")             ;
    printf("-5- un lit double et un lit simple\n") ;
    printf("Saisir le type de lits : ")            ;
    test = scanf("%d", &cible_type_lits)           ;
    if(test == 0)
    {
      printf("Erreur de saisie.\n")                ;
      while((poubelle=getchar()) != '\n')          ;
    }
    else
    {
      if((cible_type_lits < 1) || (cible_type_lits > 5))
      {
        printf("Choix non valide.\n")              ;
      }
    }

  }
  chambre.type_lits = cible_type_lits              ;

  switch(cible_type_lits)
  {
    case 1 :
      chambre.type_chambre = 1                     ;
      break                                        ;
    case 2 :
    case 3 :
      chambre.type_chambre = 2                     ;
      break                                        ;
    case 4 :
    case 5 :
      chambre.type_chambre = 3                     ;
      break                                        ;
  }

  cible_cat_chambre = 999                          ;
  while((cible_cat_chambre < 0) || (cible_cat_chambre > 1))
  {
    printf("Quelle catégorie de chambre ?\n")      ;
    printf("-0- chambre\n")                        ;
    printf("-1- suite\n")                          ;
    printf("Saisir la catégorie : ")               ;
    test = scanf("%d", &cible_cat_chambre)         ;
    if(test == 0)
    {
      printf("Erreur de saisie.\n")                ;
      while((poubelle=getchar()) != '\n')          ;
    }
    else
    {
      if((cible_cat_chambre < 0) || (cible_cat_chambre > 1))
      {
        printf("Choix non valide.\n")              ;
      }
    }
  }
  chambre.categorie_chambre = cible_cat_chambre    ;

  cible_balcon = 999                               ;
  while((cible_balcon < 0) || (cible_balcon > 1))
  {
    printf("Chambre avec balcon ?\n")              ;
    printf("-0- pas de balcon\n")                  ;
    printf("-1- balcon\n")                         ;
    printf("Choix : ")                             ;
    test = scanf("%d", &cible_balcon)              ;
    if(test == 0)
    {
      printf("Erreur de saisie.\n")                ;
      while((poubelle=getchar()) != '\n')          ;
    }
    else
    {
      if((cible_balcon < 0) || (cible_balcon > 1))
      {
        printf("Choix non valide.\n")              ;
      }
    }
  }
  chambre.balcon = cible_balcon                    ;

  cible_bain = 999                                 ;
  while((cible_bain < 0) || (cible_bain > 1))
  {
    printf("Quel type de salle de bain ?\n")       ;
    printf("-0- baignoire\n")                      ;
    printf("-1- douche\n")                         ;
    printf("Choix : ")    ;
    test = scanf("%d", &cible_bain)                ;
    if(test == 0)
    {
      printf("Erreur de saisie.\n")                ;
      while((poubelle=getchar()) != '\n')          ;
    }
    else
    {
      if((cible_bain < 0) || (cible_bain > 1))
      {
        printf("Choix non valide.\n")              ;
      }
    }
  }
  chambre.bain = cible_bain                        ;

  cible_vue = 999                                  ;
  while((cible_vue < 0) || (cible_vue > 1))
  {
    printf("Chambre avec vue ?\n")                 ;
    printf("-0- pas de vue\n")                     ;
    printf("-1- vue\n")                            ;
    printf("Choix : ")                             ;
    test = scanf("%d", &cible_vue)                 ;
    if(test == 0)
    {
      printf("Erreur de saisie.\n")                ;
      while((poubelle=getchar()) != '\n')          ;
    }
    else
    {
      if((cible_vue < 0) || (cible_vue > 1))
      {
        printf("Choix non valide.\n")              ;
      }
    }
  }
  chambre.vue = cible_vue                          ;

  cible_fumeur = 999                               ;
  while((cible_fumeur < 0) || (cible_fumeur > 1))
  {
    printf("Chambre pour fumeur ?\n")              ;
    printf("0 - non fumeur\n")                     ;
    printf("1 - fumeur\n")                         ;
    printf("Choix : ")                             ;
    test = scanf("%d", &cible_fumeur)              ;
    if(test == 0)
    {
      printf("Erreur de saisie.\n")                ;
      while((poubelle=getchar()) != '\n')          ;
    }
    else
    {
      if((cible_fumeur < 0) || (cible_fumeur > 1))
      {
        printf("Choix non valide.\n")              ;
      }
    }
  }
  chambre.fumeur = cible_fumeur                    ;


  cible_animaux = 999                              ;
  while((cible_animaux < 0) || (cible_animaux > 1))
  {
    printf("Chambre avec animaux autorisés?\n")    ;
    printf("0 - animaux non autorisés\n")          ;
    printf("1 - animaux autorisés\n")              ;
    printf("Choix : ")                             ;
    test = scanf("%d", &cible_animaux)             ;
    if(test == 0)
    {
      printf("Erreur de saisie.\n")                ;
      while((poubelle=getchar()) != '\n')          ;
    }
    else
    {
      if((cible_animaux < 0) || (cible_animaux > 1))
      {
        printf("Choix non valide.\n")              ;
      }
    }
  }
  chambre.animaux = cible_animaux                  ;
}

/*############################################
#                                            #
#           cible_chambre_simple             #
#                                            #
##############################################

Procédure pour déterminer quelle chambre recherche le client sur moins de critères.
Les données sont chargées dans la struct cha chambre.
*/

void cible_chambre_simple()
{
  int cible_cat_chambre                            ; /* 0 chambre, 1 suite*/
  int cible_type_lits                              ; /* 1 lit simple, 2 deux lits simples, 3 lit double, 4 trois lits simples, 5 lit simple et lit double */
  int test = 0                                     ;

  cible_type_lits = 999                            ;
  while((cible_type_lits < 1) || (cible_type_lits > 5))
  {
    printf("Quel type de lits ?\n")                ;
    printf("-1- un lit simple\n")                  ;
    printf("-2- deux lits simples\n")              ;
    printf("-3- un lit double\n")                  ;
    printf("-4- trois lits simples\n")             ;
    printf("-5- un lit double et un lit simple\n") ;
    printf("Saisir le type de lits : ")            ;
    test = scanf("%d", &cible_type_lits)           ;
    if(test == 0)
    {
      printf("Erreur de saisie.\n")                ;
      while((poubelle=getchar()) != '\n')          ;
    }
    else
    {
      if((cible_type_lits < 1) || (cible_type_lits > 5))
      {
        printf("Choix non valide.\n")              ;
      }
    }
  }
  chambre.type_lits = cible_type_lits              ;

  switch(cible_type_lits)
  {
    case 1 :
      chambre.type_chambre = 1                     ;
      break                                        ;
    case 2 :
    case 3 :
      chambre.type_chambre = 2                     ;
      break                                        ;
    case 4 :
    case 5 :
      chambre.type_chambre = 3                     ;
      break                                        ;
  }

  cible_cat_chambre = 999                          ;
  while((cible_cat_chambre < 0) || (cible_cat_chambre > 1))
  {
    printf("Quelle catégorie de chambre ?\n")      ;
    printf("-0- chambre\n")                        ;
    printf("-1- suite\n")                          ;
    printf("Saisir la catégorie : ")               ;
    test = scanf("%d", &cible_cat_chambre)         ;
    if(test == 0)
    {
      printf("Erreur de saisie.\n")                ;
      while((poubelle=getchar()) != '\n')          ;
    }
    else
    {
      if((cible_cat_chambre < 0) || (cible_cat_chambre > 1))
      {
        printf("Choix non valide.\n")              ;
      }
    }
  }
  chambre.categorie_chambre = cible_cat_chambre    ;
}

/*############################################
#                                            #
#             rech_periode                   #
#                                            #
##############################################

Trouve les indices des cases dans le planning pour les dates données.

*/

void rech_periode(long unsigned int datearrivee, long unsigned int datedepart)
{
  int i=0                                   ;

  numcase_resa_date_debut=NON_TROUVE        ;
  numcase_resa_date_fin=NON_TROUVE          ;


  while((i<ANNEE)&&(numcase_resa_date_debut==NON_TROUVE))
  {
    if(demande.datearrivee==calendrier[i].date)
    {
      numcase_resa_date_debut=i             ;
    }
    else
    {
      i++                                   ;
    }
  }
  if (numcase_resa_date_debut!=NON_TROUVE)
  {
    while ((i<ANNEE)&&(numcase_resa_date_fin==NON_TROUVE))
    {
      if(demande.datedepart==calendrier[i].date)
      {
        numcase_resa_date_fin=i              ;
      }
      else
      {
        i++                                  ;
      }
    }
  }
  else
  {
      printf("Date d'arrivée non trouvée\n") ;
  }
  if (numcase_resa_date_fin==NON_TROUVE)
  {
    printf("Date de départ non trouvée\n")   ;
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
  int i                       ;

  i = numcase_resa_date_debut ;
  demande.nuitees_resa[0] = 0 ;
  demande.nuitees_resa[1] = 0 ;


  while(i < (numcase_resa_date_fin + 1))
  {
    if(calendrier[i].saison == 0)
    {
      demande.nuitees_resa[0]++ ;
    }
    else
    {
      demande.nuitees_resa[1]++ ;
    }
    i++                         ;
  }
  if((demande.nuitees_resa[0] == 0) && (demande.nuitees_resa[1] == 0))
  {
    printf("Erreur dans le calcul des nuitées.") ;
  }
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
  int chambres_ok[MAX_NB_CHAMBRES]         ;
  int chambres_dispo[MAX_NB_CHAMBRES]      ;
  int i, j, k, l, m, test, chambre_choisie ;
  j = 0                                    ;


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
      test = 1            ;
      k = chambres_ok[i]  ;
      m = numcase_resa_date_debut ;
      while((test==1)&&(m <= numcase_resa_date_fin))
       /*disponibilité sur le premier jour*/
      {
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
    return(0)                                ;
    /*Offrir la possibilité de modifier les critères de chambre*/
  }
  /*Si l == 0, pas de choix disponibles dans la période, avec les critères donnés*/
  if(l==0)
  {
    printf("Il n'y a pas de chambres disponibles dans la période définie selon les critères donnés\n") ;
    return(0) ;
    /*Offrir la possibilité de modifier les critères de date*/
  }
  else
  {
    printf("Chambres disponibles : %d\n", l)                    ;
    for(i=0; i < l; i++)
    {
      j = chambres_dispo[i]                                     ;
      printf("Chambre n.%d\n", tab_chambres[j].num_chambre)     ;
    }
  }
  test = NON_TROUVE                                             ;
  while(test == NON_TROUVE)
  {
    printf("Choisir la chambre à réserver (0 pour quitter) : ") ;
    scanf("%d", &chambre_choisie)                               ;
    if(chambre_choisie == 0)
    {
      return(0)                                                 ;
    }
    else
    {

      i = 0                                                     ;
      while((test == NON_TROUVE) && (i < l)) /*test pour vérifier que le choix fait est parmi les choix possibles*/
      {
        j = chambres_dispo[i]                                   ;
        if(chambre_choisie == tab_chambres[j].num_chambre)
        {
          test = 1                                              ;
        }
        else
        {
          i++                                                   ;
        }
      }
      if(test == NON_TROUVE)
      {
        printf("Le choix n'est pas valide. Choisir une des chambres disponibles affichées.\n") ;
      }
    }
  }
  demande.chambre_resa = chambre_choisie                        ;
  return(1)                                                     ;
}

/*############################################
#                                            #
#           choix_chambre_simple             #
#                                            #
##############################################
Dans les bornes du planning données par rech_periode, recherche de chambres avec code de réservation qui indique qu'elles sont libres.
On désigne une liste des chambres possibles.
On demande d'en choisir une ou bien de renoncer.
*/


int choix_chambre_simple()
{
  int chambres_ok[MAX_NB_CHAMBRES]         ;
  int chambres_dispo[MAX_NB_CHAMBRES]      ;
  int i, j, k, l, m, test, chambre_choisie ;
  j = 0                                    ;


  /* On trouve les chambres qui correspondent à la chambre souhaitée */

  for(i=0 ; i < MAX_NB_CHAMBRES ; i++)
  {
    if
    (
      (chambre.type_chambre == tab_chambres[i].type_chambre) &&
      (chambre.type_lits == tab_chambres[i].type_lits) &&
      (chambre.categorie_chambre == tab_chambres[i].categorie_chambre)
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
      test = 1            ;
      k = chambres_ok[i]  ;
      m = numcase_resa_date_debut ;
      while((test==1)&&(m <= numcase_resa_date_fin))
       /*disponibilité sur le premier jour*/
      {
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
    return(0)                                ;
    /*Offrir la possibilité de modifier les critères de chambre*/
  }
  /*Si l == 0, pas de choix disponibles dans la période, avec les critères donnés*/
  if(l==0)
  {
    printf("Il n'y a pas de chambres disponibles dans la période définie selon les critères donnés\n") ;
    return(0) ;
    /*Offrir la possibilité de modifier les critères de date*/
  }
  else
  {
    printf("Chambres disponibles : %d\n", l)                    ;
    for(i=0; i < l; i++)
    {
      j = chambres_dispo[i]                                     ;
      printf("Chambre n.%d\n", tab_chambres[j].num_chambre)     ;
    }
  }
  test = NON_TROUVE                                             ;
  while(test == NON_TROUVE)
  {
    printf("Choisir la chambre à réserver (0 pour quitter) : ") ;
    scanf("%d", &chambre_choisie)                               ;
    if(chambre_choisie == 0)
    {
      return(0)                                                 ;
    }
    else
    {

      i = 0                                                     ;
      while((test == NON_TROUVE) && (i < l)) /*test pour vérifier que le choix fait est parmi les choix possibles*/
      {
        j = chambres_dispo[i]                                   ;
        if(chambre_choisie == tab_chambres[j].num_chambre)
        {
          test = 1                                              ;
        }
        else
        {
          i++                                                   ;
        }
      }
      if(test == NON_TROUVE)
      {
        printf("Le choix n'est pas valide. Choisir une des chambres disponibles affichées.\n") ;
      }
    }
  }
  demande.chambre_resa = chambre_choisie                        ;
  return(1)                                                     ;
}

/*############################################
#                                            #
#             saisie_client                  #
#                                            #
##############################################

À ajouter, un test sur la chaîne de caractères du numéro de téléphone.
Le premier doit être un +, les suivants que des chiffres.

*/
void saisie_client()
{
  char nom_client[100], prenom_client[200], numero_telephone_client[20] ;

  printf("Nom du client : ")                                            ;
  scanf("%s", demande.nomclient)                                        ;

  printf("Prénom du client : ")                                         ;
  scanf("%s", demande.prenomclient)                                     ;

  printf("Numéro de téléphone (format +3301234567) : ")                 ;
  scanf("%s", demande.telclient)                                        ;
}


/*############################################
#                                            #
#            nouveau_nb_resa                 #
#                                            #
##############################################

Un numéro de réservation est affecté à la demande de réservation en cours de traitement.

*/

void nouveau_nb_resa()
{
  FILE *f1                        ;
  demande.code_resa = nb_resa + 1 ; /* La nouvelle réservation = dernière réservation +1 */
  nb_resa = demande.code_resa     ; /* Mise à jour du dernier numéro de réservation */

  f1=fopen(RESA_CODE, "w")        ; /* Afin de garantir la symmétrie entre nb_resa et l'information sauvegardée dans le fichier, mise à jour du fichier */
  fprintf(f1, "%lu", nb_resa)     ;
  fclose(f1)                      ;
}


/*############################################
#                                            #
#             paiement_resa                  #
#                                            #
##############################################

*/
void paiement_resa()
{
  char date_1[11], date_2[11], temporaire[5]             ;
  int i, test = 0, a, m, j, t2                           ;
  struct prix_nuit nuit                                  ;
  FILE *f1;

  nuit.type_chambre = chambre.type_chambre               ; /* On retrouve les critères de type de chambre et catégorie de chambre, nécessaires pour déterminer le prix à la nuitée */
  nuit.categorie_chambre = chambre.categorie_chambre     ;

  i= -1;
  while (test == 0) /* On retrouve le prix à la nuitée en trouvant dans le tableau des prix le champ où type de chambre et catégorie sont les mêmes que dans notre cas */
  {
    i++                                                    ;
    if ((tab_prix_chambres[i].type_chambre==nuit.type_chambre) && (tab_prix_chambres[i].categorie_chambre==nuit.categorie_chambre))

    {
      nuit=tab_prix_chambres[i]                            ;
      test = 1                                             ;
    }
  }
  demande.total_resa=(demande.nuitees_resa[0]*nuit.prix_bs)+(demande.nuitees_resa[1]*nuit.prix_hs) ;

  date_1[0] = '\0'                                         ;
  temporaire[0] = '\0'                                     ;
  a = demande.datearrivee/10000                            ;
  m = (demande.datearrivee - (a * 10000)) / 100            ;
  j = (demande.datearrivee - (a * 10000) - (m * 100))      ;
  sprintf(temporaire, "%d", j)                             ;
  strcat(date_1, temporaire)                               ;
  strcat(date_1, "/")                                      ;
  sprintf(temporaire, "%d", m)                             ;
  strcat(date_1, temporaire)                               ;
  strcat(date_1, "/")                                      ;
  sprintf(temporaire, "%d", a)                             ;
  strcat(date_1, temporaire)                               ;

  date_2[0] = '\0'                                         ;
  temporaire[0] = '\0'                                     ;
  a = demande.datedepart/10000                             ;
  m = (demande.datedepart - (a * 10000)) / 100             ;
  j = (demande.datedepart - (a * 10000) - (m * 100))       ;
  sprintf(temporaire, "%d", j)                             ;
  strcat(date_2, temporaire)                               ;
  strcat(date_2, "/")                                      ;
  sprintf(temporaire, "%d", m)                             ;
  strcat(date_2, temporaire)                               ;
  strcat(date_2, "/")                                      ;
  sprintf(temporaire, "%d", a)                             ;
  strcat(date_2, temporaire)                               ;


  printf("Réservation n.%lu\n", demande.code_resa)         ;
  printf("Client : %s %s\n", demande.nomclient, demande.prenomclient)    ;
  printf("Séjour du %s au %s\n", date_1, date_2 )          ;
  printf("Chambre n.%d\n", demande.chambre_resa)           ;
  if(demande.nuitees_resa[0] > 0)
  {
    printf("Nuit en tarif basse saison : %d\n", demande.nuitees_resa[0]) ;
    printf("Tarif par nuit : %.2f\n", nuit.prix_bs)        ;
  }
  if(demande.nuitees_resa[1] > 0)
  {
    printf("Nuit en tarif haute saison : %d\n", demande.nuitees_resa[1]) ;
    printf("Tarif par nuit : %.2f\n", nuit.prix_hs)        ;
  }
  test = 0 ;
  while(test == 0)
  {
    printf("Montant à payer : %.2f\n", demande.total_resa) ;
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
}


/*############################################
#                                            #
#              paiement_cb                   #
#                                            #
##############################################

Si dans paiement_resa le choix de paiement saisi (demande.mode_paiement) est 3, formulaire de saisie des données de la carte bleue.

À ajouter: tests sur les valeurs saisies pour la carte de crédit, tests sur les espaces.
*/


void paiement_cb()
{
  char numero_cb[16]                       ;
  char titulaire_cb_nom[20]                ;
  char titulaire_cb_prenom[20]             ;
  int test = 0, mois_cb, annee_cb, code_cb ;

//nom, prénom, numéro, code 3 chiffres, validité

  printf("Saisir le nom du titulaire de la carte bancaire : ")                ;
  scanf("%s", titulaire_cb_nom)                                               ;

  printf("Saisir le prénom du titulaire de la carte bancaire : ")             ;
  scanf("%s", titulaire_cb_prenom)                                            ;

  printf("Saisir les 16 chiffres de la carte bancaire, sans espaces : ")      ;
  scanf("%s", numero_cb)                                                      ;

  while(test == 0)
  {
    printf("Saisir la date de fin de validité de la carte (format mm/aa) :" ) ;
    test = scanf("%d/%d", &mois_cb, &annee_cb)                                ;
    if(test == 0)
    {
      printf("Erreur de saisie.\n")                                           ;
    }
  }

  test = 0                                                                    ;
  while(test == 0)
  {
    printf("Saisir le code de sécurité de trois chiffres :" )                 ;
    test = scanf("%d", &code_cb )                                             ;
    if(test == 0)
    {
      printf("Erreur de saisie.\n")                                           ;
    }
  }
}


/*############################################
#                                            #
#           sauvegarde_resa                  #
#                                            #
##############################################

Les informations sur la réservation sont sauvegardées dans le fichier DOSSIER_RESA/$code_resa.txt.

*/

void sauvegarde_resa()
{
  char entree_resa[20], temporaire[11]          ; /* Devant acceuillir un long int, temporaire doit être 10 +'\0'*/
  FILE *f1                                      ;

  temporaire[0] = '\0'                          ;
  entree_resa[0] = '\0'                         ;
  strcat(entree_resa, DOSSIER_RESA)             ;
  sprintf(temporaire, "%lu", demande.code_resa) ;
  strcat(entree_resa, temporaire)               ;
  strcat(entree_resa, ".txt")                   ;
  f1=fopen(entree_resa, "w")                    ;
  fprintf(f1, "%lu %d %lu %lu %d %d %s %s %s %.2f %d", demande.code_resa, demande.chambre_resa, demande.datearrivee, demande.datedepart, demande.nuitees_resa[0], demande.nuitees_resa[1], demande.nomclient, demande.prenomclient, demande.telclient, demande.total_resa, demande.mode_paiement);
  fclose(f1)                                    ;
  printf("La réservation n.%lu a bien été enregistrée.\n", demande.code_resa) ;
}

/*############################################
#                                            #
#                   depart                   #
#                                            #
##############################################

Appelée dans le menu principal, lui passe la main après avoir effectué la suppresssion du fichier de réservation.
Gestion du départ: si note à régler alors afficher la note.

*/
void depart()
{
  char note_nom_cli[MAX_NOM_CLI], note_pnom_cli[MAX_PNOM_CLI] ;
  char temporaire[11], entree_note[20]                        ;
  int i=0, t1 =0 , t2                                         ;
  FILE *f1                                                    ;
  float note_total = 0                                        ;
  long unsigned int id_resa                                   ;
  struct frais note[MAX_ENTREES_FRAIS]                        ;

  while(t1 == 0)
  {
    printf("Saisir le numéro de réservation : " )             ;
    t2 = scanf("%lu", &id_resa)                               ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                            ;
      while((poubelle=getchar()) != '\n')                     ;
    }
    else
    {
      t1 = 1 ;
    }
  }

  temporaire[0] = '\0'                                        ;
  entree_note[0] = '\0'                                       ;
  strcat(entree_note, DOSSIER_NOTES)                          ;
  sprintf(temporaire, "%lu", id_resa)                         ;
  strcat(entree_note, temporaire)                             ;
  strcat(entree_note, ".txt")                                 ;
  t1 = 0                                                      ;
  while(t1 == 0)
  {
    i = 0                                                     ;
    f1=fopen(entree_note, "r")                                ;
    fscanf(f1, "%s %s\n", note_nom_cli, note_pnom_cli) ; /*Pour avoir accès à toutes les informations rapidement et de manière indépendante de la réservation, on met dans la première ligne du fichier nom et prénom du client*/
    while(!feof(f1))
    {
      fscanf(f1, "%lu %s %f", &note[i].datefrais, note[i].nomfrais, &note[i].montantfrais) ;
      note_total += note[i].montantfrais                      ;
      i++                                                     ;
    }
    fclose(f1)                                                ;

    if (i>0)
    {
      printf("Il reste une note à payer.\n")                  ;
      affichage_note(entree_note)                             ;
    }
    else
    {
      t1 = 1                                                  ;
    }
  }
  supprime_note(id_resa)                                      ;
  printf("Aucune note à payer. Bon départ !\n")               ;
}

/*############################################
#                                            #
#              supprime_resa                 #
#                                            #
##############################################

Appelée dans le annul_origine() et dans depart(), leur passe la main après avoir effectué la suppresssion du fichier de réservation.

*/

void supprime_resa(long unsigned int p_code_resa)
{
  char entree_resa[20], temporaire[11]    ;
  FILE *f1                                ;
  int test                                ;

  temporaire[0] = '\0'                    ;
  entree_resa[0] = '\0'                   ;
  strcat(entree_resa, DOSSIER_RESA)       ;
  sprintf(temporaire, "%lu", p_code_resa) ;
  strcat(entree_resa, temporaire)         ;
  strcat(entree_resa, ".txt")             ;

  test = unlink(entree_resa)              ;
  if(test == -1)
  {
    printf("Erreur dans la suppression du fichier\n")              ;
    printf("Supprimez manuellemenet le fichier %s\n", entree_resa) ;
  }
}

/*############################################
#                                            #
#           recherche_resa                   #
#                                            #
##############################################

Appelé dans le main() le programme gère la recherche et, le cas échéant, modification d'une réservation.
Appelle dans l'ordre chargement_resa(), affichage_resa() et choix_modif_resa().

*/

void recherche_resa()
{
  int test = 0, t2                                                      ;
  long unsigned int code_modif_resa                                     ;
  printf("Recherche de réservation.\n")                                 ;
  while(test == 0)
  {
    printf("Veuillez saisir le numéro de la réservation à rechercher ") ;
    printf("(0 pour revenir au menu principal) : ")                     ;
    t2 = scanf("%lu", &code_modif_resa)                                 ;
    if(t2 == 0)
    {
      printf("Choix non valide.\n")                                     ;
      while((poubelle=getchar()) != '\n')                               ;
    }
    else /* l'utilisateur a effectivement saisi un numérique */
    {
       if((code_modif_resa > nb_resa)||(code_modif_resa == 1)) /* 0 est le code pour indiquer que la réservation est possible, 1 pour signaler des travaux. On ne veut pas permettre leur modification */
       {
         printf("Code de réservation invalide.\n")                      ;
       }
       else
       {
         test = 1                                                       ; /* On sortira de toute façon de la boucle while */
         if(code_modif_resa == 0)
         {
           printf("Retour au menu principal.\n")                        ;
         }
         else
         {
           chargement_resa(code_modif_resa)                             ;
           affichage_resa()                                             ;
           choix_modif_resa()                                           ;
         }
       }
     } /* fin des tests sur le numérique */
   } /* fin du while */
  }

/*############################################
#                                            #
#           chargement_resa                  #
#                                            #
##############################################

Appelée par recherche_resa(), passe la main à affichage_resa() et choix_modif_resa().
Reçoit un code de réservation en paramètre et charge les données dans la variable globale demande.
Le int retourné indique le résultat de l'opération.

*/

void chargement_resa(long unsigned int p_code_resa)
{
  char entree_resa[20], temporaire[11]    ;
  FILE *f1                                ;

  temporaire[0] = '\0'                    ;
  entree_resa[0] = '\0'                   ;
  strcat(entree_resa, DOSSIER_RESA)       ;
  sprintf(temporaire, "%lu", p_code_resa) ;
  strcat(entree_resa, temporaire)         ;
  strcat(entree_resa, ".txt")             ;

  f1 = fopen(entree_resa, "r")            ;
  if(f1 != NULL)
  {
    /*changer le test du while avec la fonction qui permet de lire un caractère dans un fichier: cherche
    i= 0 ;
    while((c=getchar()) != "*")
    {
      demande.nomclient[i]=c;
      i++;
    }
    demande.nomclient[i+1] = "\0";
    */

  fscanf(f1, "%lu %d %lu %lu %d %d %s %s %s %f %d", &demande.code_resa, &demande.chambre_resa, &demande.datearrivee, &demande.datedepart, &demande.nuitees_resa[0], &demande.nuitees_resa[1], demande.nomclient, demande.prenomclient, demande.telclient, &demande.total_resa, &demande.mode_paiement) ;
  fclose(f1)                              ;
  }
  else
  {
    printf("Il n'existe pas de fichier pour la réservation %lu.\n", p_code_resa) ;
    printf("Les informations qui suivent sont fausses.\n")                       ;
  }
}


/*############################################
#                                            #
#             affichage_resa                 #
#                                            #
##############################################

Appelée par recherche_resa() après chargement_resa(), passe la main à choix_modif_resa().
Affiche la réservation chargée dans la variable globale demande.

*/

void affichage_resa()
{
  char paiement[9], date_1[11], date_2[11], temporaire[5]                ;
  int a, m, j                                                            ;
  paiement[0] = '\0'                                                     ;


  date_1[0] = '\0'                                                       ;
  temporaire[0] = '\0'                                                   ;
  a = demande.datearrivee/10000                                          ;
  m = (demande.datearrivee - (a * 10000)) / 100                          ;
  j = (demande.datearrivee - (a * 10000) - (m * 100))                    ;
  sprintf(temporaire, "%d", j)                                           ;
  strcat(date_1, temporaire)                                             ;
  strcat(date_1, "/")                                                    ;
  sprintf(temporaire, "%d", m)                                           ;
  strcat(date_1, temporaire)                                             ;
  strcat(date_1, "/")                                                    ;
  sprintf(temporaire, "%d", a)                                           ;
  strcat(date_1, temporaire)                                             ;

  date_2[0] = '\0'                                                       ;
  temporaire[0] = '\0'                                                   ;
  a = demande.datedepart/10000                                           ;
  m = (demande.datedepart - (a * 10000)) / 100                           ;
  j = (demande.datedepart - (a * 10000) - (m * 100))                     ;
  sprintf(temporaire, "%d", j)                                           ;
  strcat(date_2, temporaire)                                             ;
  strcat(date_2, "/")                                                    ;
  sprintf(temporaire, "%d", m)                                           ;
  strcat(date_2, temporaire)                                             ;
  strcat(date_2, "/")                                                    ;
  sprintf(temporaire, "%d", a)                                           ;
  strcat(date_2, temporaire)                                             ;

  switch (demande.mode_paiement)
  {
    case 1:
      strcpy(paiement, "espèces")                                        ;
      break                                                              ;
    case 2:
      strcpy(paiement, "chèque")                                         ;
      break                                                              ;
    case 3:
      strcpy(paiement, "CB")                                             ;
      break                                                              ;
    case 4:
      strcpy(paiement, "virement")                                       ;
      break                                                              ;
    default:
      printf("Le moyen de paiement n'a pas été correctement renseigné.\n") ;
      break                                                              ;
  }
  printf("Réservation n.%lu\n", demande.code_resa)                       ;
  printf("Client : %s %s\n", demande.nomclient, demande.prenomclient)    ;
  printf("Séjour du %s au %s\n", date_1, date_2 )                        ;
  printf("Chambre n.%d\n", demande.chambre_resa)                         ;
  if(demande.nuitees_resa[0] > 0)
  {
    printf("Nuit en tarif basse saison : %d\n", demande.nuitees_resa[0]) ;
/*    printf("Tarif par nuit : %.2f\n", nuit.prix_bs)                      ; Pas de décompte des tarifs par nuit: en cas de changement dans les tarifs, nous lirions le nouveau prix, ce qui donnerait un résultat en désaccord avec le total. Faute d'historisation des prix, omission ici de cette information. */
  }
  if(demande.nuitees_resa[1] > 0)
  {
    printf("Nuit en tarif haute saison : %d\n", demande.nuitees_resa[1]) ;
/*    printf("Tarif par nuit : %.2f\n", nuit.prix_hs)                      ; Pas de décompte des tarifs par nuit: en cas de changement dans les tarifs, nous lirions le nouveau prix, ce qui donnerait un résultat en désaccord avec le total. Faute d'historisation des prix, omission ici de cette information. */
  }
  printf("Montant reglé : %.2f\n", demande.total_resa)                   ;
  printf("Moyen de paiement : %s\n\n", paiement)                         ;
}

/*############################################
#                                            #
#           choix_modif_resa                 #
#                                            #
##############################################

Appelé dans recherche_resa() après affichage_resa() et chargement_resa().
Choisir entre modification, annulation ou retour au menu principal.

*/

void choix_modif_resa()
{
  int choix_mod, t1 = 0, t2 = 0                    ;

  while(t1 == 0)
  {
    while(t2 == 0)
    {
      printf("Que voulez-vous faire? \n")          ;
      printf("-1- Modifier la réservation \n")     ;
      printf("-2- Annuler la réservation \n")      ;
      printf("-3- Retourner au menu principal \n") ;
      printf("Choix : " )                          ;
      t2 = scanf("%d", &choix_mod)                 ;
      if(t2 == 0)
      {
        printf("Erreur de saisie\n")               ;
        while((poubelle=getchar()) != '\n')        ;
      }
    }
    switch (choix_mod)
    {
      case 1:
        modif_resa()                               ;
        t1 = 1                                     ;
        break                                      ;
      case 2:
        annul_origine()                            ;
        t1 = 1                                     ;
        break                                      ;
      case 3:
        t1 = 1                                     ;
        printf("Retour au menu principal\n")       ;
        break                                      ;
      default:
        mauvais_choix(choix_mod)                   ;
        t2 = 0                                     ;
        break                                      ;
    }
  }
}

/*############################################
#                                            #
#             modif_resa                     #
#                                            #
##############################################

Appelée par choix_modif_resa(), passe la main au menu principal.
Modification d'une réservation : partie dates et client

*/
void modif_resa()
{
  char nom_client[100], prenom_client[200], numero_telephone_client[20]               ;
  int jour_debut, mois_debut, annee_debut                                             ;
  int jour_fin, mois_fin, annee_fin                                                   ;
  int a, m, j, t1, t2                                                                 ;
  char datearriveeavant[10], datedepartavant[11], temporaire[5], choix_modif_chambre  ;
  int continu_modif                                                                   ;

  datearriveeavant[0] = '\0'                              ;
  temporaire[0] = '\0'                                    ;
  a = demande.datearrivee / 10000                         ;
  m = (demande.datearrivee - (a * 10000)) / 100           ;
  j = (demande.datearrivee - (a * 10000) - (m * 100))     ;
  sprintf(temporaire, "%d", j)                            ;
  strcat(datearriveeavant, temporaire)                    ;
  strcat(datearriveeavant, "/")                           ;
  sprintf(temporaire, "%d", m)                            ;
  strcat(datearriveeavant, temporaire)                    ;
  strcat(datearriveeavant, "/")                           ;
  sprintf(temporaire, "%d", a)                            ;
  strcat(datearriveeavant, temporaire)                    ;


  t1 = 0                                                                                ;
  t2 = 0                                                                                ;
  while (t1 == 0)
  {
    printf("Date actuelle de début  : %s\n", datearriveeavant)                          ;
    printf("Saisir la nouvelle date de début (jj/mm/aaaa) : ")                          ;
    t2 = scanf("%d/%d/%d", &jour_debut, &mois_debut, &annee_debut)                      ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                                                      ;
    }
    else
    {
      demande.datearrivee = jjmmaaaa_vers_aaaammjj(jour_debut, mois_debut, annee_debut) ;
      if((demande.datearrivee < calendrier[0].date) || (demande.datearrivee > calendrier[ANNEE].date))
      {
        printf("Date fausse.\n")                                                        ;
      }
      else
      {
        t1 = 1                                                                          ;
      }
    }
  }


  datedepartavant[0] = '\0'                              ;
  temporaire[0] = '\0'                                   ;
  a = demande.datedepart / 10000                         ;
  m = (demande.datedepart - (a * 10000)) / 100           ;
  j = (demande.datedepart - (a * 10000) - (m * 100))     ;
  sprintf(temporaire, "%d", j)                           ;
  strcat(datedepartavant, temporaire)                    ;
  strcat(datedepartavant, "/")                           ;
  sprintf(temporaire, "%d", m)                           ;
  strcat(datedepartavant, temporaire)                    ;
  strcat(datedepartavant, "/")                           ;
  sprintf(temporaire, "%d", a)                           ;
  strcat(datedepartavant, temporaire)                    ;

  t1 = 0                                                                         ;
  t2 = 0                                                                         ;
  while (t1 == 0)
  {
    printf("Date actuelle de fin  : %s\n", datedepartavant)                      ;
    printf("Saisir la date de la dernière nuitée (jj/mm/aaaa) : ")               ;
    t2 = scanf("%d/%d/%d", &jour_fin, &mois_fin, &annee_fin)                     ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                                               ;
    }
    else
    {
      demande.datedepart = jjmmaaaa_vers_aaaammjj(jour_fin, mois_fin, annee_fin) ;
      if((demande.datedepart < demande.datearrivee)||(demande.datedepart > calendrier[ANNEE].date))
      {
        printf("Date fausse.\n")                                                 ;
      }
      else
      {
        t1 = 1                                                                   ;
      }
    }
  }


  choix_modif_chambre='a'                               ;
  while ((choix_modif_chambre!='o')||(choix_modif_chambre!='n'))
  {
    printf("Voulez-vous modifier la chambre (o/n)?\n")  ;
    scanf("%c", &choix_modif_chambre)                   ;
    if((choix_modif_chambre!='o')&&(choix_modif_chambre!='n'))
    {
      while((poubelle=getchar()) != '\n')               ;
      printf("Choix non valide\n")                      ;
    }
  }
  if (choix_modif_chambre=='o')
  {
    modif_resa_cha();
  }
  rech_periode(demande.datearrivee, demande.datedepart) ;
  calcul_nuitees()                                      ;
  if ((numcase_resa_date_debut != NON_TROUVE) && (numcase_resa_date_fin != NON_TROUVE))
  {
    continu_modif=choix_chambre()                       ;
  }

  if (continu_modif==1)
  {
    printf("Nom actuel du client : %s\n", demande.nomclient)       ;
    printf("Nouveau nom du client : ")                             ;
    scanf("%s", demande.nomclient)                                 ;
    printf("Prénom actuel du client : %s\n", demande.prenomclient) ;
    printf("Nouveau prénom du client : ")                          ;
    scanf("%s", demande.prenomclient)                              ;
    printf("Numéro de téléphone actuel : %s\n", demande.telclient) ;
    printf("Nouveau numéro de téléphone (format +3301234567): ")   ;
    scanf("%s", demande.telclient)                                 ; /* cf test préconisé dans saisie_client() */

    /* s'il y a une différence dans le montant, il faut un paiement */
  }
  else
  {
    printf("Abandon de la procédure de modification.\nRetour au menu principal\n") ;
  }
}



/*############################################
#                                            #
#              modif_resa_cha                #
#                                            #
##############################################

Appelée par modif_resa() lui passe également la main.
Modification de la réservation : partie chambres

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
  int test = 0                      ;

  printf("Saisir les critères de la chambre souhaitée :   ")  ;
  printf("Type actuel de chambre : %d \n", chambre.type_lits) ;
  cible_type_lits = 999                                       ;
  while((cible_type_lits < 1) || (cible_type_lits > 5))
  {
    printf("Nouveau type de chambre : ")            ;
    printf("1 - un lit simple\n")                   ;
    printf("2 - deux lits simples\n")               ;
    printf("3 - un lit double\n")                   ;
    printf("4 - trois lits simples\n")              ;
    printf("5 - un lit double et un lit simple\n")  ;
    printf("Choix : ")                              ;
    test = scanf("%d", &cible_type_lits)            ;
    if(test == 0)
    {
      printf("Erreur de saisie.\n")                 ;
      while((poubelle=getchar()) != '\n')           ;
    }
    else
    {
      if((cible_type_lits < 1) || (cible_type_lits > 5))
      {
        printf("Choix non valide.\n")               ;
      }
    }
  }
  chambre.type_lits = cible_type_lits               ;

  switch(cible_type_lits)
  {
    case 1 :
      chambre.type_chambre = 1                      ;
      break                                         ;
    case 2 :
    case 3 :
      chambre.type_chambre = 2                      ;
      break                                         ;
    case 4 :
    case 5 :
      chambre.type_chambre = 3                      ;
      break                                         ;
  }

  cible_cat_chambre = 999                           ;
  while((cible_cat_chambre < 0) || (cible_cat_chambre > 1))
  {
    printf("Catégorie :")                           ;
    printf("0 - chambre\n")                         ;
    printf("1 - suite\n")                           ;
    printf("Actuellement : %d\n", chambre.categorie_chambre) ;
    printf("Choix : ")                              ;
    test = scanf("%d", &cible_cat_chambre)          ;
    if(test == 0)
    {
      printf("Erreur de saisie.\n")                 ;
      while((poubelle=getchar()) != '\n')           ;
    }
    else
    {
      if((cible_cat_chambre < 0) || (cible_cat_chambre > 1))
      {
        printf("Choix non valide.\n")               ;
      }
    }
  }
  chambre.categorie_chambre = cible_cat_chambre     ;

  cible_balcon = 999                                ;
  while((cible_balcon < 0) || (cible_balcon > 1))
  {
    printf("Balcon :")                              ;
    printf("0 - pas de balcon\n")                   ;
    printf("1 - balcon\n")                          ;
    scanf("%d", &cible_balcon)                      ;
    printf("Actuellement : %d\n", chambre.balcon);
    printf("Choix : ")                              ;
    test = scanf("%d", &cible_balcon)               ;
    if(test == 0)
    {
      printf("Erreur de saisie.\n")                 ;
      while((poubelle=getchar()) != '\n')           ;
    }
    else
    {
      if((cible_balcon < 0) || (cible_balcon > 1))
      {
        printf("Choix non valide.\n")               ;
      }
    }
  }
  chambre.balcon = cible_balcon                     ;

  cible_bain = 999                                  ;
  while((cible_bain < 0) || (cible_bain > 1))
  {
    printf("Salle de bain : ")                      ;
    printf("0 - baignoire\n")                       ;
    printf("1 - douche\n")                          ;
    printf("Actuellement : %d\n", chambre.bain)     ;
    printf("Choix : ")                              ;
    test = scanf("%d", &cible_bain)                 ;
    if(test == 0)
    {
      printf("Erreur de saisie.\n")                 ;
      while((poubelle=getchar()) != '\n')           ;
    }
    else
    {
      if((cible_bain < 0) || (cible_bain > 1))
      {
        printf("Choix non valide.\n")               ;
      }
    }
  }
  chambre.bain = cible_bain                         ;

  cible_vue = 999                                   ;
  while((cible_vue < 0) || (cible_vue > 1))
  {
    printf("Vue :")                                 ;
    printf("0 - pas de vue\n")                      ;
    printf("1 - vue\n")                             ;
    printf("Actuellement : %d\n", chambre.vue)      ;
    printf("Choix : ")                              ;
    test = scanf("%d", &cible_vue)                  ;
    if(test == 0)
    {
      printf("Erreur de saisie.\n")                 ;
      while((poubelle=getchar()) != '\n')           ;
    }
    else
    {
      if((cible_vue < 0) || (cible_vue > 1))
      {
        printf("Choix non valide.\n")               ;
      }
    }
  }
  chambre.vue = cible_vue                           ;

  cible_fumeur = 999                                ;
  while((cible_fumeur < 0) || (cible_fumeur > 1))
  {
    printf("Fumeur :")                              ;
    printf("0 - non fumeur\n")                      ;
    printf("1 - fumeur\n")                          ;
    printf("Actuellement : %d\n", chambre.fumeur)   ;
    printf("Choix : ")                              ;
    test = scanf("%d", &cible_fumeur)               ;
    if(test == 0)
    {
      printf("Erreur de saisie.\n")                 ;
      while((poubelle=getchar()) != '\n')           ;
    }
    else
    {
      if((cible_fumeur < 0) || (cible_fumeur > 1))
      {
        printf("Choix non valide.\n")               ;
      }
    }
  }
  chambre.fumeur = cible_fumeur                     ;

  cible_animaux = 999                               ;
  while((cible_animaux < 0) || (cible_animaux > 1))
  {
    printf("Animaux :")                             ;
    printf("0 - animaux non autorisés\n")           ;
    printf("1 - animaux autorisés\n")               ;
    printf("Actuellement : %d \n", chambre.animaux) ;
    printf("Choix : ")                              ;
    test = scanf("%d", &cible_animaux)              ;
    if(test == 0)
    {
      printf("Erreur de saisie.\n")                 ;
      while((poubelle=getchar()) != '\n')           ;
    }
    else
    {
      if((cible_animaux < 0) || (cible_animaux > 1))
      {
        printf("Choix non valide.\n")               ;
      }
    }
  }
  chambre.animaux = cible_animaux                   ;
}

/*############################################
#                                            #
#              annul_origine                 #
#                                            #
##############################################

Appelé dans choix_modif_resa(), ensuite on est redirigé vers le menu principal.
Vérifie l'origine de l'annulation appelle le sous-programme nécessaire.
Origine de l'annulation d'une réservation
*/
void annul_origine()
{
  int raison_annul = 0, i=0, t1= 0, t2                           ;

  while(t1 == 0)
  {
    printf("Qui est à l'origine de la demande d'annulation ?\n") ;
    printf("-1- Décision de l'hôtel\n")                          ;
    printf("-2- Décision du client\n")                           ;
    printf("-9- Quitter et revenir au menu précédent\n")         ;
    printf("Choix : ")                                           ;
    t2 = scanf("%d", &raison_annul)                              ;
    if(t2 == 0)
    {
      printf("Erreur de saisie\n")                               ;
      while((poubelle=getchar()) != '\n')                        ;
    }
    switch (raison_annul)
    {
      case 1:
        remboursement()                                          ;
        annulation_resa_planning()                               ;
        supprime_resa(demande.code_resa)                         ;
        supprime_note(demande.code_resa)                         ;
        t1 = 1                                                   ;
        break                                                    ;
      case 2:
        annul_client()                                           ;
        annulation_resa_planning()                               ;
        supprime_resa(demande.code_resa)                         ;
        supprime_note(demande.code_resa)                         ;
        t1 = 1                                                   ;
        break;
      case 9:
        printf("Abandon.\n Retour au menu principal\n")          ;
        t1 = 1                                                   ;
        break                                                    ;
      default:
        mauvais_choix(raison_annul)                              ;
        break                                                    ;
    }
  }
}


/*############################################
#                                            #
#               annul_client                 #
#                                            #
##############################################

Appelée par annul_origine().
Appelle remboursement_partiel() en lui fournissant le pourcentage de remboursement.
Après retour dans annul_origine() et donc le menu principal.
Calcul du préavis afin de rembourser la réservation.

*/

void annul_client()
{
  char c                                                                   ;
  int t1 = 0, t2, trouve = 0, deja= 0, i = 0, j = 0                        ;
  long unsigned int nb_resa_annul                                          ;

  while((trouve == 0 ) || (i < ANNEE))
  {
    if(planning[j][i] == demande.code_resa) /* i sera l'indice du calendrier et indiquera donc les jours de préavis*/
    {
      trouve = 1                                                           ;
    }
    else
    {
      if(j < MAX_NB_CHAMBRES)
      {
        j++                                                                ;
      }
      else
      {
        j = 0                                                              ;
        i++                                                                ;
      }
    }
  }
  if(trouve == 0)
  {
    printf("La réservation est déjà passée.\n")                            ;
  }
  else
  {
    while((poubelle=getchar()) != '\n')                                    ;
    printf("L'annulation a-t-elle été demandée aujourd'hui (o/n) ?")       ;
    scanf("%c", &c)                                                        ;
    if(c != 'o')
    {
      if(c == 'n')
      {
        while((poubelle=getchar()) != '\n')                                ;
        printf("Il y a combien de jours ? ")                               ;
        t2 = scanf("%d", &deja)                                            ;
        if(t2 == 0)
        {
          printf("Erreur de saisie.\n")                                    ;
          while((poubelle=getchar()) != '\n')                              ;
        }
      }
      else
      {
        printf("Choix non accepté. Les choix possibles sont 'o' pour 'oui' ou 'n' pour 'non'.\n") ;
        while((poubelle=getchar()) != '\n')                                ;
      }
    }
    i += deja                                                              ;
    switch(i) /* y en a marre des if */
    {
      case 1: case 2: case 3: case 4: case 5: case 6:
        while((poubelle=getchar()) != '\n')                                ;
        printf("Annullation la dernière semaine : aucun remboursement.\n") ;
        printf("Êtes-vous sûr de vouloir annuler la réservation (o/N) ? ") ;
        scanf("%c", &c)                                                    ;
        if(c == 'o' )
        {
          annulation_resa_planning()                                       ;
          t1 = 1                                                           ;
        }
        break                                                              ;
      case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14:
        printf("La réservation sera remboursée à hauteur de trente pour cent.\n") ;
        remboursement_partiel(REMB_SEMAINE)                                ;
        annulation_resa_planning()                                         ;
        t1 = 1                                                             ;
        break                                                              ;
        default:
        printf("La réservation sera remboursée à hauteur de soixante-dix pour cent.\n") ;
        remboursement_partiel(REMB_QUINZE)                                 ;
        t1 = 1                                                             ;
        break                                                              ;
    }
  }
}

/*############################################
#                                            #
#               remboursement                #
#                                            #
##############################################

En cas de remboursement total.

Appelée par annul_origine(), y retourne et passe la main à annulation_resa_planning().
À partir du code_resa, on supprime la case dans le planning: on remet à 0

*/

void remboursement()
{
  char paiement[9] ;
  FILE *f1         ;
  int t1 = 0, t2   ;


  switch (demande.mode_paiement)
  {
    case 1:
      strcpy(paiement, "espèces")                                              ;
      break                                                                    ;
    case 2:
      strcpy(paiement, "chèque")                                               ;
      break                                                                    ;
    case 3:
      strcpy(paiement, "CB")                                                   ;
      break                                                                    ;
    case 4:
      strcpy(paiement, "virement")                                             ;
      break                                                                    ;
    default:
      printf("La réservation contient des informations à vérifier\n")          ;
      break                                                                    ;
  }
  printf("Le montant total payé par le client, %s %s, a été de : %.2f\n", demande.prenomclient, demande.nomclient, demande.total_resa) ;
  printf("Le paiement a été effectué par %s\n", paiement)                      ;

  while(t1 == 0)
  {
    printf("Choisir le mode de remboursement de %.2f: \n", demande.total_resa) ;
    printf("-1- Espèces\n")                                                    ;
    printf("-2- Chèque\n")                                                     ;
    printf("-3- Carte bancaire\n")                                             ;
    printf("-4- Virement\n")                                                   ;
    printf("Choix : ")                                                         ;
    t2 = scanf("%d", &demande.mode_paiement)                                   ;
    if(t2 == 0)
    {
      printf("Erreur de saisie.\n")                                            ;
    }
    else
    {
      if((demande.mode_paiement < 0) || (demande.mode_paiement > 4))
      {
        mauvais_choix(demande.mode_paiement)                                   ;
      }
      else
      {
        if(demande.mode_paiement == 3)
        {
          paiement_cb()                                                        ;
        }
        printf("Le remboursement a bien été effectué.\n")                      ;
        t1 = 1                                                                 ;
      }
    }
  }
}


/*############################################
#                                            #
#           remboursement_partiel            #
#                                            #
##############################################

En cas de remboursement partiel.

Appelée par annul_origine(), y retourne et passe la main à annulation_resa_planning().
À partir du code_resa, on supprime la case dans le planning: on remet à 0

*/

void remboursement_partiel(int p_poursan)
{
  char paiement[9]                                                             ;
  FILE *f1                                                                     ;
  float combien                                                                ;
  int t1 = 0, t2                                                               ;


  switch (demande.mode_paiement)
  {
    case 1:
      strcpy(paiement, "espèces")                                              ;
      break                                                                    ;
    case 2:
      strcpy(paiement, "chèque")                                               ;
      break                                                                    ;
    case 3:
      strcpy(paiement, "CB")                                                   ;
      break                                                                    ;
    case 4:
      strcpy(paiement, "virement")                                             ;
      break                                                                    ;
    default:
      printf("La réservation contient des informations à vérifier\n")          ;
      break                                                                    ;
  }
  printf("Le montant total payé par le client, %s %s, a été de : %.2f\n", demande.prenomclient, demande.nomclient, demande.total_resa) ;
  printf("Le paiement a été effectué par %s\n", paiement)                      ;

  combien = (demande.total_resa * p_poursan) / 100                             ;
  while(t1 == 0)
  {
    printf("Choisir le mode de remboursement :\n")                             ;
    printf("-1- Espèces\n")                                                    ;
    printf("-2- Chèque\n")                                                     ;
    printf("-3- Carte bancaire\n")                                             ;
    printf("-4- Virement\n")                                                   ;
    printf("Choix : ")                                                         ;
    t2 = scanf("%d", &demande.mode_paiement)                                   ;
    if(t2 == 0)
    {
      printf("Erreur de saisie.\n")                                            ;
    }
    else
    {
      if((demande.mode_paiement < 0) || (demande.mode_paiement > 4))
      {
        mauvais_choix(demande.mode_paiement)                                   ;
      }
      else
      {
        if(demande.mode_paiement == 3)
        {
          paiement_cb()                                                        ;
        }
        printf("Le remboursement a bien été effectué.\n")                      ;
        t1 = 1                                                                 ;
      }
    }
  }
}
