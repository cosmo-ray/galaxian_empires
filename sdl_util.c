#include	"sdl_util.h"

#define	FILE_NAME "sprites.png"

extern SDL_Surface	*win;

SDL_Surface	*sdl_init(int width, int height)
{
  SDL_Surface	*sdlbuf;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    return (NULL);
  sdlbuf = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
  if (sdlbuf == NULL)
    {
      SDL_Quit();
      return (NULL);
    }
  SDL_WM_SetCaption("Galaxian_Empires", NULL);
  return (sdlbuf);
}

void	sdl_uninit()
{
  SDL_Quit();
}

SDL_Surface	*draw_load(void)
{
  return (IMG_Load(FILE_NAME));
}
