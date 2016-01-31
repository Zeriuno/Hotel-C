#include <stdio.h>

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
    printf("     PLANNING      \n\n")                      ;
    printf("5 - Mettre à jour la date du planning.\n\n")     ;
    /*printf("6 - Imprimer le programme d'aujourd'hui.\n") ; On ne l'a pas mis dans le planning, mais c'est une idée dont on avait parlé. On verra plus tard si et comment le faire.*/
    printf("-------------------\n") ;

    printf("Faire un choix : ") ;
    scanf("%d", &choix)         ; /* Attention, à partir de ce moment il y a un '\n' qui traîne dans le buffer. */
    switch(choix)
    {
      case 1: case 2: case 3: case 4: case 5: /*case 6:*/
        printf("C'est une fonction qui n'a pas encore été développée. Les auteurs sont des fainéants!\n") ;
        break ;
      case 9:
        printf("Vous avez choisi de quitter l'application.\nMerci et au revoir.\n") ;
        break ;
      default:
        printf("Vous avez choisi %d, qui n'est pas un choix valide.", choix) ;
        break ;
    }
  }

}
