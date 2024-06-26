/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneto-de <nneto-de@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:19:17 by nneto-de          #+#    #+#             */
/*   Updated: 2024/01/26 22:09:10 by nneto-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(t_minishell *ms, t_cmd *curr)
{
	int	i;

	i = 0;
	g_exit_status = 0;
	if (curr->args[1] == NULL)
	{
		printf("\n");
		ft_libertar_memoria(ms, YES, YES);
	}
	if (ft_validar_cmd_option(curr->args) == FALSE)
		ft_libertar_memoria(ms, YES, YES);
	i = ft_get_start_index(curr->args);
	while (curr->args[++i])
	{
		i += ft_tilde_expander(ms, curr, i);
		if (curr->args[i][0] != '~')
			ft_print_argument(curr->args[i]);
		if (curr->args[i + 1])
			printf(" ");
	}
	if (ft_get_start_index(curr->args) == 0)
		printf("\n");
	ft_libertar_memoria(ms, YES, YES);
}

int	ft_get_start_index(char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i])
	{
		if (args[i][0] != '-' || args[i][1] != 'n')
			break ;
		else if (args[i][0] == '-' && args[i][1] == 'n')
		{
			j = 2;
			while (args[i][j])
			{
				if (args[i][j] != 'n')
					return (i - 1);
				j++;
			}
		}
		i++;
	}
	return (i - 1);
}

int	ft_tilde_expander(t_minishell *ms, t_cmd *curr, int i)
{
	char	*home;
	char	**args;

	home = ft_find_env(ms->env_lst, "HOME");
	args = curr->args;
	if (args[i][0] != '~')
		return (0);
	if (args[i][1] == '\0')
		printf("%s", home);
	else if (args[i][1] == '-' && (args[i][2] == '\0' || args[i][2] == '/'))
		printf("%s%s", ft_find_env(ms->env_lst, "OLDPWD"), args[i] + 2);
	else if (args[i][1] == '+' && (args[i][2] == '\0' || args[i][2] == '/'))
		printf("%s%s", ft_find_env(ms->env_lst, "PWD"), args[i] + 2);
	else if (args[i][1] == '/')
		printf("%s%s", home, args[i] + 1);
	else
		printf("%s", args[i]);
	if (args[i + 1])
		return (1);
	return (0);
}

void	ft_print_argument(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1] == '\\')
			i++;
		printf("%c", s[i]);
		i++;
	}
}
