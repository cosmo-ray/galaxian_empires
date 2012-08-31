#include	<stdio.h>
#include	"sdl_util.h"

static	inline int	mb_is_num_key(unsigned int  key, unsigned int nb_anw)
{
  return ((key - SDLK_0) <= nb_anw && (key - SDLK_0) > 0);
}

static	inline int	mb_is_numpad_key(unsigned int  key, unsigned int nb_anw)
{
  return ((key - SDLK_KP0) <= nb_anw && (key - SDLK_KP0) > 0);
}

int	wait_answer(int nb_anw)
{
  static SDL_Event event;

  SDL_WaitEvent(&event);
  switch (event.type)
    {
    case SDL_KEYDOWN:
      if (mb_is_num_key(event.key.keysym.sym, nb_anw))
	return (event.key.keysym.sym  - SDLK_0 - 1);
      else if (mb_is_numpad_key(event.key.keysym.sym, nb_anw))
	return (event.key.keysym.sym  - SDLK_KP0 - 1);
      break;
    case SDL_QUIT:
      return (-2);
    default:
      break;
    }
  return (wait_answer(nb_anw));
}

int	print_menu(char **menu)
{
  int	i;

  printf("enter the number of the action you want to do\n");
  for (i = 0; menu[i] != NULL; ++i)
    {
      printf("%d: %s\n", i + 1, menu[i]);
    }
  return (wait_answer(i));
}
