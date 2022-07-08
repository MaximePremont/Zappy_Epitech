##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Made by Mikey
##

SRC     =   src/zappy_ai

NAME	=   zappy_ai

all:	$(NAME)

$(NAME):
	cp src/$(NAME) ../
	chmod +x ../$(NAME)

clean:
	@echo "cleaning ..."

fclean:	clean
	rm -f $(NAME)
	rm -f ../$(NAME)

re:	fclean all

.PHONY: all clean fclean re
