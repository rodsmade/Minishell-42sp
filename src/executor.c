/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:53:25 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/05 20:39:02 by adrianofaus      ###   ########.fr       */
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

char	*ft_strjoin_3(char *str1, char *str2, char *str3)
{
	char	*new_str;
	char	*tmp;
	
	tmp = ft_strjoin(str1, str2);
	new_str = ft_strjoin(tmp, str3);
	ft_free_ptr((void *)&tmp);	
	return (new_str);
}

char	*find_cmd_path(char *command_str)
{
	char	*cmd_path;
	char	*all_paths;
	char	**splited_paths;
	int		i;

	cmd_path = NULL;
	i = -1;
	if (!ft_strncmp(command_str, "~", 1) || !ft_strncmp(command_str, "/", 1) || \
	!ft_strncmp(command_str, "./", 2) || !ft_strncmp(command_str, "../", 3))
	{
		if (access(command_str, F_OK) == 0)
			return (command_str);
		else
		{
			ft_putendl_fd("bash: command not found", 2);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		all_paths = read_hashtable(g_tudao.hashtable[hash_string("PATH")], "PATH");
		splited_paths = ft_split(all_paths, ':');
		while (splited_paths[++i])
		{
			cmd_path = ft_strjoin_3(splited_paths[i], "/", command_str);
			if (access(cmd_path, F_OK) == 0)
				return (cmd_path);
			else
				ft_free_ptr((void *)&cmd_path);
		}
	}
	ft_putendl_fd("bash: command not found", 2);
	exit(EXIT_FAILURE);
}

void	send_to_execve(t_command *command)
{
	char	**cmd_arr;
	char	*cmd_path;
	char	**hashtable_arr;

	dprintf(2, "entrou na send_to_exec, ");
	dprintf(2, "comando: %s\n", (char *) command->cmds_with_flags->content);
	cmd_arr = assemble_cmd_array(command);
	hashtable_arr = hashtable_to_array();
	cmd_path = find_cmd_path(cmd_arr[0]);
	dprintf(2, "sending to exec: execve(%s, { ", cmd_path);
	int i=-1;
	while (cmd_arr[++i])
	{
		printf("%s", cmd_arr[i]);
		if (cmd_arr[i + 1])
			printf(", ");
	}
	dprintf(2, " }, envp);\n");
	if (execve(cmd_path, cmd_arr, hashtable_arr) == -1)
		dprintf(2, "deu ruim, libera memória ae\n");
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

void	close_and_free_pipes(int **pipes, int total_pipes)
{
	int	i;

	i = -1;
	while (++i < total_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
	}
	free(pipes);
}

void	execute_command(t_command *cmd, int **pipes, int total_pipes)
{
	// if (is_var_assignment(cmd->cmds_with_flags->content))
	// 	assign_vars(cmd);
	if (is_built_in(cmd->cmds_with_flags->content))
	{
		execute_built_in(cmd);
		free_g_tudao();
		close_and_free_pipes(pipes, total_pipes);
		exit(1);
	}
	else
	{
		dprintf(2, "executar comando: %s\n", (char *) cmd->cmds_with_flags->content);
		send_to_execve(cmd);
	}
	return ;
}

// void	capture_redirections(t_list *next_pipeline, t_command *cmd, int *pipe, int counter)
// {
// 	int	input;
// 	int	output;

// 	dprintf(2, "----- entrou na capture -----\n");
// 	if (cmd->inputs)
// 	{
// 		dprintf(2, "access input - if file exists: %i\n", access((char *) cmd->inputs->content, F_OK));
// 		dprintf(2, "access input - if file has read permission: %i\n", access((char *) cmd->inputs->content, R_OK));
// 		input = open((char *) cmd->inputs->content, O_RDONLY);
// 		if (input == -1)
// 			ft_putendl_fd("Error opening input file", 2);
// 		if (dup2(input, STDIN_FILENO) == -1)
// 			ft_putendl_fd("Error duplicating input file descriptor", 2);
// 		close(input);
// 	}
// 	//verificar a parte de concatenar
// 	if (cmd->outputs)
// 	{
// 		dprintf(2, "access input - if file exists: %i\n", access((char *) cmd->inputs->content, F_OK));
// 		dprintf(2, "access input - if file has read permission: %i\n", access((char *) cmd->inputs->content, R_OK));
// 		output = open((char *) cmd->outputs->content,
// 			O_CREAT | O_WRONLY | O_TRUNC,
// 			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
// 		if (output == -1)
// 			ft_putendl_fd("Error opening output file", 2);
// 		if (dup2(output, STDOUT_FILENO) == -1)
// 			ft_putendl_fd("Error duplicating output file descriptor", 2);
// 		// close(output);
// 	}
// 	else if (next_pipeline)
// 	{
// 		dprintf(2, "----- Pipe detectado -----\n");
// 		dprintf(2, "STDOUT_FILENO: %i\n", STDOUT_FILENO);
// 		// printf("resultado da dup2: %i\n", dup2(pipe[1], STDOUT_FILENO));
// 		dprintf(2, "pipe[0] %d // pipe[1] %d\n", pipe[0], pipe[1]);
// 		if (dup2(pipe[1], STDOUT_FILENO) == -1)
// 		{
// 			dprintf(2, "deu ruim na dup2\n");
// 			// close(pipe[0]);
// 			close(pipe[1]);
// 		}
// 		dprintf(2, "----- depois do dup2 STDOUT -----\n");
// 		dprintf(2, "STDOUT_FILENO: %i\n", STDOUT_FILENO);
// 		dprintf(2, "pipe[0] %d // pipe[1] %d\n", pipe[0], pipe[1]);
// 		// close(STDOUT_FILENO);
// 	}
// }

void	capture_inputs(t_command *cmd)
{
	t_list	*pivot;
	char	*err_msg;

	pivot = cmd->inputs;
	while (pivot)
	{
		if (access((char *) pivot->content, F_OK) == -1)
		{
			err_msg = ft_strjoin_3("bash: ", (char *) pivot->content,
				": No such file or directory");
			ft_putendl_fd(err_msg, 2);
			ft_free_ptr((void *)&err_msg);
		}
		if (access((char *) cmd->inputs->content, R_OK) == -1)
		{
			err_msg = ft_strjoin_3("bash: ", (char *) pivot->content,
				": Permission denied");
			ft_putendl_fd(err_msg, 2);
			ft_free_ptr((void *)&err_msg);
		}
		if (!pivot->next)
			dup2(open((char *) pivot->content, O_RDONLY), STDIN_FILENO);
		pivot = pivot->next;
	}
	return ;
}

void	capture_redirections(int **pipe, int counter, t_command *cmd)
{
	int	total_pipes;

	total_pipes = ft_lst_size(g_tudao.command_table.main_pipeline) - 1;
	if (counter != total_pipes && total_pipes)
	{
		if (counter)
			dup2(pipe[counter - 1][0], STDIN_FILENO);
		dup2(pipe[counter][1], STDOUT_FILENO);
	}
	else if (counter == total_pipes && total_pipes)
	{
		if (counter)
			dup2(pipe[counter -1][0], STDIN_FILENO);
	}
	capture_inputs(cmd);
}

int	**make_pipes(int total_pipes)
{
	int		i;
	int	**pipes;

	pipes = (int **)malloc(total_pipes * sizeof(int *));
	if (!pipes)
	{
		ft_putendl_fd("Malloc error", 2);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < total_pipes)
	{
		pipes[i] = (int *)malloc(2 * sizeof(int));
		if (!pipes[i])
		{
			ft_putendl_fd("Malloc error", 2);
			exit(EXIT_FAILURE);
		}
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
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
	int			counter;
	int			**pipes;
	int			total_pipes;
	
	cmd_pivot = g_tudao.command_table.main_pipeline;
	cmd = (t_command *) cmd_pivot->content;
	counter = 0;
	if (!cmd_pivot->next && is_built_in((char *)cmd->cmds_with_flags->content))
		execute_built_in(cmd);
	else
	{
		total_pipes = ft_lst_size(g_tudao.command_table.main_pipeline) - 1;
		pipes = make_pipes(total_pipes);
		while (cmd_pivot)
		{
			dprintf(2, "\n\n# COMMAND TO PROCESS: %s\n", (char *) ((t_command *) cmd_pivot->content)->cmds_with_flags->content);
			pid = fork();
			if (pid == -1)
				ft_putendl_fd("Error while forking", 2);
			else if (pid == 0)
			{
				capture_redirections(pipes, counter, cmd);
				execute_command(cmd, pipes, total_pipes);
			}
			else
			{
				waitpid(pid, &wstatus, 0);
				if (counter != total_pipes)
					close(pipes[counter][1]);
			}
			cmd_pivot = cmd_pivot->next;
			if (cmd_pivot)
				cmd = (t_command *) cmd_pivot->content;
			counter++;
		}
		close_and_free_pipes(pipes, total_pipes);
	}
	dprintf(2, "\n########## ENCERRA PIPELINE ##########\n\n");
}