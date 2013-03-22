#include	<string.h>
#include	<unistd.h>
#include	<stdio.h>
#include	"mesage_box.h"

char	g_msg[1024];
int	g_index = 0;

int	message_box_print_msg(char *msg)
{
  display_txt_on_msg_box(msg);
  return (0);
}

int	message_box_add_msg(char *msg)
{
  g_index += sprintf(g_msg + (long)g_index, msg);
  return (0);
}

int	message_box_add_int(int nbr)
{
  g_index += sprintf(g_msg + (long)g_index, "%d", nbr);
  return (0);
}

int	message_box_flush(void)
{
  g_index = 0;
  display_txt_on_msg_box(g_msg);
  return (0);
}

int	message_box_clean()
{
  g_index = 0;
  return (0);
}
