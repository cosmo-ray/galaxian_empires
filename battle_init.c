#include        <unistd.h>
#include        <stdio.h>
#include        "game.h"
#include        "battle.h"
#include        "selector.h"
#include        "mesage_box.h"
#include        "menu_box.h"

static int      pos_fleets_on_map(t_battle *bd, int dir, t_spos *pos, t_fleet *fleet)
{
  bmap_add_ship(&bd->map, pos->x, pos->y);
  if (dir == NORTH)
    pos_fleet(fleet, pos->x, pos->y, SOUTH);
  else
    pos_fleet(fleet, pos->x, pos->y, NORTH);
  return (0);
}

/*set the position of the fleet of a player on a map*/
static  int     pos_player_fleets_on_map(t_battle *bd, t_player *p, t_spos *pos, int dir)
{
  t_node        *node = p->fleets.first;
  int   i = -1; /*i set i to -1 because like this i increment i one time less*/

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
int     pos_players_fleets_on_map(t_battle *bd)
{
  t_spos        pos;

  print_msg("player's "); print_int(1); print_msg(" turns\n");
  if (pos_player_fleets_on_map(bd, bd->p1, &pos, NORTH))
    return (1);
  display_map(bd);
  print_msg("player's "); print_int(2); print_msg(" turns\n");
  if (pos_player_fleets_on_map(bd, bd->p2, &pos, SOUTH))
    return (1);
  return (0);
}
