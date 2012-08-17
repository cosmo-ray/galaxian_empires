#include	<unistd.h>
#include	<stdio.h>
#include	"game.h"

static void	battle_loop()
{
  SDL_Event event;

  while (!0)
    {
      SDL_WaitEvent(&event);
      switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
	  printf("Mouse button %d pressed at (%d,%d)\n",
		 event.button.button, event.button.x, event.button.y);
	  break;
	case SDL_KEYDOWN:
	  printf("the %s touch wat touch, his sym his: %d\n", SDL_GetKeyName(event.key.keysym.sym), event.key.keysym.sym);
	  break;
	case SDL_QUIT:
	  return ;
	}
    }
}

int	battle(t_player *p1, t_player *p2, t_bmap *map)
{
  (void) p1;
  (void) p2;
  if (p1->fleets.len == 0 || p2->fleets.len == 0)
    return (-1);
  pos_player_fleets(p1, map, NORTH);
  pos_player_fleets(p2, map, SOUTH);
  print_ship(get_fleet(p1, 0));
  print_ship(get_fleet(p2, 0));
  battle_loop();
  destroy_bmap(map);
  return (0);
}
