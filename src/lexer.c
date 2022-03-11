/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:00:45 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/03/11 12:29:31 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_tudao	g_tudao;

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

int	token_len(char *line_read)
{
	int		i;
	int		redirect;
	char	quote_type;
	
	i = 0;
	redirect = count_redirect(&line_read[i]);
	if (!redirect)
	{
		while (line_read[i] && line_read[i] != ' ' && !redirect)
		{
			if (line_read[i] == 39 || line_read[i] == 34)
			{
				quote_type = line_read[i];
				i++;
				while (line_read[i] && line_read[i] != quote_type)
					i++;
			}
			if (line_read[i])
			{
				i++;
				redirect = count_redirect(&line_read[i]);
			}
		}
		return (i);
	}
	return (redirect);
}

void	tokenizer(char *line_read, char *content)
{
	int		i;
	int		redirect;
	char	quote_type;

	i = 0;
	redirect = count_redirect(&line_read[i]);
	if (!redirect)
	{
		while (line_read[i] && line_read[i] != ' ' && !redirect)
		{
			if (line_read[i] == 39 || line_read[i] == 34)
			{
				quote_type = line_read[i];
				content[i] = line_read[i];
				i++;
				while (line_read[i] && line_read[i] != quote_type)
				{
					content[i] = line_read[i];
					i++;
				}
			}
			if (line_read[i])
			{
				content[i] = line_read[i];
				i++;
				redirect = count_redirect(&line_read[i]);
			}
		}
		content[i] = '\0';
	}
	redirect_gen(&line_read[i], content);
}

void	lexer_line(char *line_read)
{
	t_list	*head;
	char	*content;
	int		len;
	int		i;

	head = NULL;
	i = 0;
	len = 0;
	while (line_read[i])
	{
		while (line_read[i] && line_read[i] == ' ')
			i++;
		len = token_len(&line_read[i]);
		if (len)
		{
			content = (char *)malloc(sizeof(char) * (len + 1));
			tokenizer(&line_read[i], content);
			ft_lstadd_back(&head, ft_lstnew(content));
			content = NULL;
		}
		i += len;
	}
	for (t_list	*pivot = head; pivot != NULL; pivot = pivot->next)
	{
		printf("{%s}", (char *)pivot->content);
	}
	printf("\n");
}

