/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evdos-sa <evdos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:11:25 by evdos-sa          #+#    #+#             */
/*   Updated: 2024/01/27 11:11:29 by evdos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	ft_validar_cmd_option(char **args)
{
	if (args[1] && args[1][0] == '-')
	{
		if (!ft_strcmp(args[0], "cd"))
		{
			if (ft_strlen(args[1]) == 1)
				return (TRUE);
			if (ft_strlen(args[1]) == 2 && args[1][1] == '-')
				return (TRUE);
		}
		if (!ft_strcmp(args[0], "echo")
			&& (args[1][1] != 'e' && args[1][1] != 'E'))
			return (TRUE);
		g_exit_status = 2;
		dup2(STDERR_FILENO, STDOUT_FILENO);
		if (!ft_strcmp(args[0], "env"))
			printf("env: invalid option -- '%c'\n", args[1][1]);
		else
			printf("minishell: %s: -%c: invalid option\n", args[0], args[1][1]);
		return (FALSE);
	}
	return (TRUE);
}

void	ft_builtin_error(t_minishell *ms, t_cmd *curr, char *err, int ex_code)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (err)
	{
		if (!ft_strcmp(err, E_FILE))
			printf("minishell: %s: %s: %s\n", curr->cmd, curr->args[1], err);
		else if (!ft_strcmp(curr->cmd, "export"))
			printf("minishell: %s: '%s': %s\n", curr->cmd, err, E_EXPORT);
		else if (!ft_strcmp(curr->cmd, "exit") && ex_code == 1)
			printf("minishell: %s: %s\n", curr->cmd, err);
		else if (!ft_strcmp(curr->cmd, "exit") && ex_code == 2)
			printf("minishell: %s: %s: %s\n", curr->cmd, err, E_NUM);
		else
			printf("minishell: %s: %s\n", curr->cmd, err);
	}
	g_exit_status = ex_code;
	if (ms->n_pipes > 0)
		ft_libertar_memoria(ms, YES, YES);
}

char	*ft_find_env(t_env *env_lst, char *find)
{
	t_env	*current;

	current = env_lst;
	while (current)
	{
		if (!ft_strcmp(current->key, find))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	ft_update_env(t_env **env_lst, char *key, char *update)
{
	t_env	*current;

	current = *env_lst;
	while (current->next)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(current->key)))
		{
			free(current->value);
			current->value = update;
			break ;
		}
		current = current->next;
	}
}
