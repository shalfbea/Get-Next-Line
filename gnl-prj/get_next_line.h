/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:11:30 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/28 23:06:10 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <libgen.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef OPEN_MAX
#  ifdef FOPEN_MAX
#   define OPEN_MAX FOPEN_MAX
#  endif
#  ifndef FOPEN_MAX
#   define OPEN_MAX 1000
#  endif
# endif

typedef struct s_list
{
	char			content[BUFFER_SIZE];
	struct s_list	*next;
}	t_list;
char	*get_next_line(int fd);

char	*free_res(char **res);
int		gnl_read_file(int fd, char buffer[BUFFER_SIZE + 1]);
int		gnl_realloc(char **res, size_t *cur_len, size_t *max_len);
void	gnl_prev_buffer(char buffer[BUFFER_SIZE + 1],
			int end, int bytes_read);
#endif
