/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:00:45 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/20 21:19:23 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token_content(char *line, int *index)
{
	char	*token_content;
	char	quote_type;
	int		i;

	i = *index;
	token_content = ft_strdup("");
	while (line[i] && line[i] != ' ' && line[i] != '\t' && !count_redirect(&line[i]))
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote_type = line[i];
			token_content = ft_append_char(token_content, line[i]);
			i++;
			while (line[i] && line[i] != quote_type)
			{
				token_content = ft_append_char(token_content, line[i]);
				i++;
			}
		}
		token_content = ft_append_char(token_content, line[i]);
		if (line[i])
			i++;
	}
	*index = i;
	return (token_content);
}

void	create_token_list(char *line)
{
	int		i;
	int		redir;
	char	*token_content;

	i = 0;
	token_content = NULL;
	if (line)
	{
		while (line[i])
		{
			while (line[i] && (line[i] == ' ' || line[i] == '\t'))
				i++;
			redir = count_redirect(&line[i]) - 1;
			if (redir > 0)
			{
				token_content = redirect_gen(&line[i]);
				i += redir;
			}
			else if (line[i])
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
