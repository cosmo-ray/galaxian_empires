#include	"selector.h"
#include	"mesage_box.h"

static void	display_pos(t_spos *pos)
{
  display_somethink(pos->x, pos->y, 0, SELECTOR);
}

static void	undisplay_pos(t_spos *pos, t_battle *bd)
{
  display_bg_sprite(pos->x, pos->y);
  display_case(bd, pos->x, pos->y);
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

static	int	select_case_handle_keybork(t_spos *old, t_spos *pos, t_battle *bd, SDL_Event *event)
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
    case SDLK_RETURN:
      return (2);
    default:
      break;
    }
  move_pos(old, pos, bd);
  return (0);
}

static	int	select_case_switch_type_event(t_spos *old, t_spos *pos, t_battle *bd, SDL_Event *event)
{
  switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:
     return (0);
    case SDL_KEYDOWN:
      return (select_case_handle_keybork(old, pos, bd, event));
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
	{
	  if (ret != 2)
	    return (ret);
	  return (0);
	}
    }
  return (0);
}

int	select_empty_case(t_spos *pos, t_battle *bd)
{
  if (select_case(pos, bd))
    return (1);
  if (bmap_get_x_y(&bd->map, pos->x, pos->y) == EMPTY)
    return (0);
  print_msg("an empty case must be selected\n");
  return (select_empty_case(pos, bd));
}

int	select_fleet(t_spos *pos, t_battle *bd)
{
  if (select_case(pos, bd))
    return (1);
  if (bmap_get_x_y(&bd->map, pos->x, pos->y) & SHIP)
    return (0);
  print_msg("an case whith a fleet must be selected\n");
  return (select_fleet(pos, bd));
}

int	select_ally_fleet(t_spos *pos, t_battle *bd, t_player *p)
{
  if (select_fleet(pos, bd))
    return (1);
  if (get_fleet_on(p, pos->x, pos->y))
    return (0);
  print_msg("an case whith a ally fleet must be selected\n");
  return (select_ally_fleet(pos, bd, p));
}

int	select_enemy_fleet(t_spos *pos, t_battle *bd, t_player *p)
{
  if (select_fleet(pos, bd))
    return (1);
  if (!get_fleet_on(p, pos->x, pos->y))
    return (0);
  print_msg("yeah shoot your friend, good idie !\n");
  return (select_enemy_fleet(pos, bd, p));
}

