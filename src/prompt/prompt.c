/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 20:47:40 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(char *string)
{
	create_token_list(string);
	expand_tokens(g_data.token_list);
	parse_tokens();
	return ;
}

static void	assemble_line(char **line_read)
{
	char	*aux_str;
	char	*temp;

	set_signal_hook(SIGINT, sighandler_parent_extra_input, &g_data.action);
	aux_str = readline("> ");
	if (aux_str && !g_data.skip_execution)
	{
		g_data.line_count++;
		temp = aux_str;
		aux_str = ft_strjoin(" ", aux_str);
		ft_free_ptr((void *)&temp);
		temp = (*line_read);
		(*line_read) = ft_strjoin((*line_read), aux_str);
		process_input(aux_str);
		ft_free_ptr((void *)&aux_str);
		ft_free_ptr((void *)&temp);
	}
	else if (!aux_str && g_data.is_ctrl_d)
		print_syntax_error_exit();
}

static char	*getcwd_home_expanded(void)
{
	char	*cwd;
	char	*home_var;
	char	*cwd_home_expanded;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		g_data.exit.flag = true;
		return (NULL);
	}
	home_var = g_data.home_at_start;
	if (home_var && ft_strncmp(cwd, home_var, ft_strlen(home_var)) == 0)
	{
		cwd_home_expanded = ft_strjoin("~", &cwd[ft_strlen(home_var)]);
		ft_free_ptr((void *)&cwd);
		return (cwd_home_expanded);
	}
	return (cwd);
}

static char	*string_prompt(void)
{
	char	*arrow;
	char	*curr_path[3];
	char	*brackets[2];
	char	*prompt[2];

	curr_path[0] = getcwd_home_expanded();
	curr_path[1] = ft_strjoin_3(LILACB, curr_path[0], COLOUR_RESET);
	ft_free_ptr((void *)&curr_path[0]);
	brackets[0] = ft_strjoin_3(BWHITE, "[ 📁 ", COLOUR_RESET);
	curr_path[2] = ft_strjoin(brackets[0], curr_path[1]);
	ft_free_ptr((void *)&curr_path[1]);
	ft_free_ptr((void *)&brackets[0]);
	brackets[1] = ft_strjoin_3(BWHITE, " ]", COLOUR_RESET);
	arrow = ft_strjoin_3(BMAGENTA, " ➳  ", COLOUR_RESET);
	prompt[0] = ft_strjoin_3(curr_path[2], brackets[1], arrow);
	ft_free_ptr((void *)&curr_path[2]);
	ft_free_ptr((void *)&brackets[1]);
	ft_free_ptr((void *)&arrow);
	prompt[1] = ft_strjoin(prompt[0], COLOUR_RESET);
	ft_free_ptr((void *)&prompt[0]);
	return (prompt[1]);
}

void	display_cmd_prompt(void)
{
	char	*prompt;

	dup2(g_data.backup_stdin, STDIN_FILENO);
	set_signal_hook(SIGINT, sighandler_parent, &g_data.action);
	prompt = string_prompt();
	g_data.prompt_input = readline(prompt);
	ft_free_ptr((void *)&prompt);
	if (g_data.prompt_input)
	{
		g_data.line_count++;
		process_input(g_data.prompt_input);
		while (g_data.token_list && !g_data.exit.flag && !g_data.syntax_error
			&& !g_data.skip_execution
			&& is_pipe_and_or((char *)ft_lst_last(g_data.token_list)->content))
			assemble_line(&g_data.prompt_input);
	}
	else
	{
		ft_putendl_fd("exit", 2);
		g_data.exit.flag = true;
	}
	disable_signal(SIGINT, &g_data.action);
}
