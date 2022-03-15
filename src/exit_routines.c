/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:07:45 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/15 16:57:33 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_var(void *element)
{
	ft_free_ptr((void *)&(((t_env_var *) element)->name));
	ft_free_ptr((void *)&(((t_env_var *) element)->value));
	ft_free_ptr((void *)&element);
	return ;
}

void	free_hashtable(t_list *(*hashtable)[TABLE_SIZE])
{
	int	i;

	i = -1;
	while (++i < TABLE_SIZE)
		ft_lstclear(&(*hashtable)[i], free_env_var);
	return ;
}

void	print_syntax_error_exit(t_list	*token)
/**
 * TODO: 
 * 	- free_all no q for necessário antes de encerrar o REPL
 * 	- retornar o prompt principal (repl), e setar a variável $? = 2.
 */
{
	printf("bash: syntax error near unexpected token `%s'",
		(char *) token->next->content);
	return ;
}
