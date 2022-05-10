/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:53:25 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	send_to_execve(t_command *command)
{
	char	**cmd_arr;
	char	*cmd_path;
	char	**hashtable_arr;

	cmd_arr = assemble_cmd_array(command);
	cmd_path = find_cmd_path(cmd_arr);
	hashtable_arr = hashtable_to_array();
	if (execve(cmd_path, cmd_arr, hashtable_arr) == -1)
	{
		ft_free_ptr((void *)&cmd_path);
		ft_free_ptr((void *)&cmd_arr);
		ft_free_arr((void *)&hashtable_arr);
		free_and_exit_fork(NULL, EXIT_FAILURE);
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
	else if (ft_strncmp(built_in_str, "cd", 3) == 0)
		builtin_cd(cmd_lst);
	else if (ft_strncmp(built_in_str, "echo", 5) == 0)
		builtin_echo(cmd_lst);
	else if (ft_strncmp(built_in_str, "env", 4) == 0)
		builtin_env(cmd_lst);
	else if (ft_strncmp(built_in_str, "exit", 5) == 0)
		builtin_exit(command);
	else if (ft_strncmp(built_in_str, "export", 7) == 0)
		builtin_export(cmd_lst);
	else if (ft_strncmp(built_in_str, "unset", 6) == 0)
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
			free_and_exit_fork(g_data.exit.msg, g_data.exit.code);
		}
		else
			send_to_execve(cmd);
	}
	else
		free_and_exit_fork(g_data.exit.msg, g_data.exit.code);
	return ;
}

void	await_all_children(int children_count, pid_t *cmd_pids)
{
	int	i;
	int	wstatus;
	int	waited_pid;
	int	last_cmd;

	last_cmd = children_count - 1;
	i = -1;
	while (++i < children_count)
	{
		waited_pid = waitpid(-1, &wstatus, 0);
		if (waited_pid == cmd_pids[last_cmd])
			process_child_return_code(wstatus);
	}
	ft_free_ptr((void *)&cmd_pids);
	return ;
}

void	execute_pipeline(t_list *pipeline)
{
	int			total_pipes;

	if (pipe(g_data.pipe_heredoc) == -1)
		print_error_and_exit(1, ft_strdup("Error: pipe heredoc"));
	create_new_files(pipeline);
	if (!execute_only_one_cmd(pipeline))
	{
		total_pipes = ft_lst_size(pipeline) - 1;
		g_data.cmd_pipes = ft_make_pipes(total_pipes);
		fork_and_execute_cmd(&g_data.command_table.main_pl_pids, pipeline);
		close_and_free_cmd_pipes();
		await_all_children(g_data.command_table.main_pl_size, \
		g_data.command_table.main_pl_pids);
	}
}
