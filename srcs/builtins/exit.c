/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneto-de <nneto-de@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:19:17 by nneto-de          #+#    #+#             */
/*   Updated: 2024/01/27 06:24:57 by nneto-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_minishell *ms, t_cmd *curr)
{
	if (ms->n_pipes == 0)
		printf("exit\n");
	if (curr->args[1] && ft_is_num(curr->args[1]) == YES && curr->args[2])
		return (ft_builtin_error(ms, curr, E_ARGS, 1));
	if (curr->args[1] && ft_is_num(curr->args[1]) == NO)
	{
		ft_builtin_error(ms, curr, curr->args[1], 2);
		ft_libertar_memoria(ms, YES, YES);
	}
	if (curr->args[1] && ft_is_num(curr->args[1]) == YES)
	{
		if (curr->args[1][0] == '-')
			g_exit_status = 256 - ft_atoi(curr->args[1] + 1);
		else
			g_exit_status = ft_atoi(curr->args[1]);
		ft_libertar_memoria(ms, YES, YES);
	}
	if (curr->has_heredoc == 1)
		unlink(".heredoc");
	ft_libertar_memoria(ms, YES, YES);
}

int	ft_is_num(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[1] && (s[i] == '-' || s[i] == '+'))
		{
			if (i != 0)
				return (NO);
			i++;
		}
		if (ft_isdigit(s[i]) == 0)
			return (NO);
		i++;
	}
	return (YES);
}
