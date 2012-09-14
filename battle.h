#ifndef BATTLE_H
#define BATTLE_H

#include	"bmap.h"
#include	"player.h"

typedef	struct	s_battle
{
  int		nb_players;
  t_bmap	map;
  t_player	*p1;
  t_player	*p2;  
  int		cur_turn; /*TODO*/
}	t_battle;

void	display_case(t_battle *bd, int x, int y);
int	battle(t_player *p1, t_player *p2);

#endif
