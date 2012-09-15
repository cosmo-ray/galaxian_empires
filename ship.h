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
  /*the power with the front batrie*/
  int	front;
  /*the power with the side batrie*/
  int	side;
  /*the power with the back batrie*/
  int	back;
  /*the AP needed for one shoot*/
  int	pa;
  char	flag;
}	t_weapon;

/*the power of the booster in the front, the back, and the side of the ship in case by AP*/
typedef	struct	s_mvsys
{
  float	front;
  float	side;
  float	back;
}	t_mvsys;

/*the armor is in fact a domage multiplicator, more the armor is near 0 more the armor is usefull*/
typedef	struct	s_armor
{
  float	front;
  float	side;
  float	back;  
}	t_armor;

typedef	struct	s_ship
{
  char		*name;
  /*main weapon*/
  t_weapon	mwp;
  /*movement system*/
  t_mvsys	mvsys;
  t_armor	armor;
  int		pv;
  /*action point*/
  int		ap;
}	t_ship;

int     load_ship(char *file, t_ship *ship);
void    destroy_ship(t_ship *ture);
int	get_pv(t_ship *ship);
int	get_muldmg(t_ship *ship, int dir);
int     get_ship_atk(t_ship *ship, int dir);
float	get_speed(t_ship *this, int dir);
int	get_ap(t_ship *this);
inline const char	*get_ship_name(t_ship *ship);

#endif
