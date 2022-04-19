/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 20:47:40 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/19 22:25:38 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assemble_line(char **line_read)
{
	char	*aux_str;
	char	*temp;

	set_signal(SIGINT, catch_signals_extra_input, &g_tudao.action);
	aux_str = readline("> ");
	printf("aux string: %s\n", aux_str);
	if (aux_str && !g_tudao.skip_execution)
	{
		g_tudao.line_count++;
		temp = aux_str;
		aux_str = ft_strjoin(" ", aux_str);
		ft_free_ptr((void *)&temp);
		temp = (*line_read);
		(*line_read) = ft_strjoin((*line_read), aux_str);
		lexer_line(aux_str);
		expand_tokens();
		parse_tokens();
		ft_free_ptr((void *)&aux_str);
		ft_free_ptr((void *)&temp);
		// printf("até o momento: %s\n", (*line_read));
	}
	else if (!aux_str && g_tudao.is_ctrl_d)
	{
		ft_putendl_fd("bash: syntax error: unexpected end of file", 2);
		ft_putendl_fd("exit", 2);
		g_tudao.ext_routine.code = 2;
		g_tudao.exit = true;
	}
	unset_signal(SIGINT, &g_tudao.action);
}

void	display_cmd_prompt(void)
{
	char	*curr_path;
	char	*prompt;

	curr_path = getcwd(NULL, 0);
	prompt = ft_strjoin(curr_path, " $ ");
	set_signal(SIGINT, catch_signals_parent, &g_tudao.action);
	g_tudao.prompt_input = readline(prompt);
	if (g_tudao.prompt_input)
	{
		g_tudao.line_count++;
		lexer_line(g_tudao.prompt_input);
		expand_tokens();
		parse_tokens();
		while (g_tudao.token_list && !g_tudao.exit && !g_tudao.syntax_error
			&& is_pipe_and_or((char *)ft_lst_last(g_tudao.token_list)->content)
			&& !g_tudao.skip_execution)
			assemble_line(&g_tudao.prompt_input);
		printf("[DEBUG] gtudao.prompt input: %s\n", g_tudao.prompt_input);
	}
	else
	{
		ft_putendl_fd("exit", 2);
		g_tudao.ext_routine.code = 0;
		g_tudao.exit = true;
	}
	unset_signal(SIGINT, &g_tudao.action);
	ft_free_ptr((void *)&curr_path);
	ft_free_ptr((void *)&prompt);
}
