##
## EPITECH PROJECT, 2022
## zappy
## File description:
## Makefile
##

MAKEFLAGS	+=	-s

NAME	=	zappy_gui

CXX	=	g++

ifneq (,$(shell command -v ccache))
	CXX := ccache g++
endif

SRCS	=	./src/main.cpp	\
			./src/args_manager.cpp	\
			./src/starter.cpp

OBJS	=	$(SRCS:.cpp=.o)

CXXFLAGS	=	-I./includes	\
				-g3	\
				-Wall	\
				-Wextra
				-std=c++20

COPY_PATH	=	../$(NAME)

all:	$(NAME)
	cp $(NAME) $(COPY_PATH)

$(NAME):	$(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(CXXFLAGS)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)
	rm -f $(COPY_PATH)

re:	fclean all

.PHONY: all clean fclean re
