#ifndef SELECTOR_H
#define SELECTOR_H
#include	"game.h"

typedef	struct	
{
  int	x;
  int	y;
}	t_spos;

int	select_case(t_spos *pos, t_bmap *map, t_player *p);

#endif
