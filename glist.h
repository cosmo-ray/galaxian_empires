#ifndef GLIST_H
# define GLIST_H

typedef struct s_node
{
  void *data;
  struct s_node *prev;
  struct s_node *next;
}	t_node;

struct	s_list
{
  int	len;
  t_node *last;
  t_node *first;
};

typedef struct s_list t_list;

void	init_list(t_list *list);
void	*pop_data(t_list *list);
void	push_elem(t_list *elem, t_node *add_elem);
t_node	*new_elem(void *data);
void	*get_data(t_list *list, int nbr);

#endif /* !GLIST1_H */
