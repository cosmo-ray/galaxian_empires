#include	<unistd.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"bmap.h"

char	get_x_y(t_bmap *map, int x, int y)
{
  return (map->data[x + (y * map->x)]);
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
