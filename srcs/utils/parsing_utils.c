/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evdos-sa <evdos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:11:34 by evdos-sa          #+#    #+#             */
/*   Updated: 2024/01/27 11:11:36 by evdos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_verificar_espacos(char c);
int		ft_simbolo(char c);
int		ft_contar_aspas(char *s);
int		ft_aspas_simples(char *cmd, char *stop);
int		ft_aspas_duplas(char *cmd, char *stop);

int	ft_verificar_espacos(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f')
		return (YES);
	return (NO);
}

int	ft_simbolo(char c)
{
	if (c == '\"' || c == '\'' || c == '@' || c == '*' || c == '!')
		return (1);
	else if (c == '.' || c == ',' || c == '+' || c == '%' || c == '='
		|| c == '~' || c == '^' || c == '/')
		return (2);
	else
		return (0);
}

int	ft_contar_aspas(char *s)
{
	int		i;
	int		n_quotes;
	int		in_squote;
	int		in_dquote;

	i = 0;
	n_quotes = 0;
	in_squote = 0;
	in_dquote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && in_dquote == 0)
		{
			in_squote = 1 - in_squote;
			n_quotes++;
		}
		else if (s[i] == '"' && in_squote == 0)
		{
			in_dquote = 1 - in_dquote;
			n_quotes++;
		}
		i++;
	}
	return (n_quotes);
}

int	ft_aspas_simples(char *cmd, char *stop)
{
	int		i;
	int		n_squotes;
	int		in_squote;
	int		in_dquote;

	i = 0;
	n_squotes = 0;
	in_squote = 0;
	in_dquote = 0;
	while (cmd[i] && &cmd[i] != stop)
	{
		if (cmd[i] == '\'' && in_dquote == 0)
		{
			in_squote = 1 - in_squote;
			n_squotes++;
		}
		else if (cmd[i] == '"' && in_squote == 0)
			in_dquote = 1 - in_dquote;
		i++;
	}
	if (n_squotes % 2 == 0)
		return (NO);
	return (YES);
}

int	ft_aspas_duplas(char *cmd, char *stop)
{
	int		i;
	int		n_dquotes;
	int		in_squote;
	int		in_dquote;

	i = 0;
	n_dquotes = 0;
	in_squote = 0;
	in_dquote = 0;
	while (cmd[i] && &cmd[i] != stop)
	{
		if (cmd[i] == '"' && in_squote == 0)
		{
			in_dquote = 1 - in_dquote;
			n_dquotes++;
		}
		else if (cmd[i] == '\'' && in_dquote == 0)
			in_squote = 1 - in_squote;
		i++;
	}
	if (n_dquotes % 2 == 0)
		return (NO);
	return (YES);
}
