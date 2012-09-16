#ifndef	FLEET_H_
#define	FLEET_H_

#include	"ship.h"
#include	"pos.h"
#include	"bmap.h"

typedef	struct	s_fleet
{
  t_pos		pos;
  char		*name;
  t_ship	*type;
  int		nbr;
}	t_fleet;

char    *get_fleet_name(t_fleet *fleet);
int	get_fleet_nbr(t_fleet *fleet);
void	do_fleet_dmg(t_fleet *fleet, int nbr, int dir);
void	delet_fleet(t_fleet *fleet);
t_ship	*get_fleet_type(t_fleet *fleet);
int	init_fleet(char *name, t_ship *type, int nbr, t_fleet *fleet);
int	get_fleet_dmg(t_fleet *fleet, int dir);

/*get the direction define in ship.h(FRONT, SIDE, or BACK) of the direction of the target*/
int	get_dir_fleet_target(t_fleet *fleet, t_pos *pos);

/*get the direction define in ship.h(FRONT, SIDE, or BACK) of the direction of the incoming attaque*/
int	get_dir_fleet_dmg(t_fleet *fleet, t_spos *pos);

/*position the fleet a the position defined by x, y, and dir*/
void	pos_fleet(t_fleet *fleet, int x, int y, int dir);

/*display the fleet on the screen*/
int	print_fleet_ship(t_fleet *fleet);

#endif
