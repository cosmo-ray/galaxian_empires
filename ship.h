#ifndef	SHIP_H_
#define	SHIP_H_

#define	SHIP_DIR	"ship"
/*the pos in the weapon's flag to say if you can use this weapon when you move*/
#define	MV_AT	1

#define	FRONT	0
#define	SIDE	1
#define	BACK	2


typedef	struct	s_weapon
{
  int	front;
  int	side;
  int	back;
  int	pa;
  char	flag;
}	t_weapon;

typedef	struct	s_mvsys
{
  int	front;
  int	side;
  int	back;
}	t_mvsys;

typedef	struct	s_armor
{
  float	front;
  float	side;
  float	back;  
}	t_armor;

typedef	struct	s_ship
{
  char		*name;
  t_weapon	mwp;
  t_mvsys	mvsys;
  t_armor	armor;
  int		pv;
  int		ap;
}	t_ship;

int     load_ship(char *file, t_ship *ship);
void    destroy_ship(t_ship *ture);
int	get_pv(t_ship *ship);
int	get_muldmg(t_ship *ship, int dir);
int     get_ship_atk(t_ship *ship, int dir);
inline const char	*get_ship_name(t_ship *ship);

#endif
