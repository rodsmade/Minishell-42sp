/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:00:45 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/20 02:03:30 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_len(char *line_read)
{
	int		i;
	int		redirect;

	i = 0;
	redirect = count_redirect(&line_read[i]);
	if (!redirect)
	{
		while (line_read[i] && line_read[i] != ' ' && !redirect)
		{
			skip_quotes(line_read, &i);
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

	i = 0;
	redirect = count_redirect(&line_read[i]);
	if (!redirect)
	{
		while (line_read[i] && line_read[i] != ' ' && !redirect)
		{
			quoted_generate(line_read, &i, content);
			if (line_read[i])
			{
				content[i] = line_read[i];
				i++;
				redirect = count_redirect(&line_read[i]);
			}
		}
		content[i] = '\0';
	}
	else
		redirect_gen(&line_read[i], content);
}

void	create_token_list(char *line_read)
{
	char	*content;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (line_read[i])
	{
		while (line_read[i] && (line_read[i] == ' ' || line_read[i] == '\t'))
			i++;
		len = token_len(&line_read[i]);
		if (len)
		{
			content = (char *)malloc(sizeof(char) * (len + 1));
			tokenizer(&line_read[i], content);
			ft_lst_add_back(&g_tudao.token_list, ft_lst_new(content));
			content = NULL;
		}
		i += len;
	}
}
