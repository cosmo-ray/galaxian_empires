#include	<string.h>
#include	<unistd.h>
#include	"printer.h"

void	print_msg(char *msg)
{
  write(1, msg, strlen(msg));
}
