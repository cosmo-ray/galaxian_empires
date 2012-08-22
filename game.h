#ifndef GAME_H
# define GAME_H

#include	"sdl_util.h"
#include	"player.h"
#include	"bmap.h"
#include	"sprite.h"

/*contain all the vital info for the game, that should be crast at the begin of the game and destriy at the end*/
typedef	struct	s_game
{
  SDL_Surface	*win;
  SDL_Surface	*sprite;/* gordon, what do you mean? sprite gordon approching */
  SDL_Surface   *txtsurface;
  SDL_Color     color;  
  TTF_Font      *font;
  t_list	ships; /*lays*/
  int		nb_plyaers;
}	t_game;

typedef	struct	s_battle
{
  int		nb_players;
  t_bmap	map;
  t_player	*p1;
  t_player	*p2;  
  t_player	*p3;
  t_player	*p4;  

}	t_battle;

int	give_life(void);
void    take_life();
int	battle(t_player *p1, t_player *p2, t_bmap *map);

#endif /* !GAME1_H */
