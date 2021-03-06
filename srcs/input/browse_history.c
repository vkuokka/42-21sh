/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:08:46 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/27 14:46:14 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "keyboard.h"

/*
** Moves history to older entry and replaces current
** command with the contents of that history node.
*/

static void	browse_up(t_terminal *term)
{
	if (term->h_head)
	{
		if (!term->h_current)
			term->h_current = term->h_head;
		else if (term->h_current->next)
			term->h_current = term->h_current->next;
		if (term->h_current->content_size <= ARG_MAX)
		{
			ft_bzero(term->in->string, ft_strlen(term->in->string));
			ft_memmove(term->in->string, term->h_current->content, \
			term->h_current->content_size);
			term->in->index = term->h_current->content_size - 1;
		}
	}
}

/*
** Moves history to newer entry and replaces current
** command with the contents of that history node.
*/

static void	browse_down(t_terminal *term)
{
	if (term->h_current)
	{
		if (!term->h_current->prev)
		{
			ft_bzero(term->in->string, ft_strlen(term->in->string));
			term->in->index = 0;
			term->h_current = NULL;
			return ;
		}
		if (term->h_current->content_size <= ARG_MAX)
		{
			term->h_current = term->h_current->prev;
			ft_bzero(term->in->string, ft_strlen(term->in->string));
			ft_memmove(term->in->string, term->h_current->content, \
			term->h_current->content_size);
			term->in->index = term->h_current->content_size - 1;
		}
	}
}

/*
** Searches command history entries for matching string.
*/

static int	find_match(t_terminal *term, char *str)
{
	t_dlist	*current;

	if (!str[0])
		return (1);
	current = term->h_head;
	while (current)
	{
		if (ft_strstr(current->content, str) \
		&& current->content_size <= ARG_MAX)
		{
			init_input(term->in);
			ft_memmove(term->in->string, current->content, \
			current->content_size);
			term->in->index = current->content_size - 1;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

/*
** Initializes reverse-i-search and waits for the user input.
** If input is anything else than printable or backspace
** character, the function will exit while loop and return
** into normal editor state.
*/

static void	search_history(t_terminal *term)
{
	char	str[ARG_MAX];
	int		sum;

	ft_bzero(str, ARG_MAX);
	tputs(tgetstr("cr", NULL), 1, print_char);
	tputs(tgetstr("sc", NULL), 1, print_char);
	while (term)
	{
		find_match(term, str) ? ft_printf("(reverse-i-search)`%s': ", str)
		: ft_printf("(failed reverse-i-search)`%s': ", str);
		ft_putstr(term->in->string);
		sum = listen_keys();
		tputs(tgetstr("rc", NULL), 1, print_char);
		tputs(tgetstr("cd", NULL), 1, print_char);
		if (term->in->sigint)
			break ;
		if (sum == BACK && str[0])
			str[ft_strlen(str) - 1] = '\0';
		else if (ft_isprint(sum) && ft_strlen(str) < ARG_MAX)
			str[ft_strlen(str)] = sum;
		else if (!ft_isprint(sum) && sum != BACK)
			return ;
	}
	term->in->sigint ? init_input(term->in) : 0;
}

void		browse_history(t_terminal *term, int sum)
{
	if (sum == UP)
		browse_up(term);
	else if (sum == DOWN)
		browse_down(term);
	else if (sum == CTRL_R)
		search_history(term);
}
