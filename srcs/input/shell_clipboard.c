/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_clipboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:44:32 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/02 18:45:02 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "keyboard.h"

static void	cut_after(t_terminal *term)
{
	ft_bzero(term->clipboard, ARG_MAX);
	ft_strcat(term->clipboard, term->in->string + term->in->index);
	ft_bzero(term->in->string + term->in->index, \
	ARG_MAX - term->in->index);
	term->in->index = ft_strlen(term->in->string);
}

static void	cut_before(t_terminal *term)
{
	ft_bzero(term->clipboard, ARG_MAX);
	ft_strncat(term->clipboard, term->in->string, \
	term->in->index);
	ft_memmove(term->in->string, term->in->string + term->in->index, \
	ARG_MAX - term->in->index);
	term->in->index = 0;
}

static void	paste_buffer(t_terminal *term)
{
	char	*tmp1;
	char	*tmp2;
	size_t	len;

	if (!term->clipboard[0])
		return ;
	tmp1 = ft_strreplace(term->clipboard, "\n", " ");
	tmp2 = ft_strreplace(tmp1, "\t", "    ");
	len = ft_strlen(tmp2);
	if (len < ARG_MAX)
	{
		ft_memmove(term->in->string + term->in->index + len, \
		term->in->string + term->in->index, ft_strlen(term->in->string) + term->in->index);
		ft_memmove(term->in->string + term->in->index, tmp2, len);
		term->in->index += len;
	}
	free(tmp1);
	free(tmp2);
}

void		shell_clipboard(t_terminal *term, int sum)
{
	if (sum == CTRL_K)
		cut_after(term);
	else if (sum == CTRL_U)
		cut_before(term);
	else if (sum == CTRL_Y)
		paste_buffer(term);
}