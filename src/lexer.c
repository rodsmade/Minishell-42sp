/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:14:42 by afaustin          #+#    #+#             */
/*   Updated: 2022/04/14 17:06:02 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_token_content(char *og_line, int *index)
{
	char	*token_content;
	char	quote_type;
	int		og_index;

	og_index = *index;
	token_content = ft_strdup("");
	while (og_line[og_index] && og_line[og_index] != ' ' && og_line[og_index] != '\t')
	{
		if (og_line[og_index] == '\'' || og_line[og_index] == '\"')
		{
			quote_type = og_line[og_index];
			token_content = ft_append_char(token_content, og_line[og_index]);
			og_index++;
			while (og_line[og_index] && og_line[og_index] != quote_type)
			{
				token_content = ft_append_char(token_content, og_line[og_index]);
				og_index++;
			}
		}
		token_content = ft_append_char(token_content, og_line[og_index]);
		if (og_line[og_index])
			og_index++;
	}	
	*index = og_index;
	return (token_content);
}

void	lexer_line(char *line_read)
{
	int		i;
	char	*token_content;

	i = 0;
	token_content = NULL;
	while (line_read[i])
	{
		while (line_read[i] && (line_read[i] == ' ' || line_read[i] == '\t'))
			i++;
		if (line_read[i])
			token_content = get_token_content(line_read, &i);
		if (token_content)
		{
			ft_lst_add_back(&g_tudao.token_list, ft_lst_new(token_content));
			token_content = NULL;
		}
		if (line_read[i])
			i++;
	}
}
