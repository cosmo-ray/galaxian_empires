#ifndef	BMAP_C_
#define BMAP_C_

#define	EMPTY	0
#define	SHIP	1
#define	BLOCK	2

#define	IS_SHIP_ON(X)	 X & SHIP ? 1 : 0 
#define	IS_BLOCK_ON(X)	 X & BLOCK ? 1 : 0 

typedef struct	s_bmap	
{
int	x;
int	y;
int	len;
char	*data;
}	t_bmap;

int	init_bmap(t_bmap *map, int x, int y);
void	destroy_bmap(t_bmap *box);
char	get_x_y(t_bmap *map, int x, int y);

/*debug function*/
void	debug_print_map(t_bmap *map);

#endif
