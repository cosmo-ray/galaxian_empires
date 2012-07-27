#include	<stdlib.h>
#include	<string.h>
#include	"fleet.h"
#include	"sdl_util.h"

int	init_fleet(char *name, t_ship *type, int nbr, t_fleet *fleet)
{
  if ((fleet->name = malloc(sizeof(*name) * (strlen(name) + 1))) == NULL)
    return (-1);
  strcpy(fleet->name, name);
  fleet->type = type;
  fleet->nbr = nbr;
  fleet->pos.x = -1;
  fleet->pos.y = -1;
  return (0);
}

t_ship	*get_fleet_type(t_fleet *fleet)
{
  return (fleet->type);
}

void	delet_fleet(t_fleet *fleet)
{
  free(fleet->name);
}

void	do_fleet_dmg(t_fleet *fleet, int nbr, int dir)
{
  nbr *= get_muldmg(get_fleet_type(fleet), dir);
  fleet->nbr -= (nbr / get_pv(get_fleet_type(fleet)));
}

int	get_fleet_dmg(t_fleet *fleet, int dir)
{
  return (get_ship_atk(get_fleet_type(fleet), dir) * get_fleet_nbr(fleet));
}

char	*get_fleet_name(t_fleet *fleet)
{
  return (fleet->name);
}

int	get_fleet_nbr(t_fleet *fleet)
{
  return (fleet->nbr);
}

int	get_dir_fleet_target(t_pos *pos)
{
  (void) pos;
  return (FRONT);
}

int	get_dir_fleet_dmg(t_pos *pos)
{
  (void) pos;
  return (BACK);
}

void	pos_fleet(t_fleet *fleet, int x, int y, int dir)
{
  fleet->pos.x = x;
  fleet->pos.y = y;
  fleet->pos.dir = dir;
}

int	print_ship(t_fleet *fleet)
{
  return (display_ship_sprite(&fleet->pos));
}
