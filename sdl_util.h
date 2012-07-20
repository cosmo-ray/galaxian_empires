#ifndef SDL_UTIL_H
# define SDL_UTIL_H

#include <SDL.h>
#include <SDL/SDL_image.h>

SDL_Surface	*sdl_init(int width, int height);
void		sdl_uninit();
SDL_Surface	*draw_load(void);

#endif
