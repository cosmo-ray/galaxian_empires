#include	<stdio.h>

int	print_menu(char **menu)
{
  int	i;

  printf("enter the number of the action you want to do\n");
  for (i = 0; menu[i] != NULL; ++i)
    {
      printf("%d: %s\n", i + 1, menu[i]);
    }
  return (0);
}
