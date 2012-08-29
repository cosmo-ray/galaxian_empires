#ifndef	PLAYER_H_
#define	PLAYER_H_


#include "fleet.h"
#include "glist.h"

typedef	struct	s_player
{
  int		id;
  t_list	fleets;
}	t_player;

void	init_player(t_player *player);
int	add_fleet(t_player *p, int nbr, t_ship *ship);
void	delet_player(t_player *p);
t_fleet	*get_fleet(t_player *p, int nbr);
int	get_fleet_on(t_player *p, int x, int y);
#endif
