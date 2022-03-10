/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:00:45 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/03/10 17:27:53 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_fields(char *line_read)
{
	int		i;
	int		fields;
	int		into_word;

	i = -1;
	fields = 0;
	into_word = 0;
	while (line_read[++i])
	{
		space_iter(&line_read[i], &into_word, &i);
		fields += check_char(&line_read[i], &i, &into_word);
		if (line_read[i] == 39 || line_read[i] == 34)
			fields += quote_iter(&line_read[i], &i, &into_word);
	}
	return (fields);
}

void	lexer_line(char	*line_read)
{
	int		fields;

	fields = count_fields(line_read);
	printf(">: fields %d\n", fields);
}
