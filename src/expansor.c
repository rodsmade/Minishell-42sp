/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:38:20 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/29 20:53:45 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_append_char(char *str, char c)
{
	char	*new_str;
	int		str_size;
	int		i;

	i = -1;
	if (str)
		str_size = ft_strlen(str);
	else
		str_size = 0;
	new_str = malloc((str_size + 2) * sizeof(char));
	while (++i < str_size)
		new_str[i] = str[i];
	new_str[str_size] = c;
	new_str[str_size + 1] = '\0';
	ft_free_ptr((void *)&str);
	return (new_str);
}

int		is_valid_key_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

int		expand_variable(char **expanded_content, char *variable_to_expand)
{
	int		size;
	char	*key;
	char	*env_var_value;
	char	*tmp;

	size = 0;
	while (variable_to_expand[size] && is_valid_key_char(variable_to_expand[size]) && variable_to_expand[size] != '$')
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
	return (size - 1);
}

void	expand_dollar_sign(t_list *token)
{
	char	*token_content;
	char	*expanded_content;
	int		i;

	expanded_content = NULL;
	token_content = (char *) token->content;
	i = -1;
	while (token_content[++i])
	{
		if (token_content[i] == '\'')
		{
			while (token_content[++i] && token_content[i] != '\'')
				expanded_content = ft_append_char(expanded_content, token_content[i]);
		}
		else if (token_content[i] == '\"')
		{
			while (token_content[++i] && token_content[i] != '\"')
			{
				if (token_content[i] == '$')
				{
					i++;
					i += expand_variable(&expanded_content, &token_content[i]);
				}
				else
					expanded_content = ft_append_char(expanded_content, token_content[i]);
			}
		}
		else if (token_content[i] == '$')
		{
			i++;
			i += expand_variable(&expanded_content, &token_content[i]);
		}
		else
			expanded_content = ft_append_char(expanded_content, token_content[i]);
	}
	ft_free_ptr((void *)&token->content);
	token->content = expanded_content;
}

void	expand_wildcards(void)
{
	return ;
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
