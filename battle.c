#include	<unistd.h>
#include	<stdio.h>
#include	"game.h"
#include	"battle.h"
#include	"selector.h"
#include	"mesage_box.h"
#include	"menu_box.h"

static int	init_battle_data(t_player *p1, t_player *p2, t_battle *bd)
{
  bd->p1 = p1;
  bd->p2 = p2;
  init_bmap(&(bd->map), 10, 10);
  return (0);
}

static	int is_battle_end(t_battle * bd)
{
  if (!bd->p1->fleets.len || !bd->p2->fleets.len)
    return (1);
  return (0);
}

static	int	get_nbr_player()
{
  return (2);
}

static int	battle_loop(t_battle * bd)
{
  int	ret = 0;
  int	player;

  while (!is_battle_end(bd))
    {
      for (player = 1; player <= get_nbr_player() && !is_battle_end(bd); ++player)
	{
	  if ((ret = battle_do_turn(bd, player)))
	    {
	      if (ret == 1)
		return (0);
	      else
		return (-1);
	    }
	}
    }
  return (0);
}

static	int	end_battle(t_battle *bd)
{
  destroy_bmap(&bd->map);
  return (0);
}

int	battle(t_player *p1, t_player *p2)
{
  t_battle	battle_data;

  init_battle_data(p1, p2, &battle_data);
  if (p1->fleets.len == 0 || p2->fleets.len == 0)
    return (0);
  display_map(&battle_data);
  if (pos_players_fleets_on_map(&battle_data))
    return (end_battle(&battle_data));
  display_map(&battle_data);
  battle_loop(&battle_data);
  return (end_battle(&battle_data));
}
