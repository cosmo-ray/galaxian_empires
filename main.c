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

  load_ship("battle_cruse.sp", &ship);
  init_player(&p1);
  init_player(&p2);
  printf("load sprite ret: %d\n", load_sprite());
  add_fleet(&p1, 10000, &ship);
  add_fleet(&p2, 10000, &ship);

  if (sdl_init(500, 500) == -1)
    return (-1);
  printf("p1: %d\np2: %d\n", p1.id, p2.id);
  battle(&p1, &p2);

  sdl_uninit();
  destroy_ship(&ship);
  delet_player(&p1);
  delet_player(&p2);
  return (0);
}
