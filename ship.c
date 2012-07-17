#include	<unistd.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"ship.h"

static	int	open_file(char *file)
{
  int	fd;

  if (chdir(SHIP_DIR))
    return (-1);
  if ((fd = open(file, O_RDONLY)) != 0)
    return (-1)
  if (chdir("../"))
    return (-1);
  return (fd);
}

static int	get_name_size(char *file)
{
  int	i;
  while (file[i] != '.' || file[i] != '\0')
    ++i;
  return (i);
}

static int cp_name(char *file, t_ship *ship)
{
  int	len_name = get_name_size(file);
  
  if (!len_name)
    return (-1);
  if ((ship->name = malloc(sizeof(*(ship->name)) * (len_name + 1))) == NULL)
    return (-1);
  strncpy(file, src, len_name);
  ship->name[len_name] = '\0';
  return (0);
}

int	load_ship(char *file, t_ship *ship)
{
  char	tmp[1024];
  int	fd = open_file(file);

  if (cp_name(file, ship))
    return (-1);  
}

void	destroy_ship(t_ship *ture)
{
  free(ture->name);
}
