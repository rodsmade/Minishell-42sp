/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:58:27 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/17 19:44:29 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_tokens_consistency(void)
/**
 * TODO:
 * 		- refatorar a função (muitas linhas);
 * 		- rever se dá pra deixar o while com pivot só e se pivot->next 
 * 		- se não der, considerar o caso em que o último elemento é um redirect
 * 			sozinho (< > << >>), ex:
 * 	// if (pivot == ">" ou "<" ou ">>" ou "<<")
 * 	// 	printf("bash: syntax error near unexpected token `newline'")
 * 														  ^~~~~~~~~~~ chumbar
 */
{
	t_list	*pivot;

	pivot = g_tudao.token_list;
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

void	init_command(t_command *command)
{
	command->cmds_with_flags = NULL;
	command->inputs = NULL;
	command->outputs = NULL;
	command->heredocs = NULL;
	command->o_concats = NULL;
	command->err = NULL;
	return ;
}

void	capture_redirects(t_command	*cmd)
{
	t_list	*pivot;

	pivot = g_tudao.token_list;
	while (pivot && !is_pipe_and_or(pivot->content))
	{
		if (is_input(pivot))
			ft_lstadd_back(&cmd->inputs, ft_lstnew(pivot->next->content));
		if (is_output(pivot))
			ft_lstadd_back(&cmd->outputs, ft_lstnew(pivot->next->content));
		if (is_heredoc(pivot))
			ft_lstadd_back(&cmd->heredocs, ft_lstnew(pivot->next->content));
		if (is_o_concat(pivot))
			ft_lstadd_back(&cmd->o_concats, ft_lstnew(pivot->next->content));
		pivot = pivot->next;
	}
	return ;
}

void	print_redirects(void)
{
	t_list	*pivot_cmd;
	t_list	*pivot_redirect;
	int		i;

	pivot_cmd = g_tudao.command_table.main_pipeline;
	i = -1;
	while (pivot_cmd)
	{
		printf("cmd[%i]'s redirects:\n", ++i);
		pivot_redirect = ((t_command *) pivot_cmd->content)->inputs;
		printf("\tinputs: ");
		while (pivot_redirect)
		{
			printf("(%s), ", (char *) pivot_redirect->content);
			pivot_redirect = pivot_redirect->next;
		}
		printf("\n");
		pivot_redirect = ((t_command *) pivot_cmd->content)->outputs;
		printf("\toutputs: ");
		while (pivot_redirect)
		{
			printf("(%s), ", (char *) pivot_redirect->content);
			pivot_redirect = pivot_redirect->next;
		}
		printf("\n");
		pivot_redirect = ((t_command *) pivot_cmd->content)->heredocs;
		printf("\theredocs: ");
		while (pivot_redirect)
		{
			printf("(%s), ", (char *) pivot_redirect->content);
			pivot_redirect = pivot_redirect->next;
		}
		printf("\n");
		pivot_redirect = ((t_command *) pivot_cmd->content)->o_concats;
		printf("\to_concats: ");
		while (pivot_redirect)
		{
			printf("(%s), ", (char *) pivot_redirect->content);
			pivot_redirect = pivot_redirect->next;
		}
		printf("\n");
		pivot_cmd = pivot_cmd->next;
	}
	return ;
}

void	print_single_command_full()
{

}

void	set_up_main_pipeline(void)
{
	t_command	*command;
	// t_list		*pivot;

	// pivot = g_tudao.token_list;
	// while (pivot && !is_and_or(pivot->content))
	// {
	// 	{
			command = malloc(sizeof(t_command));
			if (!command)
				printf("[ERROR] deu ruim o malloc ajustar isso aqui depois\n");
			init_command(command);
			capture_redirects(command);
			ft_lstadd_back(&g_tudao.command_table.main_pipeline,
				ft_lstnew((void *) command));
			// capture_commands(command);
	// 	}
	// }
}

void	set_up_command_table(void)
{
	set_up_main_pipeline();
	print_redirects();
	// print_commands();
	// free_commands();
	return ;
}

void	parse_tokens(void)
{
	check_tokens_consistency();
	if (!g_tudao.syntax_error)
		set_up_command_table();
	return ;
}
