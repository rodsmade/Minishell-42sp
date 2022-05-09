/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:00:45 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/05/05 14:41:05 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_token_content(char *line, int *index)
{
	char	*token_content;
	char	quote_type;

	token_content = ft_strdup("");
	while (line[*index] && !ft_is_blankspace(line[*index])
		&& !count_redirect(&line[*index]))
	{
		if (line[*index] == '\'' || line[*index] == '\"')
		{
			quote_type = line[*index];
			token_content = ft_append_char(token_content, line[*index]);
			(*index)++;
			while (line[*index] && line[*index] != quote_type)
			{
				token_content = ft_append_char(token_content, line[*index]);
				(*index)++;
			}
		}
		token_content = ft_append_char(token_content, line[*index]);
		if (line[*index])
			(*index)++;
	}
	(*index)--;
	return (token_content);
}

static void	add_to_token_list(char **token_content)
{
	if (*token_content)
	{
		mask_asterisks_in_quotes(*token_content);
		ft_lst_add_back(&g_tudao.token_list, ft_lst_new(*token_content));
		*token_content = NULL;
	}
	return ;
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
			while (line[i] && ft_is_blankspace(line[i]))
				i++;
			redir = count_redirect(&line[i]);
			if (redir > 0)
			{
				token_content = redirect_gen(&line[i]);
				i += redir;
			}
			else if (line[i])
				token_content = get_token_content(line, &i);
			add_to_token_list(&token_content);
			if (line[i] && !redir)
				i++;
		}
	}
}
