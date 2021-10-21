/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:11:30 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/21 20:15:20 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

//DELETE IT:
# include <stdio.h>
//
# include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			content[BUFFER_SIZE];
	struct s_list	*next;
}	t_list;
char	*get_next_line(int fd);

//t_list	*ft_lstnew(char content[BUFFER_SIZE]);
//char	*ft_lstclear(t_list **lst);
void	buffer_storage(int fd, char buffer[BUFFER_SIZE], int *end_pos, int *bytes_read);
char	*free_res(char **res);
#endif
