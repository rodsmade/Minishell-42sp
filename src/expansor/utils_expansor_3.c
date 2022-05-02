/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansor_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:25:13 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/03 00:39:00 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	convert_special_token(char **special_token)
{
	char	*new_token;

	if (*special_token != NULL && *special_token[0] != '\0')
	{
		if (!ft_strncmp(*special_token, "<", 2))
			new_token = ft_strdup(LESS_THAN);
		else if (!ft_strncmp(*special_token, ">", 2))
			new_token = ft_strdup(GREATER_THAN);
		else if (!ft_strncmp(*special_token, "|", 2))
			new_token = ft_strdup(PIPE);
		else if (!ft_strncmp(*special_token, "&", 2))
			new_token = ft_strdup(AMPERSAND);
		else if (!ft_strncmp(*special_token, "<<", 3))
			new_token = ft_strdup(DOUBLE_LESS_THAN);
		else if (!ft_strncmp(*special_token, ">>", 3))
			new_token = ft_strdup(DOUBLE_GREATER_THAN);
		else if (!ft_strncmp(*special_token, "&&", 3))
			new_token = ft_strdup(LOGIC_AND);
		else if (!ft_strncmp(*special_token, "||", 3))
			new_token = ft_strdup(LOGIC_OR);
		ft_free_ptr((void *)&(*special_token));
		*special_token = new_token;
	}
}

bool	is_special_chars(char *token_str)
{
	if (token_str
		&& ((ft_strncmp(token_str, "|", 2) == 0)
			|| (ft_strncmp(token_str, "&", 2) == 0)
			|| (ft_strncmp(token_str, ">", 2) == 0)
			|| (ft_strncmp(token_str, "<", 2) == 0)
			|| (ft_strncmp(token_str, "||", 3) == 0)
			|| (ft_strncmp(token_str, "&&", 3) == 0)
			|| (ft_strncmp(token_str, ">>", 3) == 0)
			|| (ft_strncmp(token_str, "<<", 3) == 0)))
		return (true);
	else
		return (false);
}
