/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalfbea <shalfbea@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:00:13 by shalfbea          #+#    #+#             */
/*   Updated: 2021/10/28 23:36:44 by shalfbea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	char	*s;
	int		file;
	size_t	i;

	file = open("file4read.txt", O_RDONLY);
	i = 0;
	while (i++ < 10)
	{
		s = get_next_line(file);
		printf("%s;", s);
		free(s);
	}
	close(file);
}
