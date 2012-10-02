#include	"pos.h"

void	pos_copy(t_pos *src, t_pos *dest)
{
  dest->x = src->x;
  dest->y = src->y;
  dest->dir = src->dir;
}
