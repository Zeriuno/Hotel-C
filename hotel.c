/*#########################################################################
#                                                                         #
#                                  hotel.c                                #
#                                                                         #
###########################################################################

* v 0.0   - 2016-01-31 squelette du main
* v 0.0.1 - 2016-02-02 ajout de l'option '6 - Modifier le catalogue des services.'
* v 0.0.2 - 2016-02-03 procédure mauvais_choix, procédure catalogue_services_menu
à faire: données
*/

#include <stdio.h>
#include <string.h>
/*Constantes*/

#define MAX_CAT_SERV 20 /*Constante qui limite le catalogue des services*/
#define MAX_NOM_SERVICE 21

/*Déclarations préliminaires*/

void catalogue_services_menu()                   ; /*Ajout de la procédure pour afficher le menu qui montre les choix sur le catalogue de services*/
void saisie_services()                           ;
void enreg_catalogue_services()                  ;

void mauvais_choix(int par_choisi)               ;
/*Variables globales*/

struct reservation{
  /*code de réservation, à déterminer comment il est construit*/
  int datearrivee  ;
  int datedepart   ;
  char nomclient[50] ;
  char prenomclient[50] ;
    char telclient[13] ;  /*+33653332003 qui peut être affiché +33 6 53 33 20 03. Vérifier de quelle taille doit être le numéro: 12?*/
};


  /*ici on parle du catalogue_services*/

int sauv_catalogue_services = 0; /*Pour contrôler s'il faut sauvegarder le catalogue_services. Si c'est 0, le catalogue n'est pas à sauvegarder, si c'est 1 il faut le sauvegarder.*/
int nb_services = 0 ;
struct service{            /*Service additionnel facturé par l'hôtel, référence du catalogue*/
  float prix_service ;
  char  nom_service[]  ;
};
struct service catalogue_services[MAX_CAT_SERV];  /*Catalogue listant les services*/
struct frais{
  int datefrais        ; /*autrement on en fera une string de 9, 'aaaammjj' (8) + '\0'*/
  float montantfrais   ;
  int codefrais[200] ;
};

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


void catalogue_services_menu(){
  int choix_cat = 0 ;
  FILE *f1          ;


  while(choix_cat != 9){
    printf("\n")                                           ;
    printf("    CATALOGUE DES SERVICES\n\n")               ;
    printf("1 - Lire le catalogue des services\n")         ;
    printf("2 - Modifier le catalogue des services\n")     ;
    printf("3 - Ajouter un service\n")                     ;
    printf("4 - Supprimer un service\n")                   ;
    printf("9 - Quitter et revenir au menu principal\n\n") ;

    printf("Choisissez une action : ")                     ;
    scanf("%d", &choix_cat)                                ;
    switch(choix_cat)
    {
      case 1:
        /*f1 = fopen("catalogue-services.txt", "r") ; À modulariser
        fclose(f1);*/
        break;
      case 2:
       /*f1 = fopen("catalogue-services.txt", "w") ; À modulariser
        fclose(f1);*/
        break;
      case 3:
       saisie_services();
        break;
      case 4:
      /*f1 = fopen("catalogue-services.txt", "w") ; À modulariser
        fclose(f1);*/
        break;
      case 9:
        break;
      default:
        mauvais_choix(choix_cat);
        break;
    }
  }
}

void mauvais_choix(int par_choix){
  printf("Vous avez sélectionné %d : ce choix n'est pas disponible. Veuillez ressaisir.\n", par_choix);
}

void saisie_services(){
  int i = nb_services ;

  strcpy(service.nom_service, "début")          ;
  while(strcmp(service.nom_service,"fin") != 0)
  {
    printf("Saisir le nom du service ('fin' pour terminer) : ") ;
    scanf("%s", service.nom_service)                            ;
    if(strcmp(service.nom_service,"fin") = 0)
    {
      printf("Fin de la saisie. Retour au menu précédent.\n") ;
    }
    else
    {
      printf("Saisir le prix : ")       ;
      scanf("%f", service.prix_service) ;
      catalogue_services[i++] = service ;
    }
  }
  if(i > 0)
  {
    nb_services = i                                ;
    printf("%d services présents.\n", nb_services) ;
    sauv_catalogue_services = 1                    ;
    enreg_catalogue_services()                     ;
  }
}
