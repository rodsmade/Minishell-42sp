/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:58:27 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/21 21:01:37 by afaustin         ###   ########.fr       */
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

void	parse_tokens(void)
{
	if (g_tudao.token_list)
		check_tokens_consistency();
	return ;
}