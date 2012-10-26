#include	<unistd.h>
#include	<stdio.h>
#include	"game.h"

extern t_game	life;

int	give_life()
{
  t_ship	*ship;

  if ((ship = malloc(sizeof(*ship))) == NULL)
    return (-1);
  init_list(&(life.ships));
  if (load_ship("battle_cruse.sp", ship))
    return (-1);
  push_elem(&(life.ships), new_elem(ship));
  if (sdl_init(800, 600) == -1)
    return (-1);
  load_sprite();
  if ((life.bg = draw_load(BG_NAME)) == NULL)
    return (-1);
  return (0);
}

void	take_life()
{
  t_ship	*ture;

  sdl_uninit();  
  while(life.ships.len)
    {
      ture = pop_data(&(life.ships));
      destroy_ship(ture);
      free(ture);
    }
}
