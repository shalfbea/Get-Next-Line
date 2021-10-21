/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:11:26 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/19 17:20:31 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	find_end_pos(char buffer[BUFFER_SIZE], int *bytes_read)
{
	size_t	i;

	i = 0;
	while (buffer[i] != '\n' && i < (size_t) *bytes_read)
		++i;
	if (i == (size_t) *bytes_read && *bytes_read != BUFFER_SIZE)
	{
		*bytes_read = -1;
		i++;
	}
	return (i);
}

size_t	modify_res(char **res, char buffer[BUFFER_SIZE], int *bytes_read, size_t *res_len)
{
	char	*new_res;
	size_t	i;
	size_t	k;
	size_t	end_pos;

	end_pos = find_end_pos(buffer, bytes_read);
	new_res = malloc(sizeof(char) * (*res_len + end_pos));
	//если не выделилась память? придумать
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
	return (end_pos);
}

void	buffer_rebuffer(char buffer[BUFFER_SIZE], size_t end_pos)
{
	char	tmp[BUFFER_SIZE];
	size_t	i;
	size_t	k;
	size_t	z;

	i = 0;
	k = 0;
	z = 0;
	while (i < end_pos)
		++i;
	while (i < BUFFER_SIZE)
		tmp[k++] = buffer[i++];
	i = 0;
	while (i < k)
		buffer[i++] = tmp[z++];
	while (i < BUFFER_SIZE)
		buffer[i++] = '\0';
}

char	*gnl_main_part(int fd, char	buffer[BUFFER_SIZE])
{
	char	*res;
	int		bytes_read;
	size_t	res_len;
	size_t	end_pos;

	bytes_read = BUFFER_SIZE;
	res_len = 1;
	res = NULL;
	if (buffer[0] != '\0')
	{
		end_pos = modify_res(&res, buffer, &bytes_read, &res_len);
		if (bytes_read == -1)
			buffer_rebuffer(buffer, end_pos);
	}
	while (bytes_read == (BUFFER_SIZE))
	{
		bytes_read = read(fd, buffer, (BUFFER_SIZE));
		if (bytes_read < 0)
		{
			free(res);
			return (NULL);
		}
		end_pos = modify_res(&res, buffer, &bytes_read, &res_len);
		if (bytes_read == -1)
			buffer_rebuffer(buffer, end_pos);
	}
	if (res[0] == '\0')
	{
		free(res);
		return (NULL);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	char *res; //redo
	char buffer[BUFFER_SIZE];
	char testforopen;
	(void) fd;

	if (read(fd, &testforopen, 0) < 0)
		return (NULL);
	buffer_storage(fd, buffer, 0);
	res = gnl_main_part(fd, buffer); //redo
	buffer_storage(fd, buffer, 1);
	/*
	if (res[0] == '\0')
	{
		free(res);
		return (NULL);
	}
	*/
	//printf("limit: %d", FOPEN_MAX);
	return (res);
}
