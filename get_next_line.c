/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:11:26 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/28 23:21:18 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	gnl_add_res(char **res, char buffer[BUFFER_SIZE + 1],
						size_t *cur_len, size_t *max_len)
{
	unsigned int	k;
	int				end;

	k = 0;
	if (gnl_realloc(res, cur_len, max_len))
		return (-1);
	end = 0;
	while (buffer[k] != '\n' && buffer[k])
		(*res)[(*cur_len)++] = buffer[k++];
	if (buffer[k] == '\n')
	{
		(*res)[(*cur_len)++] = buffer[k];
		buffer[k++] = '\0';
		end = k;
	}
	(*res)[(*cur_len)] = '\0';
	return (end);
}

static char	*gnl_make_res(char **res, size_t *cur_len)
{
	char	*trim_res;
	size_t	i;

	if ((*res)[0] == '\0' || (!(*res)))
		return (free_res(res));
	trim_res = (char *) malloc(sizeof(char) + (++(*cur_len)));
	if (!trim_res)
		return (free_res(res));
	i = 0;
	while (i < *cur_len)
	{
		trim_res[i] = (*res)[i];
		i++;
	}
	free_res(res);
	return (trim_res);
}

static char	*gnl_main_work(int fd, int *end, int *bytes_read,
							char buffer[BUFFER_SIZE + 1])
{
	char		*res;
	size_t		cur_len;
	size_t		max_len;

	res = NULL;
	cur_len = 0;
	max_len = 0;
	if (buffer[0] != '\0')
	{
		*end = gnl_add_res(&res, buffer, &cur_len, &max_len);
		if (*end < 0)
			return (free_res(&res));
	}
	while (*bytes_read == BUFFER_SIZE && !(*end))
	{
		*bytes_read = gnl_read_file(fd, buffer);
		if (*bytes_read < 0)
			return (free_res(&res));
		*end = gnl_add_res(&res, buffer, &cur_len, &max_len);
		if (*end < 0)
			return (free_res(&res));
	}
	return (gnl_make_res(&res, &cur_len));
}

char	*get_next_line(int fd)
{
	static char	buffer[OPEN_MAX][BUFFER_SIZE + 1];
	char		*res;
	int			bytes_read;
	int			end;

	end = 0;
	bytes_read = BUFFER_SIZE;
	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	res = gnl_main_work(fd, &end, &bytes_read, buffer[fd]);
	gnl_prev_buffer(buffer[fd], end, bytes_read);
	return (res);
}
