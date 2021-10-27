/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:11:11 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/20 17:09:07 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Allocates (with malloc(3)) and returns a new
** element. The variable ’content’ is initialized
** with the value of the parameter ’content’. The
** variable ’next’ is initialized to NULL.
*/
t_list	*ft_lstnew(char content[BUFFER_SIZE])
{
	t_list	*list;
	size_t i;

	i = 0;
	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	while (i < BUFFER_SIZE)
	{
		list->content[i] = content[i];
		++i;
	}
	list->next = NULL;
	return (list);
}
/*
** Deletes and frees the given element and every
** successor of that element, using the function ’del’
** and free(3).
** Finally, the pointer to the list must be set to
** NULL.
*/
char	*ft_lstclear(t_list **lst)
{
	t_list	*cur_elem;
	t_list	*next_elem;
	char	check;

	check = 1;
	if (*lst == NULL)
		return (NULL);
	cur_elem = *lst;
	next_elem = *lst;
	while (check)
	{
		if (cur_elem->next)
			next_elem = cur_elem->next;
		else
			check = 0;
		//free(cur_elem->content);
		free(cur_elem);
		cur_elem = next_elem;
	}
	*lst = NULL;
	return (NULL);
}

void buffer_storage(int fd, char buffer[BUFFER_SIZE], int mode, int *end_pos)
{
	static char	buffer_list[FOPEN_MAX][BUFFER_SIZE];
	static int	fd_list[FOPEN_MAX];
	static int 	end_pos_list[FOPEN_MAX]; //заполнить -1
	size_t	i;

	(void) fd;
	(void) buffer;
	(void) fd_list;
	i = 0;
	if (mode == 0)
	{
		while (i < BUFFER_SIZE)
		{
			buffer[i] = buffer_list[0][i];
			i++;
		}
		*end_pos = end_pos_list[0];
	}
	else
	{
		while (i < BUFFER_SIZE)
		{
			buffer_list[0][i] = buffer[i];
			i++;
		}
		end_pos_list[0] = *end_pos;
	}
}
