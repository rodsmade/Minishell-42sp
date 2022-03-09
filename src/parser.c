/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:00:45 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/03/09 17:09:12 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_fields(char *line_read)
{
	int	i;
	int	fields;
	int	into_word;

	i = -1;
	fields = 0;
	into_word = 0;
	while (line_read[++i])
	{
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
	}
	return (fields);
}

void	parse_line(char	*line_read)
{
	int		fields;
	
	fields = count_fields(line_read);
	printf(">: fields %d\n", fields);
}