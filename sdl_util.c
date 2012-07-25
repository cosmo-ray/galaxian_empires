#include	"game.h"

#define	FILE_NAME "sprite/ship.png"

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

SDL_Surface	*draw_load(char *file)
{
  return (IMG_Load(file));
}

int	load_sprite(void)
{
  if ((life.sprite = draw_load(FILE_NAME)) == NULL)
    return (-1);
  return (0);
}
