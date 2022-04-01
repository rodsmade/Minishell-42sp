/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:53:25 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/01 22:36:20 by roaraujo         ###   ########.fr       */
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

char	**assemble_cmd_array(t_command *command)
{
	char	**cmd_arr;
	t_list	*pivot;
	int		lst_len;
	int		i;

	lst_len = ft_lst_size(command->cmds_with_flags);
	cmd_arr = (char **)malloc((lst_len + 1) * sizeof(char *));
	pivot = command->cmds_with_flags;
	i = 0;
	while (pivot)
	{
		cmd_arr[i] = (char *)pivot->content;
		i++;
		pivot = pivot->next;
	}
	cmd_arr[i] = NULL;
	return (cmd_arr);
}

char	*env_var_to_string(t_env_var *env_var)
{
	char	*env_var_str;
	char	*temp;

	temp = ft_strjoin((char *) env_var->key, "=");
	if (env_var->value)
		env_var_str = ft_strjoin(temp, (char *) env_var->value);
	ft_free_ptr((void *)&temp);
	return (env_var_str);
}

int	count_env_vars(void)
{
	int		count;
	int		i;
	t_list	*pivot;

	i = -1;
	count = 0;
	while (++i < TABLE_SIZE)
	{
		pivot = g_tudao.hashtable[i];
		while (pivot)
		{
			count++;
			pivot = pivot->next;
		}
	}
	return (count);
}

char	**hashtable_to_array(void)
{
	int		env_vars_count;
	int		i;
	int		j;
	t_list	*pivot;
	char	**hashtable_arr;

	env_vars_count = count_env_vars();
	hashtable_arr = (char **) malloc((env_vars_count + 1) * sizeof(char *));
	hashtable_arr[env_vars_count] = NULL;
	i = -1;
	j = -1;
	while (++i < TABLE_SIZE)
	{
		pivot = g_tudao.hashtable[i];
		while (pivot)
		{
			hashtable_arr[++j] = env_var_to_string((t_env_var *) pivot->content);
			pivot = pivot->next;
		}
	}
	return (NULL);
}

char	*find_cmd_path(char *command_str)
{
	char	*cmd_path;

	cmd_path = NULL;
	return (cmd_path);
}

void	send_to_execve(t_command *command)
{
	char	**cmd_arr;
	char	*cmd_path;
	char	**hashtable_arr;

	cmd_arr = assemble_cmd_array(command);
	hashtable_arr = hashtable_to_array();
	cmd_path = find_cmd_path(cmd_arr[0]);
	printf("arg 1: %s\n", cmd_arr[0]);
	if (execve(cmd_path, cmd_arr, hashtable_arr) == -1)
		printf("deu ruim, libera memória ae\n");
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
	return ;
}

void	execute_command(t_command *cmd)
{
	// if (is_var_assignment(cmd->cmds_with_flags->content))
	// 	assign_vars(cmd);
	if (is_built_in(cmd->cmds_with_flags->content))
	{
		execute_built_in(cmd);
		free_g_tudao();
		exit(1);
	}
	else
		send_to_execve(cmd);
	return ;
}

void	execute_main_pipeline(void)
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
	t_list		*cmd_pivot;
	int			pid;
	int			wstatus;
	t_command	*cmd;

	cmd_pivot = g_tudao.command_table.main_pipeline;
	cmd = (t_command *) cmd_pivot->content;
	if (!cmd_pivot->next && is_built_in((char *)cmd->cmds_with_flags->content))
		execute_built_in(cmd);
	else
	{
		while (cmd_pivot)
		{
			pid = fork();
			if (pid == -1)
				ft_putendl_fd("Error while forking", 1);
			else if (pid == 0)
				execute_command(cmd);
			else
				waitpid(pid, &wstatus, 0);
			cmd_pivot = cmd_pivot->next;
			if (cmd_pivot)
				cmd = (t_command *) cmd_pivot->content;
		}
	}
}
