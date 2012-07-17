#include	"bmap.h"

int	main()
{
  t_bmap map;
  t_ship ship;

  init_bmap(&map);
  load_ship("ship.sp", &ship);
  destroy_ship(&ship);
  destroy_bmap(&map);
  return (0);
}
