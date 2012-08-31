#include	<stdio.h>
#include	"sdl_util.h"

int	wait_answer(int nb_anw)
{
  static SDL_Event event;

  SDL_WaitEvent(&event);
  switch (event.type)
    {
    case SDL_KEYDOWN:
      if ((int)(event.key.keysym.sym  - SDLK_0) <= nb_anw && (event.key.keysym.sym  - SDLK_0) > 0)
	return (event.key.keysym.sym  - SDLK_0 - 1);
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
