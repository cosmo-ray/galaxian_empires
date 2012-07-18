#include	"bmap.h"
#include	"ship.h"

int	main()
{
  t_bmap map;
  t_ship ship;

  init_bmap(&map);
  load_ship("battle_cruse.sp", &ship);
  destroy_ship(&ship);
  destroy_bmap(&map);
  return (0);
}
