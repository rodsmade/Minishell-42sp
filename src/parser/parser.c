/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:58:27 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_tokens_consistency(void)
{
	t_list	*pivot;

	pivot = g_data.token_list;
	if (is_pipe_and_or((char *) pivot->content) && !pivot->next)
		print_syntax_error((char *) pivot->content);
	while (pivot && pivot->next && !g_data.syntax_error)
	{
		if (is_pipe((char *) pivot->content)
			&& (is_pipe_and_or((char *) pivot->next->content)))
			print_syntax_error((char *) pivot->next->content);
		else if (is_and_or((char *) pivot->content)
			&& (is_pipe_and_or((char *) pivot->next->content)))
			print_syntax_error((char *) pivot->next->content);
		else if (is_redirect((char *) pivot->content)
			&& (is_special_token((char *) pivot->next->content)))
			print_syntax_error((char *) pivot->next->content);
		pivot = pivot->next;
	}
	if (!g_data.syntax_error && pivot && !pivot->next
		&& is_redirect((char *) pivot->content))
		print_syntax_error("newline");
	return ;
}

void	parse_tokens(void)
{
	if (g_data.token_list)
		check_tokens_consistency();
	return ;
}
