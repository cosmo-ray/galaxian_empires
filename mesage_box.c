#include	<string.h>
#include	<unistd.h>
#include	<stdio.h>
#include	"mesage_box.h"

int	print_msg(char *msg)
{
  printf("%s", msg);
  return (0);
}

int	print_int(int nbr)
{
  printf("%d", nbr);
  return (0);
}

void	msg_box_clean()
{
}
