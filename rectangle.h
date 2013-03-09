#ifndef	RECTANGLE
#define	RECTANGLE

typedef	struct
{
  int	x;
  int	y;
  int	h;
  int	w;
}	t_rectangle;

void	rectangle_init(t_rectangle *, int x, int y, int h, int w);

#endif
