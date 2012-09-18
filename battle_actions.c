#include	"game.h"
#include	"battle.h"
#include	"selector.h"
#include	"mesage_box.h"
#include	"menu_box.h"

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


static	void	map_modifier_dmg(t_bmap *map, t_spos *src, t_spos *target, int *dmg)
{
  (void) map;
  (void) src;
  (void) target;
  (void) dmg;
}

int	attaque(t_battle * bd, t_player *p, t_fleet *pfleet)
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

void	turn(t_battle *bd, t_fleet *pfleet)
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