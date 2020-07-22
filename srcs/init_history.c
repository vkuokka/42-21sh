/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:21:06 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/22 15:53:27 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "get_next_line.h"

void		init_history(t_terminal *term)
{
	int		fd;
	char	*line;
	t_dlist	*node;
	int		count;

	fd = open(HISTFILE, O_RDONLY);
	if (fd == -1)
		return ;
	node = NULL;
	count = 0;
	while (count < HISTSIZE && get_next_line(fd, &line))
	{
		node = ft_dlstnew(line, ft_strlen(line) + 1);
		free(line);
		ft_dlstaddback(&term->h_head, node);
		count++;
	}
	term->h_tail = node;
	close(fd);
}
