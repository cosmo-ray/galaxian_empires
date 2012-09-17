#ifndef	CALCULATOR_H_
#define	CALCULATOR_H_

#include	"pos.h"

t_pos	*cal_get_Line(t_pos *a, t_pos *b);
t_pos	*cal_get_Line_ret(t_pos *a, t_pos *b, t_pos *ret);
double	get_rad(t_pos *a);

#endif
