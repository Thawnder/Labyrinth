CC=gcc
CFLAGS=-Wall -Iinclude
LDFLAGS=
EXEC=main test
SRC_PATH=src
OBJ_PATH=obj
SRC_NAME= main.c\
					creerplateau.c\
					distribuer.c\
					joueurs.c\
					victoire.c\
					jouer_tour.c\
					afficher.c\
					pousser.c
OBJ_NAME= $(SRC_NAME:.c=.o)
SRC= $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))
SRCTEST_PATH=tests
OBJTEST_PATH=obj
SRCTEST_NAME= test.c\
					joueurs_test.c\
					victoire_test.c\
					creerplateau_test.c\
					distribuer_test.c\
					jouer_tour_test.c\
					pousser_test.c
					
OBJTEST_NAME=$(SRCTEST_NAME:.c=.o)
SRCTEST=$(addprefix $(SRCTEST_PATH)/, $(SRCTEST_NAME))
OBJTEST=$(addprefix $(OBJTEST_PATH)/, $(OBJTEST_NAME))

all: $(EXEC)


main: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)

main.o: include/distribuer.h include/joueurs.h include/victoire.h include/creerplateau.h include/jouer_tour.h include/afficher.h include/pousser.h include/structures.h
	@$(CC) -c src/main.c $(CFLAGS)

obj/%.o: src/%.c
	@$(CC) -o $@ -c $< $(CFLAGS)

test: $(OBJTEST) obj/unity.o
	@$(CC) -o $@ $^ $(LDFLAGS)

test.o: include/creerplateau_test.h include/distribuer_test.h include/jouer_tour_test.h include/pousser_test.h include/joueurs_test.h include/victoire_test.h include/structures.h include/distribuer.h include/joueurs.h include/victoire.h include/creerplateau.h include/jouer_tour.h include/afficher.h include/pousser.h
	@$(CC) -c tests/test.c $(CFLAGS)

obj/unity.o:  unity/src/unity.c
	@$(CC) -o obj/unity.o -c unity/src/unity.c

obj/%.o: tests/%.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf obj/*.o
	@rm -rf tests/*.o

mrproper: clean
	@rm -rf $(EXEC)
