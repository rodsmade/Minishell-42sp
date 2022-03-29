/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:38:20 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/28 21:43:57 by adrianofaus      ###   ########.fr       */
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

/*
void	expand_dollar_sign(t_list *token)
{
	char	*token_content;
	char	*expanded_content;
	char	*env_var_value;
	char	*tmp;
	int		i;

	expanded_content = NULL;
	token_content = (char *) token->content;
	i = -1;
	while (token_content[++i] && token_content[i] != '$')
		expanded_content = ft_append_char(expanded_content, token_content[i]);
	env_var_value = read_hashtable(g_tudao.hashtable[hash_string(&token_content[i + 1])], &token_content[i + 1]);
	tmp = expanded_content;
	expanded_content = ft_strjoin(tmp, env_var_value);
	ft_free_ptr((void *)&tmp);
	ft_free_ptr((void *)&token->content);
	token->content = expanded_content;
	printf("expanded content: %s\n", expanded_content);
	printf("token content: %s\n", (char *)token->content);
	return ;
}*/

int		is_valid_key_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

int		expand_variable(char *variable_to_expand)
{
	int		len;
	char	*key;

	len = 0;
	while (variable_to_expand[len] && is_valid_key_char(variable_to_expand[len]) && variable_to_expand[len] != '$')
		len++;
	printf(">: variable_to_expand %s\n>: variable_size %d\n", variable_to_expand, len);
	key = ft_substr(variable_to_expand, 0, len);
	printf(">: key %s\n", key);
	return (1);
}

void	expand_dollar_sign(t_list *token)
{
	char	*token_content;
	char	*expanded_content;
	// char	*env_var_value;
	// char	*tmp;
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
					i += expand_variable(&token_content[i]);
				}
				else
					expanded_content = ft_append_char(expanded_content, token_content[i]);
			}
		}
		if (token_content[i] == '$')
		{
			i++;
			i += expand_variable(&token_content[i]);
		}
		else
			expanded_content = ft_append_char(expanded_content, token_content[i]);
	}
	/*
	env_var_value = read_hashtable(g_tudao.hashtable[hash_string(&token_content[i + 1])], &token_content[i + 1]);
	tmp = expanded_content;
	expanded_content = ft_strjoin(tmp, env_var_value);
	ft_free_ptr((void *)&tmp);
	ft_free_ptr((void *)&token->content);
	token->content = expanded_content;
	printf("expanded content: %s\n", expanded_content);
	printf("token content: %s\n", (char *)token->content);
	*/
}

/*
void	expand_dollar_sign(t_list *token)
{
	char	*token_content;
	char	*expanded_content;
	char	*env_var_value;
	char	*tmp;
	int		i;
	int		is_expansible;
	int		is_quoted;

	expanded_content = NULL;
	token_content = (char *) token->content;
	i = 0;
	is_expansible = true;
	is_quoted = false;
	while (token_content[i])
	{
		if (token_content[i] == '\"' && is_quoted == false)
		{
			is_quoted = true;
			i++;
		}
		else if (token_content[i] == '\"' && is_quoted == true)
		{
			is_quoted = false;
			i++;
		}
		if (token_content[i] && token_content[i] == '\'' && is_expansible == true && is_quoted == false)
		{
			is_expansible = false;
			i++;
		}
		else if (token_content[i] && token_content[i] == '\'' && is_expansible == false)
		{
			is_expansible = true;
			i++;
		}
		if (token_content[i] && token_content[i] == '$' && is_expansible == true)
		{
			expanded_content = ft_append_char(expanded_content, token_content[i]);
			i++;
		}
	}
	env_var_value = read_hashtable(g_tudao.hashtable[hash_string(&token_content[i + 1])], &token_content[i + 1]);
	tmp = expanded_content;
	expanded_content = ft_strjoin(tmp, env_var_value);
	ft_free_ptr((void *)&tmp);
	ft_free_ptr((void *)&token->content);
	token->content = expanded_content;
	printf("expanded content: %s\n", expanded_content);
	printf("token content: %s\n", (char *)token->content);
	return ;
}
*/

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
