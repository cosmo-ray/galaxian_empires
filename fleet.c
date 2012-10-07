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

  cal_get_Line(&fleet->pos, target);
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
  else if ((target->x < 0 && fleet->pos.dir == WEST)
      || (target->x > 0 && fleet->pos.dir == EAST))
    {
      if (rad > 1.249046 || (rad < -1.249046 && rad > -2))
	{ printf ("front attaque\n"); return (FRONT); }
      else
	{ printf ("side attaque\n"); return (SIDE); }
    }
  else
    {
      if (rad > 1.249046 || (rad < -1.249046 && rad > -2))
	{ printf ("back attaque\n"); return (BACK); }
      else
	{ printf ("side attaque\n"); return (SIDE); }
    }
  return (FRONT);
}

int	get_dir_fleet_dmg(t_fleet *fleet, t_pos *from)
{
  double rad;
  t_pos	 droite;

  cal_get_Line_ret(&fleet->pos, from, &droite);
  rad = get_rad(&droite);
  if ((droite.y > 0 && fleet->pos.dir == SOUTH)
      || (droite.y < 0 && fleet->pos.dir == NORTH))
    {
      if (rad < 0.321751 && rad > -0.321751)
	{ printf ("front dmg\n"); return (FRONT); }
      else
	{ printf ("side dmg\n"); return (SIDE); }
    }
  else if (fleet->pos.dir == NORTH || fleet->pos.dir == SOUTH)
    {
      if (rad < 0.321751 && rad > -0.321751)
	{ printf ("back dmg\n"); return (BACK); }
      else
	{ printf ("side dmg\n"); return (SIDE); }
    }
  else if ((droite.x < 0 && fleet->pos.dir == WEST)
      || (droite.x > 0 && fleet->pos.dir == EAST))
    {
      if (rad > 1.249046 || (rad < -1.249046 && rad > -2))
	{ printf ("front dmg\n"); return (FRONT); }
      else
	{ printf ("side dmg\n"); return (SIDE); }
    }
  else
    {
      if (rad > 1.249046 || (rad < -1.249046 && rad > -2))
	{ printf ("back dmg\n"); return (BACK); }
      else
	{ printf ("side dmg\n"); return (SIDE); }
    }
  return (FRONT);
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

void	turn_right(t_fleet *fleet)
{
  if (fleet->pos.dir == WEST)
    fleet->pos.dir = NORTH;
  else if (fleet->pos.dir == NORTH)
    fleet->pos.dir = EAST;
  else if (fleet->pos.dir == EAST)
    fleet->pos.dir = SOUTH;
  else
    fleet->pos.dir = WEST;
}

void	turn_left(t_fleet *fleet)
{
  if (fleet->pos.dir == WEST)
    fleet->pos.dir = SOUTH;
  else if (fleet->pos.dir == NORTH)
    fleet->pos.dir = WEST;
  else if (fleet->pos.dir == EAST)
    fleet->pos.dir = NORTH;
  else
    fleet->pos.dir = EAST;
}

static void	move_handle_forward(t_fleet *fleet)
{
  if (fleet->pos.dir == WEST)
    fleet->pos.x -= 1;
  else if (fleet->pos.dir == NORTH)
    fleet->pos.y -= 1;
  else if (fleet->pos.dir == EAST)
    fleet->pos.x += 1;
  else
    fleet->pos.y += 1;
}

static void	move_handle_backward(t_fleet *fleet)
{
  if (fleet->pos.dir == WEST)
    fleet->pos.x += 1;
  else if (fleet->pos.dir == NORTH)
    fleet->pos.y += 1;
  else if (fleet->pos.dir == EAST)
    fleet->pos.x -= 1;
  else
    fleet->pos.y -= 1;
}

static void	move_handle_rightward(t_fleet *fleet)
{
  if (fleet->pos.dir == WEST)
    fleet->pos.y += 1;
  else if (fleet->pos.dir == NORTH)
    fleet->pos.x += 1;
  else if (fleet->pos.dir == EAST)
    fleet->pos.y -= 1;
  else
    fleet->pos.x -= 1;
}

static void	move_handle_leftward(t_fleet *fleet)
{
  if (fleet->pos.dir == WEST)
    fleet->pos.y -= 1;
  else if (fleet->pos.dir == NORTH)
    fleet->pos.x -= 1;
  else if (fleet->pos.dir == EAST)
    fleet->pos.y += 1;
  else
    fleet->pos.x += 1;
}

void handle_move_ret(t_fleet *fleet, int ret)
{
  switch (ret)
    {
    case FORWARD:
      move_handle_forward(fleet);      
      break;
    case BACKWARD:
      move_handle_backward(fleet);      
      break;
    case RIGHTWARD:
      move_handle_rightward(fleet);      
      break;
    case LEFTWARD:
    move_handle_leftward(fleet);      
      break;
    }
}

int	fleet_rm_ap(t_fleet *fleet, float nbr)
{
  if (nbr > fleet->remain_ap)
    return (1);
  fleet->remain_ap -= nbr;
  printf("nbr:%f\nremain ap %f\n", nbr, fleet->remain_ap);
  return (0);
}

void	fleet_set_ap(t_fleet *fleet, float nbr)
{
  fleet->remain_ap = nbr;
}
