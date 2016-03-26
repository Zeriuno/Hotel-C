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
  char saisie[MAX_PNOM_CLI] ;
  char c                    ;
  int i                     ;

  while((c = getchar()) != '\n')
  {
    saisie[i] = c  ;
    i++            ;
  }
  saisie[i] = '\7' ;
  saisie[i] = '\0' ;
}
