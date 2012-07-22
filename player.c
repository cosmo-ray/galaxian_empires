#include	"player.h"
#include	"game.h"

 extern t_game	life;

 void	init_player(t_player *player)
 {   
   player->id = life.nb_plyaers + 1;
   init_list(&(player->fleets));
 }
