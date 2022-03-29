/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:38:20 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/29 15:52:11 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_variable(char **expanded_content, char *variable_to_expand)
{
	int		size;
	char	*key;
	char	*env_var_value;
	char	*tmp;

	size = 0;
	while (variable_to_expand[size] && is_valid_key_char(\
	variable_to_expand[size]) && variable_to_expand[size] != '$')
		size++;
	key = ft_substr(variable_to_expand, 0, size);
	env_var_value = read_hashtable(g_tudao.hashtable[hash_string(key)], key);
	if (env_var_value != NULL)
	{
		if (*expanded_content == NULL)
			*expanded_content = ft_strdup(env_var_value);
		else if (*expanded_content != NULL)
		{
			tmp = *expanded_content;
			*expanded_content = ft_strjoin(tmp, env_var_value);
			ft_free_ptr((void *)&tmp);
		}
	}
	ft_free_ptr((void *)&key);
	return (size);
}

void	treat_db_quote(char *token_content, char **expanded_content, int *index)
{
	int	i;

	i = 0;
	while (token_content[++i] && token_content[i] != '\"')
	{
		if (token_content[i] == '$')
			i += expand_variable(expanded_content, &token_content[i + 1]);
		else
			*expanded_content = \
			ft_append_char(*expanded_content, token_content[i]);
	}
	*index += i;
}

void	expand_dollar_sign(t_list *token)
{
	char	*token_content;
	char	*exp_content;
	int		i;

	exp_content = NULL;
	token_content = (char *) token->content;
	i = -1;
	while (token_content[++i])
	{
		if (token_content[i] == '\'')
		{
			while (token_content[++i] && token_content[i] != '\'')
				exp_content = ft_append_char(exp_content, token_content[i]);
		}
		else if (token_content[i] == '\"')
			treat_db_quote(&token_content[i], &exp_content, &i);
		else if (token_content[i] == '$')
			i += expand_variable(&exp_content, &token_content[i + 1]);
		else
			exp_content = ft_append_char(exp_content, token_content[i]);
		if (!token_content[i])
			break ;
	}
	ft_free_ptr((void *)&token->content);
	token->content = exp_content;
}

void	expand_tokens(void)
{
	t_list	*pivot;

	pivot = g_tudao.token_list;
	while (pivot)
	{
		expand_dollar_sign(pivot);
		expand_wildcards();
		pivot = pivot->next;
	}
}
