#include	"player.h"
#include	"game.h"

 extern t_game	life;

 void	init_player(t_player *player)
 {   
   player->id = life.nb_plyaers + 1;
   init_list(&(player->fleets));
   life.nb_plyaers += 1;
 }

void	delet_player(t_player *p)
{
  t_fleet	*dom;

  while(p->fleets.len)
    {
      dom = pop_data(&(p->fleets));
      delet_fleet(dom);
      free(dom);
    }
}

int	add_fleet(t_player *p, int nbr, t_ship *ship)
{
  t_fleet	*new = malloc(sizeof(*new));

  if (new == NULL)
    return (-1);
  if (init_fleet("fleet", ship, nbr, new))
    return (-1);
  push_elem(&(p->fleets), new_elem(new));
  return (0);
}

t_fleet	*get_fleet(t_player *p, int nbr)
{
  return (get_data(&p->fleets, nbr - 1));
}

int	get_fleet_on(t_player *p, int x, int y)
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
