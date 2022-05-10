/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routines_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:21:28 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_command_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_free_ptr((void *)&lst);
		lst = tmp;
	}
}

void	free_main_pipeline(t_list **pipeline)
{
	t_list		*lst;
	t_list		*tmp;
	t_command	*cmd;

	lst = *pipeline;
	while (lst)
	{
		cmd = (t_command *) lst->content;
		free_t_command_list(cmd->cmds_with_flags);
		free_t_command_list(cmd->inputs);
		free_t_command_list(cmd->outputs);
		free_t_command_list(cmd->heredocs);
		free_t_command_list(cmd->o_concats);
		free_t_command_list(cmd->err);
		tmp = lst->next;
		ft_free_ptr((void *)&(lst->content));
		ft_free_ptr((void *)&(lst));
		lst = tmp;
	}
	*pipeline = NULL;
	return ;
}

void	free_and_exit_fork(char *err_msg, int err_code)
{
	t_list	*pivot;
	char	*err_msg_f;

	g_data.exit.code = err_code;
	if (err_msg)
	{
		err_msg_f = ft_strjoin_3(BRED, "✘ minishell: ", COLOUR_RESET);
		ft_putstr_fd(err_msg_f, 2);
		ft_putendl_fd(err_msg, 2);
		ft_free_ptr((void *)&err_msg_f);
		ft_free_ptr((void *)&err_msg);
	}
	pivot = g_data.command_table.main_pipeline;
	while (pivot)
	{
		close_fds((t_command *) pivot->content);
		pivot = pivot->next;
	}
	ft_free_ptr((void *)&g_data.command_table.main_pl_pids);
	ft_close_pipe_fds(g_data.pipe_heredoc);
	close_heredoc_pipe();
	close_and_free_cmd_pipes();
	free_g_data();
	exit(g_data.exit.code);
}

void	free_env_var(void *element)
{
	ft_free_ptr((void *)&(((t_env_var *) element)->key));
	ft_free_ptr((void *)&(((t_env_var *) element)->value));
	ft_free_ptr((void *)&element);
	return ;
}

void	free_hashtable(t_list *(*hashtable)[TABLE_SIZE])
{
	int	i;

	i = -1;
	while (++i < TABLE_SIZE)
		ft_lst_clear(&(*hashtable)[i], free_env_var);
	return ;
}
