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

#endif
