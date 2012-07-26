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

  memset(&life, '\0', sizeof(life));

  if (load_ship("battle_cruse.sp", &ship))
    return (-1);
  init_player(&p1);
  init_player(&p2);
  add_fleet(&p1, 10000, &ship);
  add_fleet(&p2, 10000, &ship);

  if (sdl_init(500, 500) == -1)
    return (-1);

  load_sprite();

  printf("p1: %d\np2: %d\n", p1.id, p2.id);
  battle(&p1, &p2);

  t_pos pos;
  pos.x = 0;
  pos.y = 0;
  pos.dir = 0;

  printf("display sprite ret %d\n", display_sprite(&pos));

  pos.x = 0;
  pos.y = 1;
  pos.dir = 0;
  printf("display sprite ret %d\n", display_sprite(&pos));
  pos.x = 1;
  pos.y = 0;
  pos.dir = 0;
  printf("display sprite ret %d\n", display_sprite(&pos));
  sleep(1);

  sdl_uninit();
  destroy_ship(&ship);
  delet_player(&p1);
  delet_player(&p2);
  return (0);
}
