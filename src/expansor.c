/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:38:20 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/12 01:05:56 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exp_common_var(char **exp_content, char *var_to_expand, int size)
{
	char	*key;
	char	*env_var_value;
	char	*tmp;

	if (size)
	{
		key = ft_substr(var_to_expand, 0, size);
		env_var_value = \
		read_hashtable(g_tudao.hashtable[hash_string(key)], key);
		if (env_var_value != NULL)
		{
			if (*exp_content == NULL)
				*exp_content = ft_strdup(env_var_value);
			else if (*exp_content != NULL)
			{
				tmp = *exp_content;
				*exp_content = ft_strjoin(tmp, env_var_value);
				ft_free_ptr((void *)&tmp);
			}
		}
		ft_free_ptr((void *)&key);
	}
}

int	expand_variable(char **expanded_content, char *variable_to_expand)
{
	int		size;
	char	*env_var_value;

	size = 0;
	if (!ft_strncmp(variable_to_expand, "?", 2))
	{
		if (g_tudao.is_forked == false)
			env_var_value = ft_itoa(g_tudao.ext_routine.code);
		else if (g_tudao.is_forked == true)
			env_var_value = ft_itoa(WEXITSTATUS(g_tudao.ext_routine.code));
		*expanded_content = env_var_value;
		return (1);
	}
	else
	{
		while (variable_to_expand[size] && is_valid_key_char(\
		variable_to_expand[size]) && variable_to_expand[size] != '$')
			size++;
		exp_common_var(expanded_content, variable_to_expand, size);
		return (size);
	}
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
	remove_null_nodes_from_token_list();
}
