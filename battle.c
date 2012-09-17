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

char	*turn_tab[] = {
  "Left",
  "Right",
  NULL
};

static	t_player	*get_player_from_int(t_battle * bd, int nbr)
{
  if (nbr == 1)
    return (bd->p1);
  return (bd->p2);
}

static	void	map_modifier_dmg(t_bmap *map, t_spos *src, t_spos *target, int *dmg)
{
  (void) map;
  (void) src;
  (void) target;
  (void) dmg;
}

static	t_fleet	*get_fleet_by_pos_battle(t_battle * bd, int x, int y)
{
  t_fleet	*fleet;

  if ((fleet = get_fleet_by_pos(bd->p1, x, y)) != NULL)
    return (fleet);
  if ((fleet = get_fleet_by_pos(bd->p2, x, y)) != NULL)
    return (fleet);
  return (NULL);
}

static	t_player *get_enemy_player(t_battle *bd, t_fleet *fleet)
{
  t_pos	*pos = &fleet->pos;

  if (get_fleet_on(bd->p1, pos->x, pos->y))
    return (bd->p1);
  if (get_fleet_on(bd->p2, pos->x, pos->y))
    return (bd->p2);
  return (NULL);
}

static	int	battle_rm_fleet(t_battle *bd, t_fleet *fleet)
{
  bmap_rm_ship(&bd->map, fleet->pos.x, fleet->pos.y);
  player_delet_fleet(get_enemy_player(bd, fleet), fleet);
  return (0);
}

static	int	attaque(t_battle * bd, t_player *p, t_fleet *pfleet)
{
  t_spos	target;
  int		dmg;
  t_fleet	*tfleet; /*target fleet*/
  
  if (select_enemy_fleet(&target, bd, p))
    return (1);
  tfleet = get_fleet_by_pos_battle(bd, target.x, target.y);
  dmg = get_fleet_dmg(pfleet, get_dir_fleet_target(pfleet, (t_pos *)&target));
  map_modifier_dmg(&bd->map, (t_spos *)&pfleet->pos, &target, &dmg);
  do_fleet_dmg(tfleet, dmg, get_dir_fleet_dmg(tfleet, &pfleet->pos));
  printf("%d\n", tfleet->nbr);
  if (tfleet->nbr < 1)
    battle_rm_fleet(bd, tfleet);
  display_case(bd, target.x, target.y);
  return (0);
}

static	void	turn(t_battle *bd, t_fleet *pfleet)
{
  int	ret;

  print_msg("Turn in which direction ?");
  ret = print_menu(turn_tab);
  if (ret == 0)
    turn_left(pfleet);
  else
    turn_right(pfleet);
  display_case(bd, pfleet->pos.x, pfleet->pos.y);
}

static	int	exec_player_action(t_battle *bd, t_spos *pos, int player, int action_type)
{
  t_player *p = get_player_from_int(bd, player);

  if (action_type == -2)
    return (1);
  switch (action_type)
    {
    case ATTAQUE:
      if (attaque(bd, p, get_fleet_by_pos(p, pos->x, pos->y)))
	return (1);
      break;
    case MOVE:
      break;
    case TURN:
      turn(bd, get_fleet_by_pos(p, pos->x, pos->y));
      break;
    case SKIP:
      break;
    }
  return (0);  
}

static	int	do_turn(t_battle * bd, int player)
{
  t_spos pos;
  int	ret;

  print_msg("player's "); print_int(player); print_msg(" turns\n");
  if (select_ally_fleet(&pos, bd, get_player_from_int(bd, player)))
    return (1);
  ret = print_menu(menu_tab);
  return (exec_player_action(bd, &pos, player, ret));
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
