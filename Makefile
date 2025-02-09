##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## The makefile to compile the project.
##

NAME	=	my_butterfly

SRCS	=	$(shell find . -type f -name '*.c')

LIBS = -lcsfml-graphics -lcsfml-audio -lcsfml-system -lcsfml-window -lm

all	:	$(NAME)

$(NAME)	:
		gcc -o $(NAME) $(SRCS) $(LIBS)

clean	:
		rm -rf $(NAME)

fclean	:	clean

re	:	fclean	all
