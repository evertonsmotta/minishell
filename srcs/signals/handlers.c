/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneto-de <nneto-de@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:19:17 by nneto-de          #+#    #+#             */
/*   Updated: 2024/01/26 22:11:02 by nneto-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_libertar_heredoc(int signum, t_minishell *ms)
{
	static t_minishell	*h;

	if (!signum && ms)
	{
		h = ms;
		return ;
	}
	if (signum == SIGINT)
	{
		if (h->n_pipes > 0)
			ft_libertar_memoria(h, YES, YES);
		else
			ft_libertar_memoria(h, NO, YES);
	}
}

void	ft_handler_sigint(int signum)
{
	if (signum != SIGINT)
		return ;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 130;
}

void	ft_handler_heredoc(int signum)
{
	g_exit_status = 130;
	ft_libertar_heredoc(signum, NULL);
}

void	ft_handler_child(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		return ;
	}
	else if (signum == SIGQUIT)
		g_exit_status = 128 + signum;
}
