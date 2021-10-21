/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:11:26 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/21 20:51:02 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	gnl_read_file(int fd, char buffer[BUFFER_SIZE + 1])
{
	int bytes_read;
	int	k;

	bytes_read = read(fd, buffer, (BUFFER_SIZE));
	if (bytes_read < 0)
		return (-1);
	k = bytes_read;
	while (k < (BUFFER_SIZE + 1))
		buffer[k++] = '\0';
	return (1);
}

static void	gnl_prev_buffer(char prev_buffer[BUFFER_SIZE +1], char buffer[BUFFER_SIZE + 1])
{
	unsigned int	i;
	unsigned int	k;

	i = 0;
	k = 0;
	while (buffer[i])
		++i;
	if (i == 0 && buffer[i + 1] != '\0')
	{
		prev_buffer[0] = '\0';
		return ;
	}
	i++;
	while (i < (BUFFER_SIZE + 1))
		prev_buffer[k++] = buffer[i++];
	prev_buffer[k] = '\0';
}

static int gnl_realloc(char **res, size_t *cur_len, size_t *max_len)
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
	while (i < *cur_len )
	{
		new_res[i] = (*res)[i];
		++i;
	}
	free_res(res);
	*res = new_res;
	return (0);
}

static int gnl_add_res(char **res, char buffer[BUFFER_SIZE + 1], size_t *cur_len, size_t *max_len)
{
	unsigned int 	k;
	int				end;

	if (gnl_realloc(res, cur_len, max_len))
		return (-1);
	k = 0;
	while (buffer[k] != '\n' && buffer[k])
		(*res)[(*cur_len)++] = buffer[k++];
	if (buffer[k] == '\n')
	{
		(*res)[(*cur_len)++] = buffer[k];
		buffer[k++] = '\0';
		end = 0;
	}
	else
		end = BUFFER_SIZE;
	(*res)[(*cur_len)] = '\0';
	return (end);
}

static char	*gnl_make_res(char **res)
{
	//trim str
	if ((*res)[0] == '\0')
		return (free_res(res));
	return (*res);
}
char	*get_next_line(int fd)
{
	static	char	prev_buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char	*res;
	char	buffer[BUFFER_SIZE + 1];
	size_t	cur_len;
	size_t	max_len;
	int		bytes_read;

	res = NULL;
	cur_len = 0;
	max_len = 0;
	bytes_read = BUFFER_SIZE;
	//buffer[0] = '\0';
	if (fd < 0 || fd > FOPEN_MAX)
		return (NULL);
	if (prev_buffer[fd][0] != '\0')
	{
		bytes_read = gnl_add_res(&res, prev_buffer[fd], &cur_len, &max_len );
		if (bytes_read < 0)
			return (free_res(&res));
	}
	while (bytes_read == BUFFER_SIZE)
	{
		bytes_read = gnl_read_file(fd, buffer);
		if (bytes_read < 0)
			return (free_res(&res));
		bytes_read = gnl_add_res(&res, buffer, &cur_len, &max_len );
		if (bytes_read < 0)
			return (free_res(&res));
	}
	gnl_prev_buffer(prev_buffer[fd], buffer);
	return (gnl_make_res(&res));
}
