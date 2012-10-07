#ifndef BATTLE_H
#define BATTLE_H

#include	"bmap.h"
#include	"player.h"

typedef	struct	s_battle
{
  int		nb_players;
  t_bmap	map;
  t_player	*p1;
  t_player	*p2;  
  int		cur_turn; /*TODO*/
}	t_battle;

/*actions*/
int		attaque(t_battle * bd, t_player *p, t_fleet *pfleet);
void		turn(t_battle *bd, t_fleet *pfleet);
int		move(t_battle *bd, t_fleet *pfleet);
void		skip(t_fleet *fleet);

/*display*/
int		display_map(t_battle *bd);
void		display_case(t_battle *bd, int x, int y);
/*display the object(like ship or asteroide) on a case*/
void		display_obj_on_case(t_battle *bd, int x, int y);

/*other*/
int		pos_players_fleets_on_map(t_battle *bd);
int		battle_do_turn(t_battle * bd, int player);
t_player	*get_player_from_int(t_battle * bd, int nbr);
int		battle(t_player *p1, t_player *p2);
#endif
