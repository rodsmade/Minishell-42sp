/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:56:32 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/03 00:45:19 by roaraujo         ###   ########.fr       */
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

char	*special_token_to_string(char *token)
{
	if (ft_strncmp(token, AMPERSAND, ft_strlen(AMPERSAND) + 1) == 0)
		return ("&");
	else if (ft_strncmp(token, DOUBLE_GREATER_THAN,
			ft_strlen(DOUBLE_GREATER_THAN) + 1) == 0)
		return (">>");
	else if (ft_strncmp(token, DOUBLE_LESS_THAN,
			ft_strlen(DOUBLE_LESS_THAN) + 1) == 0)
		return ("<<");
	else if (ft_strncmp(token, GREATER_THAN, ft_strlen(GREATER_THAN) + 1) == 0)
		return (">");
	else if (ft_strncmp(token, LESS_THAN, ft_strlen(LESS_THAN) + 1) == 0)
		return ("<");
	else if (ft_strncmp(token, LOGIC_AND, ft_strlen(LOGIC_AND) + 1) == 0)
		return ("&&");
	else if (ft_strncmp(token, LOGIC_OR, ft_strlen(LOGIC_OR) + 1) == 0)
		return ("||");
	else if (ft_strncmp(token, PIPE, ft_strlen(PIPE) + 1) == 0)
		return ("|");
	else
		return ("newline");
}
