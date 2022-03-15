/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:13:48 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/03/10 17:41:05 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_expansible(char line_read)
{
	if (line_read == '*' || line_read == '$')
		return (1);
	return (0);
}

int	is_redirect(char *line_read)
{
	int	i;

	i = 0;
	if ((line_read[i] == '>' && line_read[i + 1] && line_read[i + 1] == '>') || \
		(line_read[i] == '<' && line_read[i + 1] && line_read[i + 1] == '<') || \
		(line_read[i] == '&' && line_read[i + 1] && line_read[i + 1] == '&') || \
		(line_read[i] == '|' && line_read[i + 1] && line_read[i + 1] == '|'))
		return (1);
	else if (line_read[i] == '>' || line_read[i] == '<' || \
			line_read[i] == '&' || line_read[i] == '|')
		return (0);
	else
		return (-1);
}

int	quote_iter(char *line_read, int *index, int *into_word)
{
	int		count;
	int		close_quote;
	char	quote_type;

	count = 0;
	quote_type = line_read[count];
	close_quote = 0;
	while (line_read[++count] && !close_quote)
	{
		if (line_read[count] == quote_type)
			close_quote = 1;
	}
	count -= 1;
	if (count > 1)
	{
		*index += count;
		if (!(*into_word))
		{
			*into_word = 1;
			return (1);
		}
	}
	return (0);
}

void	space_iter(char *line_read, int *into_word, int *index)
{
	int	count;

	count = 0;
	while (line_read[count + 1] && line_read[count] == ' ')
	{
		count++;
		*into_word = 0;
	}
	*index += count;
}

int	check_char(char *line_read, int *index, int *into_word)
{
	if ((ft_isalpha(line_read[0]) && !(*into_word) && line_read[0]) || \
		(is_expansible(line_read[0]) && !(*into_word) && line_read[0]))
	{
		*into_word = 1;
		return (1);
	}
	if (is_redirect(line_read) >= 0)
	{
		if (is_redirect(line_read))
			*index += 1;
		*into_word = 0;
		return (1);
	}
	return (0);
}
