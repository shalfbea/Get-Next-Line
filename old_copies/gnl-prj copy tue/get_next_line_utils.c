/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:11:11 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/19 16:27:26 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	buffer_storage(int fd, char buffer[BUFFER_SIZE], int mode)
{
	static char	buffer_list[FOPEN_MAX][BUFFER_SIZE];
	static int	fd_list[FOPEN_MAX];
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
	}
	else
	{
		while (i < BUFFER_SIZE)
		{
			buffer_list[0][i] = buffer[i];
			i++;
		}
	}
}
