# Liste des fichiers sources
SOURCE=hotel.c utilitaires.c

# Liste des fichiers objets
OBJETS=hotel.o utilitaires.o

hotel : $(OBJETS)
	cc -o hotel $(OBJETS)

hotel.o : hotel.c declarations.h
	cc -c hotel.c

utilitaires.o : utilitaires.c declarations.h
	cc -c utilitaires.c
