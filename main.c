#include	<unistd.h>
#include	<stdio.h>
#include	"game.h"
#include	"player.h"
#include	"bmap.h"

t_game	life;

int	main()
{
  t_battle	battle_data;
  t_player	p1;
  t_player	p2;  
  t_bmap	map;

  (void)battle_data;

  if (give_life())
    return (-1);
  init_player(&p1);
  init_player(&p2);
  init_bmap(&map, 10, 10);
  add_fleet(&p1, 10000, get_data(&life.ships, 0));
  add_fleet(&p2, 10000, get_data(&life.ships, 0));

  battle(&p1, &p2, &map);

  delet_player(&p1);
  delet_player(&p2);
  take_life();
  return (0);
}
