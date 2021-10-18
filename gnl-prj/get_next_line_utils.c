/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:11:11 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/18 20:12:40 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
** Allocates (with malloc(3)) and returns a new
** element. The variable ’content’ is initialized
** with the value of the parameter ’content’. The
** variable ’next’ is initialized to NULL.
*/
/*
t_list	*ft_lstnew(char *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
*/
/*
** Deletes and frees the given element and every
** successor of that element, using the function ’del’
** and free(3).
** Finally, the pointer to the list must be set to
** NULL.
*/
/*
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
		free(cur_elem->content);
		free(cur_elem);
		cur_elem = next_elem;
	}
	*lst = NULL;
	return (NULL);
}
*/
