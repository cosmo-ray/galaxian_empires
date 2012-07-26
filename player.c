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

void	pos_player_fleets(t_player *p, t_bmap *map, int	dir)
{
  /*maybe one day the loop who ask to the player where he want to pos his fleets will be implement here*/
  if (dir == NORTH)
    pos_fleet((t_fleet *)p->fleets.first->data, map->x / 2, 0, SOUTH);
  else
    pos_fleet((t_fleet *)p->fleets.first->data, map->x / 2, map->y - 1, NORTH);
}

t_fleet	*get_fleet(t_player *p, int nbr)
{
  return (get_data(&p->fleets, nbr));
}
