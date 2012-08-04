#ifndef SDL_UTIL_H
# define SDL_UTIL_H

#include <SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "pos.h"

int		sdl_init(int width, int height);
void		sdl_uninit();
SDL_Surface	*draw_load(char *file);
int		load_sprite(void);
int		display_ship_sprite(t_pos *pos);
int		display_txt_on_pos(t_pos *pos, char *txt);

#endif
