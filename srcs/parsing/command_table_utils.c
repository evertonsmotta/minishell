/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneto-de <nneto-de@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:19:17 by nneto-de          #+#    #+#             */
/*   Updated: 2024/01/26 22:03:08 by nneto-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*ft_new_cmd(t_token *first, int n_args)
{
	t_cmd	*new_cmd;
	t_token	*cur_tkn;

	cur_tkn = first;
	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = ft_get_args(first, n_args);
	new_cmd->cmd = ft_strdup(new_cmd->args[0]);
	new_cmd->f_redin = ft_add_files(first, T_FILE_IN, T_HEREDOC);
	new_cmd->f_redout = ft_add_files(first, T_FILE_TR, T_FILE_AP);
	new_cmd->t_redin = ft_add_types(first, T_FILE_IN, T_HEREDOC);
	new_cmd->t_redout = ft_add_types(first, T_FILE_TR, T_FILE_AP);
	while (cur_tkn && cur_tkn->type != T_PIPE)
	{
		if (cur_tkn->type == T_REDIR2_IN)
			new_cmd->has_heredoc = YES;
		cur_tkn = cur_tkn->next;
	}
	new_cmd->fd_in = STDIN_FILENO;
	new_cmd->fd_out = STDOUT_FILENO;
	new_cmd->index = 0;
	new_cmd->next = NULL;
	return (new_cmd);
}

char	**ft_get_args(t_token *first, int n_args)
{
	int		i;
	char	**args;
	t_token	*curr;

	i = 0;
	curr = first;
	args = (char **)ft_calloc(n_args + 1, sizeof(char *));
	if (!args)
		return (NULL);
	while (curr && curr->type != T_PIPE)
	{
		if (curr->type == T_COMMAND)
		{
			args[i] = ft_strdup(curr->content);
			i++;
		}
		curr = curr->next;
	}
	args[i] = NULL;
	return (args);
}

char	**ft_add_files(t_token *first, t_type type1, t_type type2)
{
	int		i;
	int		n_redirs;
	char	**redirs;
	t_token	*curr;

	i = 0;
	n_redirs = ft_contar_redir(first, type1, type2);
	redirs = (char **)ft_calloc(n_redirs + 1, sizeof(char *));
	if (!redirs)
		return (NULL);
	curr = first;
	while (curr && curr->type != T_PIPE)
	{
		if (curr->type == type1 || curr->type == type2)
		{
			redirs[i] = ft_strdup(curr->content);
			i++;
		}
		curr = curr->next;
	}
	redirs[i] = NULL;
	return (redirs);
}

int	*ft_add_types(t_token *first, t_type type1, t_type type2)
{
	int		i;
	int		n_redirs;
	int		*types;
	t_token	*curr;

	i = 0;
	n_redirs = ft_contar_redir(first, type1, type2);
	types = (int *)ft_calloc(n_redirs + 1, sizeof(int));
	if (!types)
		return (NULL);
	curr = first;
	while (curr && curr->type != T_PIPE)
	{
		if (curr->type == type1 || curr->type == type2)
		{
			types[i] = curr->type;
			i++;
		}
		curr = curr->next;
	}
	types[i] = 0;
	return (types);
}

void	ft_add_cmd_back(t_cmd **cmd_table, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!*cmd_table)
	{
		*cmd_table = new_cmd;
		return ;
	}
	current = *cmd_table;
	while (current && current->next)
		current = current->next;
	current->next = new_cmd;
}
