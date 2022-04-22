/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 20:47:40 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/21 20:35:53 by afaustin         ###   ########.fr       */
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
		ft_putendl_fd("bash: syntax error: unexpected end of file", 2);
		ft_putendl_fd("exit", 2);
		g_tudao.ext_routine.code = 2;
		g_tudao.exit = true;
	}
}

void	display_cmd_prompt(void)
{
	char	*curr_path;
	char	*prompt;

	curr_path = getcwd(NULL, 0);
	prompt = ft_strjoin(curr_path, " $ ");
	set_signal_hook(SIGINT, catch_signal_parent, &g_tudao.action);
	dup2(g_tudao.backup_stdin, STDIN_FILENO);
	g_tudao.prompt_input = readline(prompt);
	if (g_tudao.prompt_input)
	{
		g_tudao.line_count++;
		process_input(g_tudao.prompt_input);
		while (g_tudao.token_list && !g_tudao.exit && !g_tudao.syntax_error
			&& !g_tudao.skip_execution
			&& is_pipe_and_or((char *)ft_lst_last(g_tudao.token_list)->content))
			assemble_line(&g_tudao.prompt_input);
	}
	else
	{
		ft_putendl_fd("exit", 2);
		g_tudao.exit = true;
	}
	disable_signal(SIGINT, &g_tudao.action);
	ft_free_ptr((void *)&curr_path);
	ft_free_ptr((void *)&prompt);
}
