#ifndef SDL_UTIL_H
# define SDL_UTIL_H

#include <SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "pos.h"

#define	KEY_UP			273
#define	KEY_DOWN		274
#define	KEY_RIGHT		275
#define	KEY_LEFT		276
#define	KEY_ESCAPE		27
#define	KEY_SPACE		32
#define	KEY_ENTER		13

#define	KEY_MOUSE_1		1
#define	KEY_MOUSE_2		3
#define	KEY_MOUSE_ROL		2
#define	KEY_MOUSE_ROL_UP	4
#define	KEY_MOUSE_ROL_DOWN	5

#define	FILE_NAME		"sprite/ship.png"

#define	CASE_SIZE		50

int		sdl_init(int width, int height);
void		sdl_uninit();
SDL_Surface	*draw_load(char *file);
int		load_sprite(void);
int		display_ship_sprite(t_pos *pos);
int		display_txt_on_pos(t_pos *pos, char *txt);
int		get_x_case(int pix_x_pos);
int		get_y_case(int pix_y_pos);

#endif
