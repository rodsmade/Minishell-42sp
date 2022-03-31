/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:53:25 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/31 01:38:43 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_built_in(char *str)
{
	if (str
		&& ((ft_strncmp(str, "pwd", 4) == 0)
			|| (ft_strncmp(str, "cd", 3) == 0)
			|| (ft_strncmp(str, "echo", 5) == 0)
			|| (ft_strncmp(str, "env", 4) == 0)
			|| (ft_strncmp(str, "exit", 5) == 0)
			|| (ft_strncmp(str, "export", 7) == 0)
			|| (ft_strncmp(str, "clear", 6) == 0)
			|| (ft_strncmp(str, "unset", 6) == 0)))
		return (true);
	return (false);
}

void	execute_built_in(t_command *command)
{
	char	*built_in_str;
	t_list	*cmd_lst;

	cmd_lst = command->cmds_with_flags;
	built_in_str = (char *) cmd_lst->content;
	if (ft_strncmp(built_in_str, "pwd", 4) == 0)
		builtin_pwd();
	if (ft_strncmp(built_in_str, "cd", 3) == 0)
		builtin_cd(cmd_lst);
	if (ft_strncmp(built_in_str, "echo", 5) == 0)
		builtin_echo(cmd_lst);
	if (ft_strncmp(built_in_str, "env", 4) == 0)
		builtin_env();
	if (ft_strncmp(built_in_str, "exit", 5) == 0)
		builtin_exit();
	if (ft_strncmp(built_in_str, "export", 7) == 0)
		builtin_export(cmd_lst);
	if (ft_strncmp(built_in_str, "unset", 6) == 0)
		builtin_unset(cmd_lst);
	if (ft_strncmp(built_in_str, "clear", 6) == 0)
		printf("clear detected!\n");
	return ;
}
/*
Caso is_last_cmd seja verdadeiro eu altero o
stdoutput para o outfile ou caso não tenha outfile eu altero para o terminal
caso seja falso eu altero para o fd[0] do pipe criado
*/
// void	connect_the_dots(t_command *cmd, int is_last_cmd)
// {
// 	int		fd[2];
// 	pid_t	pid;

// 	if (pipe(fd) == 1)
// 		ft_putstr_fd("Pipe", 2);
// 	pid = fork();
// 	if (pid == -1)
// 		ft_putstr_fd("Fork", 2);
// 	if (pid == 0)
// 	{
// 		if (cmd->outputs->content == NULL)
// 			dup2(fd[1], STDOUT_FILENO);
// 		else if (cmd->outputs->content != NULL)
// 		{
// 			open()
// 		}
// 		close(fd[0]);
// 		close(fd[1]);
// 		if (is_built_in(cmd->cmds_with_flags->content))
// 		{
// 			execute_built_in(cmd);
// 			//Retornar o código de exit de acordo com a exec do built-in
// 			exit(EXIT_SUCCESS);
// 		}
// 	}
// 	dup2(fd[0], STDIN_FILENO);
// 	close(fd[0]);
// 	close(fd[1]);
// 	waitpid(pid, NULL, 0);
// }

void	execute_pipelines(void)
/**
 * TODO: Intended complete structure:
 * 		handle_redirections(pivot_cmd);
 * 		if (has_only_var_assignments(pivot_cmd))
 * 			assign_var();
 * 		else if (is_built_in(((t_command *)pivot_cmd->content)->cmds_with_flags->content))
 * 			execute_built_in((t_command *)pivot_cmd->content);
 * 		else if (has_absolute_path())
 * 			exec_absolute_path();
 * 		else
 * 			exec_env_path();
 */
{
	t_list		*pivot_pipeline;
	t_command	*cmd;
	int			total_pipelines;
	int			counter;

	pivot_pipeline = g_tudao.command_table.main_pipeline;
	cmd = (t_command *) pivot_pipeline->content;
	total_pipelines = ft_lstsize(pivot_pipeline);
	counter = 1;
	while (pivot_pipeline)
	{
		// if (has_only_var_assignments(pivot_pipeline))
		// 	assign_vars(cmd);
		// else if (is_built_in(cmd->cmds_with_flags->content))
		// 	execute_built_in(cmd);
		// pivot_pipeline = pivot_pipeline->next;
		if (total_pipelines == 1)
			connect_the_dots(cmd, true);
		else if (total_pipelines > 1)
		{
			if (counter == total_pipelines)
				connect_the_dots(cmd, true);
			else
				connect_the_dots(cmd, false);
		}
	}
	return ;
}
