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
  tmp = list->last_elem->data;
  if (list->len > 1)
    list->last_elem->prev->next = NULL;
  list->len -= 1;
  dent = list->last_elem;
  list->last_elem = list->last_elem->prev;
  if (list->len == 0)
    list->first_elem = NULL;
  free(dent);
  return (tmp);
}

/*
** add the element to the element given
*/

void push_elem(t_list *list, t_node *add_elem)
{
  if (list->first_elem == NULL)
    list->first_elem = add_elem;
  else
    list->last_elem->next = add_elem;
  add_elem->prev = list->last_elem;
  add_elem->next = NULL;
  list->len += 1;
  list->last_elem = add_elem;
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
  list->last_elem = NULL;
  list->first_elem = NULL;
}
