/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:38:20 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/28 19:58:15 by adrianofaus      ###   ########.fr       */
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
	env_var_value = read_hashtable(g_tudao.hashtable[\
		hash_string(&token_content[i + 1])], &token_content[i + 1]);
	tmp = expanded_content;
	expanded_content = ft_strjoin(tmp, env_var_value);
	ft_free_ptr((void *)&tmp);
	ft_free_ptr((void *)&token->content);
	token->content = expanded_content;
	printf("expanded content: %s\n", expanded_content);
	printf("token content: %s\n", (char *)token->content);
	return ;
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
