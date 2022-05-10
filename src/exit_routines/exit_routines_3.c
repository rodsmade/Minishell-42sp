/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routines_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:22:33 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(char *token)
{
	char	*minishell_f;
	char	*aux;

	g_data.syntax_error = true;
	g_data.exit.code = 2;
	minishell_f = ft_strjoin_3(BRED, "✘ minishell: ", COLOUR_RESET);
	aux = ft_strjoin(minishell_f, "syntax error near unexpected token `");
	g_data.exit.msg = ft_strjoin_3(aux, special_token_to_string(token), "'");
	ft_putendl_fd(g_data.exit.msg, 2);
	ft_free_ptr((void *)&g_data.exit.msg);
	ft_free_ptr((void *)&minishell_f);
	ft_free_ptr((void *)&aux);
	return ;
}

void	free_g_data(void)
{
	free_hashtable(&g_data.hashtable);
	ft_free_ptr((void *)&g_data.prompt_input);
	rl_clear_history();
	free_lexer();
	free_main_pipeline(&g_data.command_table.main_pipeline);
	close_std_fds();
	ft_free_ptr((void *)&g_data.home_at_start);
	return ;
}

void	print_error_and_exit(int ext_code, char *msg)
{
	if (ext_code >= 0)
	{
		if (msg)
		{
			ft_putendl_fd(msg, 2);
			ft_free_ptr((void *)&msg);
		}
		g_data.exit.code = ext_code;
		exit(g_data.exit.code);
	}
	ft_putendl_fd("Not a valid return code", 2);
	exit(EXIT_FAILURE);
}

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list != NULL)
	{
		tmp = list->next;
		ft_free_ptr((void *)&list->content);
		ft_free_ptr((void *)&list);
		list = tmp;
	}
}
