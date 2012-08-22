#include	"selector.h"

/*memo of old debug*/
/*
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
 */

void	display_pos(t_spos *pos)
{
  display_somethink(pos->x, pos->y, 0, SELECTOR);
}

int	select_case(t_spos *pos)
{
  SDL_Event event;

  pos->x = 0;
  pos->y = 0;
  while (!0)
    {
      display_pos(pos);
      SDL_WaitEvent(&event);
      switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
	  break;
	case SDL_KEYDOWN:
	  switch (event.key.keysym.sym)
	    {
	    case SDLK_UP:
	      pos->y -= 1;
	      break;
	    case SDLK_DOWN:
	      pos->y += 1;
	      break;
	    case SDLK_RIGHT:
	      pos->x += 1;
	      break;
	    case SDLK_LEFT:
	      pos->x -= 1;
	      break;
	    default:
	      break;
	    }
	  break;
	case SDL_QUIT:
	  return (1);
	}
    }
  return (0);
}
