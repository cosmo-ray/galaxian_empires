#ifndef	HEROES_H_
#define	HEROES_H_


#include "fleet.h"
#include "glist.h"

typedef	struct	s_heroes
{
  int		id;
  t_list	fleets;
}	t_heroes;

void	init_heroes(t_heroes *heroes);
int	add_fleet(t_heroes *p, int nbr, t_ship *ship);
void	delet_heroes(t_heroes *p);
t_fleet	*get_fleet(t_heroes *p, int nbr);
int	get_fleet_on(t_heroes *p, int x, int y);
t_fleet	*get_fleet_by_pos(t_heroes *p, int x, int y);
int	display_all_fleet(t_heroes *p);
int	heroes_delet_fleet(t_heroes *p, t_fleet *f);
/*set the action point at ther initial valure stocked in type*/
void	reset_ap(t_heroes *p);
int	full_empty_ap(t_heroes *p);
float	heroes_yp_mod_at_case(t_heroes *p, t_fleet *f, t_pos *pos);

#endif
