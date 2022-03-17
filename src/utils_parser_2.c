/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:56:32 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/17 19:40:33 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_input(t_list *token)
{
	if (ft_strncmp((char *) token->content, "<", 2) == 0)
		return (true);
	else
		return (false);
}

bool	is_output(t_list *token)
{
	if (ft_strncmp((char *) token->content, ">", 2) == 0)
		return (true);
	else
		return (false);
}

bool	is_heredoc(t_list *token)
{
	if (ft_strncmp((char *) token->content, "<<", 3) == 0)
		return (true);
	else
		return (false);
}

bool	is_o_concat(t_list *token)
{
	if (ft_strncmp((char *) token->content, ">>", 3) == 0)
		return (true);
	else
		return (false);
}
