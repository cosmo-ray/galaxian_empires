#include	<unistd.h>
#include	<stdio.h>
#include	"game.h"
#include	"player.h"
#include	"bmap.h"

t_game	life;

int	main()
{
  t_ship	ship;
  t_player	p1;
  t_player	p2;  
  t_bmap	map;

  if (sdl_init(500, 500) == -1)
    return (-1);
  /*very important: load_sprite(like all other sdl func) must be after sdl_init*/
  load_sprite();
  if (load_ship("battle_cruse.sp", &ship))
    return (-1);
  init_player(&p1);
  init_player(&p2);
  init_bmap(&map, 10, 10);
  add_fleet(&p1, 10000, &ship);
  add_fleet(&p2, 10000, &ship);

  battle(&p1, &p2, &map);

  sdl_uninit();
  destroy_ship(&ship);
  delet_player(&p1);
  delet_player(&p2);
  return (0);
}
