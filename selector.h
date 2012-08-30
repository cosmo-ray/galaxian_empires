#ifndef SELECTOR_H
#define SELECTOR_H
#include	"game.h"
#include	"battle.h"

typedef	struct	
{
  int	x;
  int	y;
}	t_spos;

int	select_case(t_spos *pos, t_battle *bd);
int	select_empty_case(t_spos *pos, t_battle *bd);
#endif
