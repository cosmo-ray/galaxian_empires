#include	<stdlib.h>
#include	<string.h>
#include	"calculaor.h"
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

int	get_dir_fleet_target(t_fleet *fleet, t_pos *target)
{
  double rad;

  target = cal_get_Line(&fleet->pos, target);
  rad = get_rad(target);
  if ((target->y > 0 && fleet->pos.dir == SOUTH)
      || (target->y < 0 && fleet->pos.dir == NORTH))
    {
      if (rad < 0.321751 && rad > -0.321751)
	{ printf ("front attaque\n"); return (FRONT); }
      else
	{ printf ("side attaque\n"); return (SIDE); }
    }
  else if (fleet->pos.dir == NORTH || fleet->pos.dir == SOUTH)
    {
      if (rad < 0.321751 && rad > -0.321751)
	{ printf ("back attaque\n"); return (BACK); }
      else
	{ printf ("side attaque\n"); return (SIDE); }
    }
  else if ((target->x > 0 && fleet->pos.dir == WEST)
      || (target->x < 0 && fleet->pos.dir == EAST))
    {
      if (rad < 1.249046 && rad > -1.249046)
	{ printf ("front attaque\n"); return (FRONT); }
      else
	{ printf ("side attaque\n"); return (SIDE); }
    }
  else
    {
      if (rad < 1.249046 && rad > -1.249046)
	{ printf ("back attaque\n"); return (BACK); }
      else
	{ printf ("side attaque\n"); return (SIDE); }
    }
  return (FRONT);
}

int	get_dir_fleet_dmg(t_fleet *fleet, t_pos *pos)
{
  (void)fleet;
  (void) pos;
  return (BACK);
}

void	pos_fleet(t_fleet *fleet, int x, int y, int dir)
{
  fleet->pos.x = x;
  fleet->pos.y = y;
  fleet->pos.dir = dir;
}

int	print_fleet_ship(t_fleet *fleet)
{
  static char int_tab[5];

  if (fleet == NULL)
    return (0);
  display_ship_sprite(&fleet->pos);
  sprintf(int_tab, "%d", fleet->nbr);
  return (display_txt_on_pos(&fleet->pos, int_tab));
}

void	turn_left(t_fleet *fleet)
{
  if (fleet->pos.dir == WEST)
    fleet->pos.dir = NORTH;
  else if (fleet->pos.dir == NORTH)
    fleet->pos.dir = EAST;
  else if (fleet->pos.dir == EAST)
    fleet->pos.dir = SOUTH;
  else if (fleet->pos.dir == SOUTH)
    fleet->pos.dir = WEST;
}

void	turn_right(t_fleet *fleet)
{
  if (fleet->pos.dir == WEST)
    fleet->pos.dir = SOUTH;
  else if (fleet->pos.dir == NORTH)
    fleet->pos.dir = WEST;
  else if (fleet->pos.dir == EAST)
    fleet->pos.dir = NORTH;
  else if (fleet->pos.dir == SOUTH)
    fleet->pos.dir = EAST;
}
