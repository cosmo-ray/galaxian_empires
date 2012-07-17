#ifndef	BMAP_C_
#define BMAP_C_

typedef struct	s_bmap	
{
  int	x;
  int	y;
  char	*data;
}	t_bmap;

int	init_bmap(t_bmap *map);
void	destroy_bmap(t_bmap *box);
char	get_x_y(t_bmap *map, int x, int y);
#endif
