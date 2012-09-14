#include	"sdl_util.h"
#include	"battle.h"

void	display_case(t_battle *bd, int x, int y)
{
  if (IS_SHIP_ON(bmap_get_x_y(&bd->map, x, y)))
    {
      print_fleet_ship(get_fleet(bd->p1, get_fleet_on(bd->p1, x, y)));
      print_fleet_ship(get_fleet(bd->p2, get_fleet_on(bd->p2, x, y)));
    }
}

int	display_map(t_battle *bd)
{
  if (display_all_bg(bd))
    return (-1);
  display_all_fleet(bd->p1);  
  display_all_fleet(bd->p2);
  return (0);
}
