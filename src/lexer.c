/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:00:45 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/20 02:03:30 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token_content(char *og_line, int *index)
{
	char	*token_content;
	char	quote_type;
	int		idx;

	idx = *index;
	token_content = ft_strdup("");
	while (og_line[idx] && og_line[idx] != ' ' && og_line[idx] != '\t')
	{
		if (og_line[idx] == '\'' || og_line[idx] == '\"')
		{
			quote_type = og_line[idx];
			token_content = ft_append_char(token_content, og_line[idx]);
			idx++;
			while (og_line[idx] && og_line[idx] != quote_type)
			{
				token_content = ft_append_char(token_content, og_line[idx]);
				idx++;
			}
		}
		token_content = ft_append_char(token_content, og_line[idx]);
		if (og_line[idx])
			idx++;
	}	
	*index = idx;
	return (token_content);
}

void	create_token_list(char *line)
{
	int		i;
	char	*token_content;

	i = 0;
	token_content = NULL;
	if (line)
	{
		while (line[i])
		{
			while (line[i] && (line[i] == ' ' || line[i] == '\t'))
				i++;
			if (line[i])
				token_content = get_token_content(line, &i);
			if (token_content)
			{
				ft_lst_add_back(&g_tudao.token_list, ft_lst_new(token_content));
				token_content = NULL;
			}
			if (line[i])
				i++;
		}
	}
}
