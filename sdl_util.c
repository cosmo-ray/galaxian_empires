#include	"game.h"

#define	FILE_NAME "sprite/ship.png"

extern t_game	life;

/*yeah !, hem no fuck you balck magic !*/
void	set_color(int color)
{
  life.color.r = ((char *)(&color))[0];
  life.color.g = ((char *)(&color))[1];
  life.color.b = ((char *)(&color))[2];
}

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
  if (TTF_Init() < 0)
    return (-1);
  /*for the moment we use FOO.ttf*/
  life.font = TTF_OpenFont("./font/FOO.ttf", 15);
  /*we set the default color of the text to white*/
  set_color(0xFFFFFF);
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

int	display_ship_sprite(t_pos *pos)
{
  static SDL_Rect	src;
  static SDL_Rect	dest;

  src.y = 0;
  src.x = pos->dir * 50;
  src.w = src.h = dest.w = dest.h = 50;
  dest.x = pos->x * 50;
  dest.y = pos->y * 50;
  /* printf("%d. %d\n", pos->x, pos->y); */
  if (SDL_BlitSurface(life.sprite, &src, life.win, &dest))
    return (-1);
  /* if (SDL_FillRect(life.win, &dest, 0xffffff)) */
  /*   return -1; */

  SDL_UpdateRect(life.win, dest.x, dest.y, src.w, src.h);
  return (0);
}

int	display_txt_on_pos(t_pos *pos, char *txt)
{
  static SDL_Rect	src;

  src.y = 0;
  src.x = pos->dir * 50;
  src.w = src.h = 50;

  life.txtsurface = TTF_RenderText_Solid(life.font, txt, life.color);

  /* printf("%d. %d\n", pos->x, pos->y); */
  if (SDL_BlitSurface(life.txtsurface, NULL, life.win, &src))
    return (-1);
  /* if (SDL_FillRect(life.win, &dest, 0xffffff)) */
  /*   return -1; */

  SDL_Flip(life.win);
  return (0);
}
