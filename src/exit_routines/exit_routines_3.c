/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routines_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:22:33 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/03 00:46:22 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(char *token)
{
	char	*minishell_f;
	char	*aux;

	g_tudao.syntax_error = true;
	g_tudao.exit.code = 2;
	minishell_f = ft_strjoin_3(BRED, "✘ minishell: ", COLOUR_RESET);
	aux = ft_strjoin(minishell_f, "syntax error near unexpected token `");
	g_tudao.exit.msg = ft_strjoin_3(aux, special_token_to_string(token), "'");
	ft_putendl_fd(g_tudao.exit.msg, 2);
	ft_free_ptr((void *)&g_tudao.exit.msg);
	ft_free_ptr((void *)&minishell_f);
	ft_free_ptr((void *)&aux);
	return ;
}

void	free_g_tudao(void)
{
	free_hashtable(&g_tudao.hashtable);
	ft_free_ptr((void *)&g_tudao.prompt_input);
	rl_clear_history();
	free_lexer();
	free_main_pipeline(&g_tudao.command_table.main_pipeline);
	close_std_fds();
	ft_free_ptr((void *)&g_tudao.home_at_start);
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
		g_tudao.exit.code = ext_code;
		exit(g_tudao.exit.code);
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
