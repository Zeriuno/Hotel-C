#include "declarations.h"

/*############################################
#                                            #
#                PARTIE JOURS                #
#        #############################       #
#                                            #
#                   saisie                   #
#                                            #
##############################################

Afin de permettre de saisir avec des espaces (jusqu'à "\n").

*/

void saisie()
{
  char saisie[];

  while((c = getchar()) != '\n')
  {
    strcat(saisie, c)  ;
  }
  strcat(saisie, '*')  ;
  strcat(saisie, '\0') ;
}
