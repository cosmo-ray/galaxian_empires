#include	<unistd.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"bmap.h"
#include	"calculaor.h"

/*get change an int in pos to comme near target*/
void	bmap_avance_to_target(t_spos *pos, t_spos *target)
{
  if (cal_get_dist(pos->x, target->x) > cal_get_dist(pos->y, target->y))
    pos->x += COME_NEAR(pos->x, target->x);
  else
    pos->y += COME_NEAR(pos->y, target->y);
}

char	bmap_get_x_y(t_bmap *map, int x, int y)
{
  return (map->data[x + (y * map->x)]);
}

void	bmap_add_ship(t_bmap *map, int x, int y)
{
  map->data[x + (y * map->x)] |= SHIP;
}

void	bmap_rm_ship(t_bmap *map, int x, int y)
{
  map->data[x + (y * map->x)] ^= SHIP;
}

int	init_bmap(t_bmap *map, int x, int y)
{
  map->x = x;
  map->y = y;
  map->len = x * y - 1;
  if ((map->data = malloc(sizeof(*(map->data)) * (x * y))) == NULL)
    return (-1);
  memset(map->data, EMPTY, map->x * map->y);
  return (0);
}

void	destroy_bmap(t_bmap *box)
{
  free(box->data);
}

int	is_spos_equale(t_spos *pos1, t_spos *pos2)
{
  return (pos1->x == pos2->x && pos1->y == pos2->y);
}

inline	t_spos	*pos_to_spos(t_pos *pos)
{
  return ((t_spos *)pos);
}
