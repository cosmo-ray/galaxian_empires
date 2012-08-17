#ifndef SDL_UTIL_H
# define SDL_UTIL_H

#include <SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "pos.h"

#define	KEY_UP		273
#define	KEY_DOWN	274
#define	KEY_RIGHT	275
#define	KEY_LEFT	276
#define	KEY_ESCAPE	27
#define	KEY_SPACE	32
#define	KEY_ENTER	13


int		sdl_init(int width, int height);
void		sdl_uninit();
SDL_Surface	*draw_load(char *file);
int		load_sprite(void);
int		display_ship_sprite(t_pos *pos);
int		display_txt_on_pos(t_pos *pos, char *txt);

#endif
