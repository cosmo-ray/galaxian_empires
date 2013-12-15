NAME=		BoGH

SRC=		main.c \
		bmap.c \
		ship.c \
		fleet.c \
		glist.c \
		sdl_util.c \
		pos.c \
		heroes.c \
		battle.c \
		battle_display.c \
		battle_actions.c \
		battle_init.c \
		battle_turn.c \
		selector.c \
		calculaor.c \
		game.c \
		mesage_box.c \
		menu_box.c \

OBJ=		$(SRC:.c=.o)

CC=		gcc

CFLAGS		+= -Wall -Wextra  -Werror -g
CFLAGS		+= ${shell sdl-config --cflags}
LDFLAGS		+= ${shell sdl-config --libs} -lSDL_image -lSDL_ttf -lm

all:	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		clean all

.PHONY:		all clean re
