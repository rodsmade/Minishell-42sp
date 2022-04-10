/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routines_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:21:28 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/10 19:52:22 by roaraujo         ###   ########.fr       */
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

void	free_and_exit_fork(char *err_msg)
/**
 * TODO: handle properly the return code.
 */
{
	t_list	*pivot;

	if (err_msg)
	{
		ft_putendl_fd(err_msg, 2);
		ft_free_ptr((void *)&err_msg);
	}
	pivot = g_tudao.command_table.main_pipeline;
	while (pivot)
	{
		close_fds_by_cmd((t_command *) pivot->content);
		pivot = pivot->next;
	}
	close_and_free_pipes();
	free_g_tudao();
	exit(1);
	return ;
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
