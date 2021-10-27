/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:11:26 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/27 21:13:41 by shalfbea         ###   ########.fr       */
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
	return (bytes_read);
}

static void	gnl_prev_buffer(char buffer[BUFFER_SIZE + 1], int end, int bytes_read)
{
	unsigned int	i;
	unsigned int	k;

	//TEST
	/*
	printf("buffer to add:");
	for (int j = 0; j <= BUFFER_SIZE; ++j)
		printf("%d,", (int)buffer[j]);
	printf("\n");
	*/
	//
	i = end;
	k = 0;
	if (bytes_read < BUFFER_SIZE && (end >= bytes_read || end == 0))
	{
		buffer[0] = '\0';
		return ;
	}
	//while (i < (BUFFER_SIZE + 1)
	while (i < (unsigned int) (bytes_read + 1))
		buffer[k++] = buffer[i++];
	buffer[k] = '\0';
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

	if ((*res)[0] == '\0')
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
char	*get_next_line(int fd)
{
	static	char	buffer[OPEN_MAX][BUFFER_SIZE + 1];
	char	*res;
	size_t	cur_len;
	size_t	max_len;
	int		bytes_read;
	int		end;

	res = NULL;
	cur_len = 0;
	max_len = 0;
	end = 0;
	bytes_read = BUFFER_SIZE;
	if (fd < 0 || fd > FOPEN_MAX)
		return (NULL);
	if (buffer[fd][0] != '\0')
	{
		end = gnl_add_res(&res, buffer[fd], &cur_len, &max_len);
		if (end < 0)
			return (free_res(&res));
	}
	while (bytes_read == BUFFER_SIZE && !end)
	{
		bytes_read = gnl_read_file(fd, buffer[fd]);
		if (bytes_read < 0)
			return (free_res(&res));
		end = gnl_add_res(&res, buffer[fd], &cur_len, &max_len );
		if (end < 0)
			return (free_res(&res));
	}
	gnl_prev_buffer(buffer[fd], end, bytes_read);
	return (gnl_make_res(&res, &cur_len));
}
