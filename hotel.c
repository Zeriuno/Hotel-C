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
*/

#include <stdio.h>
#include <string.h>


/*Constantes*/

#define MAX_CAT_SERV 20    /* Constante qui limite le catalogue des services -- ajouter un test concernant cette limite - Utilisé pour catalogue_services */
#define MAX_NOM_SERVICE 21 /* Taille maximale de la chaîne de caractères qui décrit les services complémentaires - Utilisé pour nom_service */
#define MAX_NB_CHAMBRES 50 /*Utilisée dans tab_chambres[]*/
#define NON_TROUVE -1 /*Pour tester si un résultat a été trouvé à la recherche*/

/*Chambres*/
int rech_chambre(int chambre_rech);
void chargement_chambres()        ;
void modification_chambre()       ;
void enreg_chambre()              ;
void affichage_chambre()          ;

/*Déclarations préliminaires*/
void mauvais_choix(int par_choisi)   ; /* Mauvais choix à l'intérieur des menus*/

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

struct resa
{
  /*code de réservation, à déterminer comment il est construit*/
  int datearrivee       ;
  int datedepart        ;
  char nomclient[50]    ;
  char prenomclient[50] ;
  char telclient[13]    ;  /*+33653332003 qui peut être affiché +33 6 53 33 20 03. Vérifier de quelle taille doit être le numéro: 12?*/
};

struct cha
{  /* structure pour les chambres*/
  /*int code_chambre ;*/
  int num_chambre ; /* Numéro selon la codification de l'hôtel */
  int nb_lits     ;
  int vue         ; /* 0 pas de vue; 1 avec vue */
  int bain        ; /* 0 baignoire; 1 douche */
  int fumeur      ; /* 0 non fumeur, 1 fumeur */
  int animaux     ; /* 0 pas d'animaux, 1 animaux acceptés */
  /*champ remarques en chaîne de caractères*/
};
  /* Variables globales concernant les chambres*/
struct cha tab_chambres[MAX_NB_CHAMBRES]; /*Tableau listant les chambres*/
int a_sauv_chambre=0                    ; /*pour la modification des chambres*/

  /* Variables globales concernant les frais*/
struct frais{
  int datefrais        ; /*autrement on en fera une string de 9, 'aaaammjj' (8) + '\0'*/
  float montantfrais   ;
  int codefrais[200] ;
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

main()
{
  int choix = 0 ; /* Déclaration de la variable et initialisation à une valeur qui permet de rentrer dans le 'while'. */
  int res_chambre = 0; /*Résultat recherche chambres */
  int chambre_cible = 0; /*Chambre recherchée*/
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
    printf("     PARAMÉTRES    \n\n")                      ;
    printf("5 - Mettre à jour la date du planning.\n")     ;
    printf("6 - Catalogue des services.\n\n")              ;
    printf("------------------------------------------\n") ;
    printf("     QUITTER    \n\n")                         ;
    printf("9 - Quitter l'application.\n")               ;
    /*printf("7 - Imprimer le programme d'aujourd'hui.\n") ; On ne l'a pas mis dans le planning, mais c'est une idée dont on avait parlé. On verra plus tard si et comment le faire.*/
    printf("-------------------\n") ;

    printf("Faire un choix : ") ;
    scanf("%d", &choix)         ; /* Attention, à partir de ce moment il y a un '\n' qui traîne dans le buffer. */
    struct cha chambre          ;

    switch(choix)
    {
      case 1: case 2: case 3:
        printf("C'est une fonction qui n'a pas encore été développée. Les auteurs sont des fainéants!\n") ;
        break                                                                                             ;
      case 4:
        chargement_chambres()                                                                             ;
        printf("Entrez le numéro de la chambre à rechercher: ")                                           ;
        scanf("%d", &chambre_cible)                                                                       ;
        res_chambre=rech_chambre(chambre_cible)                                                           ;
        if(res_chambre == NON_TROUVE)
        {
          printf("%d n'a pas été trouvé. \n", chambre_cible)                                              ;
        }
        else
        {
          chambre=tab_chambres[res_chambre]                                                               ;
          printf("%d\n", chambre.num_chambre)                                                             ;
        }
        break                                                                                             ;
      case 5: /*case 7:*/
        printf("C'est une fonction qui n'a pas encore été développée. Les auteurs sont des fainéants!\n") ;
        break                                                                                             ;
      case 6:
        catalogue_services_menu()                                                                         ;
        break                                                                                             ;
      case 9:
        printf("Vous avez choisi de quitter l'application.\nMerci et au revoir.\n") ;
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

Fonction appellée par les menus de choix.
Elle signale à l'utilisateur que le choix fait n'est pas disponible.
Elle reçoit un paramètre pour signaler quel est le choix qui a été fait.

*/
void mauvais_choix(int par_choix)
{
  printf("Vous avez sélectionné %d : ce choix n'est pas disponible. Veuillez ressaisir.\n", par_choix);
}


/*############################################
#                                            #
#             PARTIE RESERVATIONS            #
#       #############################        #
#                                            #
#             creer_reservation              #
#                                            #
##############################################

Procédure pour créer un réservation.


*//*pour l'instant cela ne peut pas marcher
void creer_reservation()
{
  cible_date()    ;
  cible_chambre() ;
  rech_période(date_debut, date_fin ) ;

}

/*############################################
#                                            #
#                cible_date                  #
#                                            #
##############################################

Procédure pour créer un saisir une date.


*//*ça ne peut pas marcher pour le moment
void /*à voir: affecte des variables globales? saisie_date()
{
  printf("Saisir la date de début (jj/mm/aa) : ")           ;
  scanf("%d/%d/%d\n", &jour_debut, &mois_debut, &an_debut)  ;
  printf("Saisir la date de fin (jj/mm/aa) : ")             ;
  scanf("%d/%d/%d\n", &jour_fin, &mois_fin, &an_fin)        ;
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
int bain        ; 0 baignoire; 1 douche
int fumeur      ; 0 non fumeur, 1 fumeur
int animaux     ; 0 pas d'animaux, 1 animaux acceptés

  printf("Combien de lits (saisir 1 ou 2) ? ");
  scanf("%d", &cible lits) ;
  printf("Chambre avec vue ? ") ;
  scanf("%", &cible_vue) ;
  printf("");
  printf("");
  printf("");
  printf("");
}*/
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
#              modif_chambre                 #
#                                            #
##############################################

*/
void modif_chambre()
{

}

/*############################################
#                                            #
#             chargement_chambres            #
#                                            #
##############################################

Lit le fichier chambres.txt et charge son contenu dans le tableau de chambres.

*/
void chargement_chambres()
{
  FILE *f1                      ;
  struct cha chambre            ;
  int i                         ;

  f1 = fopen("chambres.txt", "r") ;
  while(!feof(f1))
  {
    fscanf(f1, "%d %d %d %d %d %d\n", &chambre.num_chambre, &chambre.nb_lits, &chambre.vue, &chambre.bain, &chambre.fumeur, &chambre.animaux) ;
    tab_chambres[i] = chambre                                         ;
    i++                                                               ;
  }
  fclose(f1)                                                          ;
  nb_services = i                                                     ;
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
  struct cha chambre                ;
  int chambre_rech=0                ;
  int i, numcase_chambre=NON_TROUVE ;
  for (i=0; i<MAX_NB_CHAMBRES; i++)
  {
    chambre=tab_chambres[i];
    if (chambre.num_chambre==chambre_rech)
    {
      numcase_chambre=i;
    }
  }
  return numcase_chambre;
}

/*############################################
#                                            #
#           modification_chambre                     #
#                                            #
##############################################

Modifier les chambres par la recherche de leur numéro.


*/
void modification_chambre()
{
  struct cha chambre                                    ;
  int chambre_rech=0                                    ;
  int res_chambre = 0                                   ; /*Résultat recherche chambres */
  printf("Entrez le numéro de la chambre à modifier : ");
  scanf("%d",&chambre_rech )                            ;
  res_chambre=rech_chambre(chambre_rech)                ;
  if (res_chambre == NON_TROUVE)
  {
    printf("Aucune modification: %d n'a pas été trouvé\n", chambre_rech);
  }
  else
  {
    chambre=tab_chambres[res_chambre];
    printf("Numéro actuel de la chambre: %d\n", chambre.num_chambre) ;
    printf("Nouveau numéro de la chambre: %d\n", chambre.num_chambre);
    scanf("%d", &chambre.num_chambre)                                ;

    printf("Nombre actuel de lits: %d\n", chambre.nb_lits)           ;
    printf("Nouveau nombre de lits: %d\n", chambre.nb_lits)          ;
    scanf("%d", &chambre.nb_lits)                                    ;

    printf("Chambre avec vue : %d\n", chambre.vue)                   ;
    printf("Chambre avec vue : %d\n", chambre.vue)                   ;
    scanf("%d", &chambre.vue)                                        ;

    printf("Douche ou baignoire : %d\n", chambre.bain)               ;
    printf("Douche ou baignoire : %d\n", chambre.bain)               ;
    scanf("%d", &chambre.bain)                                       ;

    printf("Fumeur ou non : %d\n", chambre.fumeur)                   ;
    printf("Fumeur ou non : %d\n", chambre.fumeur)                   ;
    scanf("%d", &chambre.fumeur)                                     ;

    printf("Animaux acceptés ou non : %d\n", chambre.animaux)        ;
    printf("Animaux ou non : %d\n", chambre.animaux)                 ;
    scanf("%d", &chambre.animaux)                                    ;

    tab_chambres[res_chambre]=chambre                                ;
    a_sauv_chambre=1                                                 ;
    enreg_chambre()                                                  ;
  }
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
  f1 = fopen("chambres.txt", "w")           ;
  int i                                     ;
  struct cha chambre                        ;

  for(i = 0; i < MAX_NB_CHAMBRES ; i++)
  {
    chambre = tab_chambres[i]               ;
    fscanf(f1, "%d %d %d %d %d %d\n", &chambre.num_chambre, &chambre.nb_lits, &chambre.vue, &chambre.bain, &chambre.fumeur, &chambre.animaux) ;
  }
  fclose(f1)                                                ;
  a_sauv_chambre = 0                                        ;
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
  struct cha chambre                                                   ;
  int i                                                                ;
  for(i=0; i < MAX_NB_CHAMBRES; i++)
    {
      chambre = tab_chambres[i]                                        ;
      printf"%d %d %d %d %d %d\n", &chambre.num_chambre, &chambre.nb_lits, &chambre.vue, &chambre.bain, &chambre.fumeur, &chambre.animaux) ;
    }
}
