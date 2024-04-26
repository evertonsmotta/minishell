/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneto-de <nneto-de@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:19:17 by nneto-de          #+#    #+#             */
/*   Updated: 2024/01/26 22:09:10 by nneto-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_minishell *ms, t_cmd *cur)
{
	t_env	*env;

	env = ms->env_lst;
	if (ft_validar_cmd_option(cur->args) == FALSE)
		g_exit_status = 125;
	else if (cur->args[1])
		ft_builtin_error(ms, cur, E_FILE, 127);
	else
	{
		while (env)
		{
			if (env->value)
				printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
		g_exit_status = 0;
	}
	ft_libertar_memoria(ms, YES, YES);
}
