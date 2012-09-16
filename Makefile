SRC=		main.c \
		bmap.c \
		ship.c \
		fleet.c \
		glist.c \
		sdl_util.c \
		player.c \
		battle.c \
		battle_display.c \
		selector.c \
		calculaor.c \
		game.c \
		mesage_box.c \
		menu_box.c \

OBJ=		$(SRC:.c=.o)

NAME=		galaxian_empires

CC=		gcc

CFLAGS		+= -Wall -Wextra -g3 -Werror
CFLAGS		+= ${shell sdl-config --cflags}
LDFLAGS		+= ${shell sdl-config --libs} -lSDL_image -lSDL_ttf -lm

all:	$(OBJ)
	$(CC) -o $(NAME) $(LDFLAGS) $(OBJ)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		clean all

.PHONY:		all clean re


