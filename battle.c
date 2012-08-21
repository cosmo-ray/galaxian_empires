#include	<unistd.h>
#include	<stdio.h>
#include	"game.h"
#include	"selector.h"

static int	do_turn(t_player *p, t_bmap *map)
{
  t_spos pos;
  (void) p;
  (void) map;

  select_case(&pos);
  return (0);
}

static int	battle_loop(t_player *p1, t_player *p2, t_bmap *map)
{
  int	ret = 0;

  while(1)
    {
      if ((ret = do_turn(p1, map)))
	{
	  if (ret == 1)
	    return (0);
	  else
	    return (-1);
	}
      if ((ret = do_turn(p2, map)))
	{
	  if (ret == 1)
	    return (0);
	  else
	    return (-1);
	}
    }
  return (0);
}

int	battle(t_player *p1, t_player *p2, t_bmap *map)
{
  if (p1->fleets.len == 0 || p2->fleets.len == 0)
    return (-1);
  pos_player_fleets(p1, map, NORTH);
  pos_player_fleets(p2, map, SOUTH);
  print_ship(get_fleet(p1, 0));
  print_ship(get_fleet(p2, 0));
  battle_loop(p1, p2, map);
  destroy_bmap(map);
  return (0);
}
