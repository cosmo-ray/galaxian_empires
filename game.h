#ifndef GAME_H
# define GAME_H

#include	"sdl_util.h"

/*contain all the vital info for the game, that should be crast at the begin of the game and destriy at the end*/
typedef	struct	s_game
{
  SDL_Surface	*win;
  int		nb_plyaers;
}	t_game;

#endif /* !GAME1_H */
