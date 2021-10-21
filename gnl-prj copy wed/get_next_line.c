/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:11:26 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/20 18:45:05 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	gnl_add_to_list(char buffer[BUFFER_SIZE], t_list **head, t_list *tail, int *bytes_read)
{
	int	i;
	int ans;

	if (*bytes_read < 1)
		return (3);
	if (*head == NULL)
	{
		*head = ft_lstnew(buffer);
		tail = *head;
	}
	else
	{
		tail->next = ft_lstnew(buffer);
		tail = tail->next;
	}
	i = -1;
	ans = 0;
	if (*bytes_read < BUFFER_SIZE)
		return ('\0');
	while (i < BUFFER_SIZE && (buffer[i] != '\n'))
		++i;
	*bytes_read = i;
	if (i < BUFFER_SIZE)
		return ('\n');
	return (-1);
}

size_t	res_size(t_list *head, int bytes_read, char mode)
{
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	while (head->next)
	{
		len++;
		head = head->next;
	}
	if (mode == '\n')
		bytes_read++;
	return (len * ((size_t) BUFFER_SIZE) + bytes_read + 1);
}

char	*make_res(t_list **head, char mode, int end_pos)
{
	char	*res;
	t_list	*tmp;
	size_t	i;
	size_t	k;

	if (mode == 3)
		return (ft_lstclear(head));
	res = (char *) malloc(sizeof(char)  * res_size(*head, end_pos, mode));
	tmp = *head;
	i = 0;
	while (tmp->next)
	{
		k = end_pos;
		while (k < BUFFER_SIZE)
			res[i++] = tmp->content[k++];
		tmp = tmp->next;
	}
	if (tmp)
	{
		k = 0;
		while (tmp)
		if (tmp->content[k] == '\n')
			res[i++] = '\n';
	}
	res[i] = '\0';
	ft_lstclear(head);
	if (res[0] == '\0')
		return (NULL);
	return (res);
}

char	*gnl_main_part(int fd, char buffer[BUFFER_SIZE], int *end_pos)
{
	t_list *head;
	t_list *tail;
	int		mode;
	int		bytes_read;

	head = NULL;
	tail = NULL;
	bytes_read = BUFFER_SIZE;
	if (*end_pos)
	{
		mode = gnl_add_to_list(buffer, &head, tail, &bytes_read);
		*end_pos = 0;
	}
	while (bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buffer, (BUFFER_SIZE));
		mode = gnl_add_to_list(buffer, &head, tail, &bytes_read);
	}
	*end_pos = bytes_read;
	return (make_res(&head, end_pos, mode, bytes_read));
}

char	*get_next_line(int fd)
{
	char *res;
	char buffer[BUFFER_SIZE];
	(void) fd;
	int end_pos;

	end_pos = 0;
	buffer_storage(fd, buffer, 0, &end_pos);
	res = gnl_main_part(fd, buffer, &end_pos); //redo
	buffer_storage(fd, buffer, 1, &end_pos);
	return (res);
}
