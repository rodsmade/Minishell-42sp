/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:53:25 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/12 02:59:08 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	send_to_execve(t_command *command)
{
	char	**cmd_arr;
	char	*cmd_path;
	char	**hashtable_arr;

	cmd_arr = assemble_cmd_array(command);
	cmd_path = find_cmd_path(cmd_arr[0]);
	if (!cmd_path)
	{
		ft_putendl_fd(ft_strjoin_3("bash: ",
				cmd_arr[0], ": command not found"), 2);
		ft_free_ptr((void *)&cmd_arr);
		ft_close_pipe_fds(g_tudao.pipe_heredoc);
		close_fds_by_cmd(command);
		free_and_exit_fork(NULL);
	}
	hashtable_arr = hashtable_to_array();
	if (execve(cmd_path, cmd_arr, hashtable_arr) == -1)
	{
		ft_free_ptr((void *)&cmd_arr);
		ft_putendl_fd("couldn't execute", 2);
		ft_free_arr((void *)&hashtable_arr);
		ft_close_pipe_fds(g_tudao.pipe_heredoc);
		close_fds_by_cmd(command);
		free_and_exit_fork(NULL);
	}
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
		builtin_env(cmd_lst);
	if (ft_strncmp(built_in_str, "exit", 5) == 0)
		builtin_exit();
	if (ft_strncmp(built_in_str, "export", 7) == 0)
		builtin_export(cmd_lst);
	if (ft_strncmp(built_in_str, "unset", 6) == 0)
		builtin_unset(cmd_lst);
	return ;
}

void	execute_command(t_command *cmd)
{
	if (cmd->cmds_with_flags)
	{
		if (is_built_in(cmd->cmds_with_flags->content))
		{
			execute_built_in(cmd);
			ft_close_pipe_fds(g_tudao.pipe_heredoc);
			close_fds_by_cmd(cmd);
			free_and_exit_fork(g_tudao.ext_routine.msg);
		}
		else
			send_to_execve(cmd);
	}
	else
	{
		ft_close_pipe_fds(g_tudao.pipe_heredoc);
		close_fds_by_cmd(cmd);
		free_and_exit_fork(g_tudao.ext_routine.msg);
	}
	return ;
}

void	capture_redirections(int cmd_counter, t_command *cmd)
{
	int	total_pipes;

	total_pipes = ft_lst_size(g_tudao.command_table.main_pipeline) - 1;
	if (!cmd->heredocs)
	{
		if (cmd_counter)
			dup2(g_tudao.cmd_pipes[cmd_counter - 1][0], STDIN_FILENO);
	}
	else
		capture_heredocs(cmd, cmd_counter);
	if (cmd_counter != total_pipes && total_pipes)
		dup2(g_tudao.cmd_pipes[cmd_counter][1], STDOUT_FILENO);
	capture_inputs(cmd);
	capture_outputs(cmd);
	capture_o_concats(cmd);
}

void	execute_pipeline(t_list *pipeline)
{
	t_list		*cmd_pivot;
	t_command	*cmd;
	int			counter;
	int			total_pipes;

	create_new_files(pipeline);
	if (pipe(g_tudao.pipe_heredoc) == -1)
		ft_putendl_fd("Error trying to create pipe g_tudao.pipe_heredoc", 2);
	if (!execute_only_one_cmd(pipeline))
	{
		cmd_pivot = pipeline;
		cmd = (t_command *) cmd_pivot->content;
		counter = -1;
		total_pipes = ft_lst_size(pipeline) - 1;
		g_tudao.cmd_pipes = ft_make_pipes(total_pipes);
		while (cmd_pivot)
		{
			cmd = (t_command *) cmd_pivot->content;
			process_executor(total_pipes, ++counter, cmd);
			close_fds_by_cmd(cmd);
			cmd_pivot = cmd_pivot->next;
		}
		close_and_free_pipes();
	}
	add_heredocs_to_history();
}
