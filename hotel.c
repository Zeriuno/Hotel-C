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

*/

#include <stdio.h>
#include <string.h>


/*Constantes*/

#define MAX_CAT_SERV 20    /* Constante qui limite le catalogue des services -- ajouter un test concernant cette limite*/
#define MAX_NOM_SERVICE 21 /* Taille maximale de la chaîne de caractères qui décrit les services complémentaires*/


/*Déclarations préliminaires*/

void mauvais_choix(int par_choisi)   ; /* Mauvais choix à l'intérieur des menus*/

/*Gestion des services complémentaires*/
void catalogue_services_menu()       ; /* Menu qui montre les choix possibles pour le catalogue de services*/
void chargement_catalogue_services() ; /* Prend le fichier des services et le charge en mémoire (dans un tableau). Procédure transparente*/
void affichage_catalogue()           ; /* Montre le tableau de services*/
void saisie_services()               ; /* Pour saisir de nouveaux services, à la suite de ceux déjà listés*/
void enreg_catalogue_services()      ; /* Sauvegarde le tableau chargé en mémoire dans un fichier*/
void modif_services()                ; /* Pour modifier les services déjà listés*/

/*Variables globales*/

struct resa{
  /*code de réservation, à déterminer comment il est construit*/
  int datearrivee       ;
  int datedepart        ;
  char nomclient[50]    ;
  char prenomclient[50] ;
  char telclient[13]    ;  /*+33653332003 qui peut être affiché +33 6 53 33 20 03. Vérifier de quelle taille doit être le numéro: 12?*/
};

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
    switch(choix)
    {
      case 1: case 2: case 3: case 4: case 5: /*case 7:*/
        printf("C'est une fonction qui n'a pas encore été développée. Les auteurs sont des fainéants!\n") ;
        break ;
      case 6:
        catalogue_services_menu();
        break;
      case 9:
        printf("Vous avez choisi de quitter l'application.\nMerci et au revoir.\n") ;
        break ;
      default:
        mauvais_choix(choix);
        break ;
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
    strcpy(nom_serv, "début")          ;
    while(strcmp(nom_serv,"fin") != 0)
    {
      service = catalogue_services[i]                                  ;
      printf("Nom actuel du service : %s\n", service.nom_service)      ;
      printf("Nouveau nom ('fin' pour terminer) : ")                   ;
      scanf("%s", nom_serv)                                            ;
      if (strcmp(nom_serv, "fin"))
      {
        printf("Fin de la modification. Retour au menu précédent. \n") ;
      }
      else
      {
        printf("Prix actuel du service : %f\n", service.prix_service) ;
        printf("Nouveau prix : ")                                     ;
        scanf("%.2f", &prix_serv)                                       ;
        i++                                                           ;
      }
    }
    sauv_catalogue_services=1                                         ;
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
    nb_services = i                                ;
    printf("%d services présents dans le catalogue.\n", nb_services) ;
    sauv_catalogue_services = 1                    ;
    enreg_catalogue_services()                     ;
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
    service = catalogue_services[i]                                   ;
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
  fclose(f1)                                                        ;
  nb_services = i                                                   ;
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
      printf("%s : %.2f\n", service.nom_service, service.prix_service) ;
    }
  }
}