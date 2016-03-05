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
  char choix_date = 'f'                ;
  char date_chaine[11], temporaire[5]  ;
  int i = 0, a, m, j                   ;

  printf("Test des paramètres\n")      ;
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
        while((poubelle=getchar()) != '\n')            ;
      }
    }
  }
  if(i != 0)
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
  char date_chaine[11], temporaire[5] ;
  char choix_saison = 'z'             ;
  FILE *f1                            ;
  int j, a, m, d, test                ;

  programme_crea(i - 1)               ;

  for(j = i; j < ANNEE; j++) /* déplacer les valeurs des jours dans le calendrier: LE FUTUR C'EST MAINTENANT!*/
  {
    calendrier[j-i] = calendrier[j]   ;
  }
  for(j = ANNEE - i; j < ANNEE ; j++) /*créer les cases qui manquent: MORE FUTURE (slogan anti-punk)*/
  {
    date_chaine[0] = '\0'                                ; /*cette ligne et les onze suivantes étaient dans une fonction à part entière, mais retournaient une chaîne de caractères et l'affectaient à une variable, je ne sais pas faire*/
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
    test = 0 ;
    while(test == 0)
    {
      printf("Quel jour vient après le %s (format jj/mm/aaaa) ? ", date_chaine) ;
      test = scanf("%d/%d/%d", &d, &m, &a)               ;
      if(test == 0)
      {
        printf("Erreur de saisie.\n")                    ;
        while((poubelle=getchar()) != '\n')              ;
      }
    }
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
