/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evdos-sa <evdos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:19:17 by nneto-de          #+#    #+#             */
/*   Updated: 2024/01/27 11:07:15 by evdos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_expander(t_minishell *ms, t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr)
	{
		if (curr->prev && !ft_strcmp(curr->prev->content, "<<"))
			return ;
		if (curr->content[0] == '$'
			&& (!curr->content[1] || curr->content[1] == ' '))
			return ;
		if (curr->content[0] == '$' && ft_simbolo(curr->content[1]) == 2)
			return ;
		if (curr->type == T_OTHER)
			ft_expand_command(ms, curr);
		if (ft_strlen(curr->content) == 0)
			curr->type = T_EMPTY;
		curr = curr->next;
	}
}

void	ft_expand_command(t_minishell *ms, t_token *tkn)
{
	char	*tmp;
	char	*key;
	char	*value;

	while (ft_strchr(tkn->content, '$') != NULL)
	{
		if (ft_aspas_simples(tkn->content, ft_strchr(tkn->content, '$')) == YES)
			return ;
		if ((ft_aspas_duplas(tkn->content, ft_strchr(tkn->content, '$')) == YES)
			&& (!(ft_strcmp(tkn->content, "\"$\""))))
			return ;
		key = ft_get_key(tkn->content);
		if (ft_strncmp(key, "$?", 2) == 0)
			value = ft_itoa(g_exit_status);
		else
			value = ft_get_env_value(&ms->env_lst, key);
		tmp = tkn->content;
		tkn->content = ft_replace_content(tkn->content, key, value);
		free(tmp);
		free(key);
		free(value);
	}
}

char	*ft_get_key(char *cmd)
{
	int		len;
	char	*tmp;

	len = 0;
	tmp = ft_strnstr(cmd, "$", ft_strlen(cmd));
	if (tmp == NULL)
		return (NULL);
	if (tmp[1] == '?')
		return (ft_strdup("$?"));
	if (ft_simbolo(tmp[1]) == 1)
		len++;
	while (ft_isalnum(tmp[len + 1]) != 0 || tmp[len + 1] == '_')
		len++;
	return (ft_substr(tmp, 0, len + 1));
}

char	*ft_get_env_value(t_env **env_lst, char *key)
{
	t_env	*current;

	current = *env_lst;
	if (env_lst == NULL || key == NULL)
		return (NULL);
	if (key[0] == '$')
		key++;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (current->value == NULL)
				return (ft_strdup(""));
			return (ft_strdup(current->value));
		}
		current = current->next;
	}
	return (ft_strdup(""));
}

char	*ft_replace_content(char *cmd, char *key, char *value)
{
	char	*key_ptr;
	char	*new_cmd;
	int		new_len;

	if (ft_isalnum(key[1]) == 1 || ft_simbolo(key[1]) == 1)
		return (ft_strdup(key + 2));
	if (!cmd || !key || !value)
		return (NULL);
	new_len = ft_strlen(cmd) - ft_strlen(key) + ft_strlen(value);
	new_cmd = ft_calloc(new_len + 1, sizeof(char));
	if (!new_cmd)
		return (NULL);
	key_ptr = ft_strnstr(cmd, key, ft_strlen(cmd));
	if (!key_ptr)
		return (NULL);
	ft_strlcpy(new_cmd, cmd, ft_strlen(cmd) - ft_strlen(key_ptr) + 1);
	ft_strlcat(new_cmd, value, new_len + 1);
	ft_strlcat(new_cmd, key_ptr + ft_strlen(key), new_len + 1);
	return (new_cmd);
}
