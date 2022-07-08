##
## EPITECH PROJECT, 2021
## MyTeams : Mikael, Maxime, Nolann
## File description:
## Makefile
##

green = /bin/echo -e '\x1b[32m\x1b[1m$1'
red = /bin/echo -e '\x1b[31m\x1b[1m$1'
cyan = /bin/echo -e '\x1b[34m\x1b[1m$1'

CC = gcc

ifneq (,$(shell command -v ccache))
	CC := ccache gcc
endif

CFLAGS	=	-I./include 	\
			-Wall	\
			-Wextra	\
			-g3

MAIN_SRC = src/main.c
SRC	=	$(filter-out ./src/main.c, $(wildcard ./src/*.c))	\
		$(wildcard ./src/args/*.c)	\
		$(wildcard ./src/linked/*.c)	\
		$(wildcard ./src/player/*.c)	\
		$(wildcard ./src/client/*.c)	\
		$(wildcard ./src/commands/*.c)	\
		$(wildcard ./src/commands/player/*.c)	\
		$(wildcard ./src/commands/gui/*.c)	\
		$(wildcard ./src/response/*.c)

OBJ	=	$(SRC:.c=.o)
MAIN_OBJ =	$(MAIN_SRC:.c=.o)
NAME =	zappy_server

TEST_SRC =	$(wildcard ./tests/*.c)

TEST_OBJ =	$(TEST_SRC:.c=.o)
TEST_NAME =	zappy_server_test

all:	$(NAME)

object_info:
	@$(call cyan,\n[SERVER] Zappy server compilation: ...\n\x1b[36m\x1b[1m)

$(NAME): object_info $(OBJ) $(MAIN_OBJ)
		$(CC) $(OBJ) $(MAIN_OBJ) -o $(NAME) $(CFLAGS)
		@$(call green,\n[SERVER] Compilation terminé\n\x1b[0m)
		mv $(NAME) ../

clean:
	@find . -name "*.o" -exec rm -rf "{}" \;
	@find . -name "*.~" -exec rm -rf "{}" \;
	@$(call red,\n[SERVER] Fichiers temporaires et fichiers\
	objets supprimés.\x1b[0m)

fclean: clean
	@rm -f ../$(NAME)
	@rm -f ./$(TEST_NAME)
	@$(call red,[SERVER] Fichier binaire supprimé.\n\x1b[0m)

tests_run: $(OBJ) $(TEST_OBJ)
	gcc -o $(TEST_NAME) $(OBJ) $(TEST_OBJ) --coverage -lcriterion
	./$(TEST_NAME)

re: fclean all

.PHONY: re clean fclean all
