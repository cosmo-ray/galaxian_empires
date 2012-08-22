#include	"selector.h"

int	select_case(t_spos *pos)
{
  SDL_Event event;

  pos->x = 0;
  pos->y = 0;
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
	  return (1);
	}
    }
  return (0);
}
