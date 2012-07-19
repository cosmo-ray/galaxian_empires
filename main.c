#include	"bmap.h"
#include	"fleet.h"
#include	<stdio.h>

int	main()
{
  t_bmap	map;
  t_ship	ship;
  t_fleet	fleet;

  init_bmap(&map);
  load_ship("battle_cruse.sp", &ship);
  init_fleet("toto", &ship, 1, &fleet);
  printf("fleet: %s\nnbr: %d\n", get_fleet_name(&fleet), get_fleet_nbr(&fleet));
  printf("attack: %d\n", get_fleet_dmg(&fleet, FRONT));
  do_dmg(&fleet, get_fleet_dmg(&fleet, FRONT), BACK);
  printf("fleet: %s\nnbr: %d\n", get_fleet_name(&fleet), get_fleet_nbr(&fleet));
  delet_fleet(&fleet);
  destroy_ship(&ship);
  destroy_bmap(&map);
  return (0);
}
