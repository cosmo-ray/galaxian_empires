#include	"pos.h"
#include	"game.h"
#include	"battle.h"
#include	"selector.h"
#include	"mesage_box.h"
#include	"menu_box.h"

char	*move_tab[] = {
  "Forward",
  "Leftward",
  "Rightward",
  "Backward",
  NULL
};

char	*turn_tab[] = {
  "Left",
  "Right",
  NULL
};

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

static	void	get_yp_modifier(t_bmap *map, t_fleet *fleet, t_spos *target)
{
  t_pos pos;

  pos_copy(&fleet->pos, &pos);
  while (!is_spos_equale(pos_to_spos(&pos), target))
    {
      if (pos.x > target->x)
	--pos.x;
      else if (pos.x < target->x)
	++pos.x;
      else if (pos.y > target->y)
	--pos.y;
      else if (pos.y < target->y)
	++pos.y;
    }
  (void) map;
}

static	void	map_modifier_dmg(t_bmap *map, t_fleet *fleet, t_spos *target, int *dmg)
{
  get_yp_modifier(map, fleet, target);
  (void) map;
  (void) target;
  (void) dmg;
}

int	attaque(t_battle * bd, t_player *p, t_fleet *pfleet)
{
  t_spos	target;
  int		dmg;
  t_fleet	*tfleet; /*target fleet*/
  
  if (fleet_rm_ap(pfleet, get_main_weapon_cost(pfleet->type)))
    return (print_msg("not enought mp, you want to get it\n")); /*Fuck you Dougram*/
  if (select_enemy_fleet(&target, bd, p))
    return (1);
  tfleet = get_fleet_by_pos_battle(bd, target.x, target.y);
  dmg = get_fleet_dmg(pfleet, get_dir_fleet_target(pfleet, (t_pos *)&target));
  map_modifier_dmg(&bd->map, pfleet, &target, &dmg);
  do_fleet_dmg(tfleet, dmg, get_dir_fleet_dmg(tfleet, &pfleet->pos));
  printf("%d\n", tfleet->nbr);
  if (tfleet->nbr < 1)
    battle_rm_fleet(bd, tfleet);
  display_case(bd, target.x, target.y);
  return (0);
}

void	turn(t_battle *bd, t_fleet *pfleet)
{
  int	ret;

  if (fleet_rm_ap(pfleet, get_speed(pfleet->type, SIDE)))
    return (v_print_msg("not enought mp, you want to get it\n")); /*Fuck you Dougram*/
  print_msg("Turn in which direction ?");
  ret = print_menu(turn_tab);
  if (ret == 0)
    turn_left(pfleet);
  else
    turn_right(pfleet);
  display_case(bd, pfleet->pos.x, pfleet->pos.y);
}

/*get the direction defined for the move_tab by the direction defined by the defines in ship.h*/
static	int get_dir_by_dir(int dir)
{
  if (dir == LEFTWARD || dir ==  RIGHTWARD)
    return (SIDE);
  if (dir == FORWARD)
    return (FRONT);
  return (BACK);
}
/*
#define	FORWARD		0
#define	LEFTWARD	1
#define	RIGHTWARD	2
#define	BACKWARD	3

*/

int	move(t_battle *bd, t_fleet *fleet)
{
  int	ret;
  
  ret = print_menu(move_tab);
  if (fleet_rm_ap(fleet, get_speed(fleet->type, get_dir_by_dir(ret))))
    return (print_msg("Move is on your way, but not this time"));
  bmap_rm_ship(&bd->map, fleet->pos.x, fleet->pos.y);
  display_case(bd, fleet->pos.x, fleet->pos.y);
  handle_move_ret(fleet, ret);
  bmap_add_ship(&bd->map, fleet->pos.x, fleet->pos.y);
  display_case(bd, fleet->pos.x, fleet->pos.y);
  return (0);
}

void	skip(t_fleet *fleet)
{
  fleet_set_ap(fleet, 0);
}
