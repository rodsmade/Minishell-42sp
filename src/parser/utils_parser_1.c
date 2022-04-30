/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:19:36 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/30 17:12:23 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_special_token(char *token)
{
	if (token
		&& ((ft_strncmp(token, PIPE, 7) == 0)
			|| (ft_strncmp(token, AMPERSAND, 12) == 0)
			|| (ft_strncmp(token, GREATER_THAN, 15) == 0)
			|| (ft_strncmp(token, LESS_THAN, 12) == 0)
			|| (ft_strncmp(token, LOGIC_OR, 11) == 0)
			|| (ft_strncmp(token, LOGIC_AND, 12) == 0)
			|| (ft_strncmp(token, DOUBLE_GREATER_THAN, 20) == 0)
			|| (ft_strncmp(token, DOUBLE_LESS_THAN, 3) == 0)))
		return (true);
	else
		return (false);
}

bool	is_redirect(char *token)
{
	if (token
		&& ((ft_strncmp(token, GREATER_THAN, 15) == 0)
			|| (ft_strncmp(token, LESS_THAN, 12) == 0)
			|| (ft_strncmp(token, DOUBLE_GREATER_THAN, 20) == 0)
			|| (ft_strncmp(token, DOUBLE_LESS_THAN, 3) == 0)))
		return (true);
	else
		return (false);
}

bool	is_pipe(char *token)
{
	if (token && ft_strncmp(token, PIPE, 7) == 0)
		return (true);
	else
		return (false);
}

bool	is_and_or(char *token)
{
	if (token
		&& (ft_strncmp(token, LOGIC_OR, 11) == 0
			|| ft_strncmp(token, LOGIC_AND, 12) == 0))
		return (true);
	else
		return (false);
}

bool	is_pipe_and_or(char *token)
{
	if (token
		&& ((ft_strncmp(token, PIPE, 7) == 0)
			|| (ft_strncmp(token, LOGIC_OR, 11) == 0)
			|| (ft_strncmp(token, LOGIC_AND, 12) == 0)))
		return (true);
	else
		return (false);
}
