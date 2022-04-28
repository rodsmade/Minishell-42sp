/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:19:36 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/20 15:01:48 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_special_token(char *token)
{
	if (token
		&& ((ft_strncmp(token, "|", 2) == 0)
			|| (ft_strncmp(token, ">", 2) == 0)
			|| (ft_strncmp(token, "<", 2) == 0)
			|| (ft_strncmp(token, ">>", 3) == 0)
			|| (ft_strncmp(token, "<<", 3) == 0)
			|| (ft_strncmp(token, "&&", 3) == 0)
			|| (ft_strncmp(token, "||", 3) == 0)))
		return (true);
	else
		return (false);
}

bool	is_redirect(char *token)
{
	if (token
		&& ((ft_strncmp(token, ">", 2) == 0)
			|| (ft_strncmp(token, "<", 2) == 0)
			|| (ft_strncmp(token, ">>", 3) == 0)
			|| (ft_strncmp(token, "<<", 3) == 0)))
		return (true);
	else
		return (false);
}

bool	is_pipe(char *token)
{
	if (token && ft_strncmp(token, "|", 2) == 0)
		return (true);
	else
		return (false);
}

bool	is_and_or(char *token)
{
	if (token
		&& (ft_strncmp(token, "||", 3) == 0
			|| ft_strncmp(token, "&&", 3) == 0))
		return (true);
	else
		return (false);
}

bool	is_pipe_and_or(char *token)
{
	if (token
		&& ((ft_strncmp(token, "|", 2) == 0)
			|| (ft_strncmp(token, "||", 3) == 0)
			|| (ft_strncmp(token, "&&", 3) == 0)))
		return (true);
	else
		return (false);
}
