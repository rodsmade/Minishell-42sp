/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:00:45 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/03/09 18:00:06 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	jump_quotes(char *line_read)
{
	int	i;
	int	quote_type;
	int	close_quote;
	int	to_jump;

	i = 0;
	quote_type = line_read[i];
	close_quote = 0;
	while (line_read[++i] && !close_quote)
	{
		to_jump = 0;
		if (line_read[i] == quote_type)
			close_quote = 1;
		else if (line_read[i] == 39 || line_read[i] == 34)
		{
			to_jump = jump_quotes(&line_read[i]);
			if (to_jump > 1)
				i += to_jump;
		}
	}
	i -= 1;
	return (i);
}

int	count_fields(char *line_read)
{
	int	i;
	int	fields;
	int	into_word;
	int	to_jump;

	i = -1;
	fields = 0;
	into_word = 0;
	while (line_read[++i])
	{
		to_jump = 0;
		while (line_read[i] == ' ' && line_read[i])
		{
			i++;
			into_word = 0;
		}
		if (ft_isalpha(line_read[i]) && !into_word && line_read[i])
		{
			fields++;
			into_word = 1;
		}
		if (line_read[i] == 39 || line_read[i] == 34)
		{
			to_jump =  jump_quotes(&line_read[i]);
			if (to_jump > 1)
			{
				i += to_jump;
				fields++;
			}
		}
	}
	return (fields);
}

void	parse_line(char	*line_read)
{
	int		fields;
	
	fields = count_fields(line_read);
	printf(">: fields %d\n", fields);
}