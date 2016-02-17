#include "declarations.h"

/*

Dans ce fichier se trouvent les fonctions et procédures utilitaires, auxquelles on a potentiellement recours depuis toute autre partie du programme.

*/

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
  printf("Vous avez sélectionné %d : ce choix n'est pas disponible. Veuillez ressaisir.\n", par_choix) ;
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
  char temporaire[5]                            ;
  char date_chaine[11]                          ;
  annee = date/10000                            ;
  mois = (date - (annee * 10000)) /100          ;
  jour = (date - (annee *10000) - (mois * 100)) ;
  sprintf(temporaire, "%d", annee)              ;
  strcat(date_chaine, temporaire)               ;
  strcat(date_chaine, "/")                      ;
  sprintf(temporaire, "%d", mois)               ;
  strcat(date_chaine, temporaire)               ;
  strcat(date_chaine, "/")                      ;
  sprintf(temporaire, "%d", jour)               ;
  strcat(date_chaine, temporaire)               ;
  return *date_chaine                           ;
}
