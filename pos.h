#ifndef	POS_H_
#define	POS_H_

#define	NORTH	0
#define	WEST	1
#define	EAST	2
#define	SOUTH	3


typedef	struct	s_pos
{
  int		x;
  int		y;
  int		dir;
}	t_pos;

#endif
