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
    init_bmap(&map);
    destroy_bmap(&map);
    return (0);
}
