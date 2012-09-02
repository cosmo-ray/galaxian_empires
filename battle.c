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

static	int	attaque(t_battle * bd, t_spos *pos, t_player *p)
{
  t_spos	target;
  int		dmg;
  /*player's fleet*/
  t_fleet	*pfleet = get_fleet_by_pos(p, pos->x, pos->y);
  t_fleet	*tfleet; /*target fleet*/
  
  printf("pan pan\n"); /*pit heur*/
  if (select_enemy_fleet(&target, bd, p))
    return (1);
  tfleet = get_fleet_by_pos(p, target.x, target.y);
  dmg = get_fleet_dmg(pfleet, get_dir_fleet_target(pfleet, &target));
  map_modifier_dmg(&bd->map, pos, &target, &dmg);
  do_fleet_dmg(tfleet, dmg, get_dir_fleet_dmg(tfleet, pos));
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
  if (ret == -2)
    return (1);
  switch (ret)
    {
    case ATTAQUE:
      if (attaque(bd, &pos, get_player_from_int(bd, player)))
	return (1);
       break;
    case MOVE:
      printf("tchu tchu\n");
      break;
    case TURN:
      printf("wroum wroum\n");
      break;
    case SKIP:
      printf("not me\n");      
      break;
    }
  return (0);
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
  (void)bd;
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
      for (player = 1; player <= get_nbr_player(); ++player)
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
  /* pos_player_fleets(p1, &battle_data.map, NORTH); */
  /* pos_player_fleets(p2, &battle_data.map, SOUTH); */
  display_map(&battle_data);
  battle_loop(&battle_data);
  return (end_battle(&battle_data));
}
