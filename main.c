#include	"bmap.h"
#include	"fleet.h"
#include	<unistd.h>
#include	<stdio.h>
#include	"sdl_util.h"

SDL_Surface	*win;

int	main()
{
  t_bmap	map;
  t_ship	ship;
  t_fleet	fleet;

  init_bmap(&map);
  load_ship("battle_cruse.sp", &ship);
  init_fleet("toto", &ship, 1, &fleet);
  if ((win = sdl_init(500, 500)) == NULL)
    return (-1);
  sleep(1);
  sdl_uninit();
  delet_fleet(&fleet);
  destroy_ship(&ship);
  destroy_bmap(&map);
  return (0);
}
