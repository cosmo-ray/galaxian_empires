#include	"game.h"

#define	FILE_NAME "sprites.png"

extern t_game	life;

int	sdl_init(int width, int height)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    return (-1);
  life.win = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
  if (life.win == NULL)
    {
      SDL_Quit();
      return (-1);
    }
  SDL_WM_SetCaption("Galaxian_Empires", NULL);
  return (0);
}

void	sdl_uninit()
{
  SDL_Quit();
}

SDL_Surface	*draw_load(void)
{
  return (IMG_Load(FILE_NAME));
}
