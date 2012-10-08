#include	<unistd.h>
#include	<stdio.h>
#include	"game.h"
#include	"player.h"
#include	"bmap.h"
#include	"battle.h"

t_game	life;

int	main(int ac, char **av)
{
  t_player	p1;
  t_player	p2;
  (void) ac;
  (void) av;

  if (give_life())
    return (-1);
  init_player(&p1);
  init_player(&p2);
  add_fleet(&p1, 10000, get_data(&life.ships, 0));
  add_fleet(&p1, 10000, get_data(&life.ships, 0));
  add_fleet(&p2, 10000, get_data(&life.ships, 0));
  add_fleet(&p2, 10000, get_data(&life.ships, 0));

  battle(&p1, &p2);

  delet_player(&p1);
  delet_player(&p2);
  take_life();
  return (0);
}
