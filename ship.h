#ifndef	SHIP_H_
#define	SHIP_H_


#define	SHIP_DIR	"ship"
/*the pos in the weapon's flag to say if you can use this weapon when you move*/
#define	MV_AT	2

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
  int	front;
  int	side;
  int	back;  
}	t_armor;

typedef	struct	s_ship
{
  char		*name;
  t_weapon	mwp;
  t_mvsys	mvsys;
  t_armor	armor;
  int		pv;
}	t_ship;

int     load_ship(char *file, t_ship *ship);
void    destroy_ship(t_ship *ture);
int	set_pv(char *line);
int	set_mwp(char *line);
int	set_rmwp(char *line);
int	set_rar(char *line);
int	set_ap(char *line);
int	set_sp(char *line);
int	set_rsp(char *line);

#endif
