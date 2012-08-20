#include	<unistd.h>
#include	<stdio.h>
#include	"game.h"

static int	do_turn(t_player *p, t_bmap *map)
{
  SDL_Event event;

  (void) p;
  (void) map;
  while (!0)
    {
      SDL_WaitEvent(&event);
      switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
	  printf("Mouse button %d pressed at (%d,%d)\n",
		 event.button.button, get_pos_case(event.button.x), get_pos_case(event.button.y));
	  break;
	case SDL_KEYDOWN:
	  printf("the %s touch wat touch, his sym his: %d\n", SDL_GetKeyName(event.key.keysym.sym), event.key.keysym.sym);
	  break;
	case SDL_QUIT:
	  return (2);
	}
    }
  return (0);
}

static int	battle_loop(t_player *p1, t_player *p2, t_bmap *map)
{
  int	ret = 0;

  while(1)
    {
      if ((ret = do_turn(p1, map)))
	{
	  if (ret == 1)
	    return (0);
	  else
	    return (-1);
	}
      if ((ret = do_turn(p2, map)))
	{
	  if (ret == 1)
	    return (0);
	  else
	    return (-1);
	}
    }
  return (0);
}

int	battle(t_player *p1, t_player *p2, t_bmap *map)
{
  if (p1->fleets.len == 0 || p2->fleets.len == 0)
    return (-1);
  pos_player_fleets(p1, map, NORTH);
  pos_player_fleets(p2, map, SOUTH);
  print_ship(get_fleet(p1, 0));
  print_ship(get_fleet(p2, 0));
  battle_loop(p1, p2, map);
  destroy_bmap(map);
  return (0);
}
