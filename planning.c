#include "declarations.h" /*c'est ici que sont les #include et les #define*/


void enregistrement_planning()             ;

char poubelle            ; /*pour vider le buffer des \n*/

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

int numcase_resa_chambre         ; /*Identifie la case dans le tableau planning ou dans tab_chambres qui correspond à la chambre demandée/reservée*/
int numcase_resa_date_debut, numcase_resa_date_fin ; /*identifient la position dans le planning/calendrier de la case où débute et finit la réservation*/
/* Variables globales concernant les chambres*/


struct resa demande              ;
long unsigned int nb_resa        ; /* Dernière réservation faite, la suivante devra prendre nb_resa+1 */

/*Calendrier*/
struct jour
{
  long unsigned int date ; /*date aaaammjj*/
  short int saison       ; /*0 basse saison, 1 haute saison*/
}                        ;

struct jour calendrier[ANNEE] ;

long unsigned int planning[MAX_NB_CHAMBRES][ANNEE] ; /* Les valeurs dans ce tableau sont les codes de réservation. 0 est utilisé pour signaler que la chambre est libre; 1 pour déclarer des travaux. */

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


/*############################################
#                                            #
#               PARTIE PLANNING              #
#       #############################        #
#                                            #
#            chargement_planning             #
#                                            #
##############################################

Appelée au lancement du programme.
Charge en mémoire les données du planning présentes dans le fichier PLANNING.

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
#              maj_planning                  #
#                                            #
##############################################

Appelée par creer_reservation().
Appelle enregistrement_planning().
Une fois la réservation validée, son code est inséré dans le planning aux cases déjà déterminées dans rech_periode().

*/

void maj_planning()
{
  int i, j = 0                         ;


  while(demande.chambre_resa != tab_chambres[j].num_chambre ) /*Recherche, dans le tableau des chambres, de l'indice auquel correspond la case avec le bon num_chambre*/
  {
    j++                                ;
  }

  for(i = numcase_resa_date_debut ; i < numcase_resa_date_fin + 1 ; i++)
  {
    planning[j][i] = demande.code_resa ;
  }
  enregistrement_planning()            ;
  printf("La réservation %lu a bien été insérée dans le planning.\n", demande.code_resa) ;
}

/*############################################
#                                            #
#            maj_planning_travaux            #
#                                            #
##############################################

Appelée par travaux().
Appelle enregistrement_planning().

Une fois la demande de travaux validée, insertion dans le planning.

*/

void maj_planning_travaux()
{
  int i, j = 0                         ;


  while(demande.chambre_resa != tab_chambres[j].num_chambre ) /*Recherche, dans le tableau des chambres, de l'indice auquel correspond la case avec le bon num_chambre*/
  {
    j++                                ;
  }

  for(i = numcase_resa_date_debut ; i < numcase_resa_date_fin + 1 ; i++)
  {
    planning[j][i] = demande.code_resa ;
  }
  enregistrement_planning()            ;
}

/*############################################
#                                            #
#         annulation_resa_planning           #
#                                            #
##############################################

Appelé dans annul_origine(), après on revient au menu principal.
Appelle enregistrement_planning().
À partir du code_resa, on supprime la case dans le planning: on remet à 0

Le calcul pour trouver les cases du planning pourrait être extrait, car dans un des deux cas -passage par annul_client()- il a déjà eu lieu. Il s'agit de le sortir et ne le faire qu'en cas d'annulation par l'hôtel.

*/

void annulation_resa_planning()
{
 int i=0, j=0                                     ;

 while (demande.chambre_resa!=tab_chambres[i].num_chambre) /*on trouve l'indice de la chambre*/
 {
  i++                                             ;
 }
 while (demande.datearrivee!=calendrier[j].date) /*on trouve l'indice du premier jour du séjour*/
 {
  j++                                             ;
 }

 while(planning[i][j] == demande.code_resa)
 {
  planning[i][j] = 0                              ;
  j++                                             ;
 }
  enregistrement_planning()                       ;
  printf("L'annulation a bien été effectuée. \n") ;
}

/*############################################
#                                            #
#         enregistrement_planning            #
#                                            #
##############################################

Appelée par maj_planning, maj_planning_travaux et annulation_resa_planning.
Sauvegarde dans le fichier PLANNING les données du planning présentes en mémoire.

*/


void enregistrement_planning()
{
  FILE *f1                               ;
  int i, j                               ;
  f1 = fopen(PLANNING, "w")              ;
  for(i = 0 ; i < MAX_NB_CHAMBRES ; i++)
  {
    for(j = 0 ; j < ANNEE ; j++)
    {
      fprintf(f1, "%lu", planning[i][j]) ;
    }
  }
  fclose(f1)                             ;
}
/*############################################
#                                            #
#               programme_crea               #
#                                            #
##############################################

Lit le planning de hier, celui d'aujourd'hui et prépare le programme de la journée en confrontant les codes de réservation.

*/
void programme_crea(int p_hier)
{
  FILE *f1 ;
  int i, cpt_libres = 0, cpt_hiertr = 0, cpt_aujtr = 0, cpt_recouche = 0, cpt_senva = 0, cpt_arrive = 0 ;
  int hier_travaux[MAX_NB_CHAMBRES], auj_travaux[MAX_NB_CHAMBRES], recouche[MAX_NB_CHAMBRES], gdmen[MAX_NB_CHAMBRES], libres[MAX_NB_CHAMBRES] ;
  long unsigned int senva[MAX_NB_CHAMBRES], arrive[MAX_NB_CHAMBRES], chambre_hier, chambre_auj          ;

  chargement_planning()                                        ;
  for(i = 0 ; i < MAX_NB_CHAMBRES ; i++)
  {
    chambre_hier = planning[i][p_hier]                         ;
    chambre_auj = planning[i][p_hier+1]                        ;
    switch(chambre_hier)
    {
      case 0:
        break                                                  ;
      case 1:
        if(chambre_auj != 1)
        hier_travaux[cpt_hiertr] = tab_chambres[i].num_chambre ;
        cpt_hiertr++                                           ;
        break                                                  ;
      default:
        if(chambre_hier == chambre_auj)
        {
          recouche[cpt_recouche] = tab_chambres[i].num_chambre ;
          cpt_recouche++                                       ;
        }
        else
        {
          senva[cpt_senva] = chambre_hier                      ;
          gdmen[cpt_senva] = tab_chambres[i].num_chambre       ;
          cpt_senva++                                          ;
        }
    }
    switch(chambre_auj)
    {
      case 0:
        libres[cpt_libres] = tab_chambres[i].num_chambre       ;
        cpt_libres++                                           ;
        break                                                  ;
      case 1:
        auj_travaux[cpt_aujtr] = tab_chambres[i].num_chambre   ;
        cpt_aujtr++                                            ;
        break                                                  ;
      default:
        if(chambre_auj != chambre_hier)
        {
          arrive[cpt_arrive] = chambre_auj                     ;
        }
    }
  }

  f1 = fopen(PROGRAMME, "w")                                   ;
  fprintf(f1, "PROGRAMME DU JOUR\n\n")                         ;
  fprintf(f1, "Départs")                                       ;
  if(cpt_senva == 0)
  {
    fprintf(f1, " : aucun.\n")                                 ;
  }
  else
  {
    fprintf(f1, "\n")                                          ;
    for(i = 0 ; i < cpt_senva; i++)
    {
      fprintf(f1, "Chambre n.%d\n, réservation n.%lu", gdmen[i], senva[i]) ;
    }
  }
  fprintf(f1, "Arrivées")                            ;
  if(cpt_arrive == 0)
  {
    fprintf(f1, " : aucune.\n")                      ;
  }
  else
  {
    fprintf(f1, "\n")                                ;
    for(i = 0 ; i < cpt_arrive; i++)
    {
      fprintf(f1, "Réservation n.%lu\n", arrive[i])  ;
    }
  }
  fprintf(f1, "Chambres libres")                     ;
  if(cpt_libres == 0)
  {
    fprintf(f1, " : aucune.\n")                      ;
  }
  else
  {
    fprintf(f1, "\n")                                ;
    for( i = 0 ; i < cpt_libres ; i++)
    {
      fprintf(f1, "Chambre n.%d\n", libres[i])       ;
    }
  }
  fprintf(f1, "Ménage, recouches")                   ;
  if(cpt_recouche == 0)
  {
    fprintf(f1, " : aucune.\n")                      ;
  }
  else
  {
    fprintf(f1, "\n");
    for( i = 0 ; i < cpt_recouche ; i++)
    {
      fprintf(f1, "Chambre n.%d\n", recouche[i])     ;
    }
  }
  fprintf(f1, "Ménage, grand ménage")                ;
  if(cpt_senva == 0)
  {
    fprintf(f1, " : aucun.\n")                       ;
  }
  else
  {
    fprintf(f1, "\n")                                ;
    for(i = 0 ; i < cpt_senva; i++)
    {
      fprintf(f1, "Chambre n.%d\n", gdmen[i])        ;
    }
  }
  fprintf(f1, "Travaux finis hier, à vérifier")      ;
  if(cpt_hiertr == 0)
  {
    fprintf(f1, " : aucun.\n")                       ;
  }
  else
  {
    fprintf(f1, "\n")                                ;
    for(i = 0 ; i < cpt_hiertr; i++)
    {
      fprintf(f1, "Chambre n.%d\n", hier_travaux[i]) ;
    }
  }
  fprintf(f1, "Travaux prévus pour aujourd'hui")     ;
  if(cpt_aujtr == 0)
  {
    fprintf(f1, " : aucun.\n")                       ;
  }
  else
  {
    fprintf(f1, "\n")                                ;
    for(i = 0 ; i < cpt_aujtr; i++)
    {
      fprintf(f1, "Chambre n.%d\n", auj_travaux[i])  ;
    }
  }
  fclose(f1)                                         ;
  printf("Le programme de la journée est prêt.\n")   ;
}


/*############################################
#                                            #
#               programme_lis                #
#                                            #
##############################################

Appelée dans le menu principal.
Affiche le programme du jour via cat.
Ce n'est pas que de la fainéantise, c'est aussi pour permettre à l'utilisateur d'imprimer le fichier!
*/

void programme_lis()
{
  system("cat 1-Parametres/programme.txt") ;
}
