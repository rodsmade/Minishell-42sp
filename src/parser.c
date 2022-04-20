/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:58:27 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/20 19:04:27 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_tokens_consistency(void)
{
	t_list	*pivot;

	pivot = g_tudao.token_list;
	if (is_pipe_and_or((char *) pivot->content) && !pivot->next)
		print_syntax_error_exit((char *) pivot->content);
	while (pivot && pivot->next && !g_tudao.syntax_error)
	{
		if (is_pipe((char *) pivot->content)
			&& (is_pipe_and_or((char *) pivot->next->content)))
			print_syntax_error_exit((char *) pivot->next->content);
		else if (is_and_or((char *) pivot->content)
			&& (is_pipe_and_or((char *) pivot->next->content)))
			print_syntax_error_exit((char *) pivot->next->content);
		else if (is_redirect((char *) pivot->content)
			&& (is_special_token((char *) pivot->next->content)))
			print_syntax_error_exit((char *) pivot->next->content);
		pivot = pivot->next;
	}
	if (!g_tudao.syntax_error && pivot && !pivot->next
		&& is_redirect((char *) pivot->content))
		print_syntax_error_exit("newline");
	return ;
}

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
			ft_putendl_fd("[ERROR] deu ruim o malloc ajustar aqui depois", 2);
		init_command(command);
		capture_command(command, &pivot);
		ft_lst_add_back(&g_tudao.command_table.main_pipeline,
			ft_lst_new((void *) command));
		if (pivot && is_pipe(pivot->content))
			pivot = pivot->next;
	}
}

void	set_up_command_table(void)
{
	set_up_main_pipeline();
	g_tudao.command_table.main_pl_size = \
		ft_lst_size(g_tudao.command_table.main_pipeline);
	return ;
}

void	parse_tokens(void)
{
	check_tokens_consistency();
	if (!g_tudao.syntax_error)
		set_up_command_table();
	return ;
}
