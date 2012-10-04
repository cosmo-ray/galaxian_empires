#ifndef	CALCULATOR_H_
#define	CALCULATOR_H_

#include	"pos.h"

#define	ABS(X)	 X < 0 ? (X * -1) : X 
#define	COME_NEAR(X, Y)	 X < Y ? +1 : -1 
t_pos	*cal_get_Line(t_pos *a, t_pos *b);
t_pos	*cal_get_Line_ret(t_pos *a, t_pos *b, t_pos *ret);
double	get_rad(t_pos *a);
int	cal_get_dist(int a, int b);

#endif
