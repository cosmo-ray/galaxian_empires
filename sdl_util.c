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


/* i write the descriprtion of SDL_Rect(the src and dest argument of SDL_BlitSurface), because it's usefull*/

/*
CWtypedef struct{
  Sint16 x, y;
  Uint16 w, h;
} SDL_Rect;
*/

int	display_sprite(t_pos *pos)
{
  static SDL_Rect	src;
  static SDL_Rect	dest;

  src.y = 0;
  src.x = pos->dir * 50;
  src.w = src.h = dest.w = dest.h = 50;
  dest.x = pos->x * 50;
  dest.y = pos->y * 50;
  if (SDL_BlitSurface(life.sprite, &src, life.win, &dest))
    return (-1);
  SDL_UpdateRect(life.win, pos->x, pos->y, 50, 50);
  return (0);
}
