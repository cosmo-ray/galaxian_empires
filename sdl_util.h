#ifndef SDL_UTIL_H
# define SDL_UTIL_H

#include <SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "pos.h"
#include "battle.h"

#define	KEY_MOUSE_1		1
#define	KEY_MOUSE_2		3
#define	KEY_MOUSE_ROL		2
#define	KEY_MOUSE_ROL_UP	4
#define	KEY_MOUSE_ROL_DOWN	5

#define	FILE_NAME		"sprite/image_set.png"
#define	BG_NAME			"sprite/background_set.png"

#define	CASE_SIZE		50

typedef	struct
{
  t_spos	battle_screen;
  t_spos	menu_box;
  t_spos	message_box;
}	t_battle_screen;

/*t_battle_screen manipulations function*/
void	tbs_init(void);


/* other sdl manipulation function*/

int		sdl_init(int width, int height);
void		sdl_uninit();
SDL_Surface	*draw_load(char *file);
int		load_sprite(void);
int		display_ship_sprite(t_pos *pos);
int		display_txt_on_pos(t_pos *pos, char *txt);
int		display_somethink(int x, int y, int id_x, int id_y);
int		display_bg_sprite(int x, int y);
int		get_pos_case(int pix_pos);
int		display_all_bg(t_battle *bd);

#endif
