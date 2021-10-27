/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:11:11 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/20 21:43:27 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void buffer_storage(int fd, char buffer[BUFFER_SIZE], int *end_pos, int *bytes_read)
{
	static char	buffer_list[FOPEN_MAX][BUFFER_SIZE];
	static int	fd_list[FOPEN_MAX];
	static int 	end_pos_list[FOPEN_MAX]; //заполнить -1
	static int	mode;
	static int 	bytes_read_list[FOPEN_MAX];
	size_t	i;

	i = 0;
	if (mode == 0)
	{
		mode = 1;
		while (i < FOPEN_MAX)
			bytes_read_list[i++] = BUFFER_SIZE;
		i = 0;
	}
	else
		mode *= -1;
	(void) fd;
	(void) buffer;
	(void) fd_list;
	i = 0;
	if (mode == 1)
	{
		while (i < BUFFER_SIZE)
		{
			buffer[i] = buffer_list[0][i];
			i++;
		}
		*end_pos = end_pos_list[0];
		*bytes_read = bytes_read_list[0];
	}
	else
	{
		while (i < BUFFER_SIZE)
		{
			buffer_list[0][i] = buffer[i];
			i++;
		}
		end_pos_list[0] = *end_pos;
		bytes_read_list[0] = *bytes_read;
	}
}

char	*free_res(char **res)
{
	if (*res)
	{
		free(*res);
		*res = NULL;
	}
	return (NULL);
}
