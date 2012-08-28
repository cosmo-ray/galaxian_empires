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

}	t_battle;

int	battle(t_player *p1, t_player *p2);

#endif
