/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 20:47:35 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/28 20:45:39 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	capture_command(t_command	*cmd, t_list **pivot)
{
	void	*next_token;

	while ((*pivot) && !is_pipe_and_or((*pivot)->content))
	{
		if ((*pivot)->next)
			next_token = (*pivot)->next->content;
		if (is_redirect((char *)(*pivot)->content))
		{
			if (is_input((*pivot)))
				ft_lst_add_back(&cmd->inputs, ft_lst_new(next_token));
			if (is_output((*pivot)))
				ft_lst_add_back(&cmd->outputs, ft_lst_new(next_token));
			if (is_heredoc((*pivot)))
				ft_lst_add_back(&cmd->heredocs, ft_lst_new(next_token));
			if (is_o_concat((*pivot)))
				ft_lst_add_back(&cmd->o_concats, ft_lst_new(next_token));
			(*pivot) = (*pivot)->next->next;
		}
		else
		{
			ft_lst_add_back(&cmd->cmds_with_flags,
				ft_lst_new((*pivot)->content));
			(*pivot) = (*pivot)->next;
		}
	}
}

void	set_up_main_pipeline(void)
{
	t_command	*command;
	t_list		*pivot;

	pivot = g_tudao.token_list;
	while (pivot && !is_and_or(pivot->content))
	{
		command = malloc(sizeof(t_command));
		if (!command)
		{
			pivot = NULL;
			g_tudao.skip_execution = true;
			g_tudao.exit.code = EXIT_FAILURE;
			ft_putendl_fd("[ERROR] Failed to alloc memory in command table", 2);
		}
		else
		{
			init_command(command);
			capture_command(command, &pivot);
		}
		ft_lst_add_back(&g_tudao.command_table.main_pipeline,
			ft_lst_new((void *) command));
		if (pivot && is_pipe(pivot->content))
			pivot = pivot->next;
	}
}

void	set_up_command_table(void)
{
	if (g_tudao.prompt_input && !g_tudao.syntax_error)
	{
		set_up_main_pipeline();
		g_tudao.command_table.main_pl_size = \
			ft_lst_size(g_tudao.command_table.main_pipeline);
	}
	return ;
}
