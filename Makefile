##
## Makefile for C in /home/rubio-_c//work/c
##
## Made by charlie rubio-nevado
## Login   <rubio-_c@epitech.net>
##
## Started on  Wed Jan  4 07:13:12 2012 charlie rubio-nevado
## Last update Sun Jul  1 19:21:35 2012 charlie rubio-nevado
##

SRC=		main.c \
		bmap.c \
		ship.c \
		fleet.c \
		glist.c \
		sdl_util.c \
		player.c \
		battle.c \
		selector.c \
		game.c

OBJ=		$(SRC:.c=.o)

NAME=		galaxian_empires

CC=		gcc

CFLAGS		+= -Wall -Wextra -g3 -Werror
CFLAGS		+= ${shell sdl-config --cflags}
LDFLAGS		+= ${shell sdl-config --libs} -lSDL_image -lSDL_ttf

all:	$(OBJ)
	$(CC) -o $(NAME) $(LDFLAGS) $(OBJ)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		clean all

.PHONY:		all clean re


