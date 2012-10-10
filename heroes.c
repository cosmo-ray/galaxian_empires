#include	"heroes.h"
#include	"game.h"

 extern t_game	life;

 void	init_heroes(t_heroes *heroes)
 {   
   heroes->id = life.nb_plyaers + 1;
   init_list(&(heroes->fleets));
   life.nb_plyaers += 1;
 }

void	delet_heroes(t_heroes *p)
{
  t_fleet	*dom;

  while(p->fleets.len)
    {
      dom = pop_data(&(p->fleets));
      delet_fleet(dom);
      free(dom);
    }
}

int	add_fleet(t_heroes *p, int nbr, t_ship *ship)
{
  t_fleet	*new = malloc(sizeof(*new));

  if (new == NULL)
    return (-1);
  if (init_fleet("fleet", ship, nbr, new))
    return (-1);
  push_elem(&(p->fleets), new_elem(new));
  return (0);
}

t_fleet	*get_fleet(t_heroes *p, int nbr)
{
  return (get_data(&p->fleets, nbr - 1));
}

int	get_fleet_on(t_heroes *p, int x, int y)
{
  t_node	*node = p->fleets.first;
  int		ret = 1;

  while (node != NULL)
    {
      if (((t_fleet *)node->data)->pos.x == x 
	  && ((t_fleet *)node->data)->pos.y == y)
	return (ret);
      node = node->next;
      ++ret;
    }
  return (0);
}

t_fleet	*get_fleet_by_pos(t_heroes *p, int x, int y)
{
  return (get_fleet(p, get_fleet_on(p, x, y)));
}

int	display_all_fleet(t_heroes *p)
{
  int	i = 0;
  int	len = p->fleets.len;

  while (i < len)
    {
      print_fleet_ship(get_data(&p->fleets, i));
      ++i;
    }
  return (0);
}

void	reset_ap(t_heroes *p)
{
  int		i = 0;
  int		len = p->fleets.len;
  t_fleet	*fleet;
  
  while (i < len)
    {
      fleet = get_data(&p->fleets, i);
      fleet_set_ap(fleet, fleet->type->ap);
      ++i;
    }
}

int	full_empty_ap(t_heroes *p)
{
  int		i = 0;
  int		len = p->fleets.len;
  t_fleet	*fleet;
  
  while (i < len)
    {
      fleet = get_data(&p->fleets, i);
      if (fleet->remain_ap > 0)
	return (0);
      ++i;
    }
  return (1);
}

float	heroes_yp_mod_at_case(t_heroes *p, t_fleet *f, t_pos *pos)
{
  int		i = 0;
  int		len = p->fleets.len;
  t_fleet	*fleet;
  float		ret = 0;

  while (i < len)
    {
      fleet = get_data(&p->fleets, i);
      if ((fleet != f) && (comp_pos(pos, &fleet->pos) < fleet->type->ypr))
	{
	  ret += fleet->type->yp;
	}
      ++i;
    }
  return (ret);
}

int	heroes_delet_fleet(t_heroes *p, t_fleet *f)
{
  if (pop_data_elem(&p->fleets, f))
    return (-1);
  delet_fleet(f);
  return (0);
}
