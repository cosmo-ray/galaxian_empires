#ifndef	PLAYER_H_
#define	PLAYER_H_

#include "glist.h"

typedef	struct	s_player
{
  int		id;
  t_list	fleets;
}	t_player;

void	init_player(t_player *player);

#endif
