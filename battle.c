#include	<unistd.h>
#include	<stdio.h>
#include	"game.h"
#include	"battle.h"
#include	"selector.h"
#include	"mesage_box.h"
#include	"menu_box.h"

static int	init_battle_data(t_heroes *p1, t_heroes *p2, t_battle *bd)
{
  bd->p1 = p1;
  bd->p2 = p2;
  init_bmap(&(bd->map), 10, 10);
  return (0);
}

/*check, if a heroes loose the battle, and return the loosing heroes nbr*/
static	int is_battle_end(t_battle * bd)
{
  if (!bd->p1->fleets.len)
    return (2);
  if (!bd->p2->fleets.len)
    return (1);
  return (0);
}

static	int	get_nbr_heroes()
{
  return (2);
}

static int	battle_loop(t_battle * bd)
{
  int	ret = 0;
  int	heroes;

  while (!(ret = is_battle_end(bd)))
    {
      for (heroes = 1; heroes <= get_nbr_heroes() && !is_battle_end(bd); ++heroes)
	{
	  if ((ret = battle_do_turn(bd, heroes)))
	    {
	      if (ret == 1)
		return (0);
	      else
		return (-1);
	    }
	}
    }
  return (ret);
}

static	int	end_battle(t_battle *bd)
{
  destroy_bmap(&bd->map);
  return (0);
}

t_heroes	*get_heroes_from_int(t_battle * bd, int nbr)
{
  if (nbr == 1)
    return (bd->p1);
  return (bd->p2);
}

int	battle(t_heroes *p1, t_heroes *p2)
{
  t_battle	battle_data;
  int		ret;

  init_battle_data(p1, p2, &battle_data);
  if (p1->fleets.len == 0 || p2->fleets.len == 0)
    return (0);
  display_map(&battle_data);
  if (pos_heroess_fleets_on_map(&battle_data))
    return (end_battle(&battle_data));
  display_map(&battle_data);
  if ((ret = battle_loop(&battle_data)) > 0)
    printf("Hero %d win the battle!\n", ret);
  return (end_battle(&battle_data));
}
