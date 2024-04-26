/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneto-de <nneto-de@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:19:17 by nneto-de          #+#    #+#             */
/*   Updated: 2024/01/26 21:59:52 by nneto-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_parsering(t_minishell *ms, char *input)
{
	if (ft_verificar_aspas(input) == ERROR_FOUND)
		return (EXIT_FAILURE);
	ft_tokenizer(ms, input);
	if (ft_verificar_sintax(ms, ms->token_lst) == ERROR_FOUND)
		return (EXIT_FAILURE);
	ft_expander(ms, ms->token_lst);
	ft_remover_aspas(ms);
	if (ft_command_table_creator(ms) == EXIT_NO_CMD)
		return (EXIT_NO_CMD);
	return (EXIT_SUCCESS);
}

int	ft_verificar_aspas(char *input)
{
	int		n_quotes;

	n_quotes = ft_contar_aspas(input);
	if (n_quotes % 2 != 0)
	{
		g_exit_status = 2;
		printf("Error: unclosed quotes\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	ft_remover_aspas(t_minishell *ms)
{
	int		i;
	int		new_len;
	char	*old_cmd;
	t_token	*curr;

	i = 0;
	new_len = 0;
	old_cmd = NULL;
	curr = ms->token_lst;
	while (curr)
	{
		if (curr->type == T_OTHER && ft_contar_aspas(curr->content) > 0)
		{
			old_cmd = curr->content;
			new_len = ft_strlen(curr->content) - ft_contar_aspas(curr->content);
			curr->content = ft_remove_quotes(curr->content, new_len, i);
			free(old_cmd);
		}
		curr = curr->next;
	}
}

char	*ft_remove_quotes(char *cmd, int new_len, int i)
{
	int		in_squote;
	int		in_dquote;
	char	*new_cmd;

	in_squote = 0;
	in_dquote = 0;
	new_cmd = ft_calloc(new_len + 1, sizeof(char));
	if (!new_cmd)
		return (NULL);
	while (i < new_len)
	{
		if ((*cmd == '\'' && !in_dquote) || (*cmd == '\"' && !in_squote))
		{
			if (*cmd == '\'' && in_dquote == 0)
				in_squote = 1 - in_squote;
			else if (*cmd == '\"' && in_squote == 0)
				in_dquote = 1 - in_dquote;
			cmd++;
		}
		else
			new_cmd[i++] = *cmd++;
	}
	new_cmd[i] = '\0';
	return (new_cmd);
}
