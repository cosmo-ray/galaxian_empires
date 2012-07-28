#include	<unistd.h>
#include	<stdio.h>
#include	"game.h"
#include	"player.h"
#include	"bmap.h"

int	battle(t_player *p1, t_player *p2)
{
    t_bmap	map;

    (void) p1;
    (void) p2;
    init_bmap(&map, 10, 10);
    if (p1->fleets.len == 0 || p2->fleets.len == 0)
      return (-1);
    pos_player_fleets(p1, &map, NORTH);
    pos_player_fleets(p2, &map, SOUTH);
    print_ship(get_fleet(p1, 0));
    print_ship(get_fleet(p2, 0));
    sleep(10);
    destroy_bmap(&map);
    return (0);
}
