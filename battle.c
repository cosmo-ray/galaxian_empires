#include	<unistd.h>
#include	<stdio.h>
#include	"game.h"
#include	"battle.h"
#include	"selector.h"

static int	do_turn(t_player *p, t_bmap *map)
{
  t_spos pos;
  int	ret;
  (void) p;

  ret = select_case(&pos, map, p);
  return (ret);
}

static int	init_battle_data(t_player *p1, t_player *p2, t_battle *bd)
{
  bd->p1 = p1;
  bd->p2 = p2;
  init_bmap(&(bd->map), 10, 10);
  return (0);
}

static int	battle_loop(t_battle * bd)
{
  int	ret = 0;
  while(1)
    {
      if ((ret = do_turn(bd->p1, &(bd->map))))
	{
	  if (ret == 1)
	    return (0);
	  else
	    return (-1);
	}
      if ((ret = do_turn(bd->p2, &(bd->map))))
	{
	  if (ret == 1)
	    return (0);
	  else
	    return (-1);
	}
    }
  return (0);
}

int	battle(t_player *p1, t_player *p2)
{
  t_battle	battle_data;

  init_battle_data(p1, p2, &battle_data);
  if (p1->fleets.len == 0 || p2->fleets.len == 0)
    return (-1);
  pos_player_fleets(p1, &battle_data.map, NORTH);
  pos_player_fleets(p2, &battle_data.map, SOUTH);
  print_ship(get_fleet(p1, 0));
  print_ship(get_fleet(p2, 0));
  battle_loop(&battle_data);
  destroy_bmap(&(battle_data.map));
  return (0);
}
