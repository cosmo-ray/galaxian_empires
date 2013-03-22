#ifndef	PRINTER_H
#define PRINTER_H

#include	"sdl_util.h"

int	message_box_print_msg(char *msg);

int	message_box_add_msg(char *msg);
int	message_box_add_int(int nbr);
int	message_box_flush(void);
int	message_box_clean();

#endif
