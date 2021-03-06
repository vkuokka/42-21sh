/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:09:26 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/23 22:52:52 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "keyboard.h"

static void		cursor_position(t_terminal *term, size_t len)
{
	size_t	cursor;
	size_t	count;

	count = len / term->size.ws_col;
	tputs(tgetstr("cr", NULL), 1, print_char);
	while (count--)
		tputs(tgetstr("up", NULL), 1, print_char);
	cursor = -1;
	while (++cursor != term->in->index + ft_strlen(term->in->prompt))
	{
		if (cursor / term->size.ws_col && !(cursor % term->size.ws_col))
			tputs(tgetstr("do", NULL), 1, print_char);
		tputs(tgetstr("nd", NULL), 1, print_char);
	}
	if (cursor / term->size.ws_col && !(cursor % term->size.ws_col))
		tputs(tgetstr("do", NULL), 1, print_char);
}

void			print_input(t_terminal *term)
{
	size_t		count;
	size_t		len;

	len = ft_strlen(term->in->string) + ft_strlen(term->in->prompt) - 1;
	count = term->in->line;
	tputs(tgetstr("cr", NULL), 1, print_char);
	while (count-- && len > term->size.ws_col * count)
		tputs(tgetstr("up", NULL), 1, print_char);
	tputs(tgetstr("cd", NULL), 1, print_char);
	ft_putstr(term->in->prompt);
	ft_putstr(term->in->string);
	tputs(tgetstr("sc", NULL), 1, print_char);
	cursor_position(term, len);
	term->in->line = (term->in->index + ft_strlen(term->in->prompt)) \
	/ term->size.ws_col;
}
