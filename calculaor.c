#include	<unistd.h>
#include	<math.h>
#include	<stdio.h>
#include	"calculaor.h"

/*calculate the line betwin 2 point and stock the result in ret*/
t_pos	*cal_get_Line_ret(t_pos *a, t_pos *b, t_pos *ret)
{
  ret->x = b->x - a->x;
  ret->y = b->y - a->y;
  return (ret);
}

/*calculate the line betwin 2 point and stock the result in b*/
t_pos	*cal_get_Line(t_pos *a, t_pos *b)
{
  b->x -= a->x;
  b->y -= a->y;
  return (b);
}

inline double	get_rad(t_pos *a)
{
  return (atan((double)a->x / (double)a->y));
}

int	cal_get_dist(int a, int b)
{
  return ABS((b + 1) - (a + 1));
}


/*
  12345
1 sbbbs
2 ssbss
3 ss1ss
4 ssfss
5 sfffs

   x  y
p: 1  5
p: 4  3
d: 3 -2
*/

