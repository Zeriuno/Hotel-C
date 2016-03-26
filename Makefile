# Liste des fichiers sources
SOURCE=hotel.c utilitaires.c jours.c planning.c reservations.c

# Liste des fichiers objets
OBJETS=hotel.o utilitaires.o jours.o planning.o reservations.o

hotel : $(OBJETS)
	cc -o hotel $(OBJETS)

hotel.o : hotel.c declarations.h
	cc -c hotel.c

utilitaires.o : utilitaires.c declarations.h
	cc -c utilitaires.c
