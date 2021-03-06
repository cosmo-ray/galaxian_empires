#ifndef GAME_H
# define GAME_H

#include	"sdl_util.h"
#include	"heroes.h"
#include	"sprite.h"

/*contain all the vital info for the game, that should be creat at the begin of the game and destroy at the end*/
typedef	struct	s_game
{
  SDL_Surface		*win;
  SDL_Surface		*sprite; /*gordon, what do you mean? sprite gordon approching*/
  SDL_Surface		*bg;
  SDL_Surface		*txtsurface;
  SDL_Surface		*msg_txtsurface;
  SDL_Color		color;
  TTF_Font		*font;
  TTF_Font		*mb_font;
  t_list		ships; /*lays*/
  int			nb_plyaers;
  t_battle_screen	tbs;
}	t_game;

int	give_life(void);
void    take_life();

#endif /* !GAME1_H */
