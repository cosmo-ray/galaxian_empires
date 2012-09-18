#include	<unistd.h>
#include	<stdio.h>
#include	"game.h"
#include	"battle.h"
#include	"selector.h"
#include	"mesage_box.h"
#include	"menu_box.h"

#define	ATTAQUE	0
#define	MOVE	1
#define	TURN	2
#define	SKIP	3


char	*menu_tab[] = {
  "Attaque",
  "Move",
  "Turn", /*A TURN, TURN A TURN TURN AAAAAAAAAAAAA*/
  "Skip turn",
  NULL
};

static	t_player	*get_player_from_int(t_battle * bd, int nbr)
{
  if (nbr == 1)
    return (bd->p1);
  return (bd->p2);
}

static	int	exec_player_action(t_battle *bd, t_spos *pos, t_player *p, int action_type)
{
  t_fleet  *fleet = get_fleet_by_pos(p, pos->x, pos->y);

  if (action_type == -2)
    return (1);
  switch (action_type)
    {
    case ATTAQUE:
      if (attaque(bd, p, fleet))
	return (1);
      break;
    case MOVE:
      if (move(bd, fleet))
	return (1);
      break;
    case TURN:
      turn(bd, fleet);
      break;
    case SKIP:
      break;
    }
  return (0);  
}

static	int	do_turn(t_battle * bd, int player)
{
  t_player *p = get_player_from_int(bd, player);
  t_spos pos;
  int	ret;

  reset_ap(p);
  print_msg("player's "); print_int(player); print_msg(" turns\n");
  if (select_ally_fleet(&pos, bd, get_player_from_int(bd, player)))
    return (1);
  ret = print_menu(menu_tab);
  return (exec_player_action(bd, &pos, p, ret));
}

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
	  if ((ret = do_turn(bd, player)))
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

static int	pos_fleets_on_map(t_battle *bd, int dir, t_spos *pos, t_fleet *fleet)
{
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
      pos_fleets_on_map(bd, dir, pos, get_fleet(p, i + 1));
      node = node->next;
    }
  return (0);
}

/*set the position of the 2 players in the map*/
static	int	pos_players_fleets_on_map(t_battle *bd)
{
  t_spos	pos;

  print_msg("player's "); print_int(1); print_msg(" turns\n");
  if (pos_player_fleets_on_map(bd, bd->p1, &pos, NORTH))
    return (1);
  display_map(bd);
  print_msg("player's "); print_int(2); print_msg(" turns\n");
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
  display_map(&battle_data);
  battle_loop(&battle_data);
  return (end_battle(&battle_data));
}
