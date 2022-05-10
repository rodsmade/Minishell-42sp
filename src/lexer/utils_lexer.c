/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:13:48 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(void)
{
	t_list	*tmp;

	while (g_data.token_list != NULL)
	{
		tmp = g_data.token_list->next;
		ft_free_ptr((void *)&g_data.token_list->content);
		ft_free_ptr((void *)&g_data.token_list);
		g_data.token_list = tmp;
	}
}

void	skip_quotes(char *line_read, int *index, int *token_len)
{
	char	quote_type;

	if (line_read[(*index)] == 39 || line_read[(*index)] == 34)
	{
		quote_type = line_read[(*index)];
		*index = (*index) + 1;
		while (line_read[(*index)] && line_read[(*index)] != quote_type)
		{
			*index = (*index) + 1;
			*token_len = (*token_len) + 1;
		}
	}
}

void	quoted_generate(char *line_read, int *index, char *content)
{
	char	quote_type;

	if (line_read[(*index)] == 39 || line_read[(*index)] == 34)
	{
		quote_type = line_read[(*index)];
		content[(*index)] = line_read[(*index)];
		*index = (*index) + 1;
		while (line_read[(*index)] && line_read[(*index)] != quote_type)
		{
			content[(*index)] = line_read[(*index)];
			*index = (*index) + 1;
		}
	}
}

int	count_redirect(char *line_read)
{
	int	i;

	i = 0;
	if ((line_read[i] == '>' && line_read[i + 1] && line_read[i + 1] == '>') || \
		(line_read[i] == '<' && line_read[i + 1] && line_read[i + 1] == '<') || \
		(line_read[i] == '&' && line_read[i + 1] && line_read[i + 1] == '&') || \
		(line_read[i] == '|' && line_read[i + 1] && line_read[i + 1] == '|'))
		return (2);
	else if (line_read[i] == '>' || line_read[i] == '<' || \
			line_read[i] == '&' || line_read[i] == '|')
		return (1);
	else
		return (0);
}

char	*redirect_gen(char *line_read)
{
	int		i;
	char	*token_content;

	i = 0;
	token_content = ft_strdup("");
	if ((line_read[i] == '>' && line_read[i + 1] && line_read[i + 1] == '>') || \
		(line_read[i] == '<' && line_read[i + 1] && line_read[i + 1] == '<') || \
		(line_read[i] == '&' && line_read[i + 1] && line_read[i + 1] == '&') || \
		(line_read[i] == '|' && line_read[i + 1] && line_read[i + 1] == '|'))
	{
		token_content = ft_append_char(token_content, line_read[i]);
		token_content = ft_append_char(token_content, line_read[i + 1]);
	}
	else if (line_read[i] == '>' || line_read[i] == '<' || \
			line_read[i] == '&' || line_read[i] == '|')
		token_content = ft_append_char(token_content, line_read[i]);
	return (token_content);
}
