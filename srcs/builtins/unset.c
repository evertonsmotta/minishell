/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneto-de <nneto-de@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:19:17 by nneto-de          #+#    #+#             */
/*   Updated: 2024/01/26 22:10:27 by nneto-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_minishell *ms, t_cmd *curr)
{
	int		i;
	t_env	*e;
	t_env	*p;

	i = 0;
	e = ms->env_lst;
	p = NULL;
	if (curr->args[1] == NULL)
		return (ft_builtin_error(ms, curr, NULL, 0));
	if (!ft_validar_cmd_option(curr->args))
		return (ft_builtin_error(ms, curr, NULL, 2));
	while (curr->args[i])
	{
		if (!ft_verificar_args(curr->args[i], NO))
			break ;
		i++;
	}
	ft_unset_unset(ms, curr, e, p);
	g_exit_status = 0;
	if (ms->n_pipes != 0)
		ft_libertar_memoria(ms, YES, YES);
}

void	ft_unset_unset(t_minishell *m, t_cmd *c, t_env *e, t_env *p)
{
	int	i;

	i = 0;
	while (c->args[++i])
	{
		e = m->env_lst;
		while (e)
		{
			if (!ft_strcmp(c->args[i], e->key))
			{
				if (c->args[i][0] == '=')
					break ;
				if (p == NULL)
					m->env_lst = e->next;
				else
					p->next = e->next;
				free(e->key);
				free(e->value);
				free(e);
				break ;
			}
			p = e;
			e = e->next;
		}
	}
}

void	ft_export_unset(t_minishell *ms, char *arg)
{
	t_env	*e;
	t_env	*p;

	e = ms->env_lst;
	p = NULL;
	while (e)
	{
		if (!strncmp(e->key, arg, ft_strlen(e->key)))
		{
			if (ft_strchr(arg, '=') == NULL && e->value)
				break ;
			if (p == NULL)
				ms->env_lst = e->next;
			else
				p->next = e->next;
			free(e->key);
			free(e->value);
			free(e);
			break ;
		}
		p = e;
		e = e->next;
	}
}
