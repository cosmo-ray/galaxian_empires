#ifndef	BMAP_C_
#define BMAP_C_

#include	"pos.h"

#define	EMPTY	0
#define	SHIP	1
#define	BLOCK	2
#define	ALL	3

#define	IS_SHIP_ON(X)	 X & SHIP ? 1 : 0 
#define	IS_BLOCK_ON(X)	 X & BLOCK ? 1 : 0 

/*spos is the position structure used by the functions in selector.c*/
typedef	struct	
{
  int	x;
  int	y;
}	t_spos;

typedef struct	s_bmap	
{
int	x;
int	y;
int	len;
char	*data;
}	t_bmap;

int	init_bmap(t_bmap *map, int x, int y);
void	destroy_bmap(t_bmap *box);
char	bmap_get_x_y(t_bmap *map, int x, int y);
void	bmap_add_ship(t_bmap *map, int x, int y);
void	bmap_rm_ship(t_bmap *map, int x, int y);
void	bmap_avance_to_target(t_spos *pos, t_spos *target);

/*spos func*/
inline	t_spos	*pos_to_spos(t_pos *pos);
void	init_pos(t_spos *pos);
int	is_spos_equale(t_spos *pos1, t_spos *pos2);

#endif
