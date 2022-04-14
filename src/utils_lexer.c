/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:13:48 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/14 01:58:02 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(void)
{
	t_list	*tmp;

	while (g_tudao.token_list != NULL)
	{
		tmp = g_tudao.token_list->next;
		ft_free_ptr((void *)&g_tudao.token_list->content);
		ft_free_ptr((void *)&g_tudao.token_list);
		g_tudao.token_list = tmp;
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

void	redirect_gen(char *line_read, char *content)
{
	int	i;

	i = 0;
	if ((line_read[i] == '>' && line_read[i + 1] && line_read[i + 1] == '>') || \
		(line_read[i] == '<' && line_read[i + 1] && line_read[i + 1] == '<') || \
		(line_read[i] == '&' && line_read[i + 1] && line_read[i + 1] == '&') || \
		(line_read[i] == '|' && line_read[i + 1] && line_read[i + 1] == '|'))
	{
		content[i] = line_read[i];
		content[i + 1] = line_read[i + 1];
		content[i + 2] = '\0';
	}
	else if (line_read[i] == '>' || line_read[i] == '<' || \
			line_read[i] == '&' || line_read[i] == '|')
	{
		content[i] = line_read[i];
		content[i + 1] = '\0';
	}
}
