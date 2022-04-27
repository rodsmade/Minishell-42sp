/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 20:47:40 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/27 21:24:21 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(char *string)
{
	create_token_list(string);
	expand_tokens(g_tudao.token_list);
	parse_tokens();
	return ;
}

static void	assemble_line(char **line_read)
{
	char	*aux_str;
	char	*temp;

	set_signal_hook(SIGINT, catch_signal_parent_extra_input, &g_tudao.action);
	aux_str = readline("> ");
	if (aux_str && !g_tudao.skip_execution)
	{
		g_tudao.line_count++;
		temp = aux_str;
		aux_str = ft_strjoin(" ", aux_str);
		ft_free_ptr((void *)&temp);
		temp = (*line_read);
		(*line_read) = ft_strjoin((*line_read), aux_str);
		process_input(aux_str);
		ft_free_ptr((void *)&aux_str);
		ft_free_ptr((void *)&temp);
	}
	else if (!aux_str && g_tudao.is_ctrl_d)
	{
		ft_putendl_fd("minishell: syntax error: unexpected end of file", 2);
		ft_putendl_fd("exit", 2);
		g_tudao.exit.code = 2;
		g_tudao.exit.flag = true;
	}
}

static char	*string_prompt(void)
{
	char	*curr_path;
	char	*curr_path_f;
	char	*dollar_sign_f;
	char	*prompt;

	curr_path = getcwd(NULL, 0);
	curr_path_f = ft_strjoin_3(BHBLU, curr_path, COLOR_RESET);
	ft_free_ptr((void *)&curr_path);
	dollar_sign_f = ft_strjoin_3(BWHT, " $ ", COLOR_RESET);
	prompt = ft_strjoin(curr_path_f, dollar_sign_f);
	ft_free_ptr((void *)&curr_path_f);
	ft_free_ptr((void *)&dollar_sign_f);
	return (prompt);
}

void	display_cmd_prompt(void)
{
	char	*prompt;

	dup2(g_tudao.backup_stdin, STDIN_FILENO);
	set_signal_hook(SIGINT, catch_signal_parent, &g_tudao.action);
	prompt = string_prompt();
	g_tudao.prompt_input = readline(prompt);
	ft_free_ptr((void *)&prompt);
	if (g_tudao.prompt_input)
	{
		g_tudao.line_count++;
		process_input(g_tudao.prompt_input);
		while (g_tudao.token_list && !g_tudao.exit.flag && !g_tudao.syntax_error
			&& !g_tudao.skip_execution
			&& is_pipe_and_or((char *)ft_lst_last(g_tudao.token_list)->content))
			assemble_line(&g_tudao.prompt_input);
	}
	else
	{
		ft_putendl_fd("exit", 2);
		g_tudao.exit.flag = true;
	}
	disable_signal(SIGINT, &g_tudao.action);
}
