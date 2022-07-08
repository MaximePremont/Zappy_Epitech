##
## EPITECH PROJECT, 2021
## MyTeams : Mikael, Maxime, Nolann
## File description:
## Makefile
##

MAKEFLAGS	+=	-s

SERVER_FOLDER	=	./Server

AI_FOLDER	=	./Gui

GUI_FOLDER	=	./Ai

MAKE_SIMPLE	=	make -C

MAKE_CLEAN	=	make clean -C

MAKE_FCLEAN	=	make fclean -C

SERVER	=	server

AI	=	ai

GUI	=	gui

all:	$(SERVER) $(AI) $(GUI)
	@$(call green,\n[SERVER] Compilation terminé\n\x1b[0m)

$(SERVER):
	@echo "Building server..."
	$(MAKE_SIMPLE) $(SERVER_FOLDER)

$(AI):
	@echo "Building AI :"
	$(MAKE_SIMPLE) $(AI_FOLDER)

$(GUI):
	@echo "Building gui :"
	$(MAKE_SIMPLE) $(GUI_FOLDER)

server_clean:
	$(MAKE_CLEAN) $(SERVER_FOLDER)

ai_clean:
	$(MAKE_CLEAN) $(AI_FOLDER)

gui_clean:
	$(MAKE_CLEAN) $(GUI_FOLDER)

server_fclean:
	$(MAKE_FCLEAN) $(SERVER_FOLDER)

ai_fclean:
	$(MAKE_FCLEAN) $(AI_FOLDER)

gui_fclean:
	$(MAKE_FCLEAN) $(GUI_FOLDER)

clean:	server_clean ai_clean gui_clean
	@$(call red,\n[SERVER] Fichiers temporaires et fichiers\
	objets supprimés.\x1b[0m)

fclean:	server_fclean ai_fclean gui_fclean
	@$(call red,[SERVER] Fichier binaire supprimé.\n\x1b[0m)

re:	fclean all

.PHONY:	server ai gui all re clean fclean
