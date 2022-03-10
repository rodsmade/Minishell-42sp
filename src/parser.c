/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:00:45 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/03/09 22:31:17 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	jump_quotes(char *line_read)
{
	int		i;
	int		close_quote;
	char	quote_type;

	i = 0;
	quote_type = line_read[i];
	close_quote = 0;
	while (line_read[++i] && !close_quote)
	{
		if (line_read[i] == quote_type)
			close_quote = 1;
	}
	i -= 1;
	return (i);
}

int	is_redirect(char *line_read)
{
	int	i;

	i = 0;
	if (line_read[i] == '>')
	{
		if (line_read[i + 1] && line_read[i + 1] == '>')
			return (1);
		return (0);
	}
	if (line_read[i] == '<')
	{
		if (line_read[i + 1] && line_read[i + 1] == '<' )
			return (1);
		return (0);
	}
	if (line_read[i] == '&')
	{
		if (line_read[i + 1] && line_read[i + 1] == '&')
			return (1);
		return (0);
	}
	if (line_read[i] == '|')
	{
		if (line_read[i + 1] && line_read[i + 1] == '|')
			return (1);
		return (0);
	}
	return (-1);
}

int	count_fields(char *line_read)
{
	int		i;
	int		fields;
	int		into_word;
	int		to_jump;

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
		if ((ft_isalpha(line_read[i]) && !into_word && line_read[i]) || (line_read[i] == '*' && !into_word) || (line_read[i] == '$' && !into_word))
		{
			fields++;
			into_word = 1;
		}
		to_jump = is_redirect(&line_read[i]);
		if (to_jump >= 0)
		{
			i += to_jump;
			fields++;
			into_word = 0;
		}
		if (line_read[i] == 39 || line_read[i] == 34)
		{
			to_jump = jump_quotes(&line_read[i]);
			//Só ignoramos caracteres caso existam caracteres dentro das aspas
			if (to_jump > 1)
				i += to_jump;
			//A contagem de field só é feita quando estamos fora de uma palavra
			if (!into_word)
				fields++;
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