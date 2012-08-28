#include	"selector.h"


static void	display_pos(t_spos *pos)
{
  display_somethink(pos->x, pos->y, 0, SELECTOR);
}

static void	undisplay_pos(t_spos *pos, t_battle *bd)
{
  display_bg_sprite(pos->x, pos->y);
  if (is_fleet_on(bd->p1, pos->x, pos->y))
    print_ship(get_fleet(bd->p1, 0));
  else if (is_fleet_on(bd->p2, pos->x, pos->y))
    print_ship(get_fleet(bd->p2, 0));
}

static	void	move_pos(t_spos *opos, t_spos *npos, t_battle *bd)
{
  undisplay_pos(opos, bd);
  display_pos(npos);  
}

static	void	init_pos(t_spos *pos)
{
  pos->x = 0;
  pos->y = 0;
}

static	void	select_case_handle_keybork(t_spos *old, t_spos *pos, t_battle *bd, SDL_Event *event)
{
  switch (event->key.keysym.sym)
    {
    case SDLK_UP:
      pos->y -= 1;
      if (pos->y < 0)
	pos->y = bd->map.y - 1;
      break;
    case SDLK_DOWN:
      pos->y += 1;
      if (pos->y == bd->map.y)
	pos->y = 0;
      break;
    case SDLK_RIGHT:
      pos->x += 1;
      if (pos->x == bd->map.x)
	pos->x = 0;
      break;
    case SDLK_LEFT:
      pos->x -= 1;
      if (pos->x < 0)
	pos->x = bd->map.x - 1;
      break;
    default:
      break;
    }
  move_pos(old, pos, bd);
}

static	int	select_case_switch_type_event(t_spos *old, t_spos *pos, t_battle *bd, SDL_Event *event)
{
  switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:
     return (0);
    case SDL_KEYDOWN:
      select_case_handle_keybork(old, pos, bd, event);
      return (0);
     case SDL_QUIT:
      return (1);
    }
  return (0);
}

int	select_case(t_spos *pos, t_battle *bd)
{
  SDL_Event event;
  t_spos old;
  int	ret;

  init_pos(pos);
  display_pos(pos);
  while (!0)
    {
      old.x = pos->x;
      old.y = pos->y;
      SDL_WaitEvent(&event);
      if ((ret = select_case_switch_type_event(&old, pos, bd, &event)))
	return (ret);
    }
  return (0);
}
