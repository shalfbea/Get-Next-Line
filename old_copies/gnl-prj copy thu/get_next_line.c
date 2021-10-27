/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:11:26 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/20 22:01:11 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_res_realloc(char **res, size_t *res_max_size, size_t *res_cur_suze)
{
	char	*new_res;
	size_t	i;

	new_res = NULL;
	if (res_cur_suze + BUFFER_SIZE + 2 < res_max_size)
		return (0);
	if (BUFFER_SIZE < 50)
		(*res_max_size) += BUFFER_SIZE + 50;
	else
		(*res_max_size) += BUFFER_SIZE + 2;
	new_res = (char *) malloc(sizeof(char) * (*res_max_size));
	if (!new_res)
		return (1);
	i = 0;
	new_res[0] = '\0';
	if (*res == NULL)
	{
		*res = new_res;
		return (0);
	}
	while ((*res)[i])
	{
		new_res[i] = (*res)[i];
		++i;
	}
	new_res[i] = '\0';
	return (0);
}

char	gnl_add_res(char buffer[BUFFER_SIZE], char *res, int *end_pos,
					 int bytes_read)
{
	int		k;
	size_t	i;
	char	end;

	i = 0;
	k = 0;
	end = 0;
	while (res[i])
		i++;
	k = *end_pos;
	while (k < bytes_read && buffer[k] != '\n')
		res[i++] = buffer[k++];
	if (buffer[k] == '\n')
	{
		res[i++] = '\n';
		end = 1;
		k++;
	}
	if (bytes_read < BUFFER_SIZE)
		end = 1;
	*end_pos = k;
	res[i] = '\0';
	return (end);
}

char	*gnl_make_res(char **res)
{
	//TRIM STR
	if (res[0] == '\0')
		return (free_res(res));
	return (*res);
}

char	*gnl_main_part(int fd, char buffer[BUFFER_SIZE], int *end_pos,
					int *bytes_read)
{
	char	*res;
	size_t	res_max_size;
	size_t	res_cur_size;
	char	end;

	res_max_size = 0;
	res_cur_size = 0;
	res = NULL;
	end = 0;
	if (*bytes_read <= 0 || *end_pos >= *bytes_read)
		return (free_res(&res));
	if (gnl_res_realloc(&res, &res_max_size, &res_cur_size))
		return (free_res(&res));
	if (*end_pos)
		end = gnl_add_res(buffer, res, end_pos, *bytes_read);
	while (*bytes_read == BUFFER_SIZE && !end)
	{
		*end_pos = 0;
		*bytes_read = read(fd, buffer, (BUFFER_SIZE));
		if (*bytes_read <= 0)
			return (free_res(&res));
		if (gnl_res_realloc(&res, &res_max_size, &res_cur_size))
			return (free_res(&res));
		end = gnl_add_res(buffer, res, end_pos, *bytes_read);
	}
	return (gnl_make_res(&res));
}

char	*get_next_line(int fd)
{
	char *res;
	char buffer[BUFFER_SIZE];
	(void) fd;
	int end_pos;
	int	bytes_read;

	end_pos = 0;
	bytes_read = 0 ;
	buffer_storage(fd, buffer, &end_pos, &bytes_read);
	res = gnl_main_part(fd, buffer, &end_pos, &bytes_read); //redo
	buffer_storage(fd, buffer, &end_pos, &bytes_read);
	//return (gnl_main_part(res));
	return (res);
}
