#include        <unistd.h>
#include        <stdio.h>
#include        "game.h"
#include        "battle.h"
#include        "selector.h"
#include        "mesage_box.h"
#include        "menu_box.h"

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
      skip(fleet);
      break;
    }
  return (0);  
}

int	battle_do_turn(t_battle * bd, int player)
{
  t_player *p = get_player_from_int(bd, player);
  t_spos pos;
  int	ret;

  reset_ap(p);
  print_msg("player's "); print_int(player); print_msg(" turns\n");
  while (!full_empty_ap(p))
    {
      if (select_ally_fleet(&pos, bd, get_player_from_int(bd, player)))
	return (1);
      ret = print_menu(menu_tab);
      if (exec_player_action(bd, &pos, p, ret))
	return (1);
    }
  return (0);
}
