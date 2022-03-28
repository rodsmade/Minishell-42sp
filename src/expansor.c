/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:38:20 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/28 15:41:24 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_dollar_sign(t_list *token)
{
	return ;
}

void	expand_wildcards(void)
{
	return ;
}

void	expand_tokens(void)
{
	t_list	*pivot;

	pivot = g_tudao.token_list;
	while (pivot)
	{
		expand_dollar_sign(pivot);
		expand_wildcards();
		pivot = pivot->next;
	}
}