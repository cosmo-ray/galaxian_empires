#include	<unistd.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"bmap.h"

#define	Y_SIZE	50
#define	X_SIZE	50

char	get_x_y(t_bmap *map, int x, int y)
{
  return (map->data[x + (y * map->x)]);
}

void	debug_print_map(t_bmap *map)
{
  int	x = 0;
  int	y = 0;

  while (y < map->y)
    {
      write(1, &(map->data[x]), map->x);
      putchar('\n');
      x += map->x;
      ++y;
    }
}

int	init_bmap(t_bmap *map)
{
  map->x = X_SIZE;
  map->y = Y_SIZE;
  if ((map->data = malloc(sizeof(*(map->data)) * (map->x * map->y + 1))) == NULL)
    return (-1);
  memset(map->data, ' ', map->x * map->y);
  map->data[map->x * map->y] = '\0';
  return (0);
}

void	destroy_bmap(t_bmap *box)
{
  free(box->data);
}
