#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"ship.h"

static	int	open_file(char *file)
{
  int	fd;

  if (chdir(SHIP_DIR))
    return (-1);
  if ((fd = open(file, O_RDONLY)) == -1)
    return (-1);
  if (chdir("../"))
    return (-1);
  return (fd);
}

static int	get_name_size(char *file)
{
  int	i = 0;
  while (file[i] != '.' && file[i] != '\0')
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
  strncpy(ship->name, file, len_name);
  ship->name[len_name] = '\0';
  return (0);
}

inline const char	*get_ship_name(t_ship *ship)
{
  return (ship->name);
}

int	load_ship(char *file, t_ship *ship)
{
  char	tmp[1024];
  int	fd = open_file(file);
  int	ret;

  if (fd == -1)
    return (-1);
  if (cp_name(file, ship))
    return (-1);
  if ((ret = read(fd, tmp, 1024)) == -1 || ret > 1023)
    return (-1);
  tmp[ret] = '\0';
  close(fd);
  printf("name: %s\ncontent: \n%s\n", get_ship_name(ship), tmp);
  return (0);
}

void	destroy_ship(t_ship *ture)
{
  free(ture->name);
}
