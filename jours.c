#include "declarations.h" /*c'est ici que sont les #include et les #define*/

void lecture_jours()       ;
void test_date()           ;
void maj_calendrier(int i) ;


char poubelle            ; /*pour vider le buffer des \n*/

/*Calendrier*/
struct jour
{
  long unsigned int date ; /*date aaaammjj*/
  short int saison       ; /*0 basse saison, 1 haute saison*/
}                        ;

struct jour calendrier[ANNEE] ;


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
