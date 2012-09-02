/*
** my_list.c for my_list.c in /home/rubio-_c//work/C/my_libc
**
** Made by charlie rubio-nevado
** Login   <rubio-_c@epitech.net>
**
** Started on  Mon Mar 19 18:04:43 2012 charlie rubio-nevado
** Last update Sun Jul  1 17:09:37 2012 charlie rubio-nevado
*/
#include <stdlib.h>
#include "glist.h"

void *pop_data(t_list *list)
{
  void *tmp;
  t_node *dent;

  if (list->len == 0)
    return (NULL);
  tmp = list->last->data;
  if (list->len > 1)
    list->last->prev->next = NULL;
  list->len -= 1;
  dent = list->last;
  list->last = list->last->prev;
  if (list->len == 0)
    list->first = NULL;
  free(dent);
  return (tmp);
}

static	t_node *get_node(t_list *list, int nbr)
{
  int	i = 1;
  t_node *ret;

  if (!nbr)
    return (NULL);
  ret = list->first;
  while (i < nbr && i < list->len)
    {
      ret = ret->next;
      ++i;
    }
  if (i != nbr)
    return (NULL);
  return (ret);
}

/*pop a node of the list at the position pos*/
void	*pop_data_pos(t_list *list, int pos)
{
  void *tmp;
  t_node *dent;

  if (pos > list->len)
    return (NULL);
  dent = get_node(list, pos);
  if (dent == NULL)
    return (NULL);
  if (list->first == dent)
    list->first = dent->next;
  else
    dent->prev->next = dent->next;
  if (list->last == dent)
    list->first = dent->prev;
  else
    dent->next->prev = dent->prev;
  tmp = dent->data;
  free(dent);
  return (tmp);
}

void	*get_data(t_list *list, int nbr)
{
  int		i = 0;
  t_node	*ret;

  ret = list->first;
  if (nbr >= list->len)
    return (NULL);  
  while (i < nbr)
    {
      ret = ret->next;
      ++nbr;
    }
  return (ret-> data);
}

/*
** add the node add_elem to the list
*/

void push_elem(t_list *list, t_node *add_elem)
{
  if (list->first == NULL)
    list->first = add_elem;
  else
    list->last->next = add_elem;
  add_elem->prev = list->last;
  add_elem->next = NULL;
  list->len += 1;
  list->last = add_elem;
}

/*
** create a new element and add the data on void generic pointer
** return null if the memory allocation of the element failed, the pointer
** on element if success
*/

t_node *new_elem(void *data)
{
  t_node	*elem;

  if ((elem = malloc(sizeof(*elem))) == NULL)
      return (NULL);
  elem->prev = NULL;
  elem->next = NULL;
  elem->data = data;
  return (elem);
}

void init_list(t_list *list)
{
  list->len = 0;
  list->last = NULL;
  list->first = NULL;
}
