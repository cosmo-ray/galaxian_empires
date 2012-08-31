#include	<unistd.h>
#include	<stdio.h>
#include	"game.h"
#include	"battle.h"
#include	"selector.h"
#include	"mesage_box.h"

static int	do_turn(t_battle * bd)
{
  t_spos pos;
  int	ret;

  ret = select_case(&pos, bd);
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
      if ((ret = do_turn(bd)))
	{
	  if (ret == 1)
	    return (0);
	  else
	    return (-1);
	}
      if ((ret = do_turn(bd)))
	{
	  if (ret == 1)
	    return (0);
	  else
	    return (-1);
	}
    }
  return (0);
}

static int	pos_fleets_on_map(t_battle *bd, int dir, t_spos *pos, t_fleet *fleet)
{
  /*maybe one day the loop who ask to the player where he want to pos his fleets will be implement here*/
  bmap_add_ship(&bd->map, pos->x, pos->y);
  if (dir == NORTH)
    pos_fleet(fleet, pos->x, pos->y, SOUTH);
  else
    pos_fleet(fleet, pos->x, pos->y, NORTH);
  return (0);
}

/*set the position of the fleet of a player on a map*/
static	int	pos_player_fleets_on_map(t_battle *bd, t_player *p, t_spos *pos, int dir)
{
  t_node	*node = p->fleets.first;
  int	i = -1; /*i set i to -1 because like this i increment i one time less*/

  while (node != NULL)
    {
      ++i;
      if (select_empty_case(pos, bd))
	return (1);
      pos_fleets_on_map(bd, dir, pos, get_fleet(p, i));
      node = node->next;
    }
  return (0);
}

/*set the position of the 2 players in the map*/
static	int	pos_players_fleets_on_map(t_battle *bd)
{
  t_spos	pos;

  print_msg(" turns\n", print_int(2, print_msg("player's ", 0)));
  if (pos_player_fleets_on_map(bd, bd->p1, &pos, NORTH))
    return (1);
  display_map(bd);
  if (pos_player_fleets_on_map(bd, bd->p2, &pos, SOUTH))
    return (1);
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
  /* pos_player_fleets(p1, &battle_data.map, NORTH); */
  /* pos_player_fleets(p2, &battle_data.map, SOUTH); */
  display_map(&battle_data);
  battle_loop(&battle_data);
  return (end_battle(&battle_data));
}
