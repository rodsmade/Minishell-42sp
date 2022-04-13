/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:38:20 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/13 19:47:56 by roaraujo         ###   ########.fr       */
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
	char	*temp;

	size = 0;
	if (variable_to_expand[0] == '?')
	{
		if (g_tudao.is_forked == false)
			env_var_value = ft_itoa(g_tudao.ext_routine.code);
		else if (g_tudao.is_forked == true)
			env_var_value = ft_itoa(WEXITSTATUS(g_tudao.ext_routine.code));
		temp = *expanded_content;
		*expanded_content = ft_strjoin(temp, env_var_value);
		ft_free_ptr((void *)&temp);
		ft_free_ptr((void *)&env_var_value);
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
	char	*token_str;
	char	*expanded_cont;
	int		i;

	expanded_cont = strdup("");
	token_str = (char *) token->content;
	i = -1;
	while (token_str[++i])
	{
		if (token_str[i] == '\'')
			append_single_quotes(&token_str[i], &expanded_cont, &i);
		else if (token_str[i] == '\"')
			treat_db_quote(&token_str[i], &expanded_cont, &i);
		else if (token_str[i] == '$' && (is_valid_key_char(token_str[i + 1])
				|| token_str[i + 1] == '?'))
			i += expand_variable(&expanded_cont, &token_str[i + 1]);
		else
			expanded_cont = ft_append_char(expanded_cont, token_str[i]);
		if (!token_str[i])
			break ;
	}
	ft_free_ptr((void *)&token->content);
	substitute_token_by_sublist(expanded_cont, &token);
}

void	expand_tokens(t_list *token_list)
{
	t_list	*pivot;

	print_token_lst(token_list);
	pivot = token_list;
	while (pivot)
	{
		if (is_expansible(pivot) == true)
		 {
			dprintf(2, ">>%s<< is expansible\n", (char *)pivot->content);
			expand_dollar_sign(pivot);
			expand_wildcards();
		 }
		 else
		 	dprintf(2, ">>%s<< is not expansible\n", (char *)pivot->content);
		pivot = pivot->next;
	}
	remove_null_nodes_from_token_list();
	print_token_lst(token_list);
}
