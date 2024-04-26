/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evdos-sa <evdos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:19:17 by nneto-de          #+#    #+#             */
/*   Updated: 2024/01/27 11:07:45 by evdos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_status;

int	main(int ac, char **av, char **envp)
{
	t_minishell	ms;

	(void) av;
	if (ac > 1)
	{
		printf("This project just takes 1 argument!\n");
		return (1);
	}
	ft_bzero(&ms, sizeof(t_minishell));
	ms.envp = envp;
	ft_init_env(&ms.env_lst, ms.envp);
	ms.paths = ft_path(ms.env_lst);
	ft_iniciar(&ms);
}

void	ft_iniciar(t_minishell *ms)
{
	while (1)
	{
		ft_signals();
		ms->input = readline("minishell> ");
		if (ms->input == NULL)
			ft_libertar_memoria(ms, NO, YES);
		add_history(ms->input);
		ft_handler_especial(ms->input);
		if (ft_espacos(ms->input) == FALSE)
		{
			ms->n_pipes = 0;
			ms->core_dump = 0;
			ms->file_error = 0;
			if (ft_parsering(ms, ms->input) == EXIT_SUCCESS)
			{
				ft_signals_child(ms);
				ft_exec(ms);
				if (ms->n_pipes > 0)
					ft_libertar_pipes(ms);
				unlink(".heredoc");
			}
			ft_libertar_memoria(ms, NO, NO);
		}
	}
	rl_clear_history();
}

void	ft_handler_especial(char *input)
{
	if (input[0] == '$' && input[1] == '?')
	{
		if (input[2] == '+' && input[3] == '$' && input[4] == '?')
		{
			printf("%i+%i: command not found\n", g_exit_status, g_exit_status);
			g_exit_status = 127;
		}
	}
}

void	ft_libertar_memoria(t_minishell *ms, int free_pipes, int exit_flag)
{
	if (ms->input == NULL)
		printf("exit\n");
	free(ms->input);
	ft_libertar_lista_token(&ms->token_lst);
	ft_libertar_lista_cmd(&ms->cmd_lst);
	if (free_pipes == YES && ms->n_pipes > 0)
		ft_libertar_pipes(ms);
	if (exit_flag == YES)
	{
		ft_libertar_env_lista(&ms->env_lst);
		ft_libertar_str_array(ms->paths);
		exit (g_exit_status);
	}
}
