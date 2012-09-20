#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"ship.h"

static	int     set_pv(char *line, t_ship *ship);
static	int     set_mwp(char *line, t_ship *ship);
static	int     set_rmwp(char *line, t_ship *ship);
static	int     set_rar(char *line, t_ship *ship);
static	int     set_ap(char *line, t_ship *ship);
static	int     set_sp(char *line, t_ship *ship);

/* data_type's define */

#define	DATA_TYPE_SIZE	7
/* yeah i know, enum is cool but i don't like it for manipulate tab */
#define PV		0
#define MWP		1
#define RMWP		2
#define RAR		3
#define AP		4
#define SP		5

static int (*asign_tab[]) (char *, t_ship *) = {
  &set_pv,
  &set_mwp,
  &set_rmwp,
  &set_rar,
  &set_ap,
  &set_sp,
};

static const char	*data_type[] = {
  "pv",
  "mwp",
  "rmwp",
  "rar",
  "ap",
  "sp",
};

/* -------------- lonely static functions ---------------- */

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

static	int	read_file(int fd, char *tmp)
{
  int	ret;

  if ((ret = read(fd, tmp, 1024)) == -1 || ret > 1023)
    return (-1);
  tmp[ret] = '\0';
  close(fd);
  return (0);
}


/* -------------- set_data static function ---------------- */

/* replace the ':' by a '\0' and return the position of the character after the ':'*/
static int	get_end_charact(char *line, char c)
{
  int	i = 0;

  while (line[i] != c)
    {
      if (line[i] == '\0')
	return (-1);
      ++i;
    }
  line[i] = '\0';
  return(i + 1);
}


/* Erk ...*/

static	int	set_pv(char *line, t_ship *ship)
{
  int	valure = atoi(line);

  ship->pv = valure;
  return (0);
}

/*set equalitary the power of the "main" weapon*/
static	int	set_mwp(char *line, t_ship *ship)
{
  int	valure = atoi(line);

  ship->mwp.front = valure;
  ship->mwp.back = valure;
  ship->mwp.side = valure;
  ship->mwp.ap = 1;
  ship->mwp.flag = MV_AT;
  return (0);
}

/*repartition of the weapon power on the ship*/
static	int	set_rmwp(char *line, t_ship *ship)
{
  int	valure;
  int	jmp;

  valure = atoi(line);
  jmp = get_end_charact(line, ',');
  ship->mwp.front = (valure * ship->mwp.front) / 100;
  line = &(line[jmp]);

  valure = atoi(line);
  jmp = get_end_charact(line, ',');
  ship->mwp.side = (valure * ship->mwp.side) / 100;
  line = &(line[jmp]);

  valure = atoi(line);
  ship->mwp.back = (valure * ship->mwp.back) / 100;

  return (0);
}

/*"armor"*/
static	int	set_rar(char *line, t_ship *ship)
{
  float	valure;
  int	jmp;

  jmp = get_end_charact(line, ',');
  valure = atoi(line);
  ship->armor.front = valure;
  line = &(line[jmp]);
  valure = atoi(line);
  jmp = get_end_charact(line, ',');
  ship->armor.side = valure;
  line = &(line[jmp]);
  valure = atoi(line);
  ship->armor.back = valure;
  return (0);
}

/*action point*/
static	int	set_ap(char *line, t_ship *ship)
{
  int	valure = atoi(line);

  ship->ap = valure;
  return (0);
}

/*old speed*/
/* static	int	set_sp(char *line, t_ship *ship) */
/* { */
/*   int	valure = atoi(line); */

/*   ship->mvsys.front = valure; */
/*   ship->mvsys.back = valure; */
/*   ship->mvsys.side = valure;   */
/*   return (0); */
/* } */

/*speed*/
static	int	set_sp(char *line, t_ship *ship)
{
  float	valure;
  int	jmp;

  valure = atof(line);
  jmp = get_end_charact(line, ',');
  ship->mvsys.front = valure;
  line += jmp;//&(line[jmp]);
  valure = atoi(line);
  jmp = get_end_charact(line, ',');
  ship->mvsys.side = valure;
  line += jmp;//&(line[jmp]);
  valure = atoi(line);
  ship->mvsys.back = valure;
  return (0);
}

int	find_charact_type(char *line)
{
  int	i = 0;

  while (i < DATA_TYPE_SIZE)
    {
      if (!strcmp(data_type[i], line))
	return (i);
      ++i;
    }
  return (-1);
}

/* parse a line and set data in ship */
static int	handle_line(t_ship *ship, char *line)
{
  int	pos_sep;
  int	charact_type;  

  if (line[0] == '#')
    return (0);
  pos_sep = get_end_charact(line, ':');
  if ((charact_type = find_charact_type(line)) == -1)
    return (-1);
  line += pos_sep;
  /*Hey, you know what? at the begin, instead of the previous line, i've write the netx commentd one*/
  /* line = &(line[pos_sep]); */
  asign_tab[charact_type](line, ship);
  return (0);
}

static int	set_data(t_ship *ship, char *file)
{
  char	*ret = strtok(file, "\n");

  while (ret != NULL)
    {
      if (handle_line(ship, ret))
	return (-1);
      ret = strtok(NULL, "\n");
    }  
  return (0);
}

/* -------------- non static functions ---------------- */

int	get_pv(t_ship *ship)
{
  return (ship->pv);
}

int	get_ap(t_ship *this)
{
  return (this->ap);
}

float	get_speed(t_ship *this, int dir)
{
  if (dir == FRONT)
    return (this->mvsys.front);
  else if (dir == SIDE)
    return (this->mvsys.side);
  return (this->mvsys.back);
}

int	get_muldmg(t_ship *ship, int dir)
{
  if (dir == FRONT)
    return (ship->armor.front);
  if (dir == SIDE)
    return (ship->armor.side);
  return (ship->armor.back);
}

int	get_ship_atk(t_ship *ship, int dir)
{
  if (dir == FRONT)
    return (ship->mwp.front);
  if (dir == SIDE)
    return (ship->mwp.side);
  return (ship->mwp.back);
}

inline const char	*get_ship_name(t_ship *ship)
{
  return (ship->name);
}

int	load_ship(char *file, t_ship *ship)
{
  char	tmp[1024];
  int	fd = open_file(file);

  if (fd == -1)
    return (-1);
  if (cp_name(file, ship))
    return (-1);
  if (read_file(fd, tmp))
    return (-1);
  if (set_data(ship, tmp))
    return (-1);
  /* printf("name: %s\ncontent: \n%s\n", get_ship_name(ship), tmp );*/
  return (0);
}

void	destroy_ship(t_ship *ture)
{
  free(ture->name);
}
