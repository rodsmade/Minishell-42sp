/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:08:58 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/28 23:25:36 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*treat_quotes(char *token_content)
{
	int		i;
	char	quote_type;
	char	*new_content;

	i = 0;
	new_content = ft_strdup("");
	while (token_content[i])
	{
		if (token_content[i] == '\'' || token_content[i] == '\"')
		{
			quote_type = token_content[i];
			i++;
			while (token_content[i] && token_content[i] != quote_type)
			{
				new_content = ft_append_char(new_content, token_content[i]);
				i++;
			}
		}
		else
			new_content = ft_append_char(new_content, token_content[i]);
		if (token_content[i])
			i++;
	}
	return (new_content);
}

int	is_valid_key_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

void	expand_wildcards(void)
{
	return ;
}

void	remove_null_nodes_from_token_list(void)
{
	t_list	*pivot;
	t_list	*tmp;

	pivot = g_tudao.token_list;
	while (pivot)
	{
		if (pivot->content == NULL)
		{
			tmp = pivot->next;
			ft_lst_remove_node(&g_tudao.token_list, pivot);
			pivot = tmp;
		}
		else
			pivot = pivot->next;
	}
	return ;
}

void	append_single_quotes(char *token_str, char **expanded_cont, int *index)
{
	int	i;

	i = 0;
	while (token_str[++i] && token_str[i] != '\'')
		*expanded_cont = ft_append_char(*expanded_cont, token_str[i]);
	*index += i;
	return ;
}
