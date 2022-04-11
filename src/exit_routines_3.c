/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routines_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:22:33 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/11 13:48:42 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error_exit(char *token)
/**
 * TODO: 
 * 	- free_all no q for necessário antes de encerrar o REPL
 * 	- retornar o prompt principal (repl), e setar a variável $? = 2.
 */
{
	char	*err_msg;

	g_tudao.syntax_error = true;
	err_msg = ft_strjoin_3("bash: syntax error near unexpected token `",
			token, "'");
	ft_putendl_fd(err_msg, 2);
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
		g_tudao.ext_routine.code = ext_code;
		exit(g_tudao.ext_routine.code);
	}
	ft_putendl_fd("Not a valid return code", 2);
	exit(EXIT_FAILURE);
}
