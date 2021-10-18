/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:11:26 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/18 22:33:06 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	find_end_pos(char buffer[BUFFER_SIZE], int *bytes_read)
{
	size_t	i;

	i = 0;
	while (buffer[i] != '\n' && i < (size_t) *bytes_read)
		++i;
	if (buffer[i] == '\n')
		*bytes_read = -1;
	return (i);
}

void	modify_res(char **res, char buffer[BUFFER_SIZE], int *bytes_read, size_t *res_len)
{
	char	*new_res;
	size_t	i;
	size_t	k;
	size_t	end_pos;

	end_pos = find_end_pos(buffer, bytes_read);
	new_res = malloc(sizeof(char) * (*res_len + end_pos));
	i = 0;
	k = 0;
	if (*res_len > 1)
	{
		while (i < ((*res_len) - 1))
		{
			new_res[i] = (*res)[i];
			++i;
		}
	}
	while(k < end_pos)
		new_res[i++] = buffer[k++];
	new_res[i] = '\0';
	if (!res)
		free(*res);
	*res_len += end_pos;
	*res = new_res;
}
char	*gnl_main_part(int fd, char	buffer[BUFFER_SIZE])
{
	char	*res;
	int		bytes_read;
	size_t	res_len;
	char	not_end;

	if (BUFFER_SIZE < 1)
		return (NULL);
	bytes_read = BUFFER_SIZE;
	res_len = 1;
	not_end = 1;
	res = NULL;
	while (bytes_read == (BUFFER_SIZE) && not_end)
	{
		bytes_read = read(fd, buffer, (BUFFER_SIZE));
		modify_res(&res, buffer, &bytes_read, &res_len);
	}
	return (res);
}
char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE];

	return (gnl_main_part(fd, buffer));
}
