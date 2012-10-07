#include	"pos.h"
#include	"calculaor.h"
void	pos_copy(t_pos *src, t_pos *dest)
{
  dest->x = src->x;
  dest->y = src->y;
  dest->dir = src->dir;
}

float	comp_pos(t_pos *pos1, t_pos *pos2)
{
  return (ABS(pos2->x - pos1->x) + ABS(pos2->y - pos1->y)) / 2;
}
