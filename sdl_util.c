#include	"game.h"

extern t_game	life;

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
  life.font = TTF_OpenFont("./font/FOO.ttf", 10);
  /*we set the default color of the text to white*/
  set_color(0xFFFFFF);
  tbs_init();
  return (0);
}

void	tbs_init()
{
  life.tbs.battle_screen.x = 0;
  life.tbs.battle_screen.y = 0;
  life.tbs.battle_screen.h = 500;
  life.tbs.battle_screen.w = 500;
  life.tbs.menu_box.x = 500;
  life.tbs.menu_box.y = 0;
  life.tbs.menu_box.h = 300;
  life.tbs.menu_box.w = 500;
  life.tbs.message_box.x = 0;
  life.tbs.message_box.y = 500;
  life.tbs.message_box.h = 500;
  life.tbs.message_box.w = 100;
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
  src.x = pos->dir * CASE_SIZE;
  src.w = src.h = dest.w = dest.h = CASE_SIZE;
  dest.x = (pos->x * CASE_SIZE) + life.tbs.battle_screen.x;
  dest.y = (pos->y * CASE_SIZE) + life.tbs.battle_screen.y;
  if (SDL_BlitSurface(life.sprite, &src, life.win, &dest))
    return (-1);
  SDL_UpdateRect(life.win, dest.x, dest.y, src.w, src.h);
  return (0);
}

int	display_txt_on_pos(t_pos *pos, char *txt)
{
  static SDL_Rect	dest;

  dest.w = dest.h = CASE_SIZE;
  dest.x = (pos->x * CASE_SIZE) + life.tbs.battle_screen.x;
  dest.y = (pos->y * CASE_SIZE) + life.tbs.battle_screen.y;
  life.txtsurface = TTF_RenderText_Solid(life.font, txt, life.color);

  if (SDL_BlitSurface(life.txtsurface, NULL, life.win, &dest))
    return (-1);
  SDL_Flip(life.win);
  return (0);
}

int	display_txt_on_msg_box(char *txt)
{
  static SDL_Rect	dest;
  static int	y_pos;

  dest.w = life.tbs.message_box.w;
  dest.h = life.tbs.message_box.h;
  dest.x = life.tbs.message_box.x;
  dest.y = life.tbs.message_box.y + (y_pos * 11);
  life.msg_txtsurface = TTF_RenderText_Solid(life.font, txt, life.color);

  if (SDL_BlitSurface(life.msg_txtsurface, NULL, life.win, &dest))
    return (-1);
  SDL_Flip(life.win);
  ++y_pos;
  return (0);
}

int	display_bg_sprite(int x, int y)
{
  static SDL_Rect	src;
  static SDL_Rect	dest;

  src.y = y * CASE_SIZE;
  src.x = x * CASE_SIZE;
  src.w = src.h = dest.w = dest.h = CASE_SIZE;
  dest.x = (x * CASE_SIZE) + life.tbs.battle_screen.x;
  dest.y = (y * CASE_SIZE) + life.tbs.battle_screen.y;

  dest.x = x * CASE_SIZE;
  dest.y = y * CASE_SIZE;
  if (SDL_BlitSurface(life.bg, &src, life.win, &dest))
    return (-1);
  SDL_UpdateRect(life.win, dest.x, dest.y, CASE_SIZE, CASE_SIZE);
  return (0);
}

int	display_somethink(int x, int y, int id_x, int id_y)
{
  static SDL_Rect	src;
  static SDL_Rect	dest;

  src.y = id_y * CASE_SIZE;
  src.x = id_x * CASE_SIZE;
  src.w = src.h = CASE_SIZE;
  dest.x = (x * CASE_SIZE) + life.tbs.battle_screen.x;
  dest.y = (y * CASE_SIZE) + life.tbs.battle_screen.y;
  if (SDL_BlitSurface(life.sprite, &src, life.win, &dest))
    return (-1);
  SDL_UpdateRect(life.win, dest.x, dest.y, src.w, src.h);
  return (0);
}

int	get_pos_case(int pix_pos)
{
  return (pix_pos / CASE_SIZE);
}

int	display_all_bg(t_battle *bd)
{
  SDL_Rect	src;
  SDL_Rect	dest;

  src.y = src.x = dest.x = dest.y = 0;
  src.h = bd->map.x * CASE_SIZE;
  src.w = bd->map.y * CASE_SIZE;
  if (SDL_BlitSurface(life.bg, &src, life.win, &dest))
    return (-1);
  SDL_UpdateRect(life.win, life.tbs.battle_screen.x, life.tbs.battle_screen.y, 0, 0);
  return (0);
}
