/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:11:11 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/28 23:18:06 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_res(char **res)
{
	(void) res;
	if (*res)
	{
		free(*res);
		*res = NULL;
	}
	return (NULL);
}

int	gnl_read_file(int fd, char buffer[BUFFER_SIZE + 1])
{
	int	bytes_read;
	int	k;

	bytes_read = read(fd, buffer, (BUFFER_SIZE));
	if (bytes_read < 0)
		return (-1);
	k = bytes_read;
	while (k < (BUFFER_SIZE + 1))
		buffer[k++] = '\0';
	return (bytes_read);
}

int	gnl_realloc(char **res, size_t *cur_len, size_t *max_len)
{
	char	*new_res;
	size_t	i;

	if (*cur_len + BUFFER_SIZE + 3 < *max_len && (*max_len != 0))
		return (0);
	*max_len += BUFFER_SIZE + 100;
	new_res = (char *)malloc(sizeof(char) * (*max_len));
	if (!new_res)
		return (1);
	i = 0;
	while (i < *cur_len)
	{
		new_res[i] = (*res)[i];
		++i;
	}
	free_res(res);
	*res = new_res;
	return (0);
}

void	gnl_prev_buffer(char buffer[BUFFER_SIZE + 1],
							int end, int bytes_read)
{
	unsigned int	i;
	unsigned int	k;

	i = end;
	k = 0;
	if (bytes_read < BUFFER_SIZE && (end >= bytes_read || end == 0))
	{
		buffer[0] = '\0';
		return ;
	}
	while (i < (unsigned int)(bytes_read + 1))
		buffer[k++] = buffer[i++];
	buffer[k] = '\0';
}
