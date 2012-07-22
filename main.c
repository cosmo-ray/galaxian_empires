#include	"bmap.h"
#include	"fleet.h"
#include	<unistd.h>
#include	<stdio.h>
#include	"game.h"
#include	"player.h"

t_game	life;

int	main()
{
  t_bmap	map;
  t_ship	ship;
  t_player	p1;
  t_player	p2;  

  init_bmap(&map);
  load_ship("battle_cruse.sp", &ship);
  init_player(&p1);
  init_player(&p2);
  add_fleet(&p1, 10000, &ship);
  add_fleet(&p2, 10000, &ship);

  if (sdl_init(500, 500) == -1)
    return (-1);
  printf("p1: %d\np2: %d\n", p1.id, p2.id);

  sleep(1);
  sdl_uninit();
  destroy_ship(&ship);
  destroy_bmap(&map);
  return (0);
}
