#ifndef	POS_H_
#define	POS_H_

#define	NORTH	0
#define	SOUTH	1
#define	WEST	2
#define	EAST	3


typedef	struct	s_pos
{
  int		x;
  int		y;
  int		dir;
}	t_pos;

void	pos_copy(t_pos *src, t_pos *dest);
float	comp_pos(t_pos *pos1, t_pos *pos2);
#endif
