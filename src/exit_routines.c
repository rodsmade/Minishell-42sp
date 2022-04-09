/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:07:45 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/09 23:24:12 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_syntax_error_exit(char *token)
/**
 * TODO: 
 * 	- free_all no q for necessário antes de encerrar o REPL
 * 	- retornar o prompt principal (repl), e setar a variável $? = 2.
 */
{
	char	*err_msg;

	g_tudao.syntax_error = true;
	err_msg = ft_strjoin_3("bash: syntax error near unexpected token `", token, "'");
	ft_putendl_fd(err_msg, 2);
	return ;
}

void	close_std_fds(void)
{
	close(0);
	close(1);
	close(2);
	return ;
}

void	free_g_tudao(void)
{
	free_hashtable(&g_tudao.hashtable);
	ft_free_ptr((void *)&g_tudao.prompt_input);
	rl_clear_history();
	free_lexer();
	free_main_pipeline();
	close_std_fds();
	return ;
}
