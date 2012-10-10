#ifndef SELECTOR_H
#define SELECTOR_H

#include	"game.h"
#include	"battle.h"

int	select_case(t_spos *pos, t_battle *bd);
int	select_empty_case(t_spos *pos, t_battle *bd);
int	select_fleet(t_spos *pos, t_battle *bd);
int	select_ally_fleet(t_spos *pos, t_battle *bd, t_heroes *p);
int	select_enemy_fleet(t_spos *pos, t_battle *bd, t_heroes *p);
int	select_y_limit_case(t_spos *pos, t_battle *bd, int low_y, int hight_y);

#endif
