/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:56:32 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/02 20:22:31 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_input(t_list *token)
{
	if (ft_strncmp((char *) token->content, LESS_THAN, 2) == 0)
		return (true);
	else
		return (false);
}

bool	is_output(t_list *token)
{
	if (ft_strncmp((char *) token->content, GREATER_THAN, 2) == 0)
		return (true);
	else
		return (false);
}

bool	is_heredoc(t_list *token)
{
	if (ft_strncmp((char *) token->content, DOUBLE_LESS_THAN, 3) == 0)
		return (true);
	else
		return (false);
}

bool	is_o_concat(t_list *token)
{
	if (ft_strncmp((char *) token->content, DOUBLE_GREATER_THAN, 3) == 0)
		return (true);
	else
		return (false);
}
